# Different ways to implement Tag Systems in C++

These C++ programs illustrate different programming styles with an emphasis on the **functional programming style**. This stylistic exercise is inspired by the reading of the book entitled *Functional Programming in C++*[^1]. They compute the same sequences of words defined by tag systems.  

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
void genTag(int delNb, std::string& word)
{
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
void genTagSeqLoop(const string& firstWord)
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
void genTagSequences(const string& word, int idx)
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

### By using left folds with the algorithm std::accumulate
Still as a stylistic exercise, the tag sequences generation is implemented in the file "genTagSeqAccu.cpp" with the accumulate algorithm :
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
The second argument of the *genNextTag* function is useless, so it is unnamed. The drawback of this implementation, besides its inefficiency, is that a vector with an appropriate size must be created before running the accumulate algorithm. The small benefit is that it is possible after the computation to iterate through this vector to process the generated words.

### By using infinite ranges
Tag systems are implemented in the file "genTagSeqRange.hpp" by using infinite (or endless) ranges as explained in the first part of this video entitled *Conquering C++20 Ranges*[^2] for computing the Fibonnaci sequence. This implementation uses the subrange class template which combines an iterator and a sentinel in a single view :
```
namespace myviews {
    template<ProdRuleFunc ProdRule, int DelNum, int MinLen, StringLiteral IniTag>
    auto tagSeq =
        std::ranges::subrange<TagSeqIter<ProdRule, DelNum, MinLen, IniTag>, std::unreachable_sentinel_t>{};
}
```
The *std::unreachable_sentinel_t* denotes the "upper bound" of an unbounded interval and thus gives the property of endlessness.  
The specific iterator *TagSeqIter* is defined as :
```
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
```
The statement *using difference_type = std::ptrdiff_t;* is used to satisfy the concepts "weakly_incrementable" and "input_or_output_iterator" (to be clarified later). The generation of tags is done by the prefix increment operator using *genNextTag* function.  
A template non-type (sic) parameter can not be of type *std::string* "because it is not structural" (as said by the compiler), so a type "StringLiteral" is defined to be used to set the initial value of the tag as explained on the blog page *[Passing String Literals as Template Parameters in C++20](https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/)* :
```
template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char(&str)[N]) {
        std::copy_n(str, N, value);
    }

    size_t length() const { return N-1; }

    char value[N];
};
```
Finally these ranges can be used as simply as :
```
constexpr StringLiteral firstTag{ "aaa" };
auto viewTagSeq = myviews::tagSeq<prod_rule2, 2, 2, firstTag>;

for (int idx = 0; const auto& tag : viewTagSeq) {
    if (tag.length() == 0) {
        break;
    }
    std::cout << "> " << idx++ << ": " << tag << std::endl;
}
```
Actually the elements composing the range are generated only when iterating on it and the computation is stopped when the length of the generated word is equal to 0 (assuming that there is a length method on the objects into the range).  
Todo : could be improved by using a specific sentinel in the range definition.

The great benefit of ranges is that several transformations can be chained using the pipe syntax that overloads the | operator as in this example :
```
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
```
Doing so, the data generation and the various data processing operations are separated which is not the case with a handwritten loop. But what is the price to pay for this ?

[^1]: Yvan Cukic. *Functional Programming in C++*. Manning Publications Co., 2019.
[^2]: [Conquering C++20 Ranges - Tristan Brindle - CppCon 2021](https://www.youtube.com/watch?v=3MBtLeyJKg0)
