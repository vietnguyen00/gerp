/*
 * testGerp.cpp
 * COMP15
 * Spring 2019
 * Viet Nguyen
 *
 * Unit tests for 2 query functions of HashTable.cpp
 *
 */
#include <string>
#include <fstream>
#include <HashTable.h>

using namespace std;

int main() {
	string input_test_queries = "/h/vnguye04/comp15/proj2/unittests";

	/*
	 * Here is my input file: 
	 * 
	 * Dynamic
	 * DynAmiC
	 * dynamic 
	 * dynamic$$4 // No leading/trailing special chatacters but in the middle
	 * dynamic dynamic // 2 exactly same words on the same line
	 * DynamiC dynamic // 2 similar words on the same line 
	 * dynamic array Dynamic. // One period after Dynamic
	 * dynamic!!! Array array. // Special chatacter after a word in input text
	 *                        // 2 similar words on the same line
	 * 
	 */

	HashTable ht(input_test_queries);

	// Note: I will comment each test case out before move on with the next test
	//        for clearer output view

	///////////////////////////////////////////////////////////////////////////
	// This tests the normal insensitve query case
	/* 
	 * Expected output: 
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:1: Dynamic
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:7: dynamic array Dynamic.
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:2: DynAmiC
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:3: dynamic
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:5: dynamic dynamic
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:6: DynamiC dynamic
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:7: dynamic array Dynamic.
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:8: dynamic!!! Array array.
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:6: DynamiC dynamic
     ///////////////////
     * Explanation for line 6 and 7: For the sake of querying "Dynamic" in case
     *  sensitive case, take line 7 for example, "DynamiC" and "dynamic" are 
     *  considered 2 different instances, so the line is printed twice. 
     *  
     *  Line 5 is only printed once because if both words on that line are the 
     *   same, so they are treated as one instance. 
	 */
	
	ht.query_insensitive("Dynamic", cout);
	cout << endl;

	///////////////////////////////////////////////////////////////////////////
	// This tests the normal sensitve query case
	/* 
	 * Expected output: 
	 * /h/vnguye04/comp15/proj2/unittests/input1.txt:1: Dynamic
	 * /h/vnguye04/comp15/proj2/unittests/input1.txt:7: dynamic array Dynamic.
	 */
	ht.query_sensitive("Dynamic", cout);
	cout << endl;
	
	///////////////////////////////////////////////////////////////////////////
	// This tests the sensitve query case but with leadinging and trailing
	//  special characters
	/* 
	 * Expected output: 
	 * /h/vnguye04/comp15/proj2/unittests/input1.txt:1: Dynamic
	 * /h/vnguye04/comp15/proj2/unittests/input1.txt:7: dynamic array Dynamic.
	 */
	ht.query_sensitive("$$Dynamic!!!", cout);
	cout << endl;

	///////////////////////////////////////////////////////////////////////////
	// This tests the case when there are 2 similar words (different capitalization)
	//  on the same line
	/* 
	 * Expected output: 
	 * /h/vnguye04/comp15/proj2/unittests/input1.txt:7: dynamic array Dynamic.
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:8: dynamic!!! Array array.
     * /h/vnguye04/comp15/proj2/unittests/input1.txt:8: dynamic!!! Array array.
     //////
     * Explanation for line 7 being printed twice: Similar to the first case
     */
	ht.query_insensitive("array!!", cout);
	cout << endl;
}
