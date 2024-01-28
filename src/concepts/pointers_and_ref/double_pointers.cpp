#include "double_pointers.hpp"
#include <iostream>
#include "concepts/mylogging.hpp"
#include <glog/logging.h>

void double_pointers_in_action() {
    double_pointer_with_matrices();
    double_pointer_of_std_array();
    double_pointer_with_matricesII();
    double_pointer_with_matricesIII();
    double_pointer_with_matricesIV();
}

void double_pointer_with_matrices() {
    // Assume we have a 2x3 matrix with the following values
    int matrix[2][3] = {{10, 20, 30}, {40, 50, 60}};

    // Initializing the pointer
    int* ptr_rows[2];
    for (int i = 0; i < 2; i++) {
        ptr_rows[i] = matrix[i];
    }
    // We assign a pointer to point to the first element
    int** ptr_cols = ptr_rows;

    LOG(INFO) << BLUE << ptr_cols << RESET;
    LOG(INFO) << RED << *(ptr_rows) << RESET;
    LOG(INFO) << RED << *((*ptr_cols)) << RESET;
    LOG(INFO) << RED << *((ptr_cols[0])) << RESET;
    LOG(INFO) << RED << ptr_cols[0][0] << RESET;
}

void double_pointer_of_std_array() {
    int my_array[]{100, 200, 300};
    std::array<int, 3> my_std_array = {400, 500, 600};

    int* ptr1 = my_array;
    int* ptr2 = my_std_array.data();

    LOG(INFO) << RED << "PRINTING THE POINER ITSELF OR my_array          -> " << BLUE << ptr1
              << RESET;
    LOG(INFO) << RED << "DEREFERENCING THE POINER ITSELF OR my_array     -> " << BLUE << *ptr1
              << RESET;
    LOG(INFO) << YELLOW << "PRINTING THE POINER ITSELF OR my_std_array      -> " << BLUE << ptr2
              << RESET;
    LOG(INFO) << YELLOW << "DEREFERENCING THE POINER ITSELF OR my_std_array -> " << BLUE << *ptr2
              << RESET;
}

/*
This function will show the power of double pointers with matrices.
*/
void double_pointer_with_matricesII() {
    const int rows = 2;
    const int cols = 3;
    int my_array[rows][cols] = {{1, 2, 3}, {4, 5, 6}};

    // LOG(INFO) << my_array;

    int* array_ptr[rows];
    for (int i = 0; i < rows; i++) {
        array_ptr[i] = my_array[i];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            LOG(INFO)
                << GREEN
                << "Casting our pointer to char with a size of one byte, incrementing it by four \n"
                << "bytes, and then casting it again to an integer before dereferencing it. -> \n"
                << "4-bytes as a 1-cell occupied with a single integer value, and int -> 4-bytes \n"
                << YELLOW << *(int*)((char*)array_ptr[i] + (j * 4)) << RESET;
        }
    }

    int** array_rows_ptr = array_ptr;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            LOG(INFO) << RED << "POINTER TO POINTER -> " << YELLOW << array_rows_ptr[i][j] << RESET;
        }
    }
}

/*
Understanding more about the double pointers
*/
void double_pointer_with_matricesIII() {
    const int rows = 4;
    const int cols = 4;

    // Allocate memeory for the matrix on the heap
    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Initialize the matrix

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            LOG(INFO) << MAGENTA << "i = " << BLUE << i << MAGENTA << " , j = " << BLUE << j << RED
                      << " cell value = " << YELLOW << i * cols + j << RESET;
            matrix[i][j] = 10 + (i * cols) + j;
        }
    }

    // Matrix before incrementing
    std::cout << RED << "------\n" << RESET;
    printMatrix(matrix, rows, cols);
    increment_matrix(matrix, rows, cols);
    std::cout << RED << "------\n" << RESET;
    printMatrix(matrix, rows, cols);

    delete[] matrix;
    matrix = nullptr;
}

void increment_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j]++;
        }
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << RED << matrix[i][j] << " " << RESET;
        }
        std::cout << std::endl;
    }
}

void double_pointer_with_matricesIV() {
    const int rows = 2;
    const int cols = 3;
    int my_array[rows][cols] = {{1000, 2000, 3000}, {4000, 5000, 6000}};

    int* ptr[rows];

    for (int i = 0; i < rows; i++) {
        ptr[i] = my_array[i];
    }

    int** matrix_ptr = ptr;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << BLUE << " -> " << YELLOW << matrix_ptr[i][j] << RESET;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Notice that we cast the pointer to a char to access its bytes individually.
            // Then,we increment the pointer by 4 bytes (the size of each cell) in each jump.
            // Since we have shiftted by a char, we cast back to an int to obtain the real value
            // occupied with the 4-bytes.
            std::cout << MAGENTA << *(int*)((char*)matrix_ptr[i] + (j * 4)) << BLUE "  " << RESET;
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // The pointer matrix_ptr[0] refere to the the full array {1,2,3}
            // which will giev us the right way to shift our matrix.
            // We are moving here 12-bytes for each step.
            // as matrix_ptr[0] or matrix_ptr[1] size is defined as 12-bytes
            std::cout << MAGENTA << *(matrix_ptr[i] + j * 1) << BLUE "  " << RESET;
        }

        std::cout << std::endl;
    }
}

