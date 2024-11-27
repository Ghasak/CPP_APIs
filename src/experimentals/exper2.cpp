#include <iostream>
#include <glog/logging.h>
#include "concepts/mylogging.hpp"

void meaning_of_pointers() {
    int x[3] = {1, 2, 3};
    for (size_t i = 0; i < std::size(x); i++) {
        LOG(INFO) << RED << "Value of x" << YELLOW << "  => " << BLUE << x[i] << RESET;
    }

    LOG(INFO) << BLUE << "I want to access the second element and get it back from x[3] = {1,2,3}" << RESET;
    LOG(INFO) << RED << "Address of second elment is given as (x+1), x is a pointer as we know: " << (x + 1) << RESET;
    LOG(INFO) << RED << "Dereference the Address of second elment is given as (x+1), x is a pointer as we know: " << *(x + 1) << RESET;
    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "Getting memory address of each byte of" << "[" << YELLOW << (x + i) << RESET << "]" << RESET;
    }

    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "The value of i -> " << *(x + i) << BLUE << RESET;
    }

    // Access by casting to a 1-byte
    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "the value of x is -> " << YELLOW << (int*)((char*)x + 4 * i) << RESET;
    }

    if ((sizeof(x) / sizeof(x[0])) == (std::size(x))) {
        LOG(INFO) << YELLOW << "<YES>" << BLUE << " sizeof(x)/sizeof(x[0]) " << RED " IS EQUAL " << RESET << BLUE << " std::size(x)" RESET;
    }

    /*int x[3] = {1, 2, 3};*/
    /*int* ptr = &x;*/
    /*std::cout << sizeof(x) << std::endl;*/
    /*std::cout << (ptr + )*/
    /*void* ptr;*/
    /**(int*)((char*)ptr + 1) = x[0];*/
    /*std::cout << sizeof(x) << std::endl;*/
    /*std::cout << "OUTPUT of *(int*)((char*)ptr + 2) : " << *(int*)((char*)ptr + 2) << std::endl;*/

    /*int x = 300;*/
    /**/
    /*int* ptr = &x;  // Pointer to x*/
    /**/
    /*// Print the address of x directly*/
    /*std::cout << "Address of x: " << std::hex << std::showbase << &x << std::endl;*/
    /**/
    /*// Print the pointer value*/
    /*std::cout << "Pointer value: " << std::hex << std::showbase << ptr << std::endl;*/
    /**/
    /*// Alternatively, use printf for consistent output*/
    /*printf("Address of x: %p\n", (void*)&x);*/
    /*printf("Pointer value: %p\n", (void*)ptr);*/
    /**/
    /*std::cout << "Hex value of x => " << std::hex << x << std::endl;*/
}
