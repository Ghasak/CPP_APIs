#include <iostream>
#include "moduleAHeader.hpp"
/* function with refernce - alias */
void myFunction(int& val ){
    std::cout << "value of val is : "<< val << std::endl;
}

/* Passing a memeory address and capture it with pointer
   of course you need to dererence your pointer once you do that.
*/
void myFunctionPointer(int* val){
    std::cout << "value of val is : "<< *val << std::endl;
}
/* our first program in c++ */
int main(){
    std::cout << "This is just a test in CPP " << std::endl;

    int var = 8;
    int* ptr = &var ;

    std::cout << "The value of ptr: " << ptr << std::endl;
    std::cout << "The value of derefernce the ptr: " << *ptr << std::endl;

    char s = 'A';
    char* ptr2 = &s;

    std::cout << "lets print ptr2 ...  " << *ptr2 << std::endl;

    /* char k[40] = "Working on current project"; */
    /* std::cout << "lets print the char => " << k << std::endl; */



    int myVal = 10;
    myFunction(myVal);
    myFunctionPointer(&myVal);

    /* Import my module function */
    float a  = 0 ;
    float b = 0;
    float c = 0;
    std::cout << "The value of adding the two vars is : " << c << std::endl;
    for (int i = 0 ; i < 100; i++){
        a = a + i;
        b = b + i;
        c  = addFunction(a, b);

        std::cout << "\033[0;33;42m Adding value is equal:: !\033[0m" <<c << std::endl;
        std::cout << "\033[1;31mbold red text[\uf423 ]\033[0m"<<"["<<i<<"]"<< std::endl;
    }

    for (int i = 0; i < 10; i++){
        myFirstFunction( myVal, i);
        std::cout << "********************************" << std::endl;
        myPointerFunction(&myVal, &i);
    }




    return 0;
}


