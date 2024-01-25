#include "array_concept.hpp"
#include <iostream>
#include "../mylogging.hpp"
#include <glog/logging.h>
#include <array>

// Caller function
void array_function_in_depth() {
    c_style_array();
    standard_array_cpp();
    pointer_with_array_arithmatic();
    vector_allocated_on_heap();
    what_is_vecotor_on_heap();
}

// concepts functions
void c_style_array() {
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

void standard_array_cpp() {
    std::array<int, 3> my_array = {5};
    LOG(INFO) << "Size of the standard array from std::array -> " << my_array.size();
    // int* ptr = my_array; you cannot do that as the std::array is not automatically casted into
    // pointer.

    int* ptr = my_array.data();
    LOG(INFO) << "Getting a pointer to first element in  std::array similar to C-style -> "
              << *(ptr);
}

void pointer_with_array_arithmatic() {
    int my_array[4]{0, 1, 2, 3};
    int* ptr = my_array;
    LOG(INFO) << RED << "[0][0]-[0][0]-[0][0]-[0][0] " << RESET;
    LOG(INFO) << BLUE << "---1------2------3------4---" << RESET;
    LOG(INFO) << RED << "MY ARRAY IS :" << BLUE << my_array << RESET;
    LOG(INFO) << RED << "MY ARRAY IS :" << BLUE << my_array[0] << ", " << my_array[1] << ", "
              << my_array[2] << ", " << my_array[3] << RESET;

    *(ptr + 3) = 20;
    LOG(INFO) << "ELEMENT my_array[*(ptr + 4)] -> " << RED << *(ptr + 3) << RESET;
    LOG(INFO) << RED << "MY ARRAY IS :" << BLUE << my_array[0] << ", " << my_array[1] << ", "
              << my_array[2] << ", " << my_array[3] << RESET;

    *(int*)((char*)ptr + 8) = 30;
    LOG(INFO) << "ELEMENT my_array[*(int*)((char*)ptr + 8)] -> " << RED << *(int*)((char*)ptr + 8)
              << RESET;
    LOG(INFO) << RED << "MY ARRAY IS :" << BLUE << my_array[0] << ", " << my_array[1] << ", "
              << my_array[2] << ", " << my_array[3] << RESET;
}

/*
This function will show exactly that we can
extend even the heap allocated data structure such
as our std::vector by allowing it to live outside of its scope.
*/
void vector_allocated_on_heap() {
    std::vector<int>* my_vector_heap_ptr;
    {
        my_vector_heap_ptr = new std::vector<int>({10, 20, 30});
        int size = my_vector_heap_ptr->size();
        LOG(INFO) << RED << "Size of our vector is => " << BLUE << size << RESET;
    }
    for (size_t i = 0; i < (*my_vector_heap_ptr).size(); i++) {
        LOG(INFO) << RED << (*my_vector_heap_ptr)[i] << RESET;
    }

    LOG(INFO) << RED << "(*my_vector_heap_ptr).size() is same as my_vector_heap_ptr->size()"
              << RESET;

    my_vector_heap_ptr = nullptr;
    delete my_vector_heap_ptr;
}

void what_is_vecotor_on_heap() {
    std::vector<int>* my_vector_heap_ptr = new std::vector<int>({10, 20, 30});
    LOG(INFO) << BLUE << "My Vector Heap Pointer: Memeory Address: " << my_vector_heap_ptr << RESET;
    LOG(INFO) << BLUE << "My Vector Heap Pointer: Capacity       : " << (*my_vector_heap_ptr).size()
              << RESET;
    LOG(INFO) << BLUE
              << "My Vector Heap Pointer: Length         : " << (*my_vector_heap_ptr).capacity()
              << RESET;
}
