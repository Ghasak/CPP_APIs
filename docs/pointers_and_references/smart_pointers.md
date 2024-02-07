# Smart Pointers in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Smart Pointers in C++](#smart-pointers-in-c)
  - [1.My Understanding](#1my-understanding)
    - [1.1. Smart Pointer - Unique Pointer](#11-smart-pointer---unique-pointer)
  - [2.Smart Pointers in depth](#2smart-pointers-in-depth)
    - [What Are Smart Pointers?](#what-are-smart-pointers)
    - [Types of Smart Pointers in C++](#types-of-smart-pointers-in-c)
    - [How to Use Them](#how-to-use-them)
    - [When to Use Them](#when-to-use-them)
    - [Things to Consider](#things-to-consider)
    - [Common Practices and Mistakes](#common-practices-and-mistakes)
    - [Using Smart Pointers with Classes](#using-smart-pointers-with-classes)
    - [Scenarios and Examples](#scenarios-and-examples)
    - [Summary Table](#summary-table)
    - [Additional Tips](#additional-tips)
  - [3.Smart Pointers How to use them correctly](#3smart-pointers-how-to-use-them-correctly)

<!-- markdown-toc end -->

## Plan on this guide

1. Smart pointers in general
2. How Smart Pointers works
3. Ownership of smart pointer
4. Smart pointers with functions
5. Local creating heap alloction inside a function

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

## 2.Smart Pointers in depth

Smart pointers in C++ are a crucial feature that help developers manage dynamic
memory without the direct need to call `delete`. They ensure that memory is
automatically managed, preventing leaks and dangling pointers, which are common
issues in manual memory management. This lecture will cover the essentials of
smart pointers in C++, including their types, usage, syntax, best practices, and
common pitfalls.

### What Are Smart Pointers?

Smart pointers are template classes in the C++ Standard Library that provide
automatic memory management. When a smart pointer goes out of scope, the memory
it points to is automatically reclaimed without the need for explicit deletion.
This feature is known as RAII (Resource Acquisition Is Initialization), ensuring
resources are properly released when they are no longer needed.

### Types of Smart Pointers in C++

1. **`std::unique_ptr`**: Owns and manages another object through a pointer and
   ensures that no other smart pointer can share ownership. It's useful for
   exclusive ownership of resources.
2. **`std::shared_ptr`**: Allows multiple `shared_ptr` instances to own the same
   object. The resource is released when the last `shared_ptr` is destroyed or
   reset.
3. **`std::weak_ptr`**: Complements `shared_ptr` by holding a non-owning
   reference to an object that is managed by `shared_ptr`. It's used to break
   circular references among `shared_ptr` instances.

### How to Use Them

- **`std::unique_ptr`**:

  ```cpp
  std::unique_ptr<Type> ptr(new Type(arguments));
  // or using make_unique (C++14 and above)
  std::unique_ptr<Type> ptr = std::make_unique<Type>(arguments);
  ```

- **`std::shared_ptr`**:

  ```cpp
  std::shared_ptr<Type> ptr(new Type(arguments));
  // or using make_shared (preferable for performance)
  std::shared_ptr<Type> ptr = std::make_shared<Type>(arguments);
  ```

- **`std::weak_ptr`**:
  ```cpp
  std::weak_ptr<Type> weakPtr = sharedPtr;
  ```

### When to Use Them

- Use `std::unique_ptr` when you need exclusive ownership of a resource.
- Use `std::shared_ptr` when you need shared ownership or when dealing with
  circular references.
- Use `std::weak_ptr` to access an object managed by `shared_ptr` without owning
  it, especially to avoid circular references.

### Things to Consider

- **Ownership and Lifespan**: Understand the ownership semantics of each smart
  pointer type to ensure correct management of resources.
- **Performance**: While `std::shared_ptr` is versatile, it introduces overhead
  due to reference counting. Use it judiciously.
- **Circular References**: Be cautious of circular references with `shared_ptr`,
  which can lead to memory leaks. Use `weak_ptr` to break these cycles.

### Common Practices and Mistakes

- **Do** use `std::make_unique` and `std::make_shared` for creating instances.
  They are safer and can be more efficient.
- **Don't** use raw pointers for ownership or manual memory management when
  smart pointers can be used.
- **Avoid** converting raw pointers to smart pointers indiscriminately, as it
  can lead to double-free errors or leaks.

### Using Smart Pointers with Classes

When designing classes, prefer smart pointers for managing dynamically allocated
resources. For example:

```cpp
class MyClass {
public:
    std::unique_ptr<AnotherClass> resource;

    MyClass() : resource(std::make_unique<AnotherClass>()) {}
};
```

### Scenarios and Examples

- **C-Style Array**: Prefer `std::vector` over smart pointers for arrays. If
  necessary, `std::unique_ptr` can manage dynamic arrays:

  ```cpp
  std::unique_ptr<int[]> arr(new int[10]);
  ```

- **Char Pointer List**:

  ```cpp
  std::unique_ptr<char[]> cString(new char[10]);
  std::strcpy(cString.get(), "Hello");
  ```

- **std::vector**:
  Use smart pointers inside containers to manage dynamic objects.

  ```cpp
  std::vector<std::shared_ptr<Type>> vec;
  vec.push_back(std::make_shared<Type>(arguments));
  ```

- **std::string**: Smart pointers are not typically used with `std::string`, as
  it already manages its memory.

### Summary Table

| Smart Pointer     | Syntax Example                                              | Use Case                               |
| ----------------- | ----------------------------------------------------------- | -------------------------------------- |
| `std::unique_ptr` | `std::unique_ptr<Type> ptr = std::make_unique<Type>(args);` | Exclusive ownership of single objects. |
| `std::shared_ptr` | `std::shared_ptr<Type> ptr = std::make_shared<Type>(args);` | Shared ownership of objects.           |
| `std::weak_ptr`   | `std::weak_ptr<Type>                                        |

weakPtr = sharedPtr;` | Weak reference to an object owned by`shared_ptr`.|

### Additional Tips

- Always prefer using smart pointers over raw pointers to leverage C++'s memory
  management features.
- Understand the ownership semantics of your program to choose the appropriate
  smart pointer type.
- Be mindful of the overhead and use them where they make sense, especially in
  performance-critical sections.

By adhering to these guidelines and understanding the different smart pointers'
semantics, you can write safer, cleaner, and more efficient C++ code.
