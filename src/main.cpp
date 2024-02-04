#include "concepts/classes/Friends.hpp"
#include "concepts_bundles.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <ostream>

class Vec2d {
    int x;
    int y;
    const char* c;

public:
    Vec2d(int xi, int yi, const char* ci)
        : x{xi},
          y{yi},
          c{ci} {}
};

int main(int argc, char* argv[]) {
    // Initialize logging before processing arguments
    init_logging(argv);

    // You run directly the ../build/debug/main arg1 arg2 arg3 ..etc.
    for (int i = 0; i < argc; i++) {
        std::cout << RED << "Argument No. " << BLUE << "[" << YELLOW << i << BLUE "]" << BLUE
                  << " which is -> " << MAGENTA << argv[i] << RESET << std::endl;
    }

    // Demonstrate various concepts
    // Uncomment the functions you wish to run
    // array_function_in_depth();
    // class_implementation();
    // classes_concepts_hub();
    // virtual_function_concept();
    // friends_in_action();
    // operators_and_operatos_overloading_concept();
    // object_life_time_concpet();
    // data_type_table();
    // pointers_concept();
    // const_in_action();
    // cstyle_string_as_apointer();
    // c_style_string_in_action();
    // double_pointers_in_action();
    // enums_concept_hub();

    const char* my_name = "ABC";
    LOG(INFO) << RED "Size of this char* pointer data type -> " << BLUE << sizeof(my_name) << RESET;

    Vec2d v1 = Vec2d(10, 20, "ABC");
    LOG(INFO) << RED "Size of this Vec2d Class data type -> " << BLUE << sizeof(Vec2d) << RESET;

    return 0;
}

// int[] my_function_return_array_cstyle() {
//     int my_array[]{1, 2, 3, 4};
//     return my_array;
// }
