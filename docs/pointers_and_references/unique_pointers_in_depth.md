# Unique Pointers in Depth
<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Unique Pointers in Depth](#unique-pointers-in-depth)
    - [Review the raw pointer concept](#review-the-raw-pointer-concept)
    - [Unique Pointers Concept](#unique-pointers-concept)
    - [1.My Understanding](#1my-understanding)
        - [1.1. Smart Pointer - Unique Pointer](#11-smart-pointer---unique-pointer)
    - [1. Raw Pointers vs Unique Pointers](#1-raw-pointers-vs-unique-pointers)
    - [2. Move Ownership of unique pointers](#2-move-ownership-of-unique-pointers)
    - [Passing a Pointer of an object to a function](#passing-a-pointer-of-an-object-to-a-function)
        - [Passing a raw pointer](#passing-a-raw-pointer)
        - [Passing by unique pointer](#passing-by-unique-pointer)

<!-- markdown-toc end -->


## Review the raw pointer concept

```cpp

The connection will break once the pointer reach to
end of its scope and get freed from memory
So, we have to call delete before that can happen.
|
|                +----------------+
+---->   +-------|  Raw Pointer   |  <-- memory address (pointer) stored on stack
         |       +----------------+
         |                        |
    ____ |                        +-----> integer (on x64 machines it is 8-bytes)
   /     \                                 (e.g., 0x00ffabacddx)
   | obj |     <--- Object can be primative, class/struct object,
   \_____/          other data types std::vector, std::string ..etc.

```

Explanation:

- The stack contains local variables, including the raw pointer (ptr).
- This pointer (ptr) is directed towards a specific location in the heap where
  memory has been allocated for an object or primitive data type.
- To avoid memory leaks, it is essential to manually manage this heap memory by
  using 'delete' for the allocated memory when it is no longer needed, before
  the pointer goes out of scope.

```cpp

The concept of a raw pointer in C++:

+-----------------------------------------------------+
|                      STACK                          |
| +------------------+  +--------------------------+  |
| |  Raw Pointer     |  | Other Stack Variables... |  |
| |  (ptr)           |  +--------------------------+  |
| +-------|----------+                                |
|         |                                           |
|         |  (points to memory allocated on the heap) |
+-----------------------------------------------------+
          |
          |
          V
+-----------------------------------------------------+
|                      HEAP                           |
|    +---------------------------+                    |
|    | Memory Allocated for      |                    |
|    | Object/Primitive          |                    |
|    | (e.g., an int, class)     |                    |
|    |                           |                    |
|    +---------------------------+                    |
|    Other dynamically allocated memory...            |
+-----------------------------------------------------+


```

## Unique Pointers Concept

The concept of a unique pointer in C++:

```cpp
+-----------------------------------------------------+
|                       STACK                         |
| +----------------------+  +----------------------+  |
| | Unique Pointer (uptr)|  | Other Stack Variables|  |
| +----------|-----------+  +----------------------+  |
|            |                                        |
|            |  (owns and uniquely points to          |
|            |   memory allocated on the heap)        |
+-----------------------------------------------------+
             |
             |
             V
+-----------------------------------------------------+
|                       HEAP                          |
|                                                     |
|    +----------------------------+                   |
|    | Memory Allocated for       |                   |
|    | Object/Primitive           |                   |
|    | (e.g., an int, class)      |                   |
|    |                            |                   |
|    +----------------------------+                   |
|                                                     |
|    Other dynamically allocated memory...            |
+-----------------------------------------------------+
```

Explanation:

- The stack contains local variables, including the unique pointer (uptr).
- The unique pointer (uptr) owns a specific heap-allocated memory for an object
  or primitive data type, ensuring that only one unique pointer can point to
  that memory at any time.
- When the unique pointer (uptr) goes out of scope, it automatically releases
  the heap memory it owns, thereby preventing memory leaks without manual
  intervention.
- This automatic management of heap memory simplifies resource management and
  improves code safety and reliability.

## 1.My Understanding

- Notice that we create a pointer to an object
- The object can be any type either primitive or more complex data structure
  like classes, structs, enums ..etc.
- Meaning, this pointer can access the object public methods, attributes ..etc.

### 1.1. Smart Pointer - Unique Pointer

- Unique Pointers:
  - The smart unique pointer is just an `integer` on stack depends on the system
    (x64 usually they are 8-bytes)(Later we learn that this address can also
    stored at the heap, like we store set of addresses/pointers using
    std::vector on a heap with new keyword).
  - The smart unique pointer if deleted it will delete all the related data to
    the object it refers to.
  - The main usage is to free the object with all its allocated data on heap
    once it goes out of the scope automatically.

```cpp
+------------------------------+
|        Entity Class          |
+------------------------------+

class Entity{
    public:
        Entity(){
            std::cout
            << "Created Entity!"
            << std::endl;
        }
        ~Entity(){
            std::cout
            <<"Destoryed Entity!"
            << std::endl;
        }
        void Print(){

        }
}

+------------------------------+
|        Main Function         |
+------------------------------+
| #include <memory>
| #include <string>
| #include <iostream>
| int main(int argc, char* argv[]){
|     // Create an inner-scope
|     {                                                                                                                                          <-------+
|         +-----------------------------------------------+                                                                                              |
|         | std::unique_ptr<Entity> entity(new Entity()) ;| <- This is way is possible                                                                   | I
|         +-----------------------------------------------+                                                                                              | N
|         +-------------------------------------------------------------------+                                                                          | N
|         | std::unique_ptr<Entity> entity = std::make_unique<Entity>() ;     | <- this is the most common way                                           | E
|         +-------------------------------------------------------------------+                                                                          | R
|                                                                 ^                                                                                      | -
|     //Accessing the smart pointer using:                        |                                                                                      | S
|     entity->Print();                                            |                                                                                      | C
|     //or                                                        |                                                                                      | O
|     (*entity).Print();                                          +----- make unique with that entity there the primary                                  | P
|     std::cin.get();                                                    reason that that's important                                                    | E
|                                                                        it is for exception safety (will throw an error if its not possible)            | D
|     }                                                                                                                                          <-------+
|                                                                                    +
|                                                                                    |
|                                                                                    |
|                                                                                    +-----> the smart unique pointer is gone and no longer is existed.
|                                                                                            Means the object that it refer to it is already gone too
|
| }

// NOTICE THIS IS NOT ALLOWED IN C++
+-------------------------------------------------------------------------------------------------+
| std::unique_ptr<Entity> entity = new Entity() ; <--- This is not allowed (unique_ptr constructor|
|                                                      is explicit to the brackts). There is no   |
|                                                      inversion constructor, by the C++ library  |
+-------------------------------------------------------------------------------------------------+
```


## 1. Raw Pointers vs Unique Pointers

a simple example of a class named Vec2b which represents a 2D vector with basic
integer coordinates x and y. We will first show how to handle dynamic memory
allocation for this class using a raw pointer, and then how to manage it using
std::unique_ptr from the C++ standard library for better memory management and
safety.

- Here is how you might define the Vec2b class and allocate an instance of it on
  the heap using a raw pointer:

```cpp

+-----------------------------------------+                  +------------------------------------+
|             class Vec2b                 |                  |       main function call           |
+-----------------------------------------+                  +------------------------------------+
|  #include <iostream>                    |                  | int main() {                       |
|  class Vec2b {                          |                  |     // Allocation on the           |
|  public:                                |                  |     // heap using raw pointer      |
|      int x, y;                          |    ----->        |     Vec2b* vec = new Vec2b(10, 20);|  <-- declare the vec, allocated on heap and inialized
|      // constructor                     |                  |     // Access and use              |      (creating an object from the class)
|      Vec2b(int x, int y)                |                  |                                    |
|         : x(x), y(y) {}                 |                  |     vec->print();                  |  <-- Accessing the pointer can be
|      // method for printing             |                  |     // It's crucial to manually    |      done in this scope and all inner-scoped
|      // the object attributes           |                  |     // delete to avoid memory leaks|
|      void print() const {               |                  |     delete vec;                    |  <-- delete the pointer in
|          std::cout << "Vec2b("          |                  | }                                  |      same scope you declared (important)
|                    << x                 |                  +------------------------------------+
|                    << ", "              |
|                    << y                 |
|                    << ")" << std::endl; |
|      }                                  |
|  };                                     |
+-----------------------------------------+

```

- Using std::unique_ptr:
- Now, let's refactor the example to use std::unique_ptr for automatic memory
  management. This approach eliminates the need for explicit delete, as the
  std::unique_ptr will automatically release the allocated memory when it goes out
  of scope or is otherwise destroyed.

```cpp

+-----------------------------------------+                  +------------------------------------+
|             class Vec2b                 |                  |       main function call           |
+-----------------------------------------+                  +------------------------------------+
|  #include <iostream>                    |                  | int main() {                       |
|  #include <memory> // For std::unique_ptr                  |                                    |
|  class Vec2b {                          |                  |     // Allocation on the           |
|  public:                                |                  |     // heap using raw pointer      |
|      int x, y;                          |    ----->        |     std::unqiue_ptr<Vec2b> vec = std::make_unique<Vec2b>(10, 20);   // Allocation on the heap using unique_ptr
|      // constructor                     |                  |     // Access and use              |      (creating an object from the class)
|      Vec2b(int x, int y)                |                  |                                    |
|         : x(x), y(y) {}                 |                  |     vec->print();                  |  <-- Accessing the pointer can be
|      // method for printing             |                  |     // It's crucial to manually    |      done in this scope and all inner-scoped
|      // the object attributes           |                  |     // delete to avoid memory leaks|
|      void print() const {               |                  |                                       <-- No need for explicit delete;
|          std::cout << "Vec2b("          |                  | }                                  |      memory will be automatically released
|                    << x                 |                  +------------------------------------+
|                    << ", "              |
|                    << y                 |
|                    << ")" << std::endl; |
|      }                                  |
|  };                                     |
+-----------------------------------------+

```

- In the second example, std::make_unique<Vec2b>(10, 20) creates a new instance
  of Vec2b on the heap and returns a std::unique_ptr<Vec2b> that owns this newly
  allocated instance.
- The std::unique_ptr takes care of deallocating the memory when it is destroyed
  or when its ownership is transferred, which significantly reduces the risk of
  memory leaks and makes the code cleaner and safer.

## 2. Move Ownership of unique pointers

To move ownership from one std::unique_ptr to another, you should use the
std::move() function from the `utility` header, which casts its argument to an
r-value indicating that it's safe to transfer ownership of the resource. Your
example has a small mistake in calling the .move() method directly on the smart
pointer, which is not correct. Instead, you should use
std::move(smart_ptr_on_heap_object_Vec2b2).

- Here's how you can correctly move ownership from smart_ptr_on_heap_object_Vec2b2
  to smart_ptr_on_heap_object_Vec2b1:

```cpp

#include <iostream>
#include <memory> // For std::unique_ptr
#include <utility> // For std::move

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b1 = nullptr;

    {
        std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b2 = std::make_unique<Vec2b>(200, 300);
        smart_ptr_on_heap_object_Vec2b2->Print();
        smart_ptr_on_heap_object_Vec2b1 = std::move(smart_ptr_on_heap_object_Vec2b2);
    }

    // At this point, smart_ptr_on_heap_object_Vec2b2 is nullptr, and ownership has been transferred to smart_ptr_on_heap_object_Vec2b1
    if (smart_ptr_on_heap_object_Vec2b1) {
        smart_ptr_on_heap_object_Vec2b1->Print(); // Confirming the ownership has been transferred
    }
}

```

In this corrected example, the std::move() function is used to transfer the
ownership of the Vec2b object from smart_ptr_on_heap_object_Vec2b2 to
smart_ptr_on_heap_object_Vec2b1.

- After the move, smart_ptr_on_heap_object_Vec2b2 becomes nullptr, and
  smart_ptr_on_heap_object_Vec2b1 now owns the resource. This is demonstrated by
  the ability to call Print() on smart_ptr_on_heap_object_Vec2b1 after the block
  in which smart_ptr_on_heap_object_Vec2b2 was declared has ended.

## Passing a Pointer of an object to a function

### Passing a raw pointer

Let's demonstrate this concept by defining a simple function that takes a
raw pointer to a `Vec2b` object as its parameter. This function will simply call
the `Print` method of the `Vec2b` object to which it points.

First, using a raw pointer:

```cpp
#include <iostream>

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

// Function taking a raw pointer to Vec2b
void PrintVec2b(const Vec2b* vec) {
    if (vec) { // Always check if the pointer is not null before dereferencing
        vec->Print();
    } else {
        std::cout << "Null pointer provided." << std::endl;
    }
}

int main() {
    Vec2b* vec = new Vec2b(10, 20); // Allocation on the heap using raw pointer
    PrintVec2b(vec); // Pass raw pointer to function

    delete vec; // Clean up to avoid memory leak
}
```

In this example, the `PrintVec2b` function takes a raw pointer to a `Vec2b`
object and calls its `Print` method. The `main` function creates a `Vec2b`
object on the heap and passes a pointer to this object to `PrintVec2b`. After
using the object, `main` properly cleans up by deleting the allocated object to
prevent a memory leak.

### Passing by unique pointer

The same example using smart unique pointer

To modify the example to use a `std::unique_ptr`, we'll adjust the function to
accept a reference to a `std::unique_ptr<Vec2b>` instead. This allows us to
maintain ownership semantics while still being able to use the object within the
function. Note that functions typically take `std::unique_ptr` by reference if
they don't intend to take ownership, or by value if they need to take ownership.
Since the goal here is just to use the object without transferring ownership,
we'll use a reference.

Here's how you do it with a `std::unique_ptr`:

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

// Function taking a reference to a unique_ptr to Vec2b
void PrintVec2b(const std::unique_ptr<Vec2b>& vec) {
    if (vec) { // The unique_ptr overrides the bool operator for null check
        vec->Print();
    } else {
        std::cout << "Null pointer provided." << std::endl;
    }
}

int main() {
    std::unique_ptr<Vec2b> vec = std::make_unique<Vec2b>(10, 20); // Allocation on the heap using unique_ptr
    PrintVec2b(vec); // Pass unique_ptr by reference to function

    // No need for explicit delete; memory will be automatically released
}
```

In this version, the `PrintVec2b` function accepts a reference to a
`std::unique_ptr<Vec2b>`. This means that when you call `PrintVec2b`, you're not
transferring ownership of the `Vec2b` object; you're merely allowing the
function to access the object via the smart pointer. The smart pointer ensures
that the memory is automatically managed, making this approach safer and
avoiding memory leaks without needing an explicit `delete`.

## Demo - Move Ownership unique pointer

To correctly move ownership from one `std::unique_ptr` to another, you should
use the `std::move()` function from the `<utility>` header, which casts its
argument to an r-value indicating that it's safe to transfer ownership of the
resource. Your example has a small mistake in calling the `.move()` method
directly on the smart pointer, which is not correct. Instead, you should use
`std::move(smart_ptr_on_heap_object_Vec2b2)`.

Here's how you can correctly move ownership from
`smart_ptr_on_heap_object_Vec2b2` to `smart_ptr_on_heap_object_Vec2b1`:

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr
#include <utility> // For std::move

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b1 = nullptr;

    {
        std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b2 = std::make_unique<Vec2b>(200, 300);
        smart_ptr_on_heap_object_Vec2b2->Print();
        smart_ptr_on_heap_object_Vec2b1 = std::move(smart_ptr_on_heap_object_Vec2b2);
    }

    // At this point, smart_ptr_on_heap_object_Vec2b2 is nullptr, and ownership has been transferred to smart_ptr_on_heap_object_Vec2b1
    if (smart_ptr_on_heap_object_Vec2b1) {
        smart_ptr_on_heap_object_Vec2b1->Print(); // Confirming the ownership has been transferred
    }
}
```

In this corrected example, the `std::move()` function is used to transfer the
ownership of the `Vec2b` object from `smart_ptr_on_heap_object_Vec2b2` to
`smart_ptr_on_heap_object_Vec2b1`. After the move,
`smart_ptr_on_heap_object_Vec2b2` becomes `nullptr`, and
`smart_ptr_on_heap_object_Vec2b1` now owns the resource. This is demonstrated by
the ability to call `Print()` on `smart_ptr_on_heap_object_Vec2b1` after the
block in which `smart_ptr_on_heap_object_Vec2b2` was declared has ended.
