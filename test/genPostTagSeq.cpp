#include <algorithm>
#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    const int ntag = (argc <=1 ) ? 10 : atoi(argv[1]);

    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq = myviews::tagSeq<prod_rule3, 3, 1, firstTag>
            | views::take(ntag);

        for (int idx = 0; const auto & tag : viewTagSeq) {
            cout << "> " << idx++ << ": " << tag << endl;
        }
    }
    catch (const std::exception& ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    return 0;
}