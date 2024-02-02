#include "concepts_bundles.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <ostream>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        // You run directly the ../build/debug/main arg1 arg2 arg3 ..etc.
        std::cout << RED << "Argument No. " << BLUE << "[" << YELLOW << i << BLUE "]" << BLUE
                  << " which is -> " << MAGENTA << argv[i] << std::endl;
    }

    // ------------------------------
    // array_function_in_depth();
    // ------------------------------
    // class_implementation();
    // classes_concepts_hub();
    // virtual_function_concept();
    // ------------------------------
    // data_type_table();
    // ------------------------------
    // pointers_concept();
    // ------------------------------
    // const_in_action();
    // ------------------------------
    // cstyle_string_as_apointer();
    // ------------------------------
    // c_style_string_in_action();
    // ------------------------------
    // double_pointers_in_action();
    // ------------------------------
    // enums_concept_hub();

    return 0;
}
