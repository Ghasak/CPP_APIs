#include "concepts_bundles.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <ostream>

// Definition of the default constructor with a message
// StringG::StringG() noexcept { std::cout << "Shallow copy is called, which is default by the C++ created it for us" << std::endl; }

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
<<<<<<< HEAD
     array_function_in_depth();
     class_implementation();
     classes_concepts_hub();
     classes_size_concept();
     virtual_function_concept();
     friends_in_action();
     operators_and_operatos_overloading_concept();
     object_life_time_concpet();
     similar_to_unique_pointer_from_scratch_concept();
     data_type_table();
     pointers_concept();
     smart_pointers_concept();
     copying_and_copy_constructor_concept();
     const_in_action();
     cstyle_string_as_apointer();
     c_style_string_in_action();
     double_pointers_in_action();
     enums_concept_hub();
||||||| parent of 5cb1792 ([NEW BRANCH LINUX] Debugging and operating on Linux Ubuntu ...)
    // array_function_in_depth();
    // class_implementation();
    // classes_concepts_hub();
    // classes_size_concept();
    // virtual_function_concept();
    // friends_in_action();
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
=======
    // array_function_in_depth();
    // class_implementation();
    // classes_concepts_hub();
    // classes_size_concept();
    // virtual_function_concept();
    // friends_in_action();
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
    // enums_concept_hub();
    copying_and_copy_constructor_concept();
>>>>>>> 5cb1792 ([NEW BRANCH LINUX] Debugging and operating on Linux Ubuntu ...)

    return 0;
}
