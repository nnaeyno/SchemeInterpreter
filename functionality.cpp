#include "functionality.hpp"
#include <iostream>



myVal* add(int argNum, myVal** parameters) {
    double result = 0;
  //  cout << "here3" << endl;
    for(int i = 0; i < argNum; i++){
        result += static_cast<myNumber*>(parameters[i])->get();
    }
 //   cout << "here4" << endl;
    return new myNumber (result);
}

myVal *sub(int argNum, myVal** parameters){
    double result = static_cast<myNumber*>(parameters[0])->get();
  //  cout << "here3" << endl;
    for(int i = 1; i < argNum; i++){
        result -= static_cast<myNumber*>(parameters[i])->get();
    }
 //   cout << "here4" << endl;
  
    return new myNumber (result);
}
myVal *mult(int argNum, myVal** parameters){
    double result = 1;
  //  cout << "here3" << endl;
    for(int i = 0; i < argNum; i++){
        result *= static_cast<myNumber*>(parameters[i])->get();
    }
 //   cout << "here4" << endl;
 
    return new myNumber (result);
}
myVal *DIV(int argNum, myVal** parameters){
    double result = static_cast<myNumber*>(parameters[0])->get();
 //   cout << "here3" << endl;
    for(int i = 1; i < argNum; i++){
        if(static_cast<myNumber*>(parameters[i])->get() == 0)
            throw "divison by zero!";
        result /= static_cast<myNumber*>(parameters[i])->get();
    }
 //   cout << "here4" << endl;
   
    return new myNumber (result);
}
myVal *cons(int argNum, myVal** parameters){
    myVal* elem = parameters[0];
    mySymbol* dest = static_cast<mySymbol*>(parameters[1]);
    dest->push(elem);
    
    return dest;
}
myVal *cdr(int argNum, myVal** parameters){
    myList* lst = new myList();
    mySymbol* res = new mySymbol(lst);
    for(int i = 1; i <  static_cast<mySymbol*>(parameters[0])->size(); i++)
        res->add(static_cast<mySymbol*>(parameters[0])->get(i));
    return res;
}
myVal *car(int argNum, myVal** parameters){
    
    return  static_cast<mySymbol*>(parameters[0])->get(0);
}
myVal *AND(int argNum, myVal** parameters){
    bool result = static_cast<myBool*>(parameters[0])->get();
   
    for(int i = 1; i < argNum; i++){
        result = result && static_cast<myBool*>(parameters[i])->get();
    }
    
    return new myBool (result);
}
myVal *OR(int argNum, myVal** parameters){
     bool result = static_cast<myBool*>(parameters[0])->get();
  //  cout << "here3" << endl;
    for(int i = 1; i < argNum; i++){
        result = result || static_cast<myBool*>(parameters[i])->get();
    }
 //   cout << "here4" << endl;
   
    return new myBool(result);

}

myVal *append(int argNum, myVal** parameters){
    myList* lst = new myList();
    mySymbol* res = new mySymbol(lst);
    for(int i = 0; i < static_cast<mySymbol*> (parameters[0])->size(); i++){
        res->add(static_cast<mySymbol*> (parameters[0])->get(i));
    }
    for(int i = 0; i < static_cast<mySymbol*> (parameters[1])->size(); i++){
        res->add(static_cast<mySymbol*> (parameters[1])->get(i));
    }
    return res;
}
myVal *null(int argNum, myVal** parameters){
    myVal* lst = parameters[0];
    if(lst->getType() == myVal::LIST){
        return new myBool(static_cast<myList*>(lst)->size() == 0);
    }
    return new myBool(static_cast<mySymbol*>(lst)->size() == 0);
}
myVal* len(int argNum, myVal** parameters){
    myVal* lst = parameters[0];
    if(lst->getType() == myVal::LIST){
        return new myNumber(static_cast<myList*>(lst)->size());
    }
    return new myNumber(static_cast<mySymbol*>(lst)->size());
}



myVal* map(int argNum, myVal** parameters) {
    cout << argNum << endl;
    return NULL;
}