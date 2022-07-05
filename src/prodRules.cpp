#include "prodRules.hpp"
#include "prodExcep.hpp"

// Example: A simple 2-tag illustration
std::string prod_rule1(char c) {
    switch(c) {
        case 'a':
            return "ccbaH";
            break;
        case 'b':
            return "cca";
            break;
        case 'c':
            return "cc";
            break;
        case 'H': // Halting symbol
            throw HaltingSymbolException(c);
            break;
        default:  // Not in the alphabet
            throw NotInAlphabetException(c);
            break;
    }
}

// Example: Computation of Collatz sequences
std::string prod_rule2(char c) {
    switch (c) {
        case 'a':
            return "bc";
            break;
        case 'b':
            return "a";
            break;
        case 'c':
            return "aaa";
            break;
        default: // Not in the alphabet
            throw NotInAlphabetException(c);
            break;
    }
}

// 3-système de tague (Post)
std::string prod_rule3(char c) {
    switch (c) {
        case 'a':
            return "aa";
            break;
        case 'b':
            return "bbab";
            break;
        default: // Not in the alphabet
            throw NotInAlphabetException(c);
            break;
    }
}