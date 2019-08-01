#include <iostream>
#include <stdio.h>

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



    cin.get();
}
