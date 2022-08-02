#include <iostream>
#include <string>

#include "genTagSeqRange.hpp"
#include "prodRules.hpp"

using namespace std;

bool isOneLetterComposed(const string& word, char letter)
{
    for (char c : word) {
        if (c != letter) {
            return false;
        }
    }
    return true;
}

int main()
{
    try {
        // Compute the Collatz sequence starting at 27.
        constexpr StringLiteral firstTag{ "aaaaaaaaaaaaaaaaaaaaaaaaaaa" };
        auto viewTagSeq = myviews::tagSeq<prod_rule2, 2, 2, firstTag>
            | views::filter([](const auto& tag) { return isOneLetterComposed(tag, 'a'); })
            | views::transform([](auto tag) { return tag.length(); });

        for (int idx = 0; const auto& tag : viewTagSeq) {
            if (tag == 1) {
                cout << "> " << idx++ << ": " << tag << endl;
                break;
            }
            cout << "> " << idx++ << ": " << tag << endl;
        }
    }
    catch (const std::exception& ex) {
        cout << "Exception : " << ex.what() << endl;
    }

    return 0;
}