# Pointer to Pointer in Action

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Pointer to Pointer in Action](#pointer-to-pointer-in-action)
  - [-](#-)
  - [Example of a Pointer to a Pointer for an Array of Strings](#example-of-a-pointer-to-a-pointer-for-an-array-of-strings)
  - [Dereferencing and Obtaining Information](#dereferencing-and-obtaining-information)
  - [Pointer Arithmetic](#pointer-arithmetic)
  - [Array of String Literals as a Pointer](#array-of-string-literals-as-a-pointer)
  - [Pointer to Pointer - Matrix Example](#pointer-to-pointer---matrix-example)
    - [Example Code](#example-code)
    - [Explanation](#explanation)
  - [More Explanation](#more-explanation)
    - [Understanding Double Pointers](#understanding-double-pointers)
    - [Use Cases and Examples](#use-cases-and-examples)
    - [Additional Points](#additional-points)
  - [More Examples](#more-examples)
    - [1. Array of Arrays](#1-array-of-arrays)
    - [2. Array of C-Style Strings](#2-array-of-c-style-strings)
    - [3. Array of Pointers to Integers](#3-array-of-pointers-to-integers)
    - [General Considerations](#general-considerations)

<!-- markdown-toc end -->

Pointers to pointers in C++ are essentially variables that store the address of
another pointer. These double pointers can be quite useful in various
scenarios. Here's a detailed explanation:

## My Understanding for Pointer to Pointer

Regarding pointer sizes, in C++, the size of a pointer is typically consistent
across all pointer types on a given platform and does not depend on the type of
data it points to. This size is usually determined by the architecture of the
system (32-bit or 64-bit):

- On a 32-bit system, pointers are generally 4 bytes (32 bits) in size.
- On a 64-bit system, pointers are generally 8 bytes (64 bits) in size.

Means that the pointer itself is just an integer which is either a 32bits or
64bits depends on the operating system. When we want to know the size of a
pointer, it is:

- Refecting the size of this address as an integer not to how many bytes it
  refer to.
- We know it is just an address and to know the data that we want to retreive
  using this pointer we give a type to this pointer

  - For example a `int a = 5; int* ptr = &a;`, Means the `ptr` is a pointer with
    a size `8-bites` on my `macOS` system of `64-bits`.
  - This pointer `ptr` is a type of `int` which we told the ptr your stop limit
    to retrive the data is upt to 4-bytes.
  - Now, when we dereference this pointer, the complier knows that we want to
    retireve the `4-bytes` as we specified the pointer size.
  - So, its not defile our logic or understand when we see that the
    `sizeof(ptr)` will be `8-bytes` as its a different thing.

- To understand this better:

  1. **Pointer as an Integer Representing an Address:** A pointer in C++ is indeed
     a type that stores the address of another variable. The size of the pointer
     (32 bits or 64 bits) depends on the architecture of the system, not the
     operating system. On a 32-bit architecture, pointers are typically 32 bits (4
     bytes), and on a 64-bit architecture, they are typically 64 bits (8 bytes).

  2. **Size of a Pointer:**

  - The size of a pointer reflects the size needed to store an address in
    memory. It does not indicate the size of the data the pointer points to.
  - The size of the pointer is consistent regardless of the data type it points
    to. Whether it's an `int*`, `char*`, or `double*`, the pointer size remains
    the same on a given system architecture.

  3. **Type of the Pointer:**

  - The type of the pointer (`int*` in your example) tells the compiler what
    kind of data the pointer is pointing to. This information is used to
    determine how to interpret the memory at the pointed-to address and how
    much memory to read or manipulate when the pointer is dereferenced.
  - In your example, `int a = 5; int* ptr = &a;`, `ptr` is a pointer to an
    `int`. If you are on a 64-bit macOS system, `ptr` would typically be 8
    bytes (64 bits). This size indicates the size of the pointer itself, not
    the size of the data it points to.
  - The type `int*` tells the compiler that `ptr` points to an integer. Since
    the size of an `int` is typically 4 bytes, when you dereference `ptr` using
    `*ptr`, the compiler knows to read 4 bytes from the memory location `ptr`
    is pointing to.

  4. **Dereferencing and Size of Pointer:**

  - When you dereference a pointer, like `*ptr`, you get the value stored at
    the memory address the pointer is pointing to. The size of this value
    depends on the type of the pointer.
  - The `sizeof(ptr)` gives the size of the pointer itself, which is 8 bytes on
    a 64-bit system. This size is for storing the address and is unrelated to
    the size of the data the pointer points to.

In summary, pointers in C++ store memory addresses, and their size is determined
by the system architecture. The type of a pointer determines how much data is
read from or written to the memory location it points to when it is
dereferenced.

- See the example in the `void pointer_more_insight()` function for more
  clarification.

```sh

        int my_array[2][3] = {{1,2,3}, {4,5,6}};

        |----------- 1 ------------ | ----------- 2 -------------||----------- 3 -------------|     |----------- 1 ------------ | ----------- 2 -------------||----------- 3 -------------|
        [0][0]-[0][0]-[0][0]-[0][0]|||[0][0]-[0][0]-[0][0]-[0][0]|||[0][0]-[0][0]-[0][0]-[0][0] <-> [0][0]-[0][0]-[0][0]-[0][0]|||[0][0]-[0][0]-[0][0]-[0][0]|||[0][0]-[0][0]-[0][0]-[0][0]
        |-------------------------------- 1 ---------------------------------------------------- | -------------------------------- 2 ----------------------------------------------------|
        ^
        |
        |
        +--- Pointer to main array with 2-elements

        |[0][0]-[0][0]-[0][0]-[0][0]||[0][0]-[0][0]-[0][0]-[0][0]||[0][0]-[0][0]-[0][0]-[0][0]|
        ^
        |                           |
        +<---- Second pointer------>+
        ^                                                                                     |
        |                                                                                     |
        +<--------------------------------- First poitner ----------------------------------->+

        NOTE: The terms "first" and "second" when referring to pointers are simply used to denote the first element,
        and the diagram above is presented theoretically to demonstrate
        what would be obtained by dereferencing a pointer of size that has already been defined.

int* array_ptr[rows]; <- We allocate here an array but a pointer of array; and we know by the defintionn that the
                         cstyle array decay to apointer for first element (given us the address of first element)
                         It means, `array_ptr` is a pointer.

for (int i = 0; i < rows; i++) {       <-  Now, we will initialize the array (which is also a pointer)
     array_ptr[i] = my_array[i];             to occupy the values of each element in our first dimension my_array
 }                                           each element of this array is another array holding the sub-array of `my_array`.
int** array_rows_ptr = array_ptr;      <- We assign the double pointer for the first dimension and it will be our matrix.


array_rows_ptr[i][j]    <- Accessing the double pointer is simple as it is refering to the two-dimensional array,
                           Using the brackets is much easier for us to handle.

```

### Use Cases for Pointer to a Pointer

1. **Dynamic Memory Allocation for Multi-dimensional Arrays:** They are often
   used to dynamically allocate memory for multi-dimensional arrays. For
   example, in a 2D array, a pointer to a pointer can be used to allocate memory
   for each row.

   ```cpp
   int** arr = new int*[row];
   for (int i = 0; i < row; i++) {
       arr[i] = new int[col];
   }
   ```

2. **Changing the Address Stored in a Pointer:** If you want a function to
   modify the address stored in a pointer, you can pass a pointer to that
   pointer to the function.

   ```cpp
   void changeAddress(int** ptr) {
       // some logic that changes the address stored in ptr
   }
   ```

3. **Advanced Data Structures:** In data structures like a graph represented
   using adjacency lists, a pointer to a pointer can represent the lists.

### Example of a Pointer to a Pointer for an Array of Strings

For the array `{"hello", " ", "world!"}`, you can have a pointer to a pointer to
access these strings.

```cpp
const char* strings[] = {"hello", " ", "world!"};
const char** ptr = strings;
```

### Dereferencing and Obtaining Information

To dereference and obtain information, you use the `*` operator. For a pointer
to a pointer, you might need to use it twice.

```cpp
std::cout << *ptr;     // prints "hello"
std::cout << *(ptr+1); // prints " "
std::cout << *(ptr+2); // prints "world!"
```

### Pointer Arithmetic

Pointer arithmetic allows you to navigate through an array. Here's a simple
example:

```cpp
const char** ptr2 = ptr + 1; // Points to the second element (" ")
std::cout << *ptr2;          // prints " "
```

### Array of String Literals as a Pointer

Yes, an array of string literals like `{"Hello", " ", "world!"}` can be treated
as a pointer to the first element. To access each element:

```cpp
const char* array[] = {"Hello", " ", "world!"};
const char* first = array[0];  // Accessing the first element "Hello"
const char* second = array[1]; // Accessing the second element " "
const char* third = array[2];  // Accessing the third element "world!"
```

In summary, pointers to pointers are used in C++ for managing dynamic
multi-dimensional arrays, altering addresses in pointers, and implementing
complex data structures. They can be used with string arrays, support pointer
arithmetic, and allow for flexible memory management and data access.

## Pointer to Pointer - Matrix Example

Let's consider a scenario where we have a two-dimensional array (matrix) and we
want to use double pointers to reference this matrix without copying it. We'll
also create a function that takes a double pointer to this matrix and increments
each element by 1.

Here's a step-by-step breakdown:

1. **Define a Two-Dimensional Array**: We'll start by defining a 2D array
   (matrix).
2. **Use Double Pointers**: We'll create a double pointer that refers to this
   matrix.
3. **Create a Function**: This function will take a double pointer to the matrix
   and increment each element by 1.

### Example Code

```cpp
#include <iostream>

// Function to increment each element of the matrix by 1
void incrementMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] += 1;
        }
    }
}

int main() {
    const int rows = 2;
    const int cols = 3;

    // Define a 2D array
    int matrix[rows][cols] = {{1, 2, 3}, {4, 5, 6}};

    // Creating a double pointer and pointing it to the matrix
    int* ptr[rows];
    for (int i = 0; i < rows; ++i) {
        ptr[i] = matrix[i];
    }
    int** doublePtr = ptr;

    // Display original matrix
    std::cout << "Original Matrix:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Increment each element in the matrix
    incrementMatrix(doublePtr, rows, cols);

    // Display updated matrix
    std::cout << "Matrix after Increment:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
```

### Explanation

- **2D Array Initialization**: A 2D array `matrix` is defined with some initial
  values.
- **Double Pointer**: A double pointer `doublePtr` is created which points to
  the array of pointers `ptr`. Each element of `ptr` points to the corresponding
  row of the matrix.
- **Function `incrementMatrix`**: This function takes a double pointer to the
  matrix and increments each element by 1. It uses nested loops to iterate
  through the elements.
- **Avoiding Copy**: By using double pointers, we are not copying the matrix;
  instead, we are just passing the address to the function. Hence, any
  modification inside the function reflects in the original matrix.
- **Displaying the Matrix**: The matrix is displayed before and after the
  increment operation to demonstrate the changes.

This approach efficiently handles the 2D array with pointer manipulation,
ensuring that no unnecessary copying of the array occurs.

## More Explanation

Double pointers (or pointers to pointers) are a more advanced concept in C++
that can be used in various scenarios. They add an extra level of indirection
compared to regular pointers, which can be both powerful and complex. Here's a
more detailed explanation along with examples.

### Understanding Double Pointers

- **Basic Concept**: A double pointer is a pointer that points to another
  pointer. In other words, it holds the address of a pointer.

  ```cpp
  int value = 5;
  int *ptr = &value;  // Pointer to 'value'
  int **doublePtr = &ptr;  // Double pointer pointing to 'ptr'
  ```

- **Dereferencing**: To access the value pointed by a double pointer, you need
  to dereference it twice.

  ```cpp
  std::cout << **doublePtr;  // Accessing the value '5'
  ```

### Use Cases and Examples

1. **Dynamic Memory Allocation for 2D Arrays**: As previously discussed, double
   pointers are often used for dynamically allocated multi-dimensional arrays.

   ```cpp
   int **array2D = new int*[row];  // Allocate row pointers
   for (int i = 0; i < row; i++) {
       array2D[i] = new int[col];  // Allocate each row separately
   }
   ```

2. **Function Pointers**: They can be used to change the address a pointer is
   holding from within a function.

   ```cpp
   void changePointer(int **ptr) {
       static int otherValue = 10;
       *ptr = &otherValue;
   }
   ```

3. **Implementing Data Structures**: In complex data structures like trees or
   graphs, double pointers are used for pointer manipulation.

   ```cpp
   typedef struct Node {
       int data;
       Node *left, *right;
   } Node;

   void insert(Node **root, int newData) {
       if (*root == NULL) {
           *root = new Node();
           (*root)->data = newData;
           (*root)->left = (*root)->right = NULL;
       }
       // Additional logic for inserting in the right place...
   }
   ```

4. **Handling Arrays of Strings**: Useful in scenarios where you need to
   manipulate an array of strings.

   ```cpp
   char *fruits[] = {"apple", "banana", "cherry"};
   char **fruitPtr = fruits;

   for (int i = 0; i < 3; i++) {
       std::cout << fruitPtr[i] << std::endl;
   }
   ```

5. **Pointer to Pointer as Function Arguments**: Allows functions to modify the
   pointer itself.

   ```cpp
   void resetPointer(int** ptr) {
       *ptr = nullptr;
   }
   ```

### Additional Points

- **Memory Management**: When using double pointers, especially with dynamic
  memory allocation, it's important to manage memory carefully to avoid leaks.
  Remember to `delete` allocated memory.
- **Complexity**: While powerful, double pointers add complexity to your code.
  It's important to use them judiciously and ensure that your code remains
  readable and maintainable.
- **Debugging**: Debugging issues with double pointers can be more challenging,
  as you have to deal with multiple levels of indirection.

Double pointers are a powerful feature in C++ that enable advanced memory and
data structure management. However, they require careful use to avoid common
pitfalls like memory leaks or pointer mismanagement. Understanding how to
properly allocate, use, and deallocate memory with double pointers is crucial
for advanced C++ programming.

## More Examples

In C++, a double pointer (a pointer to a pointer) can be used in several
contexts, including arrays of arrays, arrays of C-style strings, and arrays of
integers. Let's break down each use case:

### 1. Array of Arrays

A double pointer can represent a dynamically allocated two-dimensional array.
It's like an array of pointers, where each pointer points to an array.

**Example: 2D Array of Integers**

```cpp
int** twoDArray = new int*[rowCount];
for (int i = 0; i < rowCount; ++i) {
    twoDArray[i] = new int[colCount];
}
// Use twoDArray[i][j] to access elements
// Remember to delete[] each sub-array and then delete[] twoDArray.
```

### 2. Array of C-Style Strings

A double pointer can be used to represent an array of C-style strings (which are
themselves pointers to characters).

**Example: Array of C-Style Strings**

```cpp
const char* arrayOfStrings[] = {"Hello", "World"};
// Or dynamically
const char** dynamicArrayOfStrings = new const char*[stringCount];
// Each element is a pointer to a char array
```

### 3. Array of Pointers to Integers

A double pointer can also represent an array of pointers, where each pointer
points to an integer.

**Example: Array of Pointers to Integers**

```cpp
int* arrayOfIntPointers[] = {new int(10), new int(20)};
// Or dynamically
int** dynamicArrayOfIntPointers = new int*[intCount];
for (int i = 0; i < intCount; ++i) {
    dynamicArrayOfIntPointers[i] = new int(i);
}
// Remember to delete each dynamically allocated int and the array itself.
```

### General Considerations

- **Memory Management:** Especially when using dynamic allocation, proper memory
  management is crucial to avoid leaks.
- **Flexibility vs. Complexity:** Double pointers offer flexibility but can
  increase the complexity of the code. Make sure to manage them carefully.

In summary, double pointers are versatile in C++ and can be used for various
purposes including multi-dimensional arrays, arrays of strings, and arrays of
pointers. However, their use requires careful attention to memory management and
code clarity.
