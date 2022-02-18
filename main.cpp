#include <iostream>
#include <string>
#include "linenoise.hpp"
#include <sstream>
#include <string.h>
#include "myTokenizer.hpp"
#include "myVal.hpp"
#include <unordered_map>
#include <functional>
#include "functionality.hpp"
#include "printerHelper.hpp"

using namespace std;
struct MyHash
{
    size_t operator()(myKeyword* const& s) const noexcept
    {
        size_t h1 = hash<string>{}(s->get());
        return h1; 
    }
};

struct MapComp {
    bool operator()(const myKeyword*  first, const myKeyword*  sec) const {
        return first->get() == sec->get();
    }
};

struct myMap{
    unordered_map <myKeyword*, myVal*, MyHash, MapComp> enviroment;
    myMap* other;
};
myVal* mapGet(myMap tmp, myKeyword* key){
    if(tmp.enviroment.find(key) == tmp.enviroment.end()){
        return mapGet(*tmp.other, key);
    }
    return tmp.enviroment.find(key)->second;
}
myVal* define(vector<string>& res, int& index);
myVal* evaluate_wrapper(myVal* processed, myMap& envi);
myVal* evaluate(myVal* processed, myMap& envi);



void enviromentSetUp( myMap& envi){
    myKeyword* op = new myKeyword("+");
    myFn* func = new myFn(add);
    envi.enviroment[op] = func;
    myKeyword* op1 = new myKeyword("*");
    myFn* func1 = new myFn(mult);
    envi.enviroment[op1] = func1;
    myKeyword* op2 = new myKeyword("/");
    myFn* func2 = new myFn(DIV);
    envi.enviroment[op2] = func2;
    myKeyword* op3 = new myKeyword("-");
    myFn* func3 = new myFn(sub);
    envi.enviroment[op3] = func3;
    myKeyword* op4 = new myKeyword("and");
    myFn* func4 = new myFn(AND);
    envi.enviroment[op4] = func4;
    myKeyword* op5 = new myKeyword("or");
    myFn* func5 = new myFn(OR);
    envi.enviroment[op5] = func5;
    myKeyword* op6 = new myKeyword("cons");
    myFn* func6 = new myFn(cons);
    envi.enviroment[op6] = func6;
    myKeyword* op7 = new myKeyword("car");
    myFn* func7 = new myFn(car);
    envi.enviroment[op7] = func7;
    myKeyword* op8 = new myKeyword("length");
    myFn* func8 = new myFn(len);
    envi.enviroment[op8] = func8;
    myKeyword* op9 = new myKeyword("null?");
    myFn* func9 = new myFn(null);
    envi.enviroment[op9] = func9;
    myKeyword* op10 = new myKeyword("cdr");
    myFn* func10 = new myFn(cdr);
    envi.enviroment[op10] = func10;
    myKeyword* op11 = new myKeyword("append");
    myFn* func11 = new myFn(append);
    envi.enviroment[op11] = func11;
    myKeyword* op12 = new myKeyword("map");
    myFn* func12 = new myFn(map);
    envi.enviroment[op12] = func12;

}


/*

თქვენს ინტერპრეტატორს უნდა შეეძლოს შემდეგი კონსტრუქციების შესრულება:
--ლამბდა ფუნქციები, მაგალითად (lambda (x y) (+ x y))  ✅
--ლამბდა ფუნქციების ადგილზე გამოძახება, მაგალითად ((lambda (x y) (+ x y)) 1 2)✅
--არითმეტიკული + - * / ოპერაციები ✅
--ლოგიკური ოპერაციები and და or ✅
--სიის აღწერა შესრულების გარეშე: ‘(1 2 3) ✅
--უნდა შეეძლოს რეკურსიული ფუნქციების შესრულება  ✅
--დამხმარე ფუნქციები: null?, length ✅
--define მაგალითად (define pi 3.14) ან (define (sum x y) (+ x y))  ✅ 
--შემსრულებელი ფუნქციები: apply, eval ✅
--სიებთან სამუშაო ფუნქციები: car, cons, cdr, append ✅
-- map 
-- if/else
*/

//keyword: lambda, define, if, apply, eval, car, cdr, cons, map, append
//operator: +, -, *, /
//


