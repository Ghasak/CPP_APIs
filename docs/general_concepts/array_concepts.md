# Array and Lists in action

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Array and Lists in action](#array-and-lists-in-action)
  - [Associated code](#associated-code)
  - [C-style array](#c-style-array)
    - [Size of array](#size-of-array)
  - [std::array](#stdarray)
    - [How to obtain a pointer from std::array simmilar to C-style array](#how-to-obtain-a-pointer-from-stdarray-simmilar-to-c-style-array)
    - [Compare C-style array vs std::array](#compare-c-style-array-vs-stdarray)
    - [Stack vs Allocation on Heap C-Style array](#stack-vs-allocation-on-heap-c-style-array)

<!-- markdown-toc end -->

Here, I will work on the array including all the variations such as:

- How the array works in depth?
- Types of arrays and lists.
- Allocation on heap, push on stack.
  - Growable in size vs fixed sized
- C-style array as a pointer
- Data containers similar to the `array`/`list`.

## Associated code

The code assoicated is located at `../src/concepts/array_and_list/`.

## C-style array

This is the basics, and we use it for fixed size daata container.

- Array hold a series of values, all of the same type.
- Array name is merely a pointer (memeory address integer value).

`int my_array[3];` Lets examine this repesentation:

- `my_array` is a pointer `memeory address` that refers to the first byte of the array.
- It has `3` int values stored and initialized with `0` for each element in this array.
- Each of these `3` elements contains a defined `int` block, and we know that the int block is just `4` bytes, so we should have
- Number of elements for the array is starting form 0 to N+1, where N is number of elements

```sh
[------ idx:0    ---------] [------ idx:1    ---------] [------ idx:2    ---------] [------ idx:3    ---------]   <--- Array Index
[------ 1st byte ---------] [------ 2nd byte ---------] [------ 3rd byte ---------] [------ 4th byte ---------]   <--- Byte repesentation
[0][0]-[0][0]-[0][0]-[0][0]=[0][0]-[0][0]-[0][0]-[0][0]=[0][0]-[0][0]-[0][0]-[0][0]=[0][0]-[0][0]-[0][0]-[0][0]   <--- Hexdecimal repesentation (memeory profile)
# Hexdecimal repesentation:
# Each element is 4-byte, and each byte is 2-bits in Hexdecimal, or 8-bits in binary
# Hexdecimal representation can take the form for 1-byte of [x][x], where x can
# be {x: 0,1,2,3...A,B,C,D,E,F}, up to 15, which is the `Hexdecimal` # You can
also write [x][x] in form of [xx] as:
[00][00][00][00]-[00][00][00][00]-[00][00][00][00]-[00][00][00][00]
```

### Size of array

```sh
size_t arraySize { sizeof(my_array) / sizeof(my_array[0]) };
```

## std::array

- This array is a C++ fixed-sized container called `std::array`, defined in
  `<array>`. It's basically a thin wrapper around C-style array.
- It has more advantages instead of C-style arrays,
  - It always know its own size,
  - It is not automatically cast to a pointer to avoid certain types of bugs,
  - It have itertors to easily loop over the elements.

```cpp
array<int, 3> my_array {1, 2, 3};
std::cout << "Array size  = " <<  my_array.size() << std::endl;
std::cout << "2nd element = " <<  my_array[1] << std::endl;
```

- C++ supports so-called `class argument deduction` `CTAD` (see Chapter `12`-
  Marc Gregoirre - Professional C++ )
- Both the C-style arrays and the std::arrays have a fixed size, which must be
  known aat compile time. They cannot grow or shrink at run time.

### How to obtain a pointer from std::array simmilar to C-style array

In C++, when you use the name of a C-style array, it can decay into a pointer to
its first element in certain contexts.

```cpp
int my_array1[] = {5};  // This declares an array with one element.
```

you can indeed obtain a pointer to the first element like this:

```cpp
int* ptr = my_array1;  // 'ptr' now points to the first element of 'my_array1'.
```

Regarding `std::array`, it's a container that behaves differently from a
C-style array. It does not decay to a pointer automatically. To get a pointer
to the first element of an `std::array`, you can use its `data()` member
function:

```cpp
std::array<int, 3> my_array2 = {5, 0, 0}; // Initializing with 3 elements
int* ptr2 = my_array2.data(); // 'ptr2' points to the first element of 'my_array2'.
```

To change the second element of the arrays using pointers, you can perform
pointer arithmetic. Here's how you can do it for both arrays:

```cpp
// For the C-style array (although it has only one element in this example)
if(sizeof(my_array1) / sizeof(my_array1[0]) > 1) {
    *(ptr + 1) = 3;  // This would change the second element, but our array has only one element.
}

// For the std::array
if(my_array2.size() > 1) {
    *(ptr2 + 1) = 3; // This changes the second element of 'my_array2' to 3.
}
```

Remember that accessing or modifying elements beyond the size of the array
leads to undefined behavior, so always ensure the array is large enough for the
operations you're performing.

### Compare C-style array vs std::array

Here's a comparison table between C-style arrays and `std::array` in C++,
highlighting various aspects including the decay to a pointer using the
`.data()` method for `std::array`:

| idx | Feature/Aspect                   | C-style Array                                                      | `std::array`                                                                          |
| --- | -------------------------------- | ------------------------------------------------------------------ | ------------------------------------------------------------------------------------- |
| 01  | **Type**                         | Basic array type                                                   | Class template in the standard library                                                |
| 02  | **Size Specification**           | Defined at declaration (fixed size)                                | Fixed size, specified as template parameter                                           |
| 03  | **Size Flexibility**             | Fixed size, cannot be resized                                      | Fixed size, cannot be resized                                                         |
| 04  | **Memory Allocation**            | Stack (usually, unless using `new`)                                | Stack (as it's a container)                                                           |
| 05  | **Element Access**               | By index, e.g., `array[0]`                                         | By index, e.g., `array[0]` or `array.at(0)` with bounds checking                      |
| 06  | **Decay to Pointer**             | Automatically decays to pointer to first element                   | Requires `.data()` to get pointer to first element                                    |
| 07  | **Safety Features**              | No bounds checking                                                 | Bounds checking with `.at()`                                                          |
| 08  | **Standard Container Functions** | Not available                                                      | Available (e.g., `.size()`, `.begin()`, `.end()`)                                     |
| 09  | **Iteration**                    | Manual indexing or pointer arithmetic                              | Can use range-based for loops, iterators                                              |
| 10  | **Initialization**               | Can be partially initialized                                       | Always fully initialized (default-initialized if not explicitly)                      |
| 11  | **Direct Memory Access**         | Easy, as it's inherently a pointer                                 | Possible through `.data()`                                                            |
| 12  | **Compatibility**                | Compatible with C functions expecting arrays                       | Not directly compatible, use `.data()` for C compatibility                            |
| 13  | **Performance**                  | Slightly faster for some operations due to less abstraction        | Slightly slower due to additional abstraction, but safer and more features            |
| 14  | **Use Case**                     | Suitable for simple, fixed-size arrays and interfacing with C code | Preferred for modern C++ development, offering safety and standard container features |

This table outlines the main differences and similarities. Note that while
`std::array` provides more features and safety, C-style arrays may still be
used for legacy code or for interfacing with C APIs. The choice between the two
often depends on the specific requirements of the application and the
programming environment.

### Stack vs Allocation on Heap C-Style array

Allocation on `Heap` for a `C-style` array assoicated with the keyword `new`. We
need to delete the assoicated data from the allocated memeory also we need to
safely ensure no one will use this pointer by setting it to `nullptr`.

```cpp
    int my_array[3]{};                       // pushed to stack
    int* my_array_ptr_on_heap = new int[3]; // allocated on heap
    delete[] my_array_ptr_on_heap;
    my_array_ptr_on_heap = nullptr;
```

## Std::vector

Assume we want to keep the `std::vector` which is allocated on heap. Assume the following case

```cpp

    {
        std::vector<int>* my_vector_heap_ptr = new std::vector<int>({10, 20, 30});
        int size = my_vector_heap_ptr->size();
    }
    for (size_t i = 0; i < (*my_vector_heap_ptr).size(); i++) {
        LOG(INFO) << RED << (*my_vector_heap_ptr)[i] << RESET;
    }

    my_vector_heap_ptr = nullptr;
    delete my_vector_heap_ptr;

```

- The above code will not works instead we can use:

## CStyle Core Design Lacking Feature

Can return cstyle as a value instead of a pointer for same example? **Remember**
the `C-style` array decays to a pointer when you call it without an index
brackets `[]`.

Returning a C-style array directly by value from a function in C++ is not
directly possible due to the language's design. C++ does not allow functions to
return arrays by value because arrays cannot be copied in the same way as other
types. When you try to return an array from a function, what you're actually
returning is a pointer to the first element of the array, which, as we've
discussed, leads to issues with scope and lifetime if the array is allocated on
the stack.

However, there are alternative methods to achieve similar functionality,
encapsulating the array in a way that it can be returned by value. Here are a
couple of methods:

### 1. Wrapping the Array in a Struct or Class

One workaround is to wrap the array in a struct or class. This allows the entire
object, including the array, to be returned by value. The struct or class can
then be copied or returned, effectively passing the array by value.

```cpp
struct ArrayWrapper {
    int my_array[5];
};

ArrayWrapper myArrayFunction() {
    ArrayWrapper aw;
    // Initialize aw.my_array here
    return aw;
}
```

### 2. Using `std::array` or `std::vector`

As previously mentioned, a more modern and convenient approach is to use
`std::array` for fixed-size arrays or `std::vector` for dynamic arrays. These
containers are part of the C++ Standard Library and are designed to be safely
returned from functions by value. They manage the underlying array memory and
support copy and move semantics, making them safe and efficient to pass around.

#### Returning a `std::array`:

```cpp
#include <array>

std::array<int, 5> myArrayFunction() {
    std::array<int, 5> my_array{};
    // Initialize my_array here
    return my_array;
}
```

#### Returning a `std::vector`:

```cpp
#include <vector>

std::vector<int> myArrayFunction() {
    std::vector<int> my_array(5);
    // Initialize my_array here
    return my_array;
}
```

Both `std::array` and `std::vector` can be returned by value from a function,
and the compiler optimizations like Return Value Optimization (RVO) and move
semantics in C++11 and later versions make this operation efficient.

### Conclusion

While you cannot return a raw C-style array by value directly due to the
language's limitations, wrapping the array in a struct or class or using C++
Standard Library containers like `std::array` or `std::vector` provides a safe
and modern approach to achieve similar functionality.

## Scenario with C-Style Array

is it possible to do the following

```cpp
int* CreateArray(){
              int array[5]{1,2,3,4,5};
              return array;
}
```

Then using in the main()

```cpp
int my_array = *CreateArray();
int size = sizeof(my_array[]) / sizeof(my_array[0]);
for (int i = 0; i < size; i++) {
    std::cout << "Retrun an array from a stack -> " << my_array[] << std::endl;
}
```

The code snippet you've provided contains several issues and misconceptions
about handling arrays in C++. Let's address these issues one by one:

### Issue with `CreateArray` Function
The `CreateArray` function attempts to return a pointer to a local array `array`
that is allocated on the stack. This is problematic because the array will be
destroyed once the function exits, leaving the returned pointer dangling.
Accessing the memory through this pointer will result in undefined behavior.

### Problem with Dereferencing and Size Calculation
The line `int my_array = *CreateArray();` in your `main()` function attempts to
copy the first element of the array returned by `CreateArray` into a single
integer variable, not the entire array. This is because the dereference operator
`*` applied to a pointer will yield the value pointed to, not the entire array.

Moreover, the expression `sizeof(my_array[]) / sizeof(my_array[0])` is
syntactically incorrect and will not compile. `sizeof` cannot be applied to a
function return value in the way you've attempted, and `my_array` is declared as
an `int`, not an array, so you cannot use `my_array[]` syntax or attempt to
calculate its size this way.

### Iterating Over the Array
The loop and the way you attempt to print the array elements are also incorrect.
Since `my_array` is an integer, not an array, the syntax `my_array[]` is
invalid.

### Correct Approach
If you want to return an array from a function and use it in `main()`, consider
the following correct approaches:

- **Dynamic Allocation**: Allocate the array on the heap and return a pointer
  (but remember to `delete[]` it to avoid memory leaks).
- **Use `std::vector` or `std::array`**: These are much safer and more flexible
  options in C++.

Here's how you can correctly use a dynamically allocated array:

```cpp
#include <iostream>

int* CreateArray() {
    int* array = new int[5]{1, 2, 3, 4, 5};
    return array;
}

int main() {
    int* my_array = CreateArray();
    int size = 5; // You need to manage size separately
    for (int i = 0; i < size; i++) {
        std::cout << "Return an array from a stack -> " << my_array[i] << std::endl;
    }
    delete[] my_array; // Don't forget to free the memory
    return 0;
}
```

If you decide to use `std::vector`, it simplifies memory management and size
handling:

```cpp
#include <iostream>
#include <vector>

std::vector<int> CreateVector() {
    return std::vector<int>{1, 2, 3, 4, 5};
}

int main() {
    std::vector<int> my_vector = CreateVector();
    for (int i = 0; i < my_vector.size(); i++) {
        std::cout << "Return an array from a stack -> " << my_vector[i] << std::endl;
    }
    return 0;
}
```

These approaches are much safer and idiomatic in C++.
