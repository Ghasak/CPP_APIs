# Function Pointers in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Function Pointers in C++](#function-pointers-in-c)
  - [Introduction](#introduction)
    - [1. Basic Function Pointer](#1-basic-function-pointer)
    - [2. Function Pointer as a Parameter](#2-function-pointer-as-a-parameter)
    - [3. Returning a Function Pointer](#3-returning-a-function-pointer)
    - [4. Function Pointer with Arguments](#4-function-pointer-with-arguments)
    - [5. Array of Function Pointers](#5-array-of-function-pointers)
    - [6. Using Function Pointers for Callbacks](#6-using-function-pointers-for-callbacks)
    - [7. Function Pointer to Overloaded Functions](#7-function-pointer-to-overloaded-functions)
    - [8. Function Pointers in Structs](#8-function-pointers-in-structs)
    - [9. Passing Function Pointers to Standard Algorithms](#9-passing-function-pointers-to-standard-algorithms)
    - [10. Using Function Pointers with Templates](#10-using-function-pointers-with-templates)
  - [Function pointers on heap - Possible](#function-pointers-on-heap---possible)
    - [Example: Function Pointer on the Heap](#example-function-pointer-on-the-heap)

<!-- markdown-toc end -->

## Introduction

Function pointers in C++ are pointers that point to a function. They can be used
to call functions indirectly, pass functions as arguments to other functions,
and store arrays of functions. The basic syntax for declaring a function pointer
is as follows:

```cpp
return_type (*pointer_name)(parameter_types);
```

Here are 10 examples, each illustrating a different concept related to function
pointers:

### 1. Basic Function Pointer

```cpp
void greet() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    void (*funcPtr)() = &greet; // Function pointer to a function that takes no arguments and returns void
    (*funcPtr)(); // Calling the function through pointer
}
```

### 2. Function Pointer as a Parameter

```cpp
void execute(void (*func)()) {
    func();
}

void hello() {
    std::cout << "Hello from function pointer!" << std::endl;
}

int main() {
    execute(hello);
}
```

### 3. Returning a Function Pointer

```cpp
void sayHello() {
    std::cout << "Hello" << std::endl;
}

void sayGoodbye() {
    std::cout << "Goodbye" << std::endl;
}

void (*getFunction(bool sayHi))() {
    if (sayHi) return &sayHello;
    else return &sayGoodbye;
}

int main() {
    auto func = getFunction(true);
    func();
}
```

### 4. Function Pointer with Arguments

```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    int (*addPtr)(int, int) = &add;
    std::cout << "Sum: " << addPtr(2, 3) << std::endl;
}
```

### 5. Array of Function Pointers

```cpp
void func1() { std::cout << "Function 1" << std::endl; }
void func2() { std::cout << "Function 2" << std::endl; }
void func3() { std::cout << "Function 3" << std::endl; }
int main() {
    void (*funcArray[3])() = {func1, func2, func3};
    for (int i = 0; i < 3; i++) {
        (*funcArray[i])();
    }
}
```

### 6. Using Function Pointers for Callbacks

```cpp
void repeatThreeTimes(void (*callback)(const std::string&), const std::string& message) {
    for (int i = 0; i < 3; i++) {
        callback(message);
    }
}

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

int main() {
    repeatThreeTimes(printMessage, "Callback message");
}
```

### 7. Function Pointer to Overloaded Functions

```cpp
void display(int i) {
    std::cout << "Integer: " << i << std::endl;
}

void display(double d) {
    std::cout << "Double: " << d << std::endl;
}

int main() {
    void (*funcPtr)(int) = &display;
    funcPtr(10);

    void (*funcPtrD)(double) = &display;
    funcPtrD(10.5);
}
```

### 8. Function Pointers in Structs

```cpp
struct Executor {
    void (*execute)(const std::string&);
};

void print(const std::string& message) {
    std::cout << message << std::endl;
}

int main() {
    Executor exec = {print};
    exec.execute("Hello from struct");
}
```

### 9. Passing Function Pointers to Standard Algorithms

```cpp
bool compare(int a, int b) {
    return a < b;
}

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};
    std::sort(numbers.begin(), numbers.end(), compare);
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
```

### 10. Using Function Pointers with Templates

```cpp
template <typename Func>
void callFunc(Func f) {
    f();
}

void sayHi() {
    std::cout << "Hi!" << std::endl;
}

int main() {
    callFunc(sayHi);
}
```

Each of these examples demonstrates a unique aspect of using function pointers,
from basic usage, passing them as arguments, working with arrays of function
pointers, to employing them in more complex scenarios like callbacks and
templates. Function pointers are a powerful tool in C++, allowing for flexible
and dynamic code design.

## Function pointers on heap - Possible

Creating and using a function pointer on the heap involves dynamically
allocating memory for the function pointer itself, which is quite an unusual
scenario because function pointers typically don't require dynamic allocation.
However, for educational purposes, here's an example of how it could be done.
This example demonstrates allocating a function pointer on the heap and then
using it to call a function.

### Example: Function Pointer on the Heap

```cpp
#include <iostream>

// Function to be pointed to
void greet() {
    std::cout << "Hello, dynamic world!" << std::endl;
}

int main() {
    // Allocate a function pointer on the heap
    void (**heapFuncPtr)() = new void (*)(void);
    *heapFuncPtr = &greet; // Store the address of the function in the allocated memory

    // Calling the function through the pointer on the heap
    (**heapFuncPtr)();

    // Clean up
    delete heapFuncPtr;

    return 0;
}
```

In this example:

1. We define a simple function `greet` that prints a greeting message to the
   console.
2. In the `main` function, we dynamically allocate memory on the heap to store a
   function pointer. The type of `heapFuncPtr` is `void (**)(void)`, which means
   it's a pointer to a function pointer that points to a function taking no
   arguments and returning void.
3. We assign the address of the `greet` function to our dynamically allocated
   function pointer.
4. We use the function pointer to call `greet`.
5. Finally, we clean up by deleting the dynamically allocated function pointer
   to avoid memory leaks.

This demonstrates how to use dynamic memory allocation with function pointers,
although it's worth noting that this approach is rarely necessary in practice.
Function pointers are usually used statically or as part of larger data
structures (like objects) where they don't need to be allocated separately on
the heap.
