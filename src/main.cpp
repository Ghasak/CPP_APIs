#include "concepts/mylogging.hpp"
#include "concepts_bundles.hpp"
#include <glog/logging.h>
#include <algorithm>
// #include <iterator>
#include <cstdint>
#include <ios>
#include <iterator>
#include <ostream>
#include <iostream>
#include <vector>
#include <string>

void MyFunction(std::string&);
void concept_of_string();
void TestingString(const char*);

int main(int argc, char* argv[]) {
    // Initialize logging before processing arguments
    init_logging(argv);

    // You run directly the ../build/debug/main arg1 arg2 arg3 ..etc.

    for (int i = 0; i < argc; i++) {
        std::cout << RED << "Argument No. " << BLUE << "[" << YELLOW << i << BLUE "]" << BLUE << " which is -> " << MAGENTA << argv[i]
                  << RESET << std::endl;
    }

    //---------------------------------------------
    // Demonstrate various concepts
    // Uncomment the functions you wish to run
    //---------------------------------------------
    // array_function_in_depth();
    // class_implementation();
    // classes_concepts_hub();
    // classes_size_concept();
    // virtual_function_concept();
    // friends_in_action()pip install --upgrade lookatme;
    // operators_and_operatos_overloading_concept();
    // object_life_time_concpet();
    // similar_to_unique_pointer_from_scratch_concept();
    // data_type_table();
    // pointers_concept();
    // smart_pointers_concept();
    // copying_and_copy_constructor_concept();
    // const_in_action();
    // cstyle_string_as_apointer();
    // c_style_string_in_action();
    // double_pointers_in_action();
    // enemas_concept_hub();
    // timing_concept();
    // tracking_memory_allocation_concpet();

    //---------------------------------------------
    //    Memory Management for objects in C++
    //---------------------------------------------
    // lvalues_and_rvalues_concepts();
    // StdMoveAndMoveAssignmentOperatorConcept();

    // MoveSemanticsConcept();
    //---------------------------------------------
    //        Experimental Session
    //      Testing concepts in action
    //---------------------------------------------
    // TwoDimensionalArray();
    TestingCalcWeigthAeverageFu();
    TestingFunction01();
    // Typical struct with rule of 5 in C++
    std::string str_example = std::string("yes");
    MyFunction(str_example);
    std::vector<float> vecx = {1.2, 1.3, 12.2, 23.23, 44.12};

    const char* testing_string = "Hello World!";
    TestingString(testing_string);
}

/**
 * Function for current objective
 * The following idea comes first form
 * the right position for making things more advanced.
 *
 * */
void MyFunction(std::string& str1) {
    // Convert str1 to lowercase
    std::string strlocal = str1;
    std::transform(strlocal.begin(), strlocal.end(), strlocal.begin(), ::tolower);
    if (strlocal == "yes" || strlocal == "y") {
        std::vector<int> v{1, 2, 3, 4, 5};
        for (int item : v) {
            std::cout << "[ " << RED << "INFO" << RESET << " ] This is the output for our current objective today ...... " << item
                      << std::endl;
        }
    }
}

void myStirngFunction(std::string& str, std::vector<float>& v) {
    if (str.empty()) {
        std::cout << "[INFO]" << "The string is -> " << str << std::endl;
    } else {
        std::cout << " [ INFO ] The value is out of bound " << std::endl;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
        }
    }

    for (size_t i = 0; i < v.size(); i++) {
        std::cout << "valeu of each element -> " << v[i] << std::endl;
    }
}

void TestingString(const char* str) {
    // Traditional for loop to iterate over each character
    for (int i = 0; i < str[i] != '\0'; i++) {
        std::cout << str[i] << std::endl;
    }
    // Modern way to do same thing

    std::string cppString = str;

    // Range-based for loop (C++11 and later) to iterate over each character.

    std::string message01{"Range-based for loop (C++11 and later) to iterate over each character"};
    LOG(INFO) << " [ " << RED << "INFO" << RESET << " ] " << BLUE << message01 << RESET << std::endl;

    for (char ch : cppString) {
        std::cout << ch << std::endl;
    }

    // Using a pointer to iterate over each character

    const char* cstringPointer = str;
    for (const char* ptr = cstringPointer; *(ptr) != '\0'; ++ptr) {
        std::cout << *ptr << std::endl;
    }

    std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    meaning_of_pointers();
}




