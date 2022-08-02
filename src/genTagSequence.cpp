#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

void displayView(const auto& view)
{
    for (int idx = 0; const auto& tag : view) {
        if (tag.length() == 0) {
            break;
        }
        std::cout << "> " << idx++ << ": " << tag << std::endl;;
    }
}

int main()
{
    try {
        constexpr StringLiteral firstTag{ "baa" };
        auto viewTagSeq1 = myviews::tagSeq<prod_rule1, 2, 1, firstTag>;

        displayView(viewTagSeq1);
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        constexpr StringLiteral firstTag{ "aaa" };
        auto viewTagSeq2 = myviews::tagSeq<prod_rule2, 2, 2, firstTag>;

        displayView(viewTagSeq2);
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq3 = myviews::tagSeq<prod_rule3, 3, 1, firstTag>;

        displayView(viewTagSeq3);
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    return 0;
}