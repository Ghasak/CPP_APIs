# Pushing to Stack vs Heap Allocation

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Pushing to Stack vs Heap Allocation](#pushing-to-stack-vs-heap-allocation)
  - [1. How we allocate on Heap](#1-how-we-allocate-on-heap)
    - [Step 1: Allocating Memory on the Heap in C++](#step-1-allocating-memory-on-the-heap-in-c)
    - [Step 2: Dereferencing the Pointer](#step-2-dereferencing-the-pointer)
    - [Step 3: ASCII Diagram of Memory](#step-3-ascii-diagram-of-memory)
    - [Step 4: Pointer and Dereferencing](#step-4-pointer-and-dereferencing)
  - [2. Allocation on HEAP for different types](#2-allocation-on-heap-for-different-types)
    - [Allocating an Integer](#allocating-an-integer)
    - [Allocating a Float](#allocating-a-float)
    - [Allocating a String](#allocating-a-string)
    - [Code Example with Deallocation](#code-example-with-deallocation)
  - [3. Why we need allocation for memeory mananged data structures?](#3-why-we-need-allocation-for-memeory-mananged-data-structures)
    - [3.1. Lifetime Management](#31-lifetime-management)
      - [3.1.1. Lifetime Management Example](#311-lifetime-management-example)
    - [3.2. Large Objects](#32-large-objects)
      - [3.2.1. Large Objects](#321-large-objects)
    - [3.3. Shared Ownership](#33-shared-ownership)
      - [3.3.1. Shared Ownership](#331-shared-ownership)
    - [3.4. Polymorphism](#34-polymorphism)
      - [3.4.1. Polymorphism](#341-polymorphism)
    - [3.5. Delayed Initialization](#35-delayed-initialization)
      - [3.5.1. Delayed Initialization](#351-delayed-initialization)
    - [3.6. Example Use Cases](#36-example-use-cases)
    - [3.7. Conclusion](#37-conclusion)

<!-- markdown-toc end -->

## 1. How we allocate on Heap

I will use here a simple example to allocate a primitive data type on the `heap`.

### Step 1: Allocating Memory on the Heap in C++

First, I'll show you how to allocate memory for an `int` on the heap in C++ and
then store the value 255 in it.

```cpp
int* ptr = new int; // Allocate memory for an int on the heap
*ptr = 255;         // Store the value 255 in the allocated memory
```

Here, `ptr` is a pointer that holds the address of the memory block allocated on the heap.

### Step 2: Dereferencing the Pointer

To access or modify the value that `ptr` points to, you use the dereference operator `*`.

```cpp
int value = *ptr;   // Dereferencing the pointer to get the value
```

### Step 3: ASCII Diagram of Memory

Now, let's create an ASCII diagram to represent the memory layout. Assume the
memory address of the allocated block is `0x1000` (just an example). Each
memory cell is one byte, and an `int` is typically 4 bytes on most systems. The
value 255 in hexadecimal is `0xFF`.

Memory layout (each cell is 1 byte):

```sh
 Address    | 0x1000 | 0x1001 | 0x1002 | 0x1003 |
------------|--------|--------|--------|--------|
 Hex Value  |   00   |   00   |   00   |   FF   |
```

In this representation:

- `0x1000` to `0x1003` are the addresses of the 4 bytes allocated for the
  integer.
- Since integers are stored in little-endian format on most systems, the least
  significant byte (`FF` for 255) is stored in the lowest address (`0x1003` in
  this case), and the other bytes are filled with zeros.

### Step 4: Pointer and Dereferencing

- `ptr` (Pointer): Holds the address `0x1000`.
- `*ptr` (Dereferencing): Accesses the 4-byte block starting at `0x1000` and
  interprets it as an integer, which in this case is `255`.

Here's a simplified diagram to illustrate this:

```sh
 Pointer
   |
   |    Memory (Heap)
   v    +----------------------------+
 ptr -- | 0x1000: 00 | 00 | 00 | FF  |
        +----------------------------+
```

In this diagram, the arrow shows that `ptr` points to the memory location
`0x1000`, and the 4-byte block starting at `0x1000` represents the integer 255.

## 2. Allocation on HEAP for different types

To allocate memory on the heap for different data types in C++ and initialize
them with specific values, you typically use the `new` operator. Here's how you
can do it for an integer, a float, and a string, initializing each with a
specific value:

### Allocating an Integer

```cpp
int* intPtr = new int(255); // Allocate an int on the heap and initialize it to 255
```

### Allocating a Float

```cpp
float* floatPtr = new float(255.0f); // Allocate a float on the heap and initialize it to 255.0
```

### Allocating a String

For a string, since `std::string` is a class, you can allocate it on the heap as well:

```cpp
std::string* stringPtr = new std::string("Hello World"); // Allocate a string on the heap and initialize it
```

### Allocated a C-style array

```cpp
int* my_array_ptr_on_heap = new int[3]; // allocated on heap
delete[] my_array_ptr_on_heap;
my_array_ptr_on_heap = nullptr;
```

- The equavlent pushed to stack array is:
  - Notice that `my_array_on_stack` is a pointer for this array which points to first element on stack.

```cpp
int my_array_on_stack[3];
```

### Code Example with Deallocation

Here's a complete example that includes all three allocations and proper deallocation of the memory:

```cpp
#include <iostream>
#include <string>

int main() {
    // Allocating on the heap
    int* intPtr = new int(255);
    float* floatPtr = new float(255.0f);
    std::string* stringPtr = new std::string("Hello World");

    // Using the allocated memory
    std::cout << "Integer value: " << *intPtr << "\n";
    std::cout << "Float value: " << *floatPtr << "\n";
    std::cout << "String value: " << *stringPtr << "\n";

    // Deallocating the memory
    delete intPtr;
    delete floatPtr;
    delete stringPtr;

    return 0;
}
```

In this code:

- `new` is used to allocate memory for an `int`, `float`, and `std::string` on
  the heap.
- The allocated memory is initialized with the values `255`, `255.0f`, and
  `"Hello World"`, respectively.
- The `delete` operator is used to free the memory when it is no longer needed.

Remember, it's crucial to match every `new` with a `delete` to avoid memory leaks.

## 3. Why we need allocation for memeory mananged data structures?

Is there a reason for dynamically allocating memory for a memory-managed data structure like `std::vector` and `std::string`?

- Allocating memory-managed data structures like `std::vector` or `std::string`
  on the heap can be useful in certain scenarios. While these data structures
  internally manage their own memory (growing and shrinking dynamically as
  needed), there are reasons why you might want to allocate them on the heap:

### 3.1. Lifetime Management

If you want the object's lifetime to extend beyond the scope in which it was
created, heap allocation is necessary. For instance, if you create a
`std::vector` inside a function and want to retain that vector after the
function returns, allocating it on the heap is one way to achieve this.

#### 3.1.1. Lifetime Management Example

```cpp
#include <iostream>
#include <vector>

std::vector<int>* createVector() {
    std::vector<int>* vec = new std::vector<int>({1, 2, 3});
    return vec;
}

int main() {
    std::vector<int>* myVec = createVector();
    // Use myVec...
    delete myVec;
    return 0;
}
```

In this example, `createVector()` creates a `std::vector` on the heap, which lives beyond the scope of the function.

### 3.2. Large Objects

When dealing with very large objects, allocating them on the heap can help
avoid stack overflow. The stack size is usually limited (often around a few
MB), but the heap can accommodate much larger objects, limited primarily by the
overall memory available.

#### 3.2.1. Large Objects

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int>* largeVec = new std::vector<int>(1000000); // A large vector
    // Use largeVec...
    delete largeVec;
    return 0;
}
```

Allocating a very large `std::vector` on the heap helps to avoid stack overflow.

### 3.3. Shared Ownership

If the data structure needs to be shared among multiple owners or parts of your
program, and its lifetime is not tied to a specific scope, heap allocation
combined with smart pointers (like `std::shared_ptr`) can be an effective
strategy. This ensures automatic and safe memory management, with the object
being deleted when no longer needed.

#### 3.3.1. Shared Ownership

```cpp
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::shared_ptr<std::vector<int>> sharedVec = std::make_shared<std::vector<int>>(std::vector<int>{1, 2, 3});
    // sharedVec can be safely shared across different parts of the program
    return 0;
}
```

Here, `sharedVec` is a smart pointer that can be shared across multiple parts
of the program, managing the vector's lifetime automatically.

### 3.4. Polymorphism

In cases where polymorphism is used (especially with classes that have virtual
functions), objects are often allocated on the heap. For instance, if you have
a base class pointer and you want it to point to an instance of a derived
class, heap allocation is commonly used.

#### 3.4.1. Polymorphism

Polymorphism typically applies to objects rather than standard containers like
`std::vector`, but for illustration, let's consider a scenario with a base and
derived class:

```cpp
#include <iostream>
#include <vector>
#include <memory>

class Base {
public:
    virtual void print() = 0;
    virtual ~Base() {}
};

class Derived : public Base {
private:
    std::vector<int> vec;
public:
    Derived() : vec({1, 2, 3}) {}
    void print() override {
        for (int i : vec) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    std::unique_ptr<Base> obj = std::make_unique<Derived>();
    obj->print();
    return 0;
}
```

The `Derived` class contains a `std::vector`, and we use polymorphism to handle it through a base class pointer.

### 3.5. Delayed Initialization

Sometimes, you may not have the data necessary to initialize an object at the
point of its creation. Allocating such objects on the heap allows you to delay
their initialization until the required data is available.

#### 3.5.1. Delayed Initialization

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int>* vecPtr = nullptr;

    // Initialization is delayed until the data is available
    vecPtr = new std::vector<int>{1, 2, 3};

    // Use vecPtr...
    delete vecPtr;
    return 0;
}
```

### 3.6. Example Use Cases

- **Long-Lived Data Structures in Applications:** In a server application, you
  might have a `std::vector` or `std::string` that stores data which needs to
  persist for the duration of a client session, which could outlive the scope in
  which it was created.

- **Large Data Processing:** For applications dealing with large datasets (such
  as image processing or scientific computations), using heap-allocated
  `std::vector` can prevent stack overflow issues.

- **Shared Resources in Concurrent Programming:** In multi-threaded
  applications, shared resources can be managed by `std::shared_ptr<std::vector>`
  or `std::shared_ptr<std::string>`, ensuring thread-safe reference counting and
  automatic memory management.

In this example, the `std::vector` is not initialized until the necessary data
becomes available.

Each of these examples illustrates a different use case for heap-allocated
memory-managed data structures in C++. The use of heap allocation here depends
on the specific needs of the application, such as managing the lifetime,
handling large data, sharing resources, using polymorphism, or delaying the
initialization of an object.

### 3.7. Conclusion

While it's true that `std::vector` and `std::string` manage their internal
memory, the decision to allocate these objects on the heap is more about the
control over their lifetime and the size of data they manage, rather than just
about memory management. It's a design choice that depends on the specific
requirements and constraints of your application.
