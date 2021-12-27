#include <iostream>
#include <string>

#include "prodRules.hpp"
#include "prodExcep.hpp"

using namespace std;

void tagOpe(int delNb, string & word) {
    if (word.length() > delNb) {
        const char first = word[0];
        word.erase(0, delNb);
        word = word + prodRule1(first);
    }
    else {
        word = "";
    }
}

int main() {
    const int deletion_number = 2;
    string word = "baaaaaa";
    int idx = 0;
    cout << "> " << idx++ << ": " << word << endl;
    try {
        while (word.length() > 0) {
            tagOpe(deletion_number, word);
            cout << "> " << idx++ << ": " << word << endl;
        }
    }
    catch (const HaltingSymbolException& haltEx) {
        cout << "Halting symbol exception : " << haltEx.buildMsg() << endl;
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }
    return 0;
}