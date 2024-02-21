#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/m_string/t_string.hpp"
#include <iostream>
#include <string>

void c_style_string_in_action() {
    // Understanding the cstyle string as a pointer
    cstyle_string_as_apointer();
    // cstyle string allocated on heap
    cstyle_string_allocated_on_heap();
    // cstyle string return a pointer
    cstyle_string_return_pointer_concept();
}
/*
All tips and tricks with C-style char* pointer
*/
void cstyle_string_as_apointer() {
    const char* my_cstyle_string_ptr = "Hello World";
    LOG(INFO) << BLUE << "Printing the string itself -> " << YELLOW << my_cstyle_string_ptr << RESET;

    // printing the address of first character in this string
    LOG(INFO) << BLUE << "This prints the memory address where the first character ('H') is stored.: " << RED
              << " static_cast<const void*>(my_cstyle_string_ptr) -> " << YELLOW << static_cast<const void*>(my_cstyle_string_ptr) << RESET;

    // printing the pointer derferencing

    LOG(INFO) << BLUE << "This will output the first character of the string: H" << RED << " *my_cstyle_string_ptr -> " << YELLOW
              << (*my_cstyle_string_ptr) << RESET;

    // Not allowed - even without const (clang complier)
    /*  my_cstyle_string_ptr[2] = 'K'; */
    /* LOG(INFO) << BLUE << "MODIFYING THE STRING" << RED << my_cstyle_string_ptr << RESET; */

    // This is not a pointer arithmetics rather shifting the H to K and give us K as ASCII code
    // which is 75
    LOG(INFO) << RED << (*my_cstyle_string_ptr + 3) << RESET;
    // THis will perform the pointer arithmetics as it will print the address after 3-bytes to
    // the end.
    LOG(INFO) << RED << (my_cstyle_string_ptr + 3) << RESET;
}

void cstyle_string_allocated_on_heap() {
    char* my_cstyle_string_array_on_heap = new char[]{"Hello World!"};
    LOG(INFO) << RED << " string literal allocated on heap - getting the actual string" << BLUE << my_cstyle_string_array_on_heap;
    LOG(INFO) << RED
              << " string literal allocated on heap - dereferencing the pointer -> "
                 "(*my_cstyle_string_array_on_heap); => "
              << YELLOW << (*my_cstyle_string_array_on_heap) << RESET;

    LOG(INFO) << RED
              << " string literal allocated on heap - dereferencing the pointer -> "
                 "static_cast<const void*>(my_cstyle_string_array_on_heap); => "
              << YELLOW << static_cast<const void*>(my_cstyle_string_array_on_heap) << RESET;

    delete[] my_cstyle_string_array_on_heap;
    my_cstyle_string_array_on_heap = nullptr;
}

void cstyle_string_return_pointer_concept() {
    char my_examined_string[] = "This is just a string to be tested ...";
    char* location = finding_letter(my_examined_string, 't');
    LOG(INFO) << MAGENTA << location << RESET;
}

/*
 * It is ok to pass external variable to our function
 * It is also to return a reference or a pointer of the function
 * of a parameter created outside the body of the function
 */
char* finding_letter(char input_string[], char what_to_find) {
    char* ptr = input_string;
    while ((*ptr) != '\0') {
        if (*ptr == what_to_find) {
            std::cout << RED << "We have found the letter ->  " << BLUE << what_to_find << " which is At: " << (const void*)ptr
                      << std::endl;
            return ptr;
        }
        ptr++;
    }
    std::cout << "Sorry we couldn't find the letter you are asking about .." << std::endl;
    return nullptr;
}
