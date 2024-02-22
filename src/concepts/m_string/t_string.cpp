#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/m_string/t_string.hpp"
#include <string>

void c_style_string_in_action() {
    // Understanding the cstyle string as a pointer
    cstyle_string_as_apointer();
    // cstyle string allocated on heap
    cstyle_string_allocated_on_heap();

    // Acceping returning a pointer with constant
    cstyle_string_return_a_poniter_as_const();
}
/*
All tips and tricks with C-style char* pointer
*/
void cstyle_string_as_apointer() {
    const char* my_cstyle_string_ptr = "Hello World";
    LOG(INFO) << BLUE << "Printing the string itself -> " << YELLOW << my_cstyle_string_ptr
              << RESET;

    // printing the address of first character in this string
    LOG(INFO) << BLUE
              << "This prints the memory address where the first character ('H') is stored.: "
              << RED << " static_cast<const void*>(my_cstyle_string_ptr) -> " << YELLOW
              << static_cast<const void*>(my_cstyle_string_ptr) << RESET;

    // printing the pointer de-referencing

    LOG(INFO) << BLUE << "This will output the first character of the string: H" << RED
              << " *my_cstyle_string_ptr -> " << YELLOW << (*my_cstyle_string_ptr) << RESET;

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
    LOG(INFO) << RED << " string literal allocated on heap - getting the actual string" << BLUE
              << my_cstyle_string_array_on_heap << RESET;
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

/* *****************************************************************
 *
 * This is a testing function for returning a pointer
 * for outside object that can be handled as we return the pointer
 * to the object which lives outside the scope of this function.
 * This version: const is required.
 *
 * *****************************************************************
 */
char* find_my_string(const char* cstyle_string_input, char search_word) {
    const char* ptr_to_cstyle_string_input = cstyle_string_input;
    int index = 0;
    while (*ptr_to_cstyle_string_input != '\0') {
        if (*ptr_to_cstyle_string_input == search_word) {
            LOG(INFO) << RED << "Original Input string " << cstyle_string_input << YELLOW
                      << " We found your character..." << BLUE << " At index: " << index << RESET;
            return const_cast<char*>(ptr_to_cstyle_string_input);
        }
        ptr_to_cstyle_string_input++;
        index++;
    }
    LOG(INFO) << RED << "We couldn't find your character...\n" << RESET;
    return nullptr;
}

/* *****************************************************************
 *
 * This is a testing function for returning a pointer
 * for outside object that can be handled as we return the pointer
 * to the object which lives outside the scope of this function.
 * This version: const is not required.
 *
 * *****************************************************************
 */
char* find_my_string(char* cstyle_string_input, char search_word) {
    const char* ptr_to_cstyle_string_input = cstyle_string_input;
    int index = 0;
    while (*ptr_to_cstyle_string_input != '\0') {
        if (*ptr_to_cstyle_string_input == search_word) {
            LOG(INFO) << RED << "Original Input string " << cstyle_string_input << YELLOW
                      << " We found your character..." << BLUE << " At index: " << index << RESET;
            return const_cast<char*>(ptr_to_cstyle_string_input);
        }
        ptr_to_cstyle_string_input++;
        index++;
    }
    LOG(INFO) << RED << "We couldn't find your character...\n" << RESET;
    return nullptr;
}

/* *****************************************************************
 *
 * This is the main concept which will allow us to understand
 * returning a char pointer from a function for an object
 * lives outside the scope of the given function body.
 *
 * *****************************************************************
 */
void cstyle_string_return_a_poniter_as_const() {
    LOG(INFO) << BLUE << "(((((((( INPUT WITH CONSTANT ))))))))" << RESET;
    const char my_string_input_for_testing[] = "This is a testing string allocated on stack...";
    const char* found_element_ptr = find_my_string(my_string_input_for_testing, 'o');
    LOG(INFO) << BLUE << "We found the letter at the address -> " << YELLOW
              << (const void*)found_element_ptr << RESET << "\n";

    LOG(INFO) << BLUE << "(((((((( INPUT WITHOUT CONSTANT ))))))))" << RESET;

    char another_string_input_for_testing[] = "This is just a testing for another string input..";
    char* found_elemnt_ptr_2 = find_my_string(another_string_input_for_testing, 'j');
    LOG(INFO) << BLUE << "We found the letter at the address -> " << YELLOW
              << (const void*)found_elemnt_ptr_2 << RESET;
}
