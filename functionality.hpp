#ifndef functionality_hpp
#define functionality_hpp
#include "myVal.hpp"
#include <string>

using namespace std;

/*

თქვენს ინტერპრეტატორს უნდა შეეძლოს შემდეგი კონსტრუქციების შესრულება:
--ლამბდა ფუნქციები, მაგალითად (lambda (x y) (+ x y))
--ლამბდა ფუნქციების ადგილზე გამოძახება, მაგალითად ((lambda (x y) (+ x y)) 1 2)
--define მაგალითად (define pi 3.14) ან (define (sum x y) (+ x y))
--არითმეტიკული + - * / ოპერაციები
--ლოგიკური ოპერაციები and და or
--if/else
--სიებთან სამუშაო ფუნქციები: car, cdr, cons, map, append
--სიის აღწერა შესრულების გარეშე: ‘(1 2 3)
--შემსრულებელი ფუნქციები: apply, eval
--უნდა შეეძლოს რეკურსიული ფუნქციების შესრულება
--დამხმარე ფუნქციები: null?, length

*/

myVal *add(int argNum, myVal** parameters);
myVal *sub(int argNum, myVal** parameters);
myVal *mult(int argNum, myVal** parameters);
myVal *DIV(int argNum, myVal** parameters);
myVal *cons(int argNum, myVal** parameters);
myVal *cdr(int argNum, myVal** parameters);
myVal *car(int argNum, myVal** parameters);
myVal *AND(int argNum, myVal** parameters);
myVal *OR(int argNum, myVal** parameters);
myVal *append(int argNum, myVal** parameters);
myVal *null(int argNum, myVal** parameters);
myVal *len(int argNum, myVal** parameters);
myVal* map(int argNum, myVal** parameters);
#endif