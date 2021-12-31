#include <iostream>
#include <string>

#include "prodRules.hpp"
#include "prodExcep.hpp"

using namespace std;

typedef string(*ProdRuleFunc)(char);

template <ProdRuleFunc ProdRule>
void tagOpe(int delNb, string & word) {
    if (word.length() >= delNb) {
        const char first = word[0];
        word.erase(0, delNb);
        word = word + ProdRule(first);
    }
    else {
        word = "";
    }
}

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
void genTagSequences(const string & word, int idx) {
    if (word.length() < MinLen) {
        return;
    }
    string next_word = word;
    tagOpe<ProdRule>(DelNum, next_word);
    cout << "> " << ++idx << ": " << next_word << endl;
    genTagSequences<ProdRule, DelNum, MinLen>(next_word, idx);
}

int main() {
    try {
        cout << "> 0: baa" << endl;
        genTagSequences<prod_rule1, 2, 1>("baa", 0);
    }
    catch (const exception & ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    try {
        cout << "> 0: aaa" << endl;
        genTagSequences<prod_rule2, 2, 2>("aaa", 0);
    }
    catch (const exception & ex) {
        cout << "Exception : " << ex.what() << endl;
    }
    return 0;
}