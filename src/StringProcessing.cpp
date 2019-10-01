/*
 * StringProcessing.cpp
 * Comp 15 
 * Spring 2019
 *
 * Name: Viet Nguyen
 * Implementation of Trie class
 *
 */
#include <iostream>
#include <string>

using namespace std;

bool check_valid (char c);
void string_processor (string &s);

int main()
{
    string test;
    while (!cin.eof()){
        cin >> test;
        string_processor (test);
        cout << test << endl;
    }
}

bool check_valid (char c){
    if ( c > 47 && c < 58)
        return true;
    if ( c > 64 && c < 91)
        return true;
    if ( c > 96 && c < 123)
        return true;
    return false; 
}

void string_processor (string &s) {
    string::iterator i = s.begin();
    while (i < s.end()){
        if ((int)s.size() == 0)
            break;
        else if (!check_valid(*i)){
            s.erase(i);
        }
        else 
            break;
    }
    
    i = s.end() - 1;
    while (i != s.begin()){
        if ((int)s.size() == 0)
            break;
        else if (!check_valid(*i)){
            s.erase(i);
            i--;
        }
        else 
            break;
    }
}
