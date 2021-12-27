#include "prodRules.hpp"
#include "prodExcep.hpp"

std::string prodRule1(char c) {
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