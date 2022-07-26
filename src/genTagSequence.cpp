#include <iostream>
#include <string>
#include <ranges>

#include "genTag.hpp"
#include "prodRules.hpp"
#include "prodExcep.hpp"

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
std::string genNextTag(const std::string& tag)
{
    if (tag.length() < MinLen) {
        return "";
    }
    std::string nextTag = tag;
    genTag<ProdRule>(DelNum, nextTag);
    return nextTag;
}

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char(&str)[N]) {
        std::copy_n(str, N, value);
    }

    char value[N];
};

template<ProdRuleFunc ProdRule, int DelNum, int MinLen, StringLiteral IniTag>
struct TagSeqIter {
    using difference_type = std::ptrdiff_t;

    const std::string& operator*() const { return m_curTag; }

    // Define prefix increment operator.
    TagSeqIter& operator++() {
        m_curTag = genNextTag<ProdRule, DelNum, MinLen>(m_curTag);
        return *this;
    }

    // Define postfix increment operator.
    TagSeqIter operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(const TagSeqIter&) const = default;

private:
    std::string m_curTag = std::string(IniTag.value);
};

namespace views {
    template<ProdRuleFunc ProdRule, int DelNum, int MinLen, StringLiteral IniTag>
    auto tagSeq =
        std::ranges::subrange<TagSeqIter<ProdRule, DelNum, MinLen, IniTag>, std::unreachable_sentinel_t>{};
}

void displayView(const auto& view, const std::string& firstTag)
{
    int idx = 0;
    std::cout << "> " << idx++ << ": " << firstTag << std::endl;
    for (const auto& tag : view) {
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
        auto viewTagSeq1 = views::tagSeq<prod_rule1, 2, 1, firstTag>;

        displayView(viewTagSeq1, std::string(firstTag.value));
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        constexpr StringLiteral firstTag{ "aaa" };
        auto viewTagSeq2 = views::tagSeq<prod_rule2, 2, 2, firstTag>;

        displayView(viewTagSeq2, std::string(firstTag.value));
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        constexpr StringLiteral firstTag{ "baabaabaabaabaabaabaa" };
        auto viewTagSeq3 = views::tagSeq<prod_rule3, 3, 1, firstTag>;

        displayView(viewTagSeq3, std::string(firstTag.value));
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    return 0;
}