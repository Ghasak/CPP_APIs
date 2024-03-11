# Move Semantics in C++

This is the second part after reading the `./lvalues_and_rvalues_in_cpp.md`
module, as we will need to understand the meaning of the `lvalue/rvalue` and
`lvalue-reference/rvalue-reference`.

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Move Semantics in C++](#move-semantics-in-c)
    - [My Understanding](#my-understanding)
    - [Explanation](#explanation)
        - [Core Concepts](#core-concepts)
            - [Lvalues and Rvalues](#lvalues-and-rvalues)
            - [std::move](#stdmove)
            - [Move Constructor and Move Assignment Operator](#move-constructor-and-move-assignment-operator)
        - [Benefits of Move Semantics](#benefits-of-move-semantics)
        - [Example: Move Semantics in General Use](#example-move-semantics-in-general-use)
    - [When Move Semantics Occur?](#when-move-semantics-occur)
        - [1. Directly Using `std::move`](#1-directly-using-stdmove)
        - [2. Returning Objects from Functions](#2-returning-objects-from-functions)
        - [3. Passing Temporary Objects to Functions](#3-passing-temporary-objects-to-functions)
        - [4. Storing Objects in Containers](#4-storing-objects-in-containers)
        - [5. Moving Elements Between Containers](#5-moving-elements-between-containers)
        - [Checking Against RVO (Return Value Optimization)](#checking-against-rvo-return-value-optimization)
        - [Common Code Practices](#common-code-practices)

<!-- markdown-toc end -->

## My Understanding

Now, we will go into details of `move_semantics` in C++.

- Let's just say that we have a class which has a char pointer of data as well as
  some kind of size this is our actual string data so what we want to do
  - The implementation here will allocated on heap twice.

```cpp

+-------------------------------------------------------+                      +--------------------------------------+
|                 STRING CLASS                          |                      |             ENTITY CLASS             |
+-------------------------------------------------------+                      +--------------------------------------+
| class StringG {                                       |                      |                                      |
| public:                                               |                      |                                      |
|                                                       |                      |  class EntityG {                     |
|     StringG() = default;                              |                      |    public:                           |
|     // Constructor with initialization                |                      |     EntityG(const StringG& name)     |
|     // The object gets created first time             |                      |       : m_Name{name} {}              |
|     StringG(const char* string) {                     |                      |     void Print() { m_Name.Print(); } |
|         printf("Object is Created!\n");               |                      |                                      |
|         m_Size = strlen(string);                      |                      |  private:                            |
|         m_Data = new char[m_Size + 1];                |                      |      StringG m_Name;                 |
|         memcpy(m_Data, string, m_Size + 1);           |                      |  };                                  |
|     }                                                 |                      |                                      |
|     // Copy Constructor - lvalue-reference            |                      +--------------------------------------+
|     StringG(const StringG& other) {                   |   ---+                               |
|         printf("Object is Copied!\n");                |      |    This is the probelm, it called when we just
|         m_Size = other.m_Size;                        |      |--- create an object of this type, which means it
|         m_Data = new char[m_Size + 1];                |      |    get created on the heap using the constructor above
|         memcpy(m_Data, other.m_Data, m_Size + 1);     |      |    and passing it to another constrctor or a function as a parameter
|     }                                                 |   ---+    This will create the problem as we will copy this twice.
|                                                       |             +-----------------------------------------------+
|                                                       |                                    |
|     ~StringG() {                                      |                                    |
|         printf("Object is deleted\n");                |                                    |
|         delete m_Data;                                |                                    |
|     }                                                 |                                    V
|     void Print() {                                    |                       +-----------------------------+
|         for (uint32_t i = 0; i < m_Size; i++) {       |                       |        MAIN FUNCTION        |
|             printf("%c", m_Data[i]);                  |                       +-----------------------------+
|             if (m_Data[i] == '\0') {                  |                       int main(int argc, char* argv[]){
|                 LOG(INFO) << RED << "WOW" << RESET;   |                           Entity entity("GAME ENGINE"); // <=same=> Entity entity(String("GAME ENGINE"))
|             }                                         |                         }
|         }                                             |                                   |
|         printf("\n");                                 |                                   |
|     }                                                 |                                   |
|                                                       |                                   |
| private:                                              |                                   V
|     char* m_Data;                                     |                          +-------------------+
|     uint32_t m_Size;                                  |                          |  RESULTS: We get  |
|                                                       |                          +-------------------+
| };                                                    |                          | Object is Created |
+-------------------------------------------------------+                          | Object is Copied! |
                                                                                   | Object is deleted |   <-  this got deleted for the object that created with the constructor.
                                                                                   | GAME ENGINE       |
                                                                                   | Object is deleted |   <- this got deleted form teh object that got copied in the copy-constructor.
                                                                                   +-------------------+

```

- What we need is a move-semantic concept with the `rvalue-reference` (a temp
  value) to use the resources of original object and pass it to the next one.
  - Bascialy the `move constructor` is doing a shallow copy for the object.
  - Destorying a shallow copied object (the pointers refers to a nullptr) it
    does nothing, but still delete the pointer once existing the scope.
    - Remember the pointer is just a `integer` primitive type (for macOS it is `double int` with 8-bytes size).
- Now, lets see how we can do the `move constructor` by making our object a `rvalue-reference` (as a temp value).

```cpp

+-------------------------------------------------------------+
|                     STRING CLASS                            |
+-------------------------------------------------------------+
|class StringG {                                              |
|  public:                                                    |
|      // Default constructor                                 |                                                          +--------------------------------------+
|      StringG() = default;                                   |                                                          |             ENTITY CLASS             |
|      // Constructor with initialization                     |                                                          +--------------------------------------+
|      /*The object gets created first time*/                 |                                                          |  class EntityG {                     |
|      StringG(const char* string) {                          |                                                          |  public:                             |
|          printf("Object is Created!\n");                    |                                                          |      EntityG(const StringG& name)    |
|          m_Size = strlen(string);                           |                                                          |          : m_Name{name} {}           |
|          m_Data = new char[m_Size + 1];                     |                                                          |                                      |
|          memcpy(m_Data, string, m_Size + 1);                |                                                          |      EntityG(StringG&& name)         |
|      }                                                      |                                                          |          : m_Name{(StringG&&)name} {}|     <----- this will be used for temp values
|                                                             |                                                          |      void Print() { m_Name.Print(); }|            rvalue-reference caller will trigger this
|      /* copy constructor - lvalue-reference*/               |                                                          |                                      |            casting(StringG&&)name <=same=> std::move(name)
|      StringG(const StringG& other) {                        |                                                          |                                      |
|          printf("Object is Copied!\n");                     |                                                          |  private:                            |
|          m_Size = other.m_Size;                             |                                                          |      StringG m_Name;                 |
|          m_Data = new char[m_Size + 1];                     |                                                          |  };                                  |
|          memcpy(m_Data, other.m_Data, m_Size + 1);          |                      +-------------------<-------------  +--------------------------------------+
|      }                                                      |                      |
|                                                             |                      |
|      // move constructor - rvalue-reference                 |                      |
|      StringG(StringG&& other) noexcept {                    |                      |                                        +--------------------------------------------+
|          printf("Object is Moved!\n");                     +|--------------------- + -------------------------------->      |               MAIN FUNCTION                |
|          m_Size = other.m_Size;                             |                                                               +--------------------------------------------+
|          m_Data = other.m_Data;                             |                                                               | int main(int argc, char* argv[]) {         |
|          other.m_Size = 0;                                  |                                                               |         EntityG e = EntityG("GAME ENGINE");|
|          other.m_Data = nullptr;                            |                                                               |   }                                        |
|      }                                                      |                                                               |                                            |
|                                                             |                                                               +--------------------------------------------+
|      ~StringG() {                                           |
|          printf("Destroying object with size %u\n", m_Size);|
|          delete[] m_Data;                                   |
|      }                                                      |
|      void Print() {                                         |
|          for (uint32_t i = 0; i < m_Size; i++) {            |
|              printf("%c", m_Data[i]);                       |
|              if (m_Data[i] == '\0') {                       |
|                  LOG(INFO) << RED << "WOW, set i<=m_Size to |see this message" << RESET;
|              }                                              |
|          }                                                  |
|          printf("\n");                                      |
|      }                                                      |
|                                                             |
|  private:                                                   |
|      char* m_Data;                                          |
|      uint32_t m_Size;                                       |
|  };                                                         |
+-------------------------------------------------------------+

NOTE: why there is only one "Deleted" line being printed on Cherno's terminal, remember that his program halts due to "std::cin.get()". Once he presses Enter, he should see the other "Destroyed" message.
Reason for two destroys: 1 where the hollow object is destroyed + 1 where the actual heap memory is deallocated. You can see the object destroyed with different sizes.
```
- The move consturctor has to be explicity called by using casting to a rvalue-reference, but we prepfer to use the `std::move()`

## Explanation

Move semantics in C++ is a powerful feature introduced with the C++11 standard
that allows developers to optimize resource management and improve the
performance of their applications. It achieves this by enabling the transfer of
resources from temporary objects (which are about to be destroyed) to another
object, rather than copying the resources, which is more expensive in terms of
performance.

### Core Concepts

#### Lvalues and Rvalues

To understand move semantics, it's crucial to grasp the distinction between
lvalues and rvalues:

- **Lvalues** refer to objects that have a persistent state and an identifiable
  location in memory. For example, variables and references are lvalues.
- **Rvalues** are temporary objects that do not have a persistent storage
  location. They are typically used in expressions and cannot be assigned to
  directly.

#### std::move

`std::move` is a standard library function that converts its argument into an
rvalue, enabling the use of move semantics. It does not actually move anything
by itself but allows an object to be moved if a move constructor or move
assignment operator is defined.

#### Move Constructor and Move Assignment Operator

- The **move constructor** initializes a new object by transferring resources
  from an rvalue object to this new object.
- The **move assignment operator** transfers resources from an rvalue object to
  an existing object, replacing its current contents and releasing any owned
  resources.

### Benefits of Move Semantics

Move semantics can significantly improve performance by:

- Reducing unnecessary copying of data, especially for objects that manage
  dynamic memory or other resources.
- Minimizing temporary object creation overhead.
- Enabling efficient transfer of resources between objects, particularly in
  container classes or with objects representing expensive resources like file
  handles or network connections.

### Example: Move Semantics in General Use

```cpp
#include <iostream>
#include <vector>
using namespace std;

// A simple class that demonstrates move semantics
class Buffer {
public:
    int* data;
    size_t size;

    // Constructor
    Buffer(size_t size) : size(size), data(new int[size]) {}

    // Move Constructor
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr; // Leave the moved-from object in a safe state
        other.size = 0;
    }

    // Destructor
    ~Buffer() {
        delete[] data;
    }

    // Move Assignment Operator
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data; // Free the existing resource
            data = other.data; // Transfer resource ownership
            size = other.size;
            other.data = nullptr; // Leave the moved-from object in a safe state
            other.size = 0;
        }
        return *this;
    }

    // Prevent copying
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
};

int main() {
    vector<Buffer> buffers;
    buffers.push_back(Buffer(1024)); // Uses move constructor
    return 0;
}
```

In this example:

- The `Buffer` class manages a dynamic array and demonstrates both move
  constructor and move assignment operator.
- The move constructor and move assignment operator transfer the ownership of
  the dynamic array from one object to another efficiently.
- The `std::vector::push_back` function utilizes the move constructor to add a
  temporary `Buffer` object to the `buffers` vector without unnecessary copying.
- Copying is explicitly disabled to enforce move semantics and prevent
  accidental copies, ensuring efficient resource management.

Move semantics is a critical concept in modern C++ programming, allowing
developers to write more efficient and performant code by optimizing resource
management and minimizing unnecessary copies.

## When Move Semantics Occur?

Move semantics in C++ are triggered under specific circumstances where the
compiler can ascertain that an object is an r-value, meaning it's temporary and
eligible for moving rather than copying. Here are the primary scenarios where
move semantics take precedence over copy semantics, along with examples and best
practices to ensure their effective use:

### 1. Directly Using `std::move`

Explicitly using `std::move` casts an l-value (an object with a name) to an
r-value, signaling that its resources can be moved.

```cpp
SimpleString a(10);
SimpleString b = std::move(a); // Move constructor is called
```

**Best Practice**: Use `std::move` when you know an object will not be used
again and moving it makes sense for performance.

### 2. Returning Objects from Functions

Modern C++ compilers can elide copies when objects are returned from functions,
utilizing move semantics when copy elision isn't possible.

```cpp
SimpleString createString() {
    SimpleString temp(100);
    return temp; // May be moved, not copied, if NRVO doesn't apply
}
```

**Best Practice**: Return objects by value and trust the compiler to optimize
the return either through NRVO (Named Return Value Optimization) or move
semantics.

### 3. Passing Temporary Objects to Functions

When temporary objects are passed to a function, they're considered r-values and
are eligible for moving.

```cpp
void processString(SimpleString str) {
    // do something with str
}

processString(SimpleString(50)); // Temporary SimpleString, move constructor is called
```

**Best Practice**: For functions taking heavy objects, accept them by value if
the function needs a copy. This enables moving for r-values and copying for
l-values.

### 4. Storing Objects in Containers

When objects are added to STL containers like `std::vector`, move semantics are
used if the objects are r-values.

```cpp
std::vector<SimpleString> strings;
strings.push_back(SimpleString(100)); // Move constructor is called
```

**Best Practice**: Emplace methods (`emplace_back`, `emplace`) are preferred
with containers as they construct objects in place and can further optimize
performance.

### 5. Moving Elements Between Containers

When elements are moved from one container to another, move semantics are
utilized.

```cpp
std::vector<SimpleString> vec1, vec2;
vec1.push_back(SimpleString(100));
// Move elements from vec1 to vec2
vec2.push_back(std::move(vec1[0])); // Move constructor is called for the element
```

### Checking Against RVO (Return Value Optimization)

RVO is an optimization technique where the compiler eliminates the temporary
object created to hold a function's return value. RVO can sometimes make it
unclear whether move semantics are being applied because the compiler may
optimize away both copy and move operations.

```cpp
SimpleString getString() {
    return SimpleString(100); // RVO applies, no move or copy constructor is called
}
```

**Best Practice**: Write code as if RVO and move semantics are both working, but
don't rely on them for correctness. Your code should work correctly whether or
not these optimizations are applied.

### Common Code Practices

- **Resource Management**: Ensure classes managing resources implement both move
  and copy operations where appropriate, following the Rule of Five
  (constructor, destructor, copy constructor, copy assignment operator, move
  constructor, and move assignment operator).
- **Noexcept**: Specify move operations as `noexcept`. This is important for
  containers like `std::vector`, which prefer `noexcept` move operations for
  exceptions safety guarantees.
- **Auto and Function Arguments**: Be mindful when using `auto` or passing
  arguments to functions. Ensure you're not inadvertently copying objects when
  intending to move them.

Move semantics and RVO work together to make C++ programs more efficient by
minimizing unnecessary copies. Understanding when and how they apply allows you
to write high-performance C++ code, leveraging modern C++ features.
