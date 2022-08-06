#include <iostream>

/* My Adding function is at moduleA.cpp*/
float addFunction(float& a , float& b){
    return a + b ;
}


/* The following function is used to pass a reference which is much better and much cleaner than passing moemeory address*/
void myFirstFunction( int& var, int& idx){
    std::cout << "Printing the current results [pointer results] ... "<<"[" << idx << "] " << var << std::endl;
    std::cout << "Lets print the address of var: "<<"[" << &var << "] "<< std::endl;

}
/* The following function uses to pass a pointer to the function ... */
void myPointerFunction(int* var, int* idx){
    std::cout << "Printing the current results [pointer results] ... "<<"[" << *idx << "] " << *var << std::endl;
    std::cout << "Lets print the address of var: "<<"[" << var << "] "<<idx<< std::endl;
}


void myFunctionM(int& val){
    std::cout << "Ghasak welcoming you in c++ value of val is : "<< val << std::endl;
    int a [] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++)
    {
        std::cout << a[i] << std::endl;
    }
}






