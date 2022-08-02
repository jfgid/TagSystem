#pragma once
#include <string>
#include <ranges>

#include "genTag.hpp"

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

    size_t length() const { return N-1; }

    char value[N];
};

template<ProdRuleFunc ProdRule, int DelNum, int MinLen, StringLiteral IniTag>
struct TagSeqIter {
    using value_type = std::string;
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

namespace myviews {
    template<ProdRuleFunc ProdRule, int DelNum, int MinLen, StringLiteral IniTag>
    auto tagSeq =
        std::ranges::subrange<TagSeqIter<ProdRule, DelNum, MinLen, IniTag>, std::unreachable_sentinel_t>{};
}