#ifndef myTokenizer_hpp
#define myTokenizer_hpp

#include <string>

using namespace std;
class myTokenizer {
public:
    myTokenizer(string& str);
    string peek();
    string next();
private:
    string tokenInsideString();
    string tokenizeNumber();
    string tokenizeOthers();
    string tokenizeSymbol();
    bool isSeparator(char ch);
    bool isNumber(char ch);
    string curr;
    size_t index;
};

#endif