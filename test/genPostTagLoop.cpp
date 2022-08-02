#include <algorithm>
#include <iostream>

#include "genTag.hpp"
#include "prodExcep.hpp"
#include "prodRules.hpp"

using namespace std;

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
void genTagSeqBoundedLoop(const string& firstWord, int idxMax)
{
    if (idxMax < 0) {
        return;
    }
    string word = firstWord;
    int idx = 0;
    while (word.length() > 0) {
        if (idx == idxMax) {
            cout << "> " << idx++ << ": " << word << endl;
            return;
        }
        genTag<ProdRule>(DelNum, word);
        idx++;
    }
}

int main(int argc, char* argv[])
{
    const int nbTag = (argc <=1 ) ? 10 : atoi(argv[1]);

    try {
        const auto idxMax = nbTag - 1;
        genTagSeqBoundedLoop<prod_rule3, 3, 1>("baabaabaabaabaabaabaa", idxMax);
    }
    catch (const std::exception& ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    return 0;
}