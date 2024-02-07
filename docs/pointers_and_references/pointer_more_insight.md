# Pointer More Insights
<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Pointer More Insights](#pointer-more-insights)
    - [Double Pointers - Intger array of array](#double-pointers---intger-array-of-array)
    - [*(my_array) --> `100`](#my_array----100)
    - [*((int*)((char*)cstyle_array + 4)) -> 200](#intcharcstyle_array--4---200)
    - [*(int*)(((char*)(*cstyle_array)) + 4) -> 200](#intcharcstyle_array--4---200)
    - [*(int*)(((*cstyle_array)) + 1) -> 200](#intcstyle_array--1---200)
    - [String with array as a double pointer](#string-with-array-as-a-double-pointer)
    - [Double Pointers allocated on heap for array of string](#double-pointers-allocated-on-heap-for-array-of-string)
    - [More Insights](#more-insights)

<!-- markdown-toc end -->

## Double Pointers - Intger array of array

1. Compare the behavior of pointers for complete objects with that of pointers for
   primitive data types.
2. Gain insight into how this concept mirrors the address or
   reference of an entire string during our discussions..

```sh
int cstyle_array[2][3] = {{100,200,300}, {400,500,600}};

| Decimal   | Hex   |
| --------- | ----- |
| 100       | 0x64  |
| 200       | 0xC8  |
| 300       | 0x12C |
| 400       | 0x190 |
| 500       | 0x1F4 |
| 600       | 0x258 |

----------------- IN Decimal -----------------
         + --------------------- +
         | [100]|||[200]|||[300] |
         + --------------------- +
         | [400]|||[500]|||[600] |
         + --------------------- +
----------------- IN Hexadecimal -------------

                        +---- SECOND LEVEL POINTEER (*cstyle_array) - length 4-bytes
                        |
                        V                    SECOND LEVEL
(**cstyle_array)     + --------------------------------------------------------------- +
length 12-bytes  --> | [64]-[00]-[00]-[00]|||[C8]-[00]-[00]-[00]|||[2C]-[01]-[00]-[00] |
|0x16f0b9fc0|        + --------------------------------------------------------------- +
  TOP LEVEL          | [90]-[01]-[00]-[00]|||[F4]-[01]-[00]-[00]|||[58]-[02]-[00]-[00] |
                     + --------------------------------------------------------------- +
--------------------------------------------------
1. We obtain a pointer cstyle_array ----> (0x16f0b9fc0) that refers to the
   first element in the array. This pointer knows that if we increment it, it
   will point to the second element in the array, which is the value `400`.
--------------------------------------------------
2. Dereferencing the double pointer:
Double dereferencing it will giev us the first value which is `100`

*(my_array) --> `100`
--------------------------------------------------
3. Increment the double reference
**(cstyle_array + 1) -> 400
- This one will increment the double pointer by 1-cell, at top level,
  means when we dereferencing this double pointer
  it will give us the second value in top level (rows)

--------------------------------------------------
4. Here, we will convert the double pointer to a single pointer with a size of
   1 byte, which is of type char. We will then increment it by 4 bytes. After
   that, we will cast it again to an integer with a size of 4 bytes and
   dereference it.

*((int*)((char*)cstyle_array + 4)) -> 200
--------------------------------------------------
5. Here, we obtain the second level pointer by first dereferencing the double
   pointer and then casting it to a char with a size of 1 byte. We increment it
   by 4 bytes. After that, we cast it back to an integer pointer and finally
   dereference it.


*(int*)(((char*)(*cstyle_array)) + 4) -> 200
--------------------------------------------------
6. Here, we obtain the first level pointer by dereferencing our double pointer
   `cstyle_array`, then we increment it by 1 byte and its size is 4 bytes. After
   that, we cast it back to an int and dereference it.

*(int*)(((*cstyle_array)) + 1) -> 200
--------------------------------------------------
7. This is analogous to Point 6. We know that the second-level pointer
   `*cstyle_array` occupies 4 bytes in length because we incremented it. When we
   dereference it again, it returns the second element at the second level.

*((*cstyle_array) + 1) -> 200
--------------------------------------------------

```

## String with array as a double pointer

The talk above is similar to a char array which can also be regarded as either
a matrix or an array of arrays (double pointer/ pointer-to-pointer).

- At the first level, we have a normal array containing a string at each index, which
  forms the second level.
- The first-level pointer jumps through the lengths of
  each of the n strings at this level, while the second-level pointer moves
  character by character (as defined).
  - Check the function (`void cstyle_string_array_as_pointer();`) for more
    details on this subject.

```sh
const char* my_char_array_ptr[] = {"Hello","World"};
const char my_char_array[][6] = {"Hello", "World"};

```

## Double Pointers allocated on heap for array of string

In C++, you can allocate a C-style array of strings on the heap using dynamic
memory allocation with pointers. Here's an example of how you can do this:

```cpp
#include <iostream>
#include <cstring>

int main() {
    // Number of strings in the array
    const int numStrings = 3;

    // Allocate an array of pointers to char (C-style strings) on the heap
    char** stringArray = new char*[numStrings];

    // Allocate memory for each individual string and store them in the array
    stringArray[0] = new char[10]; // for example, allocate space for "Hello"
    std::strcpy(stringArray[0], "Hello");

    stringArray[1] = new char[8]; // for example, allocate space for "World!"
    std::strcpy(stringArray[1], "World!");

    stringArray[2] = new char[6]; // for example, allocate space for "C++"
    std::strcpy(stringArray[2], "C++");

    // Access and print the strings
    for (int i = 0; i < numStrings; i++) {
        std::cout << stringArray[i] << std::endl;
    }

    // Deallocate memory for individual strings
    for (int i = 0; i < numStrings; i++) {
        delete[] stringArray[i];
    }

    // Deallocate memory for the array of pointers
    delete[] stringArray;

    return 0;
}
```

In this code:

1. We first allocate an array of pointers to char (`char**`) on the heap to
   store C-style strings.
2. Then, we allocate memory for each individual string using `new[]` and store
   the pointers to these strings in the array.
3. We use `strcpy` to copy the string values into the allocated memory.
4. After using the strings, we must deallocate the memory for each individual
   string using `delete[]`.
5. Finally, we deallocate the memory for the array of pointers using
   `delete[]`.

Make sure to handle errors and exceptions appropriately in a real-world
scenario, and consider using C++'s `std::string` or other modern data
structures when possible, as they provide better memory management and safety.

## More Insights

I can help you fix that line of code and also show you how to allocate a
2D array of characters (C-style strings) on the heap. Here's the corrected
code:

1. Allocating an array of pointers to C-style strings (1D array):

```cpp
char* my_cstyle_char_ptr_on_heap[] = {"Hello", "World"};

// Deallocate memory for individual strings
for (int i = 0; i < 2; i++) {
    delete[] my_cstyle_char_ptr_on_heap[i];
}
```

- In this code, we don't need to use `new` to allocate memory for individual
  strings because string literals like "Hello" and "World" are stored in
  read-only memory, so there's no need to manage their memory explicitly.
  However, you should not use `delete[]` to deallocate these string literals
  because they are not dynamically allocated.

2. Allocating a 2D array of characters (C-style strings) on the heap:

```cpp
const int numStrings = 2;
const int maxStringLength = 10; // Adjust this as needed

char** my_2d_cstyle_char_array = new char*[numStrings];

for (int i = 0; i < numStrings; i++) {
    my_2d_cstyle_char_array[i] = new char[maxStringLength];
}

// Initialize and copy strings
std::strcpy(my_2d_cstyle_char_array[0], "Hello");
std::strcpy(my_2d_cstyle_char_array[1], "World");

// Access and print the strings
for (int i = 0; i < numStrings; i++) {
    std::cout << my_2d_cstyle_char_array[i] << std::endl;
}

// Deallocate memory for individual strings
for (int i = 0; i < numStrings; i++) {
    delete[] my_2d_cstyle_char_array[i];
}

// Deallocate memory for the array of pointers
delete[] my_2d_cstyle_char_array;
```

In this code:

- We first allocate an array of pointers to char (`char*`) on the heap, and
  then allocate memory for each individual string within a loop.
- We use `std::strcpy` to copy the string values into the allocated memory.
- After using the strings, we deallocate the memory for each individual string
  and the array of pointers.

Remember to adjust `numStrings` and `maxStringLength` as needed for your
specific use case.

- You can allocate both of these types of string arrays on the heap in a
  similar manner. Here's how you can do it:

1. Allocating an array of pointers to C-style strings on the heap:

```cpp
const char* my_array[] = {"Hello", "World"};
const int numStrings = sizeof(my_array) / sizeof(my_array[0]);

// Allocate an array of pointers to C-style strings on the heap
const char** my_array_on_heap = new const char*[numStrings];

// Copy the pointers to the heap-allocated array
for (int i = 0; i < numStrings; i++) {
    my_array_on_heap[i] = my_array[i];
}

// Deallocate memory for the array of pointers
delete[] my_array_on_heap;
```

2. Allocating a 2D array of characters (C-style strings) on the heap:

```cpp
const char my_array[][6] = {"Hello", "World"};
const int numStrings = sizeof(my_array) / sizeof(my_array[0]);

// Define the maximum string length
const int maxStringLength = 6; // Adjust this as needed

// Allocate a 2D array of characters on the heap
char** my_2d_array_on_heap = new char*[numStrings];

for (int i = 0; i < numStrings; i++) {
    my_2d_array_on_heap[i] = new char[maxStringLength];

    // Copy the strings
    std::strcpy(my_2d_array_on_heap[i], my_array[i]);
}

// Deallocate memory for individual strings
for (int i = 0; i < numStrings; i++) {
    delete[] my_2d_array_on_heap[i];
}

// Deallocate memory for the array of pointers
delete[] my_2d_array_on_heap;
```

In both cases, you first determine the number of strings (`numStrings`) in the
original array and then allocate memory accordingly on the heap. You can use
loops to copy the data from the original array to the heap-allocated array, and
don't forget to deallocate the memory properly when you're done using it.
Adjust the `maxStringLength` as needed for your specific use case.

The corrected version:

```cpp
#include <iostream>

int main() {
    const char* my_array[] = {"Hello", "World"};
    const int num_strings = sizeof(my_array) / sizeof(my_array[0]);

    // Allocate an array of pointers to C-style strings on the heap
    const char** my_cstyle_char_ptr_on_heap = new const char*[num_strings];

    // Copy the pointers to the heap-allocated array
    for (int i = 0; i < num_strings; i++) {
        my_cstyle_char_ptr_on_heap[i] = my_array[i];
    }

    // Deallocate memory for the array of pointers
    delete[] my_cstyle_char_ptr_on_heap;

    return 0;
}
```

In the corrected code:

1. You allocate an array of pointers to C-style strings on the heap correctly.
2. You copy the pointers from the `my_array` to the `my_cstyle_char_ptr_on_heap` array.
3. You deallocate the memory for the array of pointers correctly.

However, there is no need to delete individual elements in this case because
you are not dynamically allocating memory for the strings themselves. Deleting
individual elements would be necessary if you were allocating memory for the
strings using `new[]`, but in your code, the strings are string literals, and
you should not delete them individually. So, I removed the unnecessary loop for
deleting individual elements.

The corrected code should work as expected to allocate and deallocate the array
of pointers to C-style strings on the heap.

If you want to allocate the individual elements (C-style strings) on the heap using `new[]`, you can do it like this:

```cpp
#include <iostream>
#include <cstring>

int main() {
    const char* my_array[] = {"Hello", "World"};
    const int num_strings = sizeof(my_array) / sizeof(my_array[0]);

    // Allocate an array of pointers to C-style strings on the heap
    const char** my_cstyle_char_ptr_on_heap = new const char*[num_strings];

    // Allocate memory for each C-style string and copy the pointers
    for (int i = 0; i < num_strings; i++) {
        my_cstyle_char_ptr_on_heap[i] = new char[strlen(my_array[i]) + 1]; // +1 for null terminator
        strcpy(const_cast<char*>(my_cstyle_char_ptr_on_heap[i]), my_array[i]);
    }

    // Deallocate memory for each C-style string
    for (int i = 0; i < num_strings; i++) {
        delete[] my_cstyle_char_ptr_on_heap[i];
    }

    // Deallocate memory for the array of pointers
    delete[] my_cstyle_char_ptr_on_heap;

    return 0;
}
```

In this code:

1. We allocate an array of pointers to C-style strings on the heap, as before.
2. Inside the loop, we allocate memory for each C-style string using `new[]`,
   and we also copy the content from the `my_array` into these dynamically
   allocated strings.
3. After we are done with the dynamically allocated strings, we must deallocate
   each of them using `delete[]` within a loop.
4. Finally, we deallocate the memory for the array of pointers using
   `delete[]`.

Make sure to use `strlen` to determine the length of each string and allocate
enough memory, including space for the null terminator (`'\0'`). Also, note the
use of `const_cast` to cast away the `const` qualifier for `strcpy`, as
`strcpy` expects non-const pointers.

---

To print each string in the case where you have allocated individual C-style
strings on the heap, you can simply iterate through the array of pointers and
print each string using a loop. Here's how you can do it:

```cpp
#include <iostream>
#include <cstring>

int main() {
    const char* my_array[] = {"Hello", "World"};
    const int num_strings = sizeof(my_array) / sizeof(my_array[0]);

    // Allocate an array of pointers to C-style strings on the heap
    const char** my_cstyle_char_ptr_on_heap = new const char*[num_strings];

    // Allocate memory for each C-style string and copy the pointers
    for (int i = 0; i < num_strings; i++) {
        my_cstyle_char_ptr_on_heap[i] = new char[strlen(my_array[i]) + 1]; // +1 for null terminator
        strcpy(const_cast<char*>(my_cstyle_char_ptr_on_heap[i]), my_array[i]);
    }

    // Print each string
    for (int i = 0; i < num_strings; i++) {
        std::cout << my_cstyle_char_ptr_on_heap[i] << std::endl;
    }

    // Deallocate memory for each C-style string
    for (int i = 0; i < num_strings; i++) {
        delete[] my_cstyle_char_ptr_on_heap[i];
    }

    // Deallocate memory for the array of pointers
    delete[] my_cstyle_char_ptr_on_heap;

    return 0;
}
```

In the code above, after allocating and copying the strings, we use a loop to
print each string using `std::cout`. Then, we deallocate the memory for each
individual string and the array of pointers as previously described.
