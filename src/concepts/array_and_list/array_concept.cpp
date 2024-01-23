#include "array_concept.hpp"
#include <iostream>
#include "../mylogging.hpp"
#include <glog/logging.h>

void array_function_in_depth() {
    std::cout << "######################################\n";
    // Array and Ptr arithmetics.
    int simple[5];

    std::cout << "Printing: Simple    -> " << simple << std::endl;
    LOG(INFO) << RED
              << "Memeory Profile: -> "
                 "[00][00][00][00]-[00][00][00][00]-[00][00][00][00]-[00][00][00][00]-[00][00]["
                 "00][00]"
              << RESET;
    int* ptr = simple;
    std::cout << "Printing: ptr       -> " << ptr << std::endl;
    LOG(INFO) << RED
              << "Memeory Profile: -> "
                 "[00][00][00][00]-[00][00][00][00]-[05][00][00][00]-[00][00][00][00]-[00][00]["
                 "00][00]"
              << RESET;
    simple[2] = 5;
    std::cout << "Printing simple[2]  -> " << simple[2] << std::endl;
    LOG(INFO) << BLUE
              << "Memeory Profile: -> "
                 "[00][00][00][00]-[00][00][00][00]-[05][00][00][00]-[00][00][00][00]-[05][00]["
                 "00][00]"
              << RESET;
    *(ptr + 4) = 5;
    std::cout << "Printing *(ptr + 4) -> " << *(ptr + 4) << std::endl;
    LOG(INFO) << BLUE
              << "Memeory Profile: -> "
                 "[00][00][00][00]-[00][00][00][00]-[05][00][00][00]-[00][00][00][00]-[05][00]["
                 "00][00]"
              << RESET;
    *(int*)((char*)ptr + 8) = 10;
    std::cout << "Printing *(int*)((char*)ptr + 8) -> " << *(int*)((char*)ptr + 8) << std::endl;
    LOG(INFO) << RED
              << "Memeory Profile: -> "
                 "[00][00][00][00]-[00][00][00][00]-[0A][00][00][00]-[00][00][00][00]-[05][00]["
                 "00][00]"
              << RESET;
}
