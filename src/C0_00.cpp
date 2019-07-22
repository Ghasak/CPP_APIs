#include <iostream>
#include <string>
#include "Log.cpp"  // declaration
#include "math.cpp"

// void Log(const char* message); // definition - this one doesn't work

using namespace std;

int main(){

    std::cout << "------------------------------- \n";
    std::cout << "Processing Data Source in Order " << std::endl;
    std::cout << "------------------------------- \n";
    Log("Welcome to our first function!!!");
    printing_message("This is to show that my file is working!!");
    Log("We will use a simple math multiplication");
    //------------------------------------------------------------
    int a;
    int b;
    a = 0; b = 0;
    cout<< "Please input the value of a is = ";
    a = cin.get();
    cout<< "Please input the value of b is = ";
    b = cin.get();
    cout << "-------OUTPUT----------";
    cout << Multiply(a, b);
    surprise();
    simpson();
    cumulative_sum();
    std::cin.get();

}
