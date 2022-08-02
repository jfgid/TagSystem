#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

int main()
{
    try {
        constexpr StringLiteral firstTag{ "aaa" };
        auto viewTagSeq = views::tagSeq<prod_rule2, 2, 2, firstTag>;

        for (int idx = 0; const auto& tag : viewTagSeq) {
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