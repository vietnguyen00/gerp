/*
 * FSTreeTraversal.cpp
 * Comp 15 
 * Spring 2019
 *
 * Name: Viet Nguyen
 * Traverses the file system and lists all subdirectories and files within it
 */

#include <iostream>
#include <FSTree.h>
#include <DirNode.h>
using namespace std;

void traverse_Tree (string path, DirNode *node);

int main(int argc, char* argv[]) {
	if (argc > 2){
		cerr << "Invalid command" << endl;
		exit(1);
	}

	string directory = argv[1];
	FSTree fstree(argv[1]);

	DirNode *root = fstree.getRoot();
	traverse_Tree (directory, root);
} 

void traverse_Tree (string path, DirNode *node){
	if (node == NULL){
		return;
	}

	for (int i = 0; i < node->numSubDirs(); i++){
		string dir = path + "/" + node->getSubDir(i)->getName();
		cout << dir << endl;
		traverse_Tree (dir, node->getSubDir(i));
	}


	for (int i = 0; i < node->numFiles(); i++){
		cout << path << "/" << node->getFile(i) << endl;
	}

	cout << path << endl;
}