#include <iostream>
#include <string>

#include "prodRules.hpp"
#include "prodExcep.hpp"

using namespace std;

template <typename ProdRuleFunction>
void tagOpe(int delNb, ProdRuleFunction prod_rule, string & word) {
    if (word.length() >= delNb) {
        const char first = word[0];
        word.erase(0, delNb);
        word = word + prod_rule(first);
    }
    else {
        word = "";
    }
}

int main() {
    const int deletion_number = 2;
    string word = "baa";
    int idx = 0;
    cout << "> " << idx++ << ": " << word << endl;
    try {
        while (word.length() > 0) {
            tagOpe(deletion_number, prod_rule1, word);
            cout << "> " << idx++ << ": " << word << endl;
        }
    }
    catch (const HaltingSymbolException& haltEx) {
        cout << "Halting symbol exception : " << haltEx.buildMsg() << endl;
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }

    word = "aaa";
    idx = 0;
    cout << "> " << idx++ << ": " << word << endl;
    try {
        while (word.length() > 1) {
            tagOpe(deletion_number, prod_rule2, word);
            cout << "> " << idx++ << ": " << word << endl;
        }
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }

    word = "baabaabaabaabaabaabaa";
    idx = 0;
    cout << "> " << idx++ << ": " << word << "(len = " << word.length() << ")" << endl;
    try {
        while (word.length() > 1) {
            tagOpe(deletion_number, prod_rule3, word);
            idx++;
            if ((idx % 1000) == 0) {
                cout << "> " << idx++ << ": len = " << word.length() << endl;
            }
        }
        cout << "End word> " << idx++ << ": " << word << endl;
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }

    return 0;
}