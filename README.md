# Functional implementation of Tag Systems in C++

These C++ programs illustrate different programming styles with an emphasis on functional style. This stylistic exercise is inspired by the reading of the book entitled *Functional Programming in C++*[^1]. They compute the same sequences of words defined by tag systems.  

Tag systems are described in Wikipedia :

* [Tag system](https://en.wikipedia.org/wiki/Tag_system)
* [Système de tague](https://fr.wikipedia.org/wiki/Syst%C3%A8me_de_tague)

## How to build the project
This project has been done on Ubuntu 22.04 with the C++ compiler GCC v11.2 compatible with the C++20 version of the C++ language. It uses the CMake utility (v3.22.1). To build the binaries from the source code after cloning the Git repository, you can create a empty sub-directory "build" and run these commands :
```
$ cd build
$ cmake ..
-- The C compiler identification is GNU 11.2.0
-- The CXX compiler identification is GNU 11.2.0
...
-- Configuring done
-- Generating done
-- Build files have been written to: .../TagSystem/build
$ make
[  8%] Building CXX object src/CMakeFiles/genTagSequence.dir/prodRules.cpp.o
[ 16%] Building CXX object src/CMakeFiles/genTagSequence.dir/genTagSequence.cpp.o
[ 25%] Linking CXX executable genTagSequence
...
```
The executables are generated into the sub-directory : build/src/

## Word (tag) generation
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
The tag sequences generation is implemented in the file "genTagSeqRec.cpp" by using recursion :
```
template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
void genTagSequences(const string & word, int idx)
{
    if (word.length() < MinLen) {
        return;
    }
    string next_word = word;
    genTag<ProdRule>(DelNum, next_word);
    cout << "> " << ++idx << ": " << next_word << endl;
    genTagSequences<ProdRule, DelNum, MinLen>(next_word, idx);
}
```
There is a drawback with this implementation because, although this code seems tail-recursive, the used compiler (g++-11 v11.2.0) doesn't employ tail-call optimization (even with the -O2 option) and the computation of the last tag sequences (the 3-tag system defined by E. Post with the initial word "baabaabaabaabaabaabaa") fails with a segmentation fault.

## Functional implementation

### By using the algorithm std::accumulate
Still as a stylistic exercise, the tag sequences generation is implemented in the file "genTagSeqAccu.cpp" with the algorithm std::accumulate :
```
template<ProdRuleFunc ProdRule, int DelNum, int MinLen>
string genNextTag(const string& curTag, const string&)
{
    if (curTag.length() < MinLen) {
        cout << ">" << endl;
        return "";
    }
    string nextTag = curTag;
    genTag<ProdRule>(DelNum, nextTag);
    cout << "> " << nextTag << endl;
    return nextTag;
}
...
        tagSeq = vector<string>{ 100 };
        firstWord = "baabaabaabaabaabaabaa";
        cout << "first: " << firstWord << endl;

        auto res = accumulate(
            tagSeq.cbegin(),
            tagSeq.cend(),
            firstWord,
            genNextTag<prod_rule3, 3, 1>);

        cout << "last: " << res << endl;
...
```
The second argument of the *genNextTag* function is useless, so it is unnamed. The drawback of this implementation, besides its inefficiency, is that a vector with an appropriate size must be created before running the accumulate algorithm. The small benefit is that this vector could be scanned after the computation to process the generated words.

### By using an infinite range
File "genTagSequence.cpp"  
To implement an infinite range : [^2]

[^1]: Yvan Cukic. *Functional Programming in C++*. Manning Publications Co., 2019.
[^2]: [Conquering C++20 Ranges - Tristan Brindle - CppCon 2021](https://www.youtube.com/watch?v=3MBtLeyJKg0)