myList* readList(vector<string>& res, int& index){
    index++;
    myList* lst = new myList();
    while(index < res.size()){
        if(res[index] == ")"){
            index++;
            break;
        }
        lst->add(define(res, index));
    }
    return lst;
}
myVal* readSymbol(vector<string>& res, int& index){
    if(res[index].size() == 1 && index + 1 < res.size() && res[index+1] == "("){
        index++;
        mySymbol* sym = new mySymbol(readList(res, index));
        return sym;
    } else {
        if(res[index].size() == 1)
            index++;
        mySymbol* sym = new mySymbol(res[index].substr(1, res[index].size()-1));
        index++;
        return sym;
    }
    
}
myOperator* readOperator(vector<string>& res, int& index){
    myOperator* op;
    if(res[index] == "and" || res[index] == "or")
         op = new myOperator(res[index]);
    else{
        string s;
        s+=res[index][0];
        op = new myOperator(s);
    }
    index++;
    return op;
}
myNumber* readNumber(vector<string>& res, int& index){
    myNumber* num = new myNumber(stod(res[index]));
    index++;
    return num;
}
myString* readString(vector<string>& res, int& index){
    string curr = res[index].substr(1, res[index].size() - 2); //remove quotes;
    string result = "";
    for(int i = 0; i < curr.size(); i++){
        char ch = curr[i];
        if(ch == '\\'){
            if(curr[i + 1] == 'n'){
                result += '\n';
            }else{
                result += curr[i+1];
            }
            i++;
        } else if (ch == '"'){
            result += '\\';
            result += curr[i];
        } else {
            result += ch;
        }
    }
    index++;
    return new myString(result);
}
myBool* readBool(vector<string>& res, int& index){
    index++;
    if(res[index-1][1] == 't'){
        return new myBool(true);
    }
    return new myBool(false);
}
myKeyword* readKeywords(vector<string>& res, int& index){
    index++;
    return new myKeyword(res[index-1]);
}
myVal* define(vector<string>& res, int& index){
    
    if(res.size() == 0)
        return NULL;
    string test = res[index];
    char ch = test[0];
    switch (ch) {
        case '(':
            return readList(res, index);
        case '-':
            if (test.length() == 1 || !isdigit(test[1]))
                return readKeywords(res, index);
            return readNumber(res, index);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return readNumber(res, index);
        case '"':
            return readString(res, index);
        case '#':
            return readBool(res, index);
        case '+':
        case '/':
        case '*':
            return readKeywords(res, index);
        default:
            break;
    }

    if(test == "define"){
        return readKeywords(res, index);
    } else if(test == "lambda"){
        return readKeywords(res, index);
    } else if(test == "if"){

    } else if(test == "else"){

    } else if(test == "or"){
        return readKeywords(res, index);
    } else if(test == "and"){
        return readKeywords(res, index);
    } else if(test[0] == '\''){
       // if(index + 1 < res.size() && res[index+1][0] == '(')
         //   return readList(res, index);
        return readSymbol(res, index);
    } else {
        return readKeywords(res, index);
    }
    return NULL;
}

myVal* sortTokens(myTokenizer tok){
    vector<string> result;
    string str = tok.next();
    while(str != ""){
    //    cout<<str << endl;
        result.push_back(str);
        str = tok.next();
    }
    int index = 0;
    return define(result, index);
}

