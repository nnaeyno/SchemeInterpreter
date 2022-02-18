#include "printerHelper.hpp"

void print(myVal* result){
    switch(result->getType()){
        case myVal::BOOLEAN:
            if( static_cast<myBool*>(result)->get())
                cout << "#t";
            else
                cout << "#f";
            break;
        case myVal::NUMBER:
            cout << static_cast<myNumber*>(result)->get();
            break;
        case myVal::SYMBOL:
            printSymbol(static_cast<mySymbol*>(result));
            break;
        case myVal::LIST:
            printList(static_cast<myList*>(result));
            break;
        case myVal::STRING:
            cout << static_cast<myString*>(result)->get();
            break;
        case myVal::KEYWORD:
             cout << static_cast<myKeyword*>(result)->get();
            break;
        default:
            cout << "<#function>";
            break;
    }
   // cout << endl;
}
void printList(myList* result){
    cout << "(";
    for(int i = 0; i < static_cast<myList*>(result)->size(); i++){
        print(result->get(i));
        if(i != result->size() -1)
            cout << " ";
    }
    cout << ")";
}
void printSymbol(mySymbol* result){
    if(result->get() == ""){
        cout << "(";
        for(int i = 0; i < result->size(); i++){
            print(result->get(i));
            if(i != result->size() -1)
                cout << " ";
        }
        cout << ")";
    } else {
        cout << static_cast<mySymbol*>(result)->get();
    }
}

/*
    case myVal::LIST:
    cout << "( ";
        for(int i = 0; i < static_cast<myList*>(result)->size(); i++)
            cout <<static_cast<myNumber*>(static_cast<myList*>(result)->get(i))->get() << " ";
        cout << ")" << endl;
        break;
    default:
        break;
*/