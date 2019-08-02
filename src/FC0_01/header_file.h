#include <iostream>
#include "calling_functions.cpp"
using namespace std;

// declare the function that you want from calling_functions main file
int add(int x, int y);

// again this function will not work unless you declare it here in the header in the top.
int USING_IF();
void Log(const char* message);
void using_loop(const char* message2);
// Using loop but with conditions out of the standard loop itself
void using_loop2(const char* message3);
// Using the while loop here
void using_while(const char* message);
// using the do-while loop
void using_do_while(const char* message);
// control flow statement with loops usually
// continue, break, return
void control_flow(const char* message);
// Pointers - memory management enhancement -this is not smart pointer
// pointer is an integer of the address of memory -
void learn_pointer(const char* message);

// Using the printf in C++ language
void using_printf(const char* message);

// Data type in C++
void data_type(const char* message);

// Practice pointers and data types
void practice_pointers_data_type(const char* message);

