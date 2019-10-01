/*
 * COMP 15 
 * Spring 2019
 * Project 2: Gerp
 * 
 * Driver for Project 2
 */

#include <iostream>
#include <string>
#include <fstream>
#include <HashTable.h>

using namespace std;

static const string INSENSITIVE_SEARCH_1 = "@i";
static const string INSENSITIVE_SEARCH_2 = "@insensitive";
static const string QUIT_1 = "@q";
static const string QUIT_2 = "@quit";
static const string PASSFILE = "@f";

int main (int argc, char* argv[]) {
	if (argc != 3){
		cout << "usage: ./gerp input_directory output_directory" << endl;
		exit(1);
	}

	ofstream outfile(argv[2]);

	HashTable ht(argv[1]);
	string command;

	do {
		cout << "Query? ";
		cin >> command;
		if (cin.eof()){
			cout << "Goodbye! Thank you and have a nice day.";
		} else if (command == INSENSITIVE_SEARCH_1 || command == INSENSITIVE_SEARCH_2){
			cin >> command;
			ht.query_insensitive(command, outfile);
		} else if (command == QUIT_1 || command == QUIT_2){
			cout << endl;
			cout << "Goodbye! Thank you and have a nice day.";
		} else if (command == PASSFILE){
			string file_input;
			cin >> file_input;
            ofstream outfile2(file_input.c_str());
            if (!outfile2.is_open()){
                cerr << "Error: could not open file " << file_input;
           		exit(1);
            }
            outfile.swap(outfile2);
		} else 
			ht.query_sensitive(command, outfile);

		cout << endl;
	
	} while (!cin.eof() && command != QUIT_1 && command != QUIT_2);
}