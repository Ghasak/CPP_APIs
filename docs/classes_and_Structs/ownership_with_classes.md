# OwnerShip with Classes

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [OwnerShip with Classes](#ownership-with-classes)
    - [-](#-)
    - [Classs Handle Move Copy and Assignment](#classs-handle-move-copy-and-assignment)
    - [How these methods works](#how-these-methods-works)
        - [Expected Output:](#expected-output)
    - [When an object moves](#when-an-object-moves)
        - [1. Return by Value](#1-return-by-value)
        - [2. Temporary Objects](#2-temporary-objects)
        - [3. Function Arguments Passed with `std::move`](#3-function-arguments-passed-with-stdmove)
        - [4. Moving Elements in Containers](#4-moving-elements-in-containers)
        - [5. Assignments](#5-assignments)
        - [6. Initialization and Assignment with `std::move`](#6-initialization-and-assignment-with-stdmove)
        - [7. Swapping](#7-swapping)
        - [8. Standard Library Functions and Classes](#8-standard-library-functions-and-classes)
        - [9. Automatic Moves](#9-automatic-moves)

<!-- markdown-toc end -->

Ownership in C++, particularly in the context of modern C++ memory management,
refers to the concept of which part of a program is responsible for managing the
lifecycle of a piece of memory. This includes knowing when to allocate and
deallocate memory. Ownership is crucial for preventing memory leaks, avoiding
double frees, and ensuring that memory is efficiently used. Unique pointers
(`std::unique_ptr`), shared pointers (`std::shared_ptr`), and weak pointers
(`std::weak_ptr`) are all part of C++'s smart pointers mechanism designed to
handle ownership in a safer, more automatic way.

**Unique Pointers (`std::unique_ptr`):** These take exclusive ownership of a
resource. Only one unique pointer can own a particular resource at a time. When
the unique pointer goes out of scope, the resource is automatically reclaimed.

**Shared Pointers (`std::shared_ptr`):** These allow multiple pointers to own a
single resource. The resource is only reclaimed when the last shared pointer
owning the resource is destroyed or reset.

**Weak Pointers (`std::weak_ptr`):** These are used in conjunction with shared
pointers to avoid circular references which can lead to memory leaks. They do
not own the resource; they only provide access to an object owned by one or more
shared pointers.

### Scenarios Where a Copy of Data Occurs

In C++, copies of objects can occur in various situations, particularly in terms
of function parameters, return values, and other considerations:

**Function Parameters:**

1. **Pass-by-value:** When an object is passed to a function by value, a copy of
   the object is made. This can be costly for large objects but is safe since
   modifications inside the function do not affect the original object.

2. **Pass-by-reference-to-const:** No copy is made, but it ensures that the
   function does not modify the argument. It’s efficient for passing large
   objects.

**Return Objects:**

1. **Return by value:** Returning an object by value from a function typically
   involves copying the object. However, modern C++ compilers apply Return Value
   Optimization (RVO) and Named Return Value Optimization (NRVO) to eliminate
   these copies when possible.

2. **Return by reference:** This avoids copying, but returning references to
   local objects can lead to dangling references.

3. **Return by moving:** When returning local objects from a function, C++ may
   use move semantics instead of copying if the object is eligible for moving.
   This is more efficient than copying for objects that manage resources like
   memory.

**Other Considerations:**

1. **Assignment:** Copying occurs when one object is assigned to another, unless
   move assignment is used, which transfers resources instead of copying them.

2. **Initialization:** Copy or move constructors are called when objects are
   initialized from another object of the same type, depending on the context.

3. **Containers:** Adding objects to containers like `std::vector` or `std::map`
   can involve copying or moving objects into the container.

4. **Capture by value in lambdas:** When a lambda captures local variables by
   value, a copy of those variables is made.

Understanding when and how copies occur is essential for writing efficient C++
code, especially for objects that manage resources or are expensive to copy.
Modern C++ provides mechanisms like move semantics and smart pointers to help
manage ownership and resource lifecycles more efficiently.

## Classs Handle Move Copy and Assignment

To illustrate a class in C++ that efficiently handles copy and move operations,
assignment, and other necessary functionalities for optimization, let's design a
simple example. This class will demonstrate:

- Copy constructor
- Move constructor
- Copy assignment operator
- Move assignment operator
- Destructor
- Any additional member functions for demonstration

For the sake of this example, let's create a `Resource` class that manages a
dynamic array of integers.

```cpp
#include <algorithm> // For std::copy
#include <cstddef>   // For std::size_t

class Resource {
public:
    // Default constructor
    Resource() : data(nullptr), size(0) {}

    // Constructor with size
    explicit Resource(std::size_t sz) : data(new int[sz]), size(sz) {}

    // Destructor
    ~Resource() {
        delete[] data;
    }

    // Copy constructor
    Resource(const Resource& other) : data(new int[other.size]), size(other.size) {
        std::copy(other.data, other.data + other.size, data);
    }

    // Move constructor
    Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Copy assignment operator
    Resource& operator=(const Resource& other) {
        if (this != &other) { // Prevent self-assignment
            delete[] data; // Free existing resource
            data = new int[other.size];
            size = other.size;
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }

    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data; // Free existing resource
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Example member function
    void setValue(std::size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }

    // Getter for demonstration
    int getValue(std::size_t index) const {
        return index < size ? data[index] : 0; // Simple boundary check
    }

    // Get the size of the data
    std::size_t getSize() const {
        return size;
    }

private:
    int* data;
    std::size_t size;
};
```

This class template provides a robust example of managing dynamic resources in
C++, covering:

- **Resource Management:** Properly allocates and deallocates dynamic memory to
  prevent memory leaks.
- **Copy Semantics:** Implements deep copying to ensure each `Resource` instance
  owns its own copy of the data.
- **Move Semantics:** Transfers ownership of resources from temporary objects to
  persisting ones, optimizing performance by avoiding unnecessary deep copies.
- **Safety Checks:** Includes checks against self-assignment in copy and move
  assignments and provides basic boundary checking in member functions.

By carefully implementing copy and move constructors along with their
corresponding assignment operators, the class ensures efficient management of
resources, especially in contexts involving object copying, moving, and
reassignment. This approach is crucial for classes that manage dynamic memory or
other resources to ensure optimal performance and resource safety in C++.

## How these methods works
To demonstrate the usage of the `Resource` class and its methods in a `main`
function, let's create a few examples. These examples will show how objects of
the `Resource` class behave when they are copied, moved, and assigned. I will
also explain the expected output for each operation.

```cpp
#include <iostream>

int main() {
    // Create a Resource object with 5 elements
    Resource res1(5);
    for (std::size_t i = 0; i < res1.getSize(); ++i) {
        res1.setValue(i, i * 10); // Set values 0, 10, 20, 30, 40
    }

    // Copy constructor usage
    Resource res2 = res1; // Copy res1 into res2
    std::cout << "res2[2] after copy: " << res2.getValue(2) << std::endl; // Expected: 20

    // Move constructor usage
    Resource res3 = std::move(res1); // Move res1 into res3
    std::cout << "res3[3] after move: " << res3.getValue(3) << std::endl; // Expected: 30
    // res1 is now in a moved-from state, so its size should be 0.
    std::cout << "res1 size after move: " << res1.getSize() << std::endl; // Expected: 0

    // Create another Resource object for assignment demonstration
    Resource res4(3); // Smaller size, to show it gets resized
    res4 = res3; // Copy assignment from res3 to res4
    std::cout << "res4[3] after copy assignment: " << res4.getValue(3) << std::endl; // Expected: 30

    // Move assignment usage
    Resource res5(10); // Larger size, to show it gets replaced
    res5 = std::move(res4); // Move assignment, res4 into res5
    std::cout << "res5[3] after move assignment: " << res5.getValue(3) << std::endl; // Expected: 30
    // res4 is now in a moved-from state, so its size should be 0.
    std::cout << "res4 size after move assignment: " << res4.getSize() << std::endl; // Expected: 0

    return 0;
}
```

### Expected Output:

The program above demonstrates the use of the copy constructor, move
constructor, copy assignment operator, and move assignment operator. Here's what
the output should look like:

```
res2[2] after copy: 20
res3[3] after move: 30
res1 size after move: 0
res4[3] after copy assignment: 30
res5[3] after move assignment: 30
res4 size after move assignment: 0
```

**Explanation:**

1. **Copy Constructor:** `res2` is created as a copy of `res1`, so it has the
   same values. Accessing `res2[2]` shows the copied value.

2. **Move Constructor:** `res3` takes ownership of `res1`'s resources, leaving
   `res1` empty (`size = 0`). Accessing `res3[3]` shows the value moved from
   `res1`.

3. **Copy Assignment:** `res4` is assigned the contents of `res3`. Since `res4`
   was originally smaller and different, this demonstrates that the copy
   assignment operator correctly manages the resource allocation and copying.

4. **Move Assignment:** `res5` acquires resources from `res4` through move
   assignment. After the operation, `res4` is empty, indicating that its
   resources were transferred to `res5`.

This example illustrates how the `Resource` class efficiently handles dynamic
memory through copy and move semantics, ensuring optimal resource management and
performance in C++.

## When an object moves

In C++, move operations are a powerful feature introduced with C++11 to optimize
resource management and improve performance by transferring resources from
temporary objects to others, rather than copying them. Move operations are
particularly beneficial for objects that manage resources like dynamic memory,
file handles, or sockets. Here are the scenarios where move semantics come into
play:

### 1. Return by Value
When a function returns an object by value, and the object is local to the
function, the compiler may use move semantics to transfer the object to the
caller, avoiding a copy. This is subject to Return Value Optimization (RVO), but
explicit moves can also be used.

```cpp
Resource createResource() {
    Resource res;
    // Initialize res
    return res; // Move may occur here
}
```

### 2. Temporary Objects
When an operation involves a temporary object, the compiler may use move
semantics to transfer resources to a new object.

```cpp
Resource res = Resource(); // Temporary Resource object moved into res
```

### 3. Function Arguments Passed with `std::move`
When passing an object to a function using `std::move`, you explicitly indicate
that the resources of that object can be moved into the function's parameter.

```cpp
void processResource(Resource res);

Resource res;
processResource(std::move(res)); // Move res into the function
```

### 4. Moving Elements in Containers
When you add elements to or rearrange elements within STL containers (e.g.,
`std::vector`, `std::map`), moves are used if the elements' types support move
semantics.

```cpp
std::vector<Resource> vec;
vec.push_back(Resource()); // Temporary Resource object moved into the vector
```

### 5. Assignments
Move assignment operators are invoked when an object is assigned the value of a
temporary object or an object explicitly marked for moving.

```cpp
Resource res1, res2;
res1 = std::move(res2); // Move assignment
```

### 6. Initialization and Assignment with `std::move`
When initializing or assigning to an object from another object using
`std::move`, the move constructor or move assignment operator is called,
transferring the resources.

```cpp
Resource res1;
Resource res2 = std::move(res1); // Move construction
```

### 7. Swapping
When swapping two objects, move semantics are employed to efficiently exchange
their resources.

```cpp
Resource res1, res2;
std::swap(res1, res2); // Uses move semantics if available
```

### 8. Standard Library Functions and Classes
Many standard library functions and classes use move semantics to transfer
resources. For example, `std::thread` objects can be moved but not copied,
reflecting the transfer of ownership of the thread execution.

### 9. Automatic Moves
The compiler may automatically apply move semantics in situations where it knows
an object is about to be destroyed and cannot be accessed thereafter, enhancing
efficiency without requiring explicit use of `std::move`.

Move semantics are a key part of modern C++'s resource management, reducing
unnecessary copying and enhancing performance, especially for resource-intensive
applications.
