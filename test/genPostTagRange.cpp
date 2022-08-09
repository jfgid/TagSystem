#include <algorithm>
#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    const int nbTag = (argc <=1 ) ? 10 : atoi(argv[1]);

    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq = myviews::tagSeq<prod_rule3, 3, 1, firstTag>;

        const auto idxMax = nbTag - 1;
        if (idxMax < 0) {
            return 1;
        }
        for (int idx = 0; const auto & tag : viewTagSeq) {
            if (idx == idxMax) {
                cout << "> " << idx++ << ": " << tag << endl;
                break;
            }
            idx++;
        }
    }
    catch (const std::exception& ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    return 0;
}