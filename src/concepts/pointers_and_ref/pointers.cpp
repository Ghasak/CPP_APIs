#include <glog/logging.h>
#include <iostream>
// #include "../mylogging.hpp"  //before using CPP_APIs/src/concepts/CMakeLists.txt
#include "concepts/mylogging.hpp"
#include "pointers.hpp"
#include <cstring>

void pointers_concept() {
    // 1.  addressing the pointer casting system for nullptr
    casting_with_pointer();

    int a = 10;
    LOG(INFO) << RED << "Original value of a: " << BLUE << a << RESET;
    passing_args_as_val(a);
    LOG(INFO) << RED << "After Passing as a value  :   " << BLUE << a << RESET;
    passing_args_as_ptr(&a);
    LOG(INFO) << RED << "After Passing as a pointer:   " << BLUE << a << RESET;
    passing_args_as_reference(a);
    LOG(INFO) << RED << "After Passing as a reference: " << BLUE << a << RESET;

    const char* message = "Hello World!!";
    print_message(message);
    pointer_more_insight();
}

// Based on my understnding to the pointer
void what_is_pointer() {}

void passing_args_as_val(int copy_of_a) {
    LOG(INFO) << RED << "[Value Call] -> " << BLUE
              << "The Parameter change but it will "
                 "not change the argument that got passed to this "
                 "function"
              << RESET;

    copy_of_a++;
}
void passing_args_as_ptr(int* ptr_to_a) {
    LOG(INFO) << RED << "[Pointer Call] -> " << BLUE
              << "The Parameter change also it will "
                 "change the argument that got passed to this "
                 "function"
              << RESET;

    (*ptr_to_a)++;
}
void passing_args_as_reference(int& ref_to_a) {
    LOG(INFO) << RED << "[Reference Call] -> " << BLUE
              << "The Parameter change also it will "
                 "change the argument that got passed to this "
                 "function"
              << RESET;

    ref_to_a++;
}

void casting_with_pointer() {
    // create a placeholder for our pointer which refer to nothing
    // such pointer is called `nullptr` and introduced in modern C++
    void* ptr = nullptr;
    // Assume we have a int value
    int my_int = 2;
    // Now we store the address of the value for our int, taking address of an object is carried out
    // using `&` operator.
    ptr = &my_int;
    LOG(INFO) << BLUE << ptr << RESET;
    // LOG(INFO) << BLUE << *ptr; // <- doesn't work
    // We have to use the `C++` which is the casting way for the void pointer, notice that the
    // syntax of the casting using C-style is not working.
    LOG(INFO) << RED << *(static_cast<int*>(ptr)) << RESET;
}

/*
Function to print the message as a dereference the pointer
The message is for printing character by character as we
loop over each byte in the string we pass as a pointer
*/
void print_message(const char* message) {
    // const char* my_string = message;
    int array_size = strlen(message) / sizeof(message[0]);

    for (int i = 0; i < array_size; i++) {
        LOG(INFO) << YELLOW << *(message + i * 1) << RESET;
    }
}

void pointer_more_insight() {
    const int rows = 2;
    const int cols = 3;

    int matrix[rows][cols] = {{1000, 2000, 3000}, {4000, 5000, 6000}};

    int* ptry[rows];

    for (int i = 0; i < rows; i++) {
        ptry[i] = matrix[i];
    }

    int** ptrx = ptry;

    // notice here that the ptrx in size is 12 bytes, so need to move 1-byte
    std::cout << "Obtain the value " << BLUE << sizeof(**ptrx + 1) << " bytes\n" << RESET;

    std::cout << "Size of ptrx[0]: " << MAGENTA << sizeof(ptrx[0]) << " bytes\n" << RESET;
    std::cout << "Obtrain the value dereferenced after moving 4 bytes: "
              << *((int*)((char*)ptry[0] + 4)) << std::endl;
    std::cout << "Size of ptry[0]   dereferenced after moving 4 bytes: "
              << sizeof(*((int*)((char*)ptry[0] + 4))) << std::endl;

    int a = 5;
    int* ptra = &a;

    LOG(INFO) << RED << "VALUE OF A : " << BLUE << ptra << RESET;
    LOG(INFO) << RED << "VALUE OF *A: " << BLUE << *ptra << RESET;
}
