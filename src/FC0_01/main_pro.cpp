#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// Calling the function using
/* cd "./." && c++ main_pro.cpp -o main_pro && "./main_pro"
This will link your file with your source code
 */

// We will call the function using the source code itself:
//#include "calling_functions.cpp"
// Now we will use the header file in our directory
#include "header_file.h"

int main(){
    cout << "Hello world" << endl;
    printf("This is Ghasak \n");
    // We will call the function directly from calling_functions.cpp
    cout << add(100, 100);
    cout << USING_IF(5);
    // input a value not valid:
    cout << USING_IF(8);
    cout << USING_IF(7);
    // Using the conditional statement
    printf("\n ======= Using if Statement ========= \n");
    const char* ptr = 0;
    const char* comparwith = "Hello";
    if(ptr) {
        cout << ptr;
    }
    else if(ptr == comparwith){
        cout << "Wow!!!!!!!";
    }
    else {
        Log("We are having a Null pointer!!");
    }
    // Using the conditional statement
    printf("\n ======= Using Loops ========= \n");
    for (int i = 0 ; i < 10; i ++)
    {
        Log("Hello world!!");
    }
    // using the function itself
    using_loop("Iteration Number");

    
    cin.get();
}
