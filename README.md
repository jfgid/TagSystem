# Tag System Project

These C++ programs showcase different programming styles with an emphasis on the functional style. This style exercise is inspired by the reading of the book entitled "Functional Programming in C++"[^1]. They compute sequences of words defined by tag systems.  

Tag systems are described in Wikipedia :

* [Tag system](https://en.wikipedia.org/wiki/Tag_system)
* [Système de tague](https://fr.wikipedia.org/wiki/Syst%C3%A8me_de_tague)

The generation of the next tag from the current one is done by the *genTag* function :
...
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
...

[^1]: Yvan Cukic. *Functional Programming in C++*. Manning Publications CO, 2019. 
