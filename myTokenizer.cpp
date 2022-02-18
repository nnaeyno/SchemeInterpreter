#include "myTokenizer.hpp"
#include <string_view>
#include <iostream>

myTokenizer::myTokenizer(string& str){
    index = 0;
    curr = str;
}

string myTokenizer::peek(){
    return "";
}

string myTokenizer::next(){
    while(index < curr.length()){
        char ch = curr[index];
        switch (ch)
        {
            case ' ':
            case '\n':
            case '\t':
                index++;
                break;           
            case '(':
            case ')':
                return curr.substr(index++, 1);
            case '"':
                return tokenInsideString();
            case '9':
            case '8':
            case '7':
            case '6':
            case '5':
            case '4':
            case '3':
            case '2':
            case '1':
            case '-':
            case '0':
                return tokenizeNumber();
            default:
                return tokenizeOthers();
        }
    }
    return "";
}

bool myTokenizer::isNumber(char ch){
    if(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
        return true;
    return false;
}
string myTokenizer::tokenizeNumber(){
    size_t start = index;
    index++;
    while(index < curr.length()){
        char ch = curr[index];
        if(isNumber(ch)){
            index++;
        } else if(curr[index] == '.'){
            if(index - start == 1 && curr[index-1] == '-'){
                throw "Invalid syntax";
                break;
            } else {
                index++;
            }
        } else if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '(' || ch == ')'){
       //     cout << "here" << endl;
      //      index++;
            break;
        } else
        index++;
    }
    if(index - start == 1 && curr[index-1] == '-'){
        index--;
        return tokenizeOthers();
    } else {
   //     cout << curr.substr(start, index-start) << endl;
        return curr.substr(start, index-start);
    }
}
bool myTokenizer::isSeparator(char ch){
    if(ch == ' ' || ch == '(' || ch == ')' || ch == '\t' || ch == '\n' || ch == '"')
        return true;
    return false;
}
string myTokenizer::tokenizeOthers(){
    size_t start = index;
    while(index < curr.length()){
        
        char ch = curr[index];
        if(isSeparator(ch)){
            break;
        } else {
            index++;
        }
    }

    return curr.substr(start, index-start);
}
string myTokenizer::tokenInsideString(){
    size_t start = index;
    index++;
    while (index < curr.length()) {
        char ch = curr[index];
        switch (ch) {
            case '"':
                index++;
                return curr.substr(start, index - start);
            case '\\':
                index++;
                break;
            }
        index++;
    }
    throw "Invalid syntax";
    return curr.substr(start, index - start);
}  