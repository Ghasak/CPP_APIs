#include <iostream>
#include "experimentals/exper1.hpp"

void TwoDimensionalArray() {
    size_t ARRAY_SIZE = 0;
    std::cout << "Input the size of the matrix (int) type " << std::endl;
    std::cin >> ARRAY_SIZE;
    /* int* array = new int[ARRAY_SIZE]; */

    int** a2d = new int*[ARRAY_SIZE];

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        a2d[i] = new int[ARRAY_SIZE];
    }
    // Initialize the array
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        for (size_t j = 0; j < ARRAY_SIZE; j++) {
            std::cin >> a2d[i][j];
        }
    }

    // print the multi-dimensional array
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        for (size_t j = 0; j < ARRAY_SIZE; j++) {
            std::cout << ", " << a2d[i][j];
        }
        std::cout << std::endl;
    }

    // Clean up the dynamically allocated memory
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        delete[] a2d[i];  // Delete each sub-array
    }
    delete[] a2d;
    a2d = nullptr;
}
