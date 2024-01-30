#include "concepts/mylogging.hpp"
#include "concepts_bundles.hpp"
#include <glog/logging.h>
#include <algorithm>
#include <iostream>
#include <ostream>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        // You run directly the ../build/debug/main arg1 arg2 arg3 ..etc.
        std::cout << "Arg No." << i << "which is -> " << argv[i] << std::endl;
    }

    // Initialize logging
    init_logging(argv);
    std::cout << "######################################\n";

    // ------------------------------
    /* array_function_in_depth(); */
    // ------------------------------
    /* class_implementation(); */
    // ------------------------------
    /* data_type_table(); */
    // ------------------------------
    /* pointers_concept(); */
    // ------------------------------
    /* const_in_action(); */
    // ------------------------------
    // cstyle_string_as_apointer();
    // ------------------------------
    /* c_style_string_in_action(); */
    // ------------------------------
    double_pointers_in_action();
    // ------------------------------

    return 0;
}

