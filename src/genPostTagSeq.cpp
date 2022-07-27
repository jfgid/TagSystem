#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

int main()
{
    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq3 = views::tagSeq<prod_rule3, 3, 1, firstTag>;

        std::cout << "> 0: " << firstTag.value << std::endl;
        for (int idx; const auto & tag : viewTagSeq3) {
            if (tag.length() == 0) {
                break;
            }
            std::cout << "> " << idx++ << ": " << tag << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    return 0;
}