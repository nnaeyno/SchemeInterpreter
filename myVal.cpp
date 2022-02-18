#include <string>
#include "myVal.hpp"
using namespace std;

myVal::type myVal::getType(){
    return NONE;
}
/*
        LIST, 
        SYMBOL, 
        STRING, 
        KEYWORD, 
        OPERATOR, 
//      TRUE, 
//      FALSE,
        BOOLEAN,
        NUMBER, 
*/
myList::myList(){

}
myVal* myList::get(int i){
    return elems[i];
}
myVal::type myList::getType(){
    return LIST;
}
void myList::add(myVal* elem){
    elems.push_back(elem);
}
void myList::push(myVal* elem){
    elems.insert(elems.begin(), elem);
}
int myList::size(){
    return elems.size();
}
mySymbol::mySymbol(string str){
    stored = str;
}
mySymbol::mySymbol(myList* str){
    lst = str;
    stored = "";
}
myVal* mySymbol::get(int i){
    return lst->get(i);
}
string mySymbol::get(){
    return stored;
}
void mySymbol::add(myVal* elem){
    lst->add(elem);
}
myVal::type mySymbol::getType(){
    return SYMBOL;
}
void mySymbol::push(myVal* elem){
    lst->push(elem);
}
int mySymbol::size(){
    return lst->size();
}
myList* mySymbol::getList(){
    return lst;
}
myBool::myBool(bool a){
    elem = a;
}
bool myBool::get(){
    return elem;
}
myVal::type myBool::getType(){
    return BOOLEAN;
}
myKeyword::myKeyword(string str){
    elem = str;
}
string myKeyword::get() const {
    return elem;
}
myVal::type myKeyword::getType(){
    return KEYWORD;
}
myNumber::myNumber(double a){
    num = a;
}
double myNumber::get(){
    return num;
}
myVal::type myNumber::getType(){
    return NUMBER;
}
myOperator::myOperator(string a){
    op = a;
}
string myOperator::get(){
    return op;
}
myVal::type myOperator::getType(){
    return OPERATOR;
}
myString::myString(string str){
    elem = str;
}
myVal::type myString::getType(){
    return STRING;
}
string myString::get(){
    return elem;
}

myFn::myFn(fn func){
    function = func;
}
myVal::type myFn::getType(){
    return DEFINE;
}
fn myFn::get(){
    return function;
}
