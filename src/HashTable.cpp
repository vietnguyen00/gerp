/*
 * HashTable.cpp
 * COMP15
 * Spring 2019
 * Viet Nguyen
 *
 * Implemetation of HashTable class
 *
 */

#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <functional>

using namespace std;

// Default constructor
HashTable::HashTable() {
	capacity = INITIAL_CAPACITY;
	word_count = 0;
	directories_counter = 0;
	lines_counter = 0;
	hash_table = new vector<Entry>[capacity];
}

// Parametrized constructor with a directory passed as parameter
HashTable::HashTable(string s) {
	capacity = INITIAL_CAPACITY;
	word_count = 0;
	directories_counter = 0;
	lines_counter = 0;
	hash_table = new vector<Entry>[capacity];
	root_directory = s;
    explore_Directory();
}

// Destructor
HashTable::~HashTable(){
	delete [] hash_table;
	hash_table = NULL;
}

/*
 * Input  : A string and an ostream object
 * Output : A None
 * Does   : Query a word in the case character capitalization matters
 *          Get the index in the hash table for the string, and print 
 *           all the locations to out
 */
void HashTable::query_sensitive (string s, ostream& out){
    remove_Spec_Characters (s);
    string key = toLower(s);
    int index = get_index(key);

    // Check if the size of the vector in given index in the hash table is 0
    if ((int)hash_table[index].size() == 0)
        out << "query not found" << endl;

    else {
    	// Search through the vector in the index to see if the key string appear
        for (size_t i = 0; i < hash_table[index].size(); i++){
            if (hash_table[index][i].key == key){
                for (size_t j = 0; j < hash_table[index][i].words.size(); j++){
                    if (hash_table[index][i].words[j].original == s){
                    	// print the specific word associated with the original
                    	//  string then return
                        print_Word(hash_table[index][i].words[j], out);
                        return;
                    }
                }
            }
        }

        // In case no word is printed out
        out << "query not found" << endl;
    }
}

/*
 * Input  : A string and an ostream object
 * Output : A None
 * Does   : Query a word in the case character capitalization doesn't matter
 *          Get the index in the hash table for the string, and print all
 *           the locations to out
 */

void HashTable::query_insensitive (string s, ostream& out){
    remove_Spec_Characters (s);
    string key = toLower(s);
    int index = get_index(key);

    // Check if the size of the vector in given index in the hash table is 0
    if ((int)hash_table[index].size() == 0)
        out << "query not found" << endl;

    else {
    	// Search through the vector in the index to see if the key string appear
        for (size_t i = 0; i < hash_table[index].size(); i++){
            if (hash_table[index][i].key == key){
            	// If yes, print all words assciated with the string 
                //  then return
                for (size_t j = 0; j < hash_table[index][i].words.size(); j++)
                    print_Word(hash_table[index][i].words[j], out);
            }
            return;
        }

        // In case no word is printed out
        out << "query not found" << endl;
    }
}

/*
 * Input  : None
 * Output : None
 * Does   : Set directory for FSTree and call the recursive helper function
 */

void HashTable::explore_Directory() {
	FSTree fstree(root_directory);
	DirNode *root = fstree.getRoot();
	explore_Directory(root_directory, root);
}

/*
 * Input  : A string for directory and a pointer to DirNode
 * Output : None
 * Does   : Explore a directory. Call the function recursively on each folder
 *           and call the function to process file for each file in directory
 */

void HashTable::explore_Directory(string path, DirNode *node){
	if (node == NULL)
		return;

	// Explore each subdirectory recursively
	for (int i = 0; i < node->numSubDirs(); i++){
		string dir = path + "/" + node->getSubDir(i)->getName();
		explore_Directory (dir, node->getSubDir(i));
	}

	// Process each file
	// Each time a file is processed, add its name to directory
	for (int i = 0; i < node->numFiles(); i++){
		string dir = path + "/" + node->getFile(i);
		directories.push_back(dir);
		process_File (dir, directories_counter);
		directories_counter++;
	}
}

/*
 * Input  : A string for directory, a size_t to store index in directory vector
 * Output : None
 * Does   : Process each file, and call the helper process line function on each line
 */

void HashTable::process_File(string directory, size_t index_dirs){
	ifstream infile;
    infile.open(directory);

    string line;
    // This is to track which line of FILE 
    int counter = 1;
    while (getline(infile,line)){
    	lines.push_back(line);
    	process_Line (line, counter, index_dirs, lines_counter);
    	// This is to track which line of the vector of lines
    	lines_counter++;
    	counter++;
    }

    infile.close();
}

/*
 * Input  : A string, a counter to store line, a size_t to store directory,
 *           a size_t to store line (in lines vector)
 * Output : None
 * Does   : Use stringstream to process each string in the line. 
 *          Call helper function to process each string in Entry structs
 */

void HashTable::process_Line (string line, int counter, size_t index_dirs, size_t index_lines){
	stringstream ss(line);
	string word;
	Location loc(index_dirs, index_lines, counter);
	while (ss >> word){
        add_New_Entry (word, loc);
	}
}

