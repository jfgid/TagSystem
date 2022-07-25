#pragma once
#include <exception>
#include <string>

class NotInAlphabetException : public std::exception {
public:
    NotInAlphabetException(char c) :
        m_not_in_alphabet(c)
    {}

    std::string buildMsg() const {
        const std::string not_in_alphabet(1, m_not_in_alphabet);
        return "Symbol not in alphabet is : " + not_in_alphabet;
    }

    const char* what() const noexcept override {
        return "Not In Alphabet Exception";
    }

private:
    char m_not_in_alphabet;
};

class HaltingSymbolException : public std::exception {
public:
    HaltingSymbolException(char halt) :
        m_halt_symbol(halt)
    {}

    std::string buildMsg() const {
        const std::string halt_symbol(1, m_halt_symbol);
        return "Halt symbol = " + halt_symbol;
    }

    const char* what() const noexcept override {
        return "Halting Symbol Exception";
    }

private:
    char m_halt_symbol;
};