/*
 * HashTable.h
 * COMP15
 * Spring 2019
 *
 * Interface of HashTable class
 *
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <FSTree.h>
#include <DirNode.h>
#include <Entry.h>

using namespace std;

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

class HashTable {
	public:
		HashTable();
		HashTable (string);
		~HashTable();
		
		// 2 query functions in insensitive and sensitive cases
		void query_insensitive (string, ostream&);
		void query_sensitive (string, ostream&);


	private:
		
		/****** Hash table constants and variables ******/

		static const int INITIAL_CAPACITY = 16061;

		// A pointer the dynamic array of Entry vectors
		vector<Entry> *hash_table;
		// A vector with directories
		vector<string> directories;
		// A vector with lines from files
		vector<string> lines;
		// An index to keep track of directories
		// Used in processing files to for Location structs 
		size_t directories_counter;
		// An index to keep track of lines
		// Used in processing files to for Location structs 
		size_t lines_counter;
		// Count the number of words inserted
		int word_count;
		// Current capacity of the array
		int capacity; 
		// The root directory to be indexed
		string root_directory;


		/****** Processing files & indexing functions ******/

		void explore_Directory ();
		// Helper function to explore files in a directory
		void explore_Directory (string, DirNode*);
		// Helper funtion to a process a file
		void process_File(string, size_t); 
		// Helper function to process a line in the given file
		void process_Line (string, int, size_t, size_t);
		// Add a new Entry object to the hash table
 		void add_New_Entry (string, Location);
 		// Helper function for adding new Entry
 		// Test if the Word added is already in the Entry
		void append_New_Word (Entry&, Word, Location);
		// Check for location repetition in the location vector of each Word
		bool check_Loc_Repetition (Location, Location);

		/****** Processing input functions ******/
		
		// Remove special characters in the user input
		void remove_Spec_Characters (string &s);
		// Helper boolean function to check special characters
		bool check_Spec_Character (char);
		// Turn all character to lower string
		// Used in indexing files and processing user input 
		string toLower (string);

		/****** Output data helper function ******/

		void print_Word (Word, ostream&);
		
		/****** Hash functions ******/

		void expand ();
		int get_index(string);
};

#endif