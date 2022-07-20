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

template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
struct TagSeqIter {
    using value_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    // TagSeqIter(const std::string& iniTag) :
    //     m_curTag{ iniTag }
    // {}

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
    std::string m_curTag = "baa";
};

namespace rng = std::ranges;

namespace views {
    template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
    auto tagSeq =
        rng::subrange<TagSeqIter<ProdRule, DelNum, MinLen>, std::unreachable_sentinel_t>{};
}

int main() {
    std::string firstWord{ "baa" };
    try {
        auto viewTagSeq = views::tagSeq<prod_rule1, 2, 1>
            | std::views::take(10);

        int idx = 0;
        for (const auto tag : viewTagSeq) {
            std::cout << "> " << idx++ << ": " << tag << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        //tagSeq = vector<string>{ 30 };
        firstWord = "aaa";
    }
    catch (const std::exception & ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    std::cout << std::endl;
    try {
        //tagSeq = vector<string>{ 100 };
        firstWord = "baabaabaabaabaabaabaa";
    }
    catch (const std::exception & ex) {
        std::cout << "Exception : " << ex.what() << std::endl;
    }

    return 0;
}