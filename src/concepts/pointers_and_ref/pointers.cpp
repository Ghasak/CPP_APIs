#include <glog/logging.h>
#include <iostream>
// #include "../mylogging.hpp"  //before using CPP_APIs/src/concepts/CMakeLists.txt
#include "concepts/mylogging.hpp"
#include "pointers.hpp"

void pointers_concept() {
    // 1.  addressing the pointer casting system for nullptr
    casting_with_pointer();
}

// Based on my understnding to the pointer
void what_is_pointer() {}

void passing_args_as_val(int copy_of_a) { copy_of_a++; }
void passing_args_as_ptr(int* ptr_to_a) { (*ptr_to_a)++; }
void passing_args_as_reference(int& ref_to_a) { ref_to_a++; }

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
    LOG(INFO) << RED << *(static_cast<int*>(ptr));
}
