# Pointers in NutShell

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Pointers in NutShell](#pointers-in-nutshell)
    - [1. Introduction](#1-introduction)
        - [1.1. Based on Memory Management](#11-based-on-memory-management)
        - [1.2. Based on Usage](#12-based-on-usage)
        - [1.3. Location and Use of Pointers](#13-location-and-use-of-pointers)
        - [1.4. Additional Points](#14-additional-points)
    - [2. My Interpretation](#2-my-interpretation)
        - [2.1 Creating Pointers](#21-creating-pointers)
        - [2.2. Dereferencing a pointer](#22-dereferencing-a-pointer)
        - [2.3. How about Entity?](#23-how-about-entity)
        - [2.4. Understanding the Pointer to an Object](#24-understanding-the-pointer-to-an-object)
    - [3. Pointers with Heap allocation](#3-pointers-with-heap-allocation)
        - [3.1. Allocating Primitive Data Types](#31-allocating-primitive-data-types)
        - [3.2. Allocating Objects](#32-allocating-objects)
        - [3.3. Pointers to Primitive Data Types](#33-pointers-to-primitive-data-types)
            - [3.3.1 Pointers to Objects](#331-pointers-to-objects)

<!-- markdown-toc end -->

## 1. Introduction

The pointer is just an integer value hold a memeory address.
There are several types of pointers that I categorize based on their usage, all
with a similar understanding, which is simply to store the memory address of a
block of memory associated with the data stored there. These blocks of memory
are allocated by bytes number based on the given type.

### 1.1. Based on Memory Management

- **Raw Pointers:**

  - Traditional pointers in C++.
  - Require manual management of memory allocation and deallocation (using `new` and `delete`).
  - Can lead to memory leaks and dangling pointers if not handled carefully.

- **Smart Pointers:**
  - Introduced in C++11 to automate memory management and improve safety.
  - Types include `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
  - They handle memory allocation and deallocation automatically.
  - `std::unique_ptr` provides unique ownership, `std::shared_ptr` allows
    shared ownership, and `std::weak_ptr` is used for a non-owning but safe
    reference.

### 1.2. Based on Usage

- **Primitive Pointer:**

  - Points to primitive data types like `int`, `float`, `char`, etc.
  - Can also point to instances of structs or classes, but without any class-specific behavior.

- **Array Pointer:**

  - Typically points to the first element of an array.
  - In C++, it's often better to use `std::vector` or `std::array` for dynamic
    and fixed-size arrays, respectively, for safety and ease of use.

- **Object Pointer:**
  - Points to objects (instances of classes or structs).
  - Can be used to access member functions and variables, and for polymorphism.

### 1.3. Location and Use of Pointers

- **Pointer on Stack:**

  - A pointer variable itself is stored on the stack.
  - Common for function scope and short-lived pointers.
  - Can point to memory allocated on the stack or heap.

- **Pointer on Stack Referring to Heap:**
  - A pointer variable is stored on the stack, but it refers to data allocated on the heap.
  - Typically associated with `new` in C++.
  - Useful for objects whose lifetime extends beyond their scope of creation.

### 1.4. Additional Points

- **Dangling Pointers:**

  - Pointers that point to memory that has been deallocated or is no longer valid.
  - Common pitfall with raw pointers.

- **Memory Leaks:**

  - Occurs when dynamically allocated memory is not freed (no corresponding `delete` for a `new`).
  - Smart pointers help prevent memory leaks.

- **Pointer Arithmetic:**

  - Applicable to raw pointers, allowing operations like incrementing to traverse arrays.
  - Not applicable to smart pointers.

- **Polymorphism:**

  - Object pointers, particularly raw pointers or `std::shared_ptr`, can be used for polymorphism.
  - Enables dynamic binding of derived class methods through base class pointers.

- **Null Pointers:**
  - Pointers that do not point to any valid memory location.
  - In C++11 and later, `nullptr` is used to represent a null pointer.

## 2. My Interpretation

### 2.1 Creating Pointers

- **Creating a pointer**:

  - Memory Addresses:
    - Each memory block in a computer's memory has a unique address, often
      represented as a hexadecimal number (like 0x16bc01fbc).
    - These addresses are used to access and manipulate data stored in
      memory.
  - Variables and Memory:
    - When you create a variable of any primitive or user-defined data type
      in C++ (e.g., int, float, Entity e), memory is allocated to store the
      value of that variable.
    - The size of the allocated memory block depends on the data type (e.g.,
      int typically requires 4 bytes).
    - We are only interested in the memory addresses that refer to the beginnings of
      each block associated with reservations of a specific type (e.g., 4-bytes for
      int).
    - In C++, the designer decidded to use `&variable_name` to retrieve the memory address
      of the first block of memory for an associated variable. We provide a type for
      the pointer solely to determine the extent to which this variable should be
      stopped, allowing us to acquire its value since we know its size.

```cpp
int var = 255;
int* ptr = &var;  <- This will be a pointer that carries the memory address of the `var` variable.

               +-------------+
               | var value   |
               +-------------+
          [0][0]-[0][0]-[0][0]-[0][0] <- Having 4-bytes for allocating for `var` as the type is int.
          [F][F]-[0][0]-[0][0]-[0][0] <- The Hex-representation for the deciaml value `255`
          ^
          |
         |0|  `0x16bc01fbc`: We have created the `ptr`, which is an `int*`, why? because it will knows the end of
         |x|                 the value that we want to to stop at which is `var` and has to stop after `4-bytes`,
         |0|                 this means by refering to this address which also has a limit up to 4-bytes, it will
         |1|                 reterive the `255` once we want to dereference it as `*ptr`.
         |6|
         |b|
         |.|
         |.|
          ^
          |
          +--- The memory address `0x16bc01fbc` refers to the first value of these allocated 4 bytes.

```

### 2.2. Dereferencing a pointer

- Dereferencing the pointer
  - Now, we want to dereference the pointer and retrieve the value stored
    there, which is 255, to perform any arithmetic or operation.
  - Since we know that this ptr is just a memory address that we specified,
    We said, please stop after `4 bytes` since we have declared its type as int.
  - And int by our compiler is already established to store 4 bytes of memory
    for assigning any value to it.
  - Therefore, knowing the ptr (memory address) and when it should stop (after
    4 bytes),
  - We can retrieve all these 4 blocks of memory and dereference them to obtain
    the values that are stored in those 4-byte blocks of memory.

```cpp

*(ptr)   <- this means dereference the pointer

                      +-------------+
                      | var value   |
                      +-------------+
                 [F][F]-[0][0]-[0][0]-[0][0] <- Having 4-bytes for allocating for `var` as the type is int.
                  ^
                  |                        | <- go to this block and stop as you know this `ptr` will stop after 4-bytes.
We have this:  0x16bc01fbc ----------------+

*(ptr) -> will give us the value `255` in deciaml, which is exactly the value we stored in the variable `var`.

```

### 2.3. How about Entity?

How to think of an `Entity` (e.g., object, struct, other data strucutres or
types). This type of pointers is called `object pointer`.

- When you have a pointer to an object in C++, such as a pointer to an instance
  of a class or struct, it's important to understand what the pointer represents
  and how it can be used. Let's explore your example with the `Entity` class and
  the pointer `ptr`.

### 2.4. Understanding the Pointer to an Object

1. **Pointer to Object**:

   - `Entity* ptr = &e;` - In this statement, `ptr` is a pointer that holds the
     memory address of the object `e`. It does not point to a specific data
     attribute of `Entity`, but rather to the start of `e` in memory, which
     encompasses all of its data attributes (`x`, `y`, `z`, `str`).

2. **Accessing Object Members**:

   - You can use the pointer `ptr` to access the members of `Entity`. For
     instance, if `Entity` has a method `getX()`, you can call it using
     `ptr->getX()`. This is equivalent to `e.getX()`.

3. **Pointer Arithmetic**:

   - Pointer arithmetic on an object pointer (like `Entity*`) is generally not
     meaningful or safe. Object pointers are not meant to be incremented or
     decremented like pointers to primitive types (e.g., `int*` or `char*`).
   - The reason is that objects can be complex, with various members of
     different types and sizes. Incrementing an `Entity*` pointer would move it
     in memory by the size of an `Entity` object, but there's rarely a valid
     `Entity` object at that new memory location. This usually leads to undefined
     behavior.

4. **Correct Thinking**:

   - Think of an object pointer as a reference to the entire object. It's a way
     to access and manipulate the object without having the actual object. This
     is particularly useful for dynamic allocation, polymorphism, and managing
     resources.
   - When you have a pointer to an object, you're not concerned with the
     individual attributes' memory locations. Instead, you interact with the
     object as a whole, using its methods and properties.

5. **Dynamic Allocation**:
   - If you dynamically allocate an object using `new`, such as `Entity* e =
new Entity(10, 20, 30.0, "my input string");`, then `e` points to an
     `Entity` object in heap memory. Here, pointer arithmetic is still not
     advisable, but managing the lifetime of the object (i.e., when to `delete`
     it) becomes important.

In summary, when dealing with pointers to objects in C++, focus on the object
as a whole rather than its internal memory layout. Use the pointer to access
and manipulate the object's members through its methods. Avoid pointer
arithmetic on object pointers, as it typically leads to undefined behavior and
does not serve a meaningful purpose in the context of high-level
object-oriented programming.

## 3. Pointers with Heap allocation

### 3.1. Allocating Primitive Data Types

We will provide some examples below to demonstrate how to allocate data on the
heap for various data types and structures.

1. **int**:

   ```cpp
   int* pInt = new int;  // Allocates an integer on the heap
   *pInt = 10;           // Assigns a value to the allocated integer
   ```

2. **float**:

   ```cpp
   float* pFloat = new float;  // Allocates a float on the heap
   *pFloat = 5.5f;             // Assigns a value to the allocated float
   ```

3. **std::string**:

   ```cpp
   std::string* pString = new std::string;  // Allocates a string on the heap
   *pString = "Hello, World!";              // Assigns a value to the allocated string
   ```

4. **char Pointer (C-style string)**:

   ```cpp
   char* pChar = new char[20];  // Allocates 20 characters on the heap
   strcpy(pChar, "Hello, C++!"); // Copies a C-string into the allocated memory
   ```

5. **C-style Array**:
   ```cpp
   int* pArray = new int[5];  // Allocates an array of 5 integers on the heap
   for (int i = 0; i < 5; ++i) {
       pArray[i] = i * i;     // Initializes the array
   }
   ```

### 3.2. Allocating Objects

For a class or struct, assume we have a class `Entity`:

```cpp
class Entity {
public:
    Entity(int x, float y) : x(x), y(y) {}
    // Other methods...

private:
    int x;
    float y;
};
```

You can allocate an `Entity` object like this:

```cpp
Entity* pEntity = new Entity(10, 20.5f);  // Allocates an Entity object on the heap
```

### 3.3. Pointers to Primitive Data Types

When you allocate a primitive data type like `int` or `float` on the heap, the
pointer holds the address of the allocated memory. You use the dereference
operator (`*`) to access or modify the value stored in that memory.

Example:

```cpp
int* pInt = new int;
*pInt = 5;
std::cout << "Value: " << *pInt << std::endl;  // Accessing the value
delete pInt;  // Don't forget to deallocate
```

#### 3.3.1 Pointers to Objects

When you allocate an object on the heap, the pointer points to the memory where
the object is stored. You can access the object's methods and attributes using
the arrow operator (`->`).

Example:

```cpp
Entity* pEntity = new Entity(10, 20.5f);
// Accessing member methods or variables
// pEntity->someMethod();
delete pEntity;  // Deallocating the object
```

In both cases (primitive types and objects), it's crucial to use `delete` (or
`delete[]` for arrays) to deallocate the memory once it's no longer needed.
This prevents memory leaks. Pointers to heap-allocated data allow for dynamic
memory management, which is essential in scenarios where the size or number of
data elements is not known at compile-time or for large objects or arrays.

```cpp

int* heap_ptr = new int;

int var = 10;
heap_ptr = &var

```
