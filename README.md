# Tag System Project

These C++ programs illustrate different programming styles with an emphasis on functional style. This stylistic exercise is inspired by the reading of the book entitled *Functional Programming in C++*[^1]. They compute the same sequences of words defined by tag systems.  

Tag systems are described in Wikipedia :

* [Tag system](https://en.wikipedia.org/wiki/Tag_system)
* [Système de tague](https://fr.wikipedia.org/wiki/Syst%C3%A8me_de_tague)

The generation of the next tag from the current one is done by the *genTag* function :
```
typedef auto (*ProdRuleFunc)(char) -> std::string;

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
```
The template argument "ProdRule" is a function implementing the set of production rules.
## Handwritten loop implementation
The file "genTagSeqLoop.cpp" implements the tag sequences generation by a straightforward handwritten loop :
```
template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
void genTagSeqLoop(const string & firstWord)
{
    string word = firstWord;
    int idx = 0;
    cout << "> " << idx++ << ": " << word << endl;
    try {
        while (word.length() > 0) {
            genTag<ProdRule>(DelNum, word);
            cout << "> " << idx++ << ": " << word << endl;
        }
    }
    catch (const HaltingSymbolException& haltEx) {
        cout << "Halting symbol exception : " << haltEx.buildMsg() << endl;
    }
    catch (const NotInAlphabetException& notInAlphaEx) {
        cout << "Not in alphabet exception : " << notInAlphaEx.buildMsg() << endl;
    }
}
```
The consecutive words are not stored in memory but written onto standard output stream.
## Recursive implementation
File "genTagSeqRec.cpp"

## Functional implementation

### By using the Accumulate algorithm
File "genTagSeqAccu.cpp"

### By using an infinite range
File "genTagSequence.cpp"

[^1]: Yvan Cukic. *Functional Programming in C++*. Manning Publications Co., 2019. 
