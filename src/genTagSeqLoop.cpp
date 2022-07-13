#include <iostream>
#include <string>

#include "genTag.hpp"
#include "prodRules.hpp"
#include "prodExcep.hpp"

using namespace std;

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
void genTagSeqLoop(const string & firstWord)
{
    string word = firstWord;
    int idx = 0;
    cout << "> " << idx++ << ": " << word << endl;
    try {
        while (word.length() > 0) {
            genTag<ProdRule>(DelNum, word);
            cout << "> " << idx++ << ": " << word << endl;
        }
    }
    catch (const HaltingSymbolException& haltEx) {
        cout << "Halting symbol exception : " << haltEx.buildMsg() << endl;
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }
}

int main() {
    try {
        genTagSeqLoop<prod_rule1, 2, 1>("baa");

        genTagSeqLoop<prod_rule2, 2, 2>("aaa");

        genTagSeqLoop<prod_rule3, 3, 1>("baabaabaabaabaabaabaa");
    }
    catch (const exception & ex) {
        cout << "Exception : " << ex.what() << endl;
    }
    return 0;
}