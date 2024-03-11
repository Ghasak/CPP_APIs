#include "concepts/array_and_list/array_concept.hpp"
#include "concepts/mylogging.hpp"
#include "concepts/classes/lvalues_and_rvalues_intro.hpp"
#include <glog/logging.h>
#include <iostream>
#include <string>

/* **************************************************************************************
 *
 * The concept of lvalue and rvalue in C++
 *   - Main function for calling related concepts
 *
 * ***************************************************************************************
 */
void lvalues_and_rvalues_concepts() {
    std::cout << "lvalues and rvalues in C++ concept up and running " << std::endl;

    std::string first_name = "Jay";
    std::string last_name = "mdotgh";
    std::string full_name = first_name + last_name;
    std::string name = "John";
    const std::string constName = "Jane";
    std::string tempName = "Doe";

    // PrintName(first_name);
    // PrintName(last_name);
    // PrintName(full_name);
    // PrintName(first_name + last_name);

    // Using the function pointers concept to show the prioritized

    // ------- Switch here to understand lvalue-reference vs rvalue-reference -------------
    bool which_function_will_be_called_lesson_one = false;

    // Based on condition, choose which functions to use
    if (which_function_will_be_called_lesson_one) {
        PrintNameLValuePtr = PrintNameLValue;
        PrintNameConstLValuePtr = PrintNameConstLValue;
        PrintNameRValuePtr = nullptr;

        // Optional: Handle the case for rvalue references differently if needed
    } else {
        // In this example, they are the same, but you can customize as needed
        PrintNameLValuePtr = PrintNameLValue;
        PrintNameConstLValuePtr = PrintNameConstLValue;
        PrintNameRValuePtr = PrintNameRValue;
    }

    // Usage
    PrintNameLValuePtr(first_name);

    if (PrintNameRValuePtr != nullptr) {
        PrintNameRValuePtr(first_name + last_name);
    }

    PrintNameConstLValuePtr(first_name + last_name);
}

/* ************************************************************************************************
 * Here the PrintName parameter lvalue-reference accept
 * an lvalue only
 * ************************************************************************************************
 */
void PrintName(std::string& name) {
    std::cout << BLUE << "[lvalue-reference] Taken from an lvalue " << YELLOW << name << RESET
              << std::endl;
}

/* ************************************************************************************************
 * Here the PrintName parameter lvalue-reference accept
 * an lvalue and rvalue
 * ************************************************************************************************
 */
void PrintName(const std::string& name) {
    std::cout << BLUE << "[const lvalue-reference] Taken from an lvalue and rvalue  " << YELLOW
              << name << RESET << std::endl;
}

/* **********************************************************************************************
 *
 * Here the PrintName parameter rvalue-reference accept
 * an lvalue and rvalue, but will be prioritized over the const method above
 *
 * **********************************************************************************************
 */
void PrintName(std::string&& name) {
    std::cout << BLUE << "[rvalue-reference] Taken from an rvalue  " << YELLOW << name << RESET
              << std::endl;
}

/* ************************************************************************************************
 *
 * Now i will implement the same thing about but with function pointer
 * so I can switch between the concepts to show the priority of lvalue-reference that accept an
 * lvalue and rvalue and also a rvalue-reference which also accept both the lvalue and rvalue, this
 * will be always prioritized over the former.
 *
 * ************************************************************************************************
 */
// Define all possible functions
void PrintNameLValue(std::string& name) {
    std::cout << BLUE << "[lvalue-reference] Taken from an lvalue " << YELLOW << name << RESET
              << std::endl;
}

void PrintNameConstLValue(const std::string& name) {
    std::cout << BLUE << "[const lvalue-reference] Taken from an lvalue and rvalue  " << YELLOW
              << name << RESET << std::endl;
}

void PrintNameRValue(std::string&& name) {
    std::cout << BLUE << "[rvalue-reference] Taken from an rvalue  " << YELLOW << name << RESET
              << std::endl;
}

// Initialize function pointers
void (*PrintNameLValuePtr)(std::string&) = PrintNameLValue;
void (*PrintNameConstLValuePtr)(const std::string&) = PrintNameConstLValue;
void (*PrintNameRValuePtr)(std::string&&) = PrintNameRValue;
