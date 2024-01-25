#include "concepts/mylogging.hpp"
#include "concepts/classes/classes.hpp"
#include "concepts/array_and_list/array_concept.hpp"
#include "concepts/data_types/variables.hpp"
#include "concepts/pointers_and_ref/pointers.hpp"
#include "concepts/m_const/t_constant.hpp"
#include <glog/logging.h>
#include <iostream>
#include <ostream>


int main(int argc, char* argv[]) {
    // Initialize logging
    init_logging(argv);
    std::cout << "######################################\n";
    // array_function_in_depth();
    /* class_implementation(); */
    /* data_type_table(); */
    // pointers_concept();
    //  const_in_action();

    int a = 10;
    LOG(INFO) << RED << "Original value of a: " << BLUE << a << RESET;
    passing_args_as_val(a);
    LOG(INFO) << RED << "After Passing as a value  :   " << BLUE << a << RESET;
    passing_args_as_ptr(&a);
    LOG(INFO) << RED << "After Passing as a pointer:   " << BLUE << a << RESET;
    passing_args_as_reference(a);
    LOG(INFO) << RED << "After Passing as a reference: " << BLUE << a << RESET;
}