/*
 * Input  : A string and a Location object
 * Output : None
 * Does   : Remove all special chacter then hash the string
 *          If the vector at given index is empty, push back the Entry struct
 *          If not, search if the Entry struct that share the key string exist,
 *           then call the helper append Word function; otherwise push back the 
 *           Entry struct
 */

void HashTable::add_New_Entry (string s, Location loc){
    remove_Spec_Characters (s);
	string key = toLower(s);
	int index = get_index(key);

	// this is the case when the vector at given index is empty
	if ((int)hash_table[index].size() == 0){
		Entry e(key, s, loc);
		hash_table[index].push_back(e);
		word_count++;
	}
	
	// this is the case when the vector at given index is non empty
	else {
		for (size_t i = 0; i < hash_table[index].size(); i++){
			// this looks for an Entry in the vector at given index that 
			//   has the same key string
			if (hash_table[index][i].key == key){
				Word word(s, loc);
				append_New_Word(hash_table[index][i], word, loc);
				return;
			}
		}

		// if no Entry in the vector has the same key string, create a new Entry
		//  object and add to the end of that vector
		Entry e(key, s, loc);
		hash_table[index].push_back(e);
		word_count++;
	}
	expand();
}

/*
 * Input  : 2 Location objects
 * Output : A boolean
 * Does   : Add a new Word object to an Entry passed by refernece
 *           If the word we want to insert has the original string in the Entry,
 *            we just need to insert  
 */

void HashTable::append_New_Word (Entry &e, Word w, Location l){
	for (size_t i = 0; i < e.words.size(); i++){
	    if (e.words[i].original == w.original){
			if (!check_Loc_Repetition (e.words[i].locations.back(), l)){
				e.words[i].locations.push_back(l);
				return; 
			}
			return; 
		}
	} 
	
	e.words.push_back(w);
}

/*
 * Input  : 2 Location objects
 * Output : A boolean
 * Does   : Helper function to print all locations that a word appears
 */

bool HashTable::check_Loc_Repetition (Location l1, Location l2){
	return (l1.lines == l2.lines && l1.path == l2.path && l1.line_in_file == l2.line_in_file);
}

/*
 * Input  : A Word object, an ostream object
 * Output : None
 * Does   : Helper function to print all locations that a word appears
 */

void HashTable::print_Word (Word w, ostream& out){
	for (size_t i = 0; i < w.locations.size(); i++){
		out << directories[w.locations[i].path] << ":" << w.locations[i].line_in_file << ": ";
		out << lines[w.locations[i].lines] << endl;
	}
}

/*
 * Input  : None
 * Output : None
 * Does   : Increase the capacity of HashTable and re-index all Entries 
 *           according to the new capacity
 */

void HashTable::expand() {
	float load_factor = (float) word_count/capacity; 
	
	// Only expand if load factor exceed 0.7
	if (load_factor < 0.7)
		return; 
	
	else {
		// Increase capacity by 2.5 times
		int old_capacity = capacity;
		capacity *= 5/2;

		// Allocate memory for a new HashTable with new capacity
		vector<Entry> *new_table = new vector<Entry>[capacity];
		// Traverse the vectors of Entry in each index of the old hash table
		for (int i = 0; i < old_capacity; i++){
			// If the size of vector of Entry is 0, continue
			if ((int)hash_table[i].size() == 0)
				continue;
			else {
				// If the size of vector is not zero, take each Entry, re-index
				//  it based on the key string of the Entry, and add it to the 
				//  respective vectors
				for (size_t j = 0; j < hash_table[i].size(); j++){
					int index = get_index (hash_table[i][j].key);
					new_table[index].push_back(hash_table[i][j]);
				}
			}
		}

		// Delete the old hash_table
		delete [] hash_table;
		hash_table = new_table;
	}
}

/*
 * Input  : A string
 * Output : None
 * Does   : Pass a string by reference and remove all special characters from it
 */

void HashTable::remove_Spec_Characters (string &s){
    string::iterator i = s.begin();
    while (i < s.end()){
        if ((int)s.size() == 0)
            break;
        else if (!check_Spec_Character(*i)){
            s.erase(i);
        }
        else 
            break;
    }
    
    i = s.end() - 1;
    while (i != s.begin()){
        if ((int)s.size() == 0)
            break;
        else if (!check_Spec_Character(*i)){
            s.erase(i);
            i--;
        }
        else 
            break;
    } 
}

/*
 * Input  : A character
 * Output : A boolean value
 * Does   : Check if a specific character is a special character
 */

bool HashTable::check_Spec_Character (char c){
	if ( c > 47 && c < 58)
        return true;
    if ( c > 64 && c < 91)
        return true;
    if ( c > 96 && c < 123)
        return true;
    return false; 
}

/*
 * Input  : A string
 * Output : A string
 * Does   : Turn all characters a string into lower case
 */

string HashTable::toLower(string s){
	string result;
	for (size_t i = 0; i < s.length(); i++){
		if (s[i] > 64 && s[i] < 91)
			result += s[i] + 32;
		else
			result += s[i];
	}
	return result;
}

/*
 * Input  : A string
 * Output : An integer
 * Does   : Hash a string then compress it modulo capacity
 */

int HashTable::get_index (string s) {
	return hash<string>{}(s) % capacity;
}
