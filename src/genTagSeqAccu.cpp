#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "genTag.hpp"
#include "prodRules.hpp"
#include "prodExcep.hpp"

using namespace std;

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
string genNextTag(const string & curTag, const string & str)
{
    if (curTag.length() < MinLen) {
        cout << ">" << endl;
        return "";
    }
    string nextTag = curTag;
    genTag<ProdRule>(DelNum, nextTag);
    cout << "> " << nextTag << endl;
    return nextTag;
}

int main() {
    vector<string> tagSeq{ 10 };

    string firstWord{ "baa" };
    try {
        cout << "first: " << firstWord << endl;

        auto res = accumulate(
            tagSeq.cbegin(),
            tagSeq.cend(),
            firstWord,
            genNextTag<prod_rule1, 2, 1>);

        cout << "last: " << res << endl;
    }
    catch (const exception& ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    cout << endl;
    try {
        tagSeq = vector<string>{ 30 };
        firstWord = "aaa";
        cout << "first: " << firstWord << endl;

        auto res = accumulate(
            tagSeq.cbegin(),
            tagSeq.cend(),
            firstWord,
            genNextTag<prod_rule2, 2, 2>);

        cout << "last: " << res << endl;
    }
    catch (const exception & ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    cout << endl;
    try {
        tagSeq = vector<string>{ 100 };
        firstWord = "baabaabaabaabaabaabaa";
        cout << "first: " << firstWord << endl;

        auto res = accumulate(
            tagSeq.cbegin(),
            tagSeq.cend(),
            firstWord,
            genNextTag<prod_rule3, 3, 1>);

        cout << "last: " << res << endl;
    }
    catch (const exception & ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    return 0;
}