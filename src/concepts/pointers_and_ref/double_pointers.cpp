#include "double_pointers.hpp"
#include <iostream>
#include "concepts/mylogging.hpp"
#include <glog/logging.h>

/*
HOSTING ALL CONCPETS
*/
void double_pointers_in_action() {
    const char* message = "DOUBLE POINER - CONCEPT ";
    double_pointer_with_matrices();
    concept_separation(message);
    double_pointer_of_std_array();
    concept_separation(message);
    double_pointer_with_matricesII();
    concept_separation(message);
    double_pointer_with_matricesIII();
    concept_separation(message);
    double_pointer_with_matricesIV();
    concept_separation(message);
    using_matrix_on_heap_demo();
    concept_separation(message);
    pointer_to_pointer_insight();
    concept_separation(message);
    cstyle_string_array_as_pointer();
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

/*
This function will create a matrix allocated on heap and using double pointers concept
You can see how to do similar in C-Style at
- [Return a dynamically allocated 2D array from a function | C Programming
Tutorial](https://www.youtube.com/watch?v=22wkCgsPZSU)

*/
void using_matrix_on_heap_demo() {
    int** matrix;

    int m;
    int n;
    int fill_value;

    std::cout << YELLOW << "Input the first dimension of your array  -> " << RESET;
    std::cin >> n;
    std::cout << YELLOW << "Input the second dimension of your array -> " << RESET;
    std::cin >> m;
    std::cout << YELLOW << "Fill it with -> " << RESET;
    std::cin >> fill_value;

    matrix = create_matrix(m, n, fill_value);
    print_matrix(matrix, m, n);

    // Free the memory

    for (int i = 1; i < m; i++) {
        delete[] matrix[i];
        // In C-style
        // free(matrix[i]);
    }
    delete[] matrix;
    // In C-style
    // free(matrix)
    matrix = nullptr;
}

/*
The function that we use for creating the matrix\n
Must be cleaned later by the user when it called
*/
int** create_matrix(int rows, int cols, int fill_value) {
    int** matrix;

    // Initialize the matrix in a form of a pointer
    matrix = new int*[rows];
    // In C-style
    // matrix = malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        // In C-style
        // matrix[i] =  malloc(sizeof(int) * cols);
    }

    // Filling the matrix with the value
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = fill_value;
        }
    }

    return matrix;
}

void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << BLUE << matrix[i][j] << " - ";
        }
        std::cout << std::endl;
    }
}

/*
Function show the pointer-to-pointer
concept, casting pointers will allow us to
clearily powerful contorl over the memory-allocation
*/
void pointer_to_pointer_insight() {
    int cstyle_array[2][3] = {{10, 20, 30}, {40, 50, 60}};

    LOG(INFO) << RED << cstyle_array << RESET;
    LOG(INFO) << BLUE << **(cstyle_array + 1) << RESET;
    LOG(INFO) << BLUE << *((int*)((char*)cstyle_array + 4)) << RESET;
    LOG(INFO) << MAGENTA << *(int*)(((char*)(*cstyle_array)) + 4) << RESET;
    LOG(INFO) << RED << *(int*)(((*cstyle_array)) + 1)
              << RESET;                                   //  <- *cstyle_array is an integer length
    LOG(INFO) << RED << *((*cstyle_array) + 1) << RESET;  //  <- *cstyle_array is an integer length

    /* I20240129 18:45:07.822881 9186708 main.cpp:43] 0x16f0b9fc0 */
    /* I20240129 18:45:07.823963 9186708 main.cpp:44] 40 */
    /* I20240129 18:45:07.823973 9186708 main.cpp:45] 20 */
    /* I20240129 18:45:07.823980 9186708 main.cpp:46] 20 */
    /* I20240129 18:47:53.410066 9188879 main.cpp:48] 20 */
}

void cstyle_string_array_as_pointer() {
    // declare a pointer-to-pointer for 2D-matrix;
    /* const char* my_char_array_ptr[] = {"Hello","World"}; */
    /* const char my_char_array[][6] = {"Hello", "World"}; */
    const char* my_cstyle_char_ptr[] = {"Hello", "World"};

    LOG(INFO) << YELLOW << "const char* my_cstyle_char_ptr[] ={\"Hello\", \"World\"};" << RESET;
    LOG(INFO) << BLUE << "Pointer of char array my_cstyle_char_ptr      -> " << my_cstyle_char_ptr
              << RESET;
    LOG(INFO) << RED << "Dereference the pointer **my_cstyle_char_ptr   -> "
              << **(my_cstyle_char_ptr) << RESET;
    LOG(INFO) << BLUE << "Dereference the pointer *my_cstyle_char_ptr   -> "
              << *(my_cstyle_char_ptr) << RESET;

    LOG(INFO) << BLUE << "dereferencing the pointer after incrementing  -> "
              << *(my_cstyle_char_ptr + 1) << RESET;

    // Navigate over each pointer in top level
    for (size_t i = 0; i < strlen(my_cstyle_char_ptr[0]); i++) {
        LOG(INFO) << RED << "deferencing with casting " << YELLOW
                  << *(((char*)(*my_cstyle_char_ptr)) + i) << RESET;
    }
    // OUTPUT
    /*  const char* my_cstyle_char_ptr[] ={"Hello", "World"}; */
    /*  Pointer of char array my_cstyle_char_ptr       -> 0x16f08df70 */
    /*  Dereference the pointer **my_cstyle_char_ptr   -> H */
    /*  Dereference the pointer *my_cstyle_char_ptr    -> Hello */
    /*  dereferencing the pointer after incrementing   -> World */
    /*  deferencing with casting H */
    /*  deferencing with casting e */
    /*  deferencing with casting l */
    /*  deferencing with casting l */
    /*  deferencing with casting o */
}

void concept_separation(const char* message) {
    std::cout << MAGENTA << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n" << RESET;
    std::cout << RED << message << RESET;
    std::cout << MAGENTA << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << RESET << "\n";
}
