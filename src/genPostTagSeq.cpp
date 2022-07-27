#include <algorithm>
#include <iostream>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

int main()
{
    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq = views::tagSeq<prod_rule3, 3, 1, firstTag>
            | std::views::transform([](auto tag) { return tag.length(); });

        for (int idx = 0; const auto & tag : viewTagSeq) {
            std::cout << "> " << idx++ << ": " << tag << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    return 0;
}