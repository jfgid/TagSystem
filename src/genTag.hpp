#pragma once
#include <string>

typedef std::string(*ProdRuleFunc)(char);

template <ProdRuleFunc ProdRule>
void genTag(int delNb, std::string & word) {
    if (word.length() >= delNb) {
        const char first = word[0];
        word.erase(0, delNb);
        word = word + ProdRule(first);
    }
    else {
        word = "";
    }
}