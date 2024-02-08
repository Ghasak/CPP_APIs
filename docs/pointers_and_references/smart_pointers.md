# Smart Pointers in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Smart Pointers in C++](#smart-pointers-in-c)
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
    - [Smart Pointers in Action](#smart-pointers-in-action)
        - [1. Using `std::unique_ptr`](#1-using-stdunique_ptr)
        - [2. Using `std::shared_ptr`](#2-using-stdshared_ptr)
        - [3. Using `std::weak_ptr`](#3-using-stdweak_ptr)
    - [Can I pass as pointer instead of a reference of the pointer?](#can-i-pass-as-pointer-instead-of-a-reference-of-the-pointer)
        - [Passing `std::unique_ptr` by Pointer](#passing-stdunique_ptr-by-pointer)
        - [Passing `std::shared_ptr` by Pointer](#passing-stdshared_ptr-by-pointer)
        - [Passing `std::weak_ptr` by Pointer](#passing-stdweak_ptr-by-pointer)
        - [Conclusion](#conclusion)
    - [Passing CStyle array Example](#passing-cstyle-array-example)
        - [Using `std::unique_ptr`](#using-stdunique_ptr)
        - [Using `std::shared_ptr`](#using-stdshared_ptr)
        - [Note on `std::weak_ptr`](#note-on-stdweak_ptr)
        - [Conclusion](#conclusion-1)
    - [Smart Pointers with function local object](#smart-pointers-with-function-local-object)
        - [Understanding `std::unique_ptr` and Scope](#understanding-stdunique_ptr-and-scope)
        - [Move Semantics and Ownership Transfer](#move-semantics-and-ownership-transfer)
        - [The Role of `return`](#the-role-of-return)
        - [Confirmation of No Premature Deallocation](#confirmation-of-no-premature-deallocation)
        - [Other Possibilities and Considerations](#other-possibilities-and-considerations)
        - [Conclusion](#conclusion-2)
    - [Understanding Return local object from a function](#understanding-return-local-object-from-a-function)
    - [Is this the only safe way to return local data from a function? Assume I don’t want to use static ?](#is-this-the-only-safe-way-to-return-local-data-from-a-function-assume-i-dont-want-to-use-static-)
        - [Dynamically Allocated Memory](#dynamically-allocated-memory)
        - [Returning by Value for Containers](#returning-by-value-for-containers)
        - [Summary](#summary)
    - [More Explanation](#more-explanation)
    - [How about Ownership Transfering](#how-about-ownership-transfering)
        - [1. Return from a Function](#1-return-from-a-function)
        - [2. std::move()](#2-stdmove)
        - [3. Passing to a Function by Value](#3-passing-to-a-function-by-value)
        - [4. Assignment to nullptr](#4-assignment-to-nullptr)
        - [5. Reset Method](#5-reset-method)
        - [6. Release Method](#6-release-method)
    - [Lifetime of Smart Pointers](#lifetime-of-smart-pointers)
        - [Raw Pointers](#raw-pointers)
        - [`std::unique_ptr`](#stdunique_ptr)
        - [`std::shared_ptr`](#stdshared_ptr)
        - [`std::weak_ptr`](#stdweak_ptr)

<!-- markdown-toc end -->

Smart pointers in C++ are a crucial feature that help developers manage dynamic
memory without the direct need to call `delete`. They ensure that memory is
automatically managed, preventing leaks and dangling pointers, which are common
issues in manual memory management. This lecture will cover the essentials of
smart pointers in C++, including their types, usage, syntax, best practices, and
common pitfalls.

## What Are Smart Pointers?

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

- **C-Style Array**: Prefer `std::vector` over smart pointers for arrays. If necessary, `std::unique_ptr` can manage dynamic arrays:

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

weakPtr = sharedPtr;`| Weak reference to an object owned by`shared_ptr`.|

### Additional Tips

- Always prefer using smart pointers over raw pointers to leverage C++'s memory
  management features.
- Understand the ownership semantics of your program to choose the appropriate
  smart pointer type.
- Be mindful of the overhead and use them where they make sense, especially in
  performance-critical sections.

By adhering to these guidelines and understanding the different smart pointers'
semantics, you can write safer, cleaner, and more efficient C++ code.

## Smart Pointers in Action

Let's build an example demonstrating the use of smart pointers by passing them
to a function. We'll use a simple scenario involving an `add` function that
operates on objects representing numeric values. This will illustrate the use of
`std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`, highlighting the
reasons for switching between these types.

### 1. Using `std::unique_ptr`

First, we'll start with `std::unique_ptr`, which is used for unique ownership of
resources.

```cpp
#include <iostream>
#include <memory>

class Number {
public:
    int value;
    Number(int value) : value(value) {}
    int getValue() const { return value; }
};

// Function accepting a unique_ptr by reference
void add(std::unique_ptr<Number>& a, std::unique_ptr<Number>& b) {
    std::cout << "Sum: " << a->getValue() + b->getValue() << std::endl;
}

int main() {
    std::unique_ptr<Number> num1 = std::make_unique<Number>(10);
    std::unique_ptr<Number> num2 = std::make_unique<Number>(20);

    add(num1, num2);

    return 0;
}
```

**Explanation**: Here, `add` takes `unique_ptr` references, allowing it to use
the `Number` objects without taking ownership. This is useful when the function
does not need to own or modify the lifetime of the objects. However,
`unique_ptr` strictly enforces unique ownership, limiting its use when ownership
needs to be shared or retained by the caller.

### 2. Using `std::shared_ptr`

To overcome the limitation of `unique_ptr`, we switch to `std::shared_ptr` for
shared ownership scenarios.

```cpp
// Function accepting shared_ptr by value
void add(std::shared_ptr<Number> a, std::shared_ptr<Number> b) {
    std::cout << "Sum: " << a->getValue() + b->getValue() << std::endl;
}

int main() {
    std::shared_ptr<Number> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Number> num2 = std::make_shared<Number>(20);

    add(num1, num2);
}
```

**Explanation**: By using `std::shared_ptr`, the `add` function allows for
shared ownership of the `Number` instances. This means that both the caller and
the function can have access to the resources, and the resources will be
automatically cleaned up once all references are out of scope. This is
particularly useful for complex object graphs where objects are shared among
multiple owners.

### 3. Using `std::weak_ptr`

Finally, let's introduce a scenario where `std::weak_ptr` is necessary to avoid
circular references or when a function needs to access a shared resource without
affecting its ownership lifecycle.

```cpp
// Function accepting a weak_ptr
void add(std::weak_ptr<Number> a, std::weak_ptr<Number> b) {
    // Convert weak_ptr to shared_ptr to use the object
    std::shared_ptr<Number> sa = a.lock();
    std::shared_ptr<Number> sb = b.lock();
    if (sa && sb) {
        std::cout << "Sum: " << sa->getValue() + sb->getValue() << std::endl;
    } else {
        std::cout << "One of the numbers is no longer available." << std::endl;
    }
}

int main() {
    std::shared_ptr<Number> num1 = std::make_shared<Number>(10);
    std::shared_ptr<Number> num2 = std::make_shared<Number>(20);

    // Creating weak_ptr from shared_ptr
    std::weak_ptr<Number> weakNum1 = num1;
    std::weak_ptr<Number> weakNum2 = num2;

    add(weakNum1, weakNum2);
}
```

**Explanation**: In this example, `add` accepts `weak_ptr` arguments, which are
converted to `shared_ptr` using `lock()` for safe access. This method ensures
that the function can access the resources if they still exist, without
affecting the reference count or ownership. It's particularly useful in
preventing memory leaks due to circular references in complex object
relationships.

**Summary of Pointer Types and Usage**:

- **`std::unique_ptr`**: For unique ownership and when passing objects to
  functions without transferring ownership.
- **`std::shared_ptr`**: For shared ownership among multiple parts of a program,
  enabling easy resource sharing.
- **`std::weak_ptr`**: For accessing resources managed by `shared_ptr` without
  owning them, preventing circular references and potential memory leaks.

This progression from `std::unique_ptr` to `std::weak_ptr` showcases the
flexibility and safety provided by smart pointers in managing dynamic memory,
especially in complex applications.

## Can I pass as pointer instead of a reference of the pointer?

Yes, you can pass a smart pointer to a function by pointer instead of by
reference, but this approach is less common and generally not recommended for
smart pointers. The main reason for this is that smart pointers are designed to
manage ownership and lifetime of dynamically allocated objects. Passing them by
pointer rather than by reference or by value can obscure ownership semantics and
lead to less clear and potentially unsafe code. However, for educational
purposes, let's explore how this could be done with each type of smart pointer,
building upon the `add` function example for `std::unique_ptr`,
`std::shared_ptr`, and `std::weak_ptr`.

### Passing `std::unique_ptr` by Pointer

To pass a `std::unique_ptr` by pointer, you would need to pass the address of
the smart pointer. However, manipulating `std::unique_ptr` through a pointer to
it is risky and can easily lead to mistakes, such as accidentally deleting the
smart pointer or creating copies that violate its unique ownership model.

```cpp
void add(std::unique_ptr<Number>* a, std::unique_ptr<Number>* b) {
    if (a && b && a->get() && b->get()) {
        std::cout << "Sum: " << (*a)->getValue() + (*b)->getValue() << std::endl;
    }
}

// Usage
std::unique_ptr<Number> num1 = std::make_unique<Number>(10);
std::unique_ptr<Number> num2 = std::make_unique<Number>(20);
add(&num1, &num2);
```

### Passing `std::shared_ptr` by Pointer

Similar to `std::unique_ptr`, you can pass a `std::shared_ptr` by pointer. This
might be slightly less risky due to the shared ownership model, but it still
complicates the ownership semantics and should be avoided when possible.

```cpp
void add(std::shared_ptr<Number>* a, std::shared_ptr<Number>* b) {
    if (a && b && *a && *b) {
        std::cout << "Sum: " << (*a)->getValue() + (*b)->getValue() << std::endl;
    }
}

// Usage
std::shared_ptr<Number> num1 = std::make_shared<Number>(10);
std::shared_ptr<Number> num2 = std::make_shared<Number>(20);
add(&num1, &num2);
```

### Passing `std::weak_ptr` by Pointer

Passing a `std::weak_ptr` by pointer is possible but, like the other examples,
complicates the code unnecessarily. The primary use case for `std::weak_ptr` is
to break cycles in shared ownership, and passing it by pointer does not align
well with its intended use.

```cpp
void add(std::weak_ptr<Number>* a, std::weak_ptr<Number>* b) {
    auto sa = a->lock();
    auto sb = b->lock();
    if (sa && sb) {
        std::cout << "Sum: " << sa->getValue() + sb->getValue() << std::endl;
    }
}

// Usage
std::shared_ptr<Number> sharedNum1 = std::make_shared<Number>(10);
std::shared_ptr<Number> sharedNum2 = std::make_shared<Number>(20);
std::weak_ptr<Number> weakNum1 = sharedNum1;
std::weak_ptr<Number> weakNum2 = sharedNum2;
add(&weakNum1, &weakNum2);
```

### Conclusion

While it's technically possible to pass smart pointers by pointer, it's not a
best practice and can lead to code that is harder to understand and maintain.
Passing smart pointers by reference (for `unique_ptr` when you don't intend to
transfer ownership) or by value (for `shared_ptr` when sharing ownership) aligns
better with their design goals and the principles of modern C++ memory
management.

## Passing CStyle array Example

Passing by reference of each of these smart pointers in form of passing two
CStyle arrays allocated on heap and the return of the add function is an array
of element-wise sum

To demonstrate passing smart pointers by reference with C-style arrays allocated
on the heap, we will define a function that takes two arrays of integers,
represented by smart pointers, and returns a new array containing the
element-wise sum of the input arrays. This example will cover `std::unique_ptr`,
`std::shared_ptr`, and a scenario involving `std::weak_ptr` for completeness,
though `std::weak_ptr` is not typically used for managing arrays directly.

### Using `std::unique_ptr`

For `std::unique_ptr`, we'll use the array specialization
`std::unique_ptr<int[]>`. This specialization allows `std::unique_ptr` to manage
dynamic arrays and properly delete them with `delete[]`.

```cpp
#include <iostream>
#include <memory>

std::unique_ptr<int[]> add(const std::unique_ptr<int[]>& a, const std::unique_ptr<int[]>& b, int size) {
    std::unique_ptr<int[]> result = std::make_unique<int[]>(size);
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

int main() {
    const int size = 3;
    std::unique_ptr<int[]> arr1 = std::make_unique<int[]>(size);
    std::unique_ptr<int[]> arr2 = std::make_unique<int[]>(size);

    // Initializing arrays
    arr1[0] = 1; arr1[1] = 2; arr1[2] = 3;
    arr2[0] = 4; arr2[1] = 5; arr2[2] = 6;

    std::unique_ptr<int[]> result = add(arr1, arr2, size);

    for (int i = 0; i < size; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Using `std::shared_ptr`

For `std::shared_ptr`, managing C-style arrays directly requires custom deleter
logic, as `std::shared_ptr` does not have a specialization for arrays like
`std::unique_ptr` does. Here's how you can implement it:

```cpp
#include <memory>
#include <iostream>

// Custom deleter for shared_ptr managing a C-style array
struct ArrayDeleter {
    void operator()(int* p) const { delete[] p; }
};

std::shared_ptr<int[]> add(const std::shared_ptr<int[]>& a, const std::shared_ptr<int[]>& b, int size) {
    // Note: shared_ptr does not have array specialization, using unique_ptr for demonstration
    std::unique_ptr<int[]> result(new int[size]);
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
    return std::shared_ptr<int[]>(result.release(), ArrayDeleter());
}

int main() {
    const int size = 3;
    std::shared_ptr<int[]> arr1(new int[size], ArrayDeleter());
    std::shared_ptr<int[]> arr2(new int[size], ArrayDeleter());

    // Initializing arrays
    arr1[0] = 1; arr1[1] = 2; arr1[2] = 3;
    arr2[0] = 4; arr2[1] = 5; arr2[2] = 6;

    std::shared_ptr<int[]> result = add(arr1, arr2, size);

    for (int i = 0; i < size; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Note on `std::weak_ptr`

`std::weak_ptr` is not suitable for managing resources directly, including
C-style arrays. It is used to hold a non-owning reference to an object managed
by a `std::shared_ptr`, to avoid circular references or to check resource
availability without extending its lifetime. Therefore, it doesn't apply to this
scenario of managing and returning arrays.

### Conclusion

The examples demonstrate how to pass smart pointers by reference to functions
dealing with C-style arrays. With `std::unique_ptr`, we leverage its array
specialization for clean syntax and automatic memory management. For
`std::shared_ptr`, custom deleter logic is necessary to manage arrays properly.
`std::weak_ptr` is not used for direct resource management, so it's not included
in the array handling example. These examples illustrate the flexibility and
safety of smart pointers in modern C++ for managing dynamic memory, including
heap-allocated arrays.

## Smart Pointers with function local object

The concerns touch on important aspects of smart pointer behavior and C++ move
semantics. Let's clarify how this works and ensure understanding of ownership
transfer with `std::unique_ptr`, especially when returning from a function.

### Understanding `std::unique_ptr` and Scope

When a `std::unique_ptr` goes out of scope, it automatically deletes the object
it owns. This is a fundamental aspect of its design, ensuring that dynamically
allocated memory is properly freed without manual intervention. However, when
you return a `std::unique_ptr` from a function, C++ move semantics come into
play.

### Move Semantics and Ownership Transfer

In the given example, the `std::unique_ptr<int[]> result` is created within the
`add` function and points to a dynamically allocated array on the heap. When
`result` is returned from the function, it is moved rather than copied, thanks
to C++'s move semantics. This means the ownership of the dynamically allocated
array is transferred from the local `result` variable to the caller's
`std::unique_ptr<int[]>` that receives the function's return value.

### The Role of `return`

When `return result;` is executed, it effectively calls the move constructor of
`std::unique_ptr<int[]>`, transferring ownership of the heap-allocated array to
the returned `std::unique_ptr<int[]>`. This move operation ensures that the
memory is not freed when the function exits and `result` goes out of scope.
Instead, the ownership is transferred outside the function, preventing the
memory from being deallocated prematurely.

### Confirmation of No Premature Deallocation

To confirm, the move operation prevents the deallocated memory issue you're
concerned about. The heap-allocated array remains valid and owned by the
returned `std::unique_ptr<int[]>` until that pointer goes out of scope or is
otherwise reset or destroyed.

### Other Possibilities and Considerations

The approach used in the example is idiomatic and efficient for modern C++.
C++11 and later standards encourage the use of move semantics and smart pointers
to simplify memory management and avoid common pitfalls such as memory leaks and
dangling pointers.

**Alternative Approaches?**

Given the design of `std::unique_ptr` and C++ move semantics, the method used is
optimal for this scenario. Other methods, such as passing smart pointers by
reference or pointer to modify them directly, complicate the design and
undermine the benefits of smart pointers and move semantics.

### Conclusion

Your intuition about the move semantics at play is correct. The function's
return statement does handle moving the `std::unique_ptr<int[]>` correctly, with
the smart pointer and its heap-allocated array safely transferred to the caller,
ensuring no premature deallocation occurs. This pattern is a best practice in
modern C++ for functions that create and return dynamically allocated resources.

## Understanding Return local object from a function

When you return a `std::unique_ptr` from a function, the ownership of the
heap-allocated data is transferred from the original `std::unique_ptr` inside
the function (which then "dies" or goes out of scope) to the `std::unique_ptr`
that receives this returned value. This transfer of ownership is a fundamental
aspect of C++ move semantics applied to smart pointers, specifically
`std::unique_ptr`.

Here's a step-by-step breakdown of what happens:

1. **Inside the Function**: A `std::unique_ptr` manages a dynamically allocated
   resource.
2. **Returning the Pointer**: When returning the `std::unique_ptr`, C++
   automatically uses move semantics. This means it moves the resource from the
   original `std::unique_ptr` to a new `std::unique_ptr` instance. The
   function's local `std::unique_ptr` essentially gives up ownership of the
   resource, ensuring that no copy operation occurs. The move is efficient and
   does not involve duplicating the managed resource.
3. **After the Return**: The original `std::unique_ptr` in the function scope is
   now empty (it does not own any resource anymore) and will be destroyed
   without affecting the dynamically allocated resource. The ownership has been
   fully transferred to the `std::unique_ptr` that received the function's
   return value.

This mechanism ensures that the resource is managed safely, with clear ownership
transfer semantics, preventing memory leaks and dangling pointers. It allows
functions to create and return dynamically allocated resources without the risk
of premature deallocation or resource leaks, leveraging the safety and
efficiency of modern C++ practices.

## Is this the only safe way to return local data from a function? Assume I don’t want to use static ?

Ah, if you're referring to returning a pointer or reference to local data
created inside the function body, such as a list, without using static storage
duration, then indeed, smart pointers are the safest way when dealing with
dynamically allocated memory. Returning a raw pointer or reference to a local
(stack-allocated) variable is unsafe because the local variable will be
destroyed when the function exits, leaving a dangling pointer or reference.

Here's why smart pointers, specifically `std::unique_ptr` or `std::shared_ptr`,
are recommended for this scenario:

### Dynamically Allocated Memory

When you allocate memory dynamically (on the heap) inside a function and want to
return it to the caller, using smart pointers ensures that:

- The memory is managed automatically.
- Ownership semantics are clear and transferable.
- Memory leaks and dangling pointers are prevented.

```cpp
std::unique_ptr<std::list<int>> createList() {
    auto myList = std::make_unique<std::list<int>>();
    myList->push_back(1);
    myList->push_back(2);
    // myList is a unique_ptr managing a heap-allocated list
    return myList; // Safe: ownership is transferred to the caller
}
```

### Returning by Value for Containers

For container types like `std::list`, `std::vector`, etc., you can safely return
by value thanks to the move semantics of modern C++. This avoids the need for
dynamic allocation or pointers altogether:

```cpp
std::list<int> createList() {
    std::list<int> myList = {1, 2, 3};
    return myList; // Safe and efficient with move semantics
}
```

In this case, even though `myList` is a local variable, returning it by value is
efficient due to move semantics. The C++ compiler is likely to optimize this
further, avoiding any copy or move operation entirely through RVO (Return Value
Optimization).

### Summary

- **For heap-allocated data**: Use smart pointers (`std::unique_ptr`,
  `std::shared_ptr`) to return a pointer to dynamically allocated memory. This
  is the safest way to manage lifetime and ownership of heap-allocated data.
- **For automatic (stack-allocated) data or STL containers**: Return by value
  and rely on move semantics and compiler optimizations for efficiency. This
  avoids the issues associated with pointers and references to local data, as
  well as the overhead of dynamic memory allocation.

Avoid returning pointers or references to local stack-allocated data, as this
will lead to undefined behavior due to the data being destroyed once the
function exits.

## More Explanation

The smart pointer is merely an integer that will be destroyed when it goes out
of scope, but it will delete the data allocated on the heap that it references,
which I believe is the essence of a unique smart pointer..

The essence of how `std::unique_ptr` operates in C++, with a slight
clarification on the nature of the smart pointer itself.

A `std::unique_ptr` is not just an integer; it's an object that encapsulates a
raw pointer to dynamically allocated memory on the heap. It manages the lifetime
of this memory, ensuring that it is properly deleted when the `std::unique_ptr`
goes out of scope. Here's a breakdown:

- **Ownership and Lifetime Management**: `std::unique_ptr` owns the object it
  points to. When the `std::unique_ptr` is destroyed (e.g., when it goes out of
  scope), it automatically deletes the object it owns, freeing the associated
  memory. This prevents memory leaks by ensuring that dynamically allocated
  memory is not forgotten.

- **Destruction**: Upon going out of scope, the destructor of `std::unique_ptr`
  is called. This destructor is responsible for deleting the heap-allocated
  object it owns. This automatic cleanup is a key feature of RAII (Resource
  Acquisition Is Initialization), a core principle in C++ that binds resource
  management to object lifetime.

- **Transfer of Ownership**: `std::unique_ptr` exclusively owns the memory it
  points to, and it does not allow for copying to ensure unique ownership.
  However, ownership can be transferred from one `std::unique_ptr` to another
  through move semantics. When moved, the source `std::unique_ptr` gives up
  ownership (becomes empty or null) and the destination `std::unique_ptr` takes
  over the ownership and responsibility for the memory.

- **Safety**: By encapsulating the raw pointer and automatically managing the
  memory it points to, `std::unique_ptr` provides a safer alternative to raw
  pointers for managing dynamically allocated memory. It helps avoid common
  errors such as double deletes, memory leaks, and dangling pointers.

In summary, `std::unique_ptr` is a smart pointer that provides scoped, exclusive
ownership of heap-allocated memory, automatically freeing this memory when the
smart pointer goes out of scope. This ensures that the dynamically allocated
memory is managed safely and efficiently, aligning with modern C++ best
practices.

## How about Ownership Transfering

Is transfer ownership is done using the return only? Is there other ways to do
so? Obviously I cannot create a new unique pointer and make it equal to another
unique pointer to a data on heap

Ownership transfer of a `std::unique_ptr` can indeed occur in several ways, not
just through function return values. The key principle is that `std::unique_ptr`
ensures unique ownership of the heap-allocated memory, so it explicitly
disallows copying but allows ownership to be transferred to ensure that only one
`std::unique_ptr` owns the memory at any time. Here are the primary ways to
transfer ownership of a `std::unique_ptr`:

### 1. Return from a Function

As discussed, returning a `std::unique_ptr` from a function transfers ownership
to the caller, using move semantics.

```cpp
std::unique_ptr<MyClass> createMyClass() {
    return std::make_unique<MyClass>();
}
```

### 2. std::move()

To transfer ownership between `std::unique_ptr` instances explicitly outside of
a return context, you use `std::move()`. This function casts its argument to an
r-value, enabling the move constructor or move assignment operator of the
`std::unique_ptr`.

```cpp
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
std::unique_ptr<MyClass> ptr2 = std::move(ptr1); // ptr1 loses ownership and becomes null
```

### 3. Passing to a Function by Value

When you pass a `std::unique_ptr` to a function by value, ownership is
transferred to the parameter within the function. This is less common than
passing by reference or pointer for modification without transfer of ownership,
but it's a valid way to transfer ownership to a function's scope.

```cpp
void takeOwnership(std::unique_ptr<MyClass> ptr) {
    // Ownership of the memory has been transferred to ptr
}

// Usage
std::unique_ptr<MyClass> myPtr = std::make_unique<MyClass>();
takeOwnership(std::move(myPtr)); // myPtr loses ownership
```

### 4. Assignment to nullptr

Assigning a `std::unique_ptr` to `nullptr` effectively releases its ownership of
the current heap-allocated object (which gets deleted) and resets the pointer to
null.

```cpp
std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
ptr = nullptr; // The MyClass instance is deleted, and ptr is reset
```

### 5. Reset Method

The `reset()` method of `std::unique_ptr` can be used to release its current
ownership (if any) and optionally take ownership of a new resource.

```cpp
std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
ptr.reset(new MyClass()); // Deletes the old object and takes ownership of a new one
```

### 6. Release Method

The `release()` method relinquishes ownership of the object, without deleting
it, and returns a raw pointer to the caller. After calling `release()`, the
`std::unique_ptr` becomes null.

```cpp
std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
MyClass* rawPtr = ptr.release(); // ptr no longer owns the object
```

Remember, after transferring ownership from a `std::unique_ptr`, the original
pointer no longer owns the heap-allocated object and becomes null. This ensures
that at any point, only one owner exists for the allocated memory, aligning with
the unique ownership model.

## Lifetime of Smart Pointers

A pointer in C++ reaches the end of its lifetime when it goes out of scope or is
explicitly deleted (for raw pointers). The precise behavior depends on the type
of pointer being used (raw pointer, `std::unique_ptr`, `std::shared_ptr`, etc.).
Here's how the lifetime ends for different types of pointers:

### Raw Pointers

- **Lifetime**: The lifetime of a raw pointer itself (the variable that holds
  the memory address) ends when it goes out of scope.
- **Memory Management**: However, the memory it points to (if it was dynamically
  allocated using `new`) does not automatically get freed when the pointer goes
  out of scope. It must be explicitly deleted using `delete` or `delete[]` for
  arrays to avoid memory leaks.

### `std::unique_ptr`

- **Lifetime and Memory Management**: The lifetime of a `std::unique_ptr` ends
  when it goes out of scope. When a `std::unique_ptr` goes out of scope, it
  automatically deletes the object it owns (if any), releasing the allocated
  memory. This automatic cleanup helps manage dynamic memory without manual
  deletions.

### `std::shared_ptr`

- **Lifetime**: The lifetime of a `std::shared_ptr` variable ends when it goes
  out of scope. However, because `std::shared_ptr` uses reference counting, the
  object it points to will only be deleted when the last `std::shared_ptr`
  pointing to the object is destroyed or reset.
- **Memory Management**: This means the dynamically allocated object's memory is
  automatically freed once the reference count drops to zero, ensuring proper
  cleanup and preventing memory leaks.

### `std::weak_ptr`

- **Lifetime**: Similar to `std::shared_ptr`, the lifetime of a `std::weak_ptr`
  ends when it goes out of scope.
- **Memory Management**: However, `std::weak_ptr` does not contribute to the
  reference count of the object it points to. It is used to break circular
  references that can occur with `std::shared_ptr`. The object's lifetime is
  managed by `std::shared_ptr`, and `std::weak_ptr` can be used to access the
  object, provided it still exists.

In summary, for raw pointers, the programmer is responsible for manually
managing the lifetime of the pointed-to object. For smart pointers like
`std::unique_ptr` and `std::shared_ptr`, the lifetime of the pointed-to object
is managed automatically, with the specific behavior depending on the smart
pointer type used. This automatic management includes freeing allocated memory
when the smart pointer goes out of scope or when no more `std::shared_ptr`
instances point to the object, respectively.
