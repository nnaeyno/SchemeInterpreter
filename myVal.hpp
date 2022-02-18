#ifndef myVal_hpp
#define myVal_hpp

#include <vector>
#include <string>
#include <functional>
using namespace std;
//keyword: apply, eval, car, cdr, cons, map, append
//operator: +, -, *, /, and, or
//SYMBOL: 'hello
//LIST: '(1 2 3 4)
class myVal{

public:   
    enum type {
        NONE,
//      LP, 
//      RP,
//      INTEGER, 
        LIST, 
        SYMBOL, 
        STRING, 
        KEYWORD, 
        OPERATOR, 
//      TRUE, 
//      FALSE,
        BOOLEAN,
        NUMBER, 
        DEFINE, 
        LAMBDA, 
        IF, 
        ELSE

};
    virtual type getType();

};
class myList : public myVal {
public:
    myList();
    virtual type getType() override;
    void add(myVal* elem);
    myVal* get(int i);
    void push(myVal* elem);
    int size();
private:
    vector<myVal* > elems;
};
class mySymbol : public myVal {
public:
    mySymbol(string str);
    mySymbol(myList* str);
    virtual type getType() override;
    void add(myVal* elem);
    myVal* get(int i);
    string get();
    myList* getList();
    void push(myVal* elem);
    int size();
    
private:
    string stored;
    myList* lst;
};
class myString : public myVal {
public:
    myString(string str);
    virtual type getType() override;
    string get();
    
private:
    string elem;
};

class myKeyword : public myVal {
public:
    myKeyword(string str);
    virtual type getType() override;
    string get()const;    
    
private:
    string elem;   
};
class myNumber : public myVal{
public:
    myNumber(double a);
    virtual type getType() override;
    double get();
    
private:
    double num;    
};
class myOperator : public myVal{
public:
    myOperator(string a);
    virtual type getType() override;
    string get();
    
private:
    string op;    
};
class myBool : public myVal{
public:
    myBool(bool a);
    virtual type getType() override;
    bool get();
    
private:
    bool elem;      
};
typedef function<myVal* (int, myVal**)> fn;
class myFn : public myVal {
public:
    myFn(fn func);
    virtual type getType() override;
    fn get();
private:
    fn function;
};
//define, lambda, if, else ??
#endif