myVal* read(string curr){
    myTokenizer tok(curr);
    return sortTokens(tok);
}
myVal* evaluate(myVal* processed, myMap& envi){

    if(processed->getType() != myVal::LIST){  
        return evaluate_wrapper(processed, envi);
    } else if (static_cast<myList*>(processed)->size() == 0){
        return processed;
    } else {
        myVal* start = static_cast<myList*>(processed)->get(0);
        if(start->getType() == myVal::KEYWORD && static_cast<myKeyword*>(start)->get() == "define"){
            if(static_cast<myList*>(processed)->get(1)->getType() == myVal::KEYWORD){
                myKeyword* name = static_cast<myKeyword*>(static_cast<myList*>(processed)->get(1));
                auto operation = evaluate(static_cast<myList*>(processed)->get(2), envi);
                envi.enviroment[name] = operation;
                return operation;
            } else {
                myList* funcName = static_cast<myList*>(static_cast<myList*>(processed)->get(1));
                myList* logic = static_cast<myList*>(static_cast<myList*>(processed)->get(2)); 
                myMap* tmpEnvi = new myMap;
                tmpEnvi->other = &(envi);  
                myKeyword* key = static_cast<myKeyword*>(funcName->get(0));    
               
                envi.enviroment[key] = new myFn([funcName, logic, tmpEnvi](int argNum, myVal** params){
            //    myList* variables = new myList();
                    for(int i = 1; i <= argNum; i++){
                    //evaluate??
                    //    cout << argNum << endl;
                        tmpEnvi->enviroment[static_cast<myKeyword*>(funcName->get(i))] = params[i-1];
                    //    cout << static_cast<myKeyword*>(funcName->get(i))->get() << endl;
                    }
                    
                    return evaluate(logic, *tmpEnvi);         
                });
                return new myKeyword("<#function>");
            }
        } else if (start->getType() == myVal::KEYWORD && static_cast<myKeyword*>(start)->get() == "lambda") {
           // cout << static_cast<myList*>(processed)->size() << endl;
            //cout << static_cast<myList*>(processed)->get(3)->getType() << endl;
            //((lambda (x y) (+ x y)) 1 2)
            myList* parameters = static_cast<myList*>(static_cast<myList*>(processed)->get(1));
            myList* logic = static_cast<myList*>(static_cast<myList*>(processed)->get(2)); 
            myMap* tmpEnvi = new myMap;
            tmpEnvi->other = &(envi);        
            return new myFn([parameters, logic, tmpEnvi](int argNum, myVal** params){
            //    myList* variables = new myList();
                for(int i = 0; i < argNum; i++){
                    //evaluate??
                    tmpEnvi->enviroment[static_cast<myKeyword*>(parameters->get(i))] = params[i];
                }
                return evaluate(logic, *tmpEnvi);         
            });
            /*
         
            */
        } else if (start->getType() == myVal::KEYWORD && static_cast<myKeyword*>(start)->get() == "apply"){
          //  myKeyword* tmp =static_cast<myKeyword*> (evaluate_wrapper(static_cast<myList*>(processed)->get(1), envi));
            fn function =static_cast<myFn*> (evaluate(static_cast<myList*>(processed)->get(1), envi))->get();
            myVal* arguments = evaluate(static_cast<myList*>(processed)->get(2), envi); //FIX
            int argNum = static_cast<mySymbol*>(arguments)->size();
            myVal* arr[argNum];
          //       cout << argNum << endl;
            for(int i = 0; i < argNum; i++)
                arr[i] =  static_cast<mySymbol*>(arguments)->get(i);
        //   cout << "here2" << endl;
            return function(argNum, arr);
        }  else if (start->getType() == myVal::KEYWORD && static_cast<myKeyword*>(start)->get() == "eval"){
          //  myKeyword* tmp =static_cast<myKeyword*> (evaluate_wrapper(static_cast<myList*>(processed)->get(1), envi));
            return evaluate(static_cast<mySymbol*>(static_cast<myList*>(processed)->get(1))->getList(), envi);
        } else {
            myList* tmp =static_cast<myList*> (evaluate_wrapper(processed, envi));
        //   cout <<tmp->get(0)->getType() << endl;
            fn function =static_cast<myFn*> (tmp->get(0))->get();
            int argNum = tmp->size()-1;
            myVal* arr[argNum];
        //         cout << "here1" << endl;
            for(int i = 0; i < argNum; i++)
                arr[i] = tmp->get(i+1);
        //   cout << "here2" << endl;
            return function(argNum, arr);
        }
  //      cout << "here" << endl;
    }
}
myVal* evaluate_wrapper(myVal* processed, myMap& envi){
  
    if(processed->getType() == myVal::KEYWORD){
    //    cout << "aaa" << endl;
      //  cout << static_cast<myKeyword*>(processed)->get() << endl;
        return mapGet(envi, static_cast<myKeyword*> (processed));
    } else if(processed->getType() == myVal::LIST){
   //     cout << "aaabbb" << endl;
        myList* result = new myList();
        myList* tmp = static_cast<myList*>(processed);
        for(int i = 0; i < tmp->size(); i++){
            result->add(evaluate(tmp->get(i), envi));
        }
        return result;    
    } else {
    //    cout << "aaaccc" << endl;
        return processed;
    }
}
void getAnswer(string curr, myMap& envi){
    myVal* ast = read(curr);
   // cout << "read is done" << endl;
    myVal* result = evaluate(ast, envi);
  //  cout << "here5" << endl;
  //  cout << static_cast<myNumber*>(result)->get() << endl;
    print(result);
//    free(ast);
  //  free(result);
    cout << endl;
}

int main(){
    myMap envi;
    enviromentSetUp(envi);
    string reading;
    const char* path = "history.txt";
    linenoise::LoadHistory(path);
    while(true){
        bool quit = linenoise::Readline("> ", reading);
        if (quit) 
            break;
        if(reading == "exit")
            break;

        getAnswer(reading, envi);
        linenoise::AddHistory(reading.c_str());
    }
    linenoise::SaveHistory(path);
    
}