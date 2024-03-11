# Object Lifetime in C++ (Stack/Scope Lifetime)

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Object Lifetime in C++ (Stack/Scope Lifetime)](#object-lifetime-in-c-stackscope-lifetime)
  - [My Understanding](#my-understanding)
    - [Key Principles of Raw Pointer Management](#key-principles-of-raw-pointer-management)
    - [Best Practices](#best-practices)
    - [Diagram For Understanding Lifetime](#diagram-for-understanding-lifetime)
    - [More Insight](#more-insight)
      - [Modified Function with Explanation](#modified-function-with-explanation)
      - [Key Points and Comparison](#key-points-and-comparison)
      - [Conclusion](#conclusion)
    - [How about this](#how-about-this)
      - [How to Avoid Memory Leaks](#how-to-avoid-memory-leaks)
  - [Lifetime - Introduction](#lifetime---introduction)
    - [What is it?](#what-is-it)
    - [Why We Need It](#why-we-need-it)
    - [How to Use It](#how-to-use-it)
    - [Common Things to Consider](#common-things-to-consider)
    - [Examples](#examples)
  - [Stack Frame](#stack-frame)
    - [Analogy: A Box for Each Task](#analogy-a-box-for-each-task)
    - [Components of a Stack Frame](#components-of-a-stack-frame)
    - [How It Works](#how-it-works)
    - [Simplified Example](#simplified-example)
  - [Important - Delete a heap-pointer?](#important---delete-a-heap-pointer)
    - [Is All Data Deleted?](#is-all-data-deleted)
  - [Caution about assign a pointer on Heap](#caution-about-assign-a-pointer-on-heap)
    - [Memory Leaks](#memory-leaks)
    - [Proper Management](#proper-management)
    - [Safety Measures](#safety-measures)
    - [Conclusion](#conclusion-1)

<!-- markdown-toc end -->

## My Understanding

In this discussion, we'll explore crucial aspects of object lifetime management
in C++, specifically focusing on dynamically allocated memory (objects,
primitives, or any data types) using raw pointers. Raw pointers are a
fundamental part of C++ that allow manual control over memory allocation and
deallocation but require careful management to avoid common pitfalls such as
memory leaks and dangling pointers.

### Key Principles of Raw Pointer Management

1. Allocation and Deallocation with new/delete:
   When allocating memory on the heap with new, it is essential to pair it with
   delete to deallocate the memory once it's no longer needed. This prevents
   memory leaks, where allocated memory is not freed, consuming resources
   indefinitely.

2. Pointeer Initialization:
   Initialize pointers to `nullptr` upon declaratoin when they are not
   immediately assigned a heap-allocated address. This practice helps in
   identifying uninitialized pointers and prevents accidental dereferencing of
   garbage values.

- It is essential to declare your pointer on the scope where you intend to access
  the data that it references during that scope and typically initialize it as
  nullptr.

3. Scope and Accessibility:
   The scope in which a pointer is declared deteremines where it can be
   accessed. To maintain access to heap-allocated memeory across different parts
   of a program, declare the pointer in a scope that encompasses all its
   intended uses.

- Within any inner scope on the heap, defining a pointer using `new` is acceptable
  as it will remain active throughout the duration of the program until the end of
  the main function.

4. Managing Memory Across Scopes:
   Objects allocated on the heap have lifetimes independent of the scope in
   which they are allocated. However, the pointer variable used to access this
   memeory must be in scope to interact with the allocated memeory or to
   deallocated it.If a pointer goes out of scope, the allocated memeory remains
   until explicitly freed, potentially leading to a memeory leak if no other
   pointer refers to it.

- But the question is whether we can access it if we created (defined) it inside
  an inner scope? The answer varies:

  - You can access the pointer data if you have already declared them in the
    scope that you want to access them from, which we will call a top-level
    scope.
  - If you did not declare the pointer in the scope that you wish to access the
    pointer data, then you will lose the pointer to refer to these data. In this
    case, the data will still be present in memory (memory leak), and you cannot
    refer or access it, as it is not deallocated (freed).

5. Proper Deallocation:
   Properly deallocate memeory usign `delete` as soon as the object is no longer
   needed. After deallocating, immediately set the pointer to `nullptr` to mark
   it as no longer pointing to valid memory. This step is crucial for avoiding
   dangling pointers, which can lead to undefined behavior if dereferenced.

- To release memory allocated with `new`, you need to use `delete` and typically
  should place it at the end of the scope in which you intend to access the
  pointed-to data. It is also recommended to assign the pointer back to `nullptr`
  to prevent accidental access by the user.

6. Memory Leaks and Dangling Pointers:
   Memory leaks occur when dynamically allocated memory is not freed before a
   pointer goes out of scope or is reassigned. Dangling pointers refer to
   pointers that continue to point to memory that has been deallocated. Both
   issues are preventable with diligent memory management practices.

### Best Practices

- Declare pointers in the appropriate scope: Ensure pointers are accessible in
  the scopes where both allocation and deallocation are intended to occur.
- Allocate and deallocate responsibly: Always pair a new with a delete to manage
  the lifecycle of dynamically allocated memory efficiently.
- Use nullptr wisely: Setting a pointer to nullptr after deallocation helps
  prevent misuse of freed memory.

By adhering to these principles and best practices, developers can effectively
manage dynamically allocated memory in C++, avoiding common errors such as
memory leaks and dangling pointers, and ensuring robust and efficient
applications.

### Diagram For Understanding Lifetime

```cpp
                                                                         [WRONG - NOT COMPLETE]                                                      [ CORRECT - COMPLETE]
                                                                            [MEMORY LEAKING]                                                           [MEMORY MANAGED]
+-------------------------------------------------+       +-------------------------------------------------------------+                  +----------------------------------------------------+
|                   EEntity - Class               |       |               Main- function                                |                  |               Main- function                       |
+-------------------------------------------------+       +-------------------------------------------------------------+                  +----------------------------------------------------+
|                                                 |       |                                                             |                  |                                                    |
|class EEntity {                                  |       |  int main(int argc, char* argv[]) {                         |                  |  int main(int argc, char* argv[]) {                |   ------------+
|public:                                          |       |                                                             |                  |                                                    |               |
|    int x;                                       |       |                                                             |                  |    EEntity* eobj_stack_ptr = nullptr;              |               |
|    std::string eobjName;                        |       |                                                             |                  |    EEntity* eobj_heap_ptr = nullptr;               |               |
|    EEntity(int x, std::string name)             |       |                                                             |                  |                                                    |               |
|        : x{x},                                  |       |    // Hypothetical Inner Scope                              |                  |    // Hypothetical Inner Scope                     |               |
|          eobjName{name} {                       |       |    {                                                        |                  |    {                                               |   ------+ I   | O
|        std::cout << RED << "Create an object "  |       |     EEntity ex = EEntity(1, "eobj_stack_ptr");              |                  |     EEntity ex = EEntity(1, "eobj_stack_ptr");     |         | N   | U
|                  << "Object Name: " << YELLOW <<|       |     // Allocate on stack                                    |                  |     // Allocate on stack                           |         | N   | T
|                  this->eobjName                 |       |     EEntity* eobj_stack_ptr = &ex;                          |                  |     eobj_stack_ptr = &ex;                          |         | E   | E
|                  << "of EEnity Class "          |       |                                                             |                  |                                                    |         | R   | R
|                  << RESET                       |       |     // Allocate on heap                                     |                  |     // Allocate on heap                            |         | -   | -
|                  << std::endl;                  |       |     EEntity* eobj_heap_ptr = new EEntity(2,"eobj_heap_ptr");|                  |     eobj_heap_ptr = new EEntity(2,"eobj_heap_ptr");|         | S   | S
|    }                                            |       |     std::cout << "Arriving to the end "                     |                  |     std::cout << "Arriving to the end "            |         | C   | C
|    EEntity()                                    |       |     << "of the hypothetical inner-scope."                   |                  |     << "of the hypothetical inner-scope."          |         | O   | O
|        : x{0} {                                 |       |      << std::endl;                                          |                  |      << std::endl;                                 |         | P   | P
|        std::cout << RED << "Create an object "  |       |    }                                                        |                  |    }                                               |   ------+ E   | E
|                  << "Object Name: " << YELLOW   |       |    std::cout << "Exited the hypothetical"                   |                  |    std::cout << "Exited the hypothetical"          |               |
|                  << this->eobjName              |       |              << "inner-scope." << std::endl;                |                  |              << "inner-scope." << std::endl;       |               |
|                  << "of EEnity Class " << RESET |       |    std::cout << "Arriving to the end"                       |                  |    std::cout << "Arriving to the end"              |               |
|                  << std::endl;                  |       |              << " of the outer-scope."                      |                  |              << " of the outer-scope."             |               |
|    }                                            |       |              << std::endl;                                  |                  |              << std::endl;                         |               |
|    ~EEntity() {                                 |       |    delete eobj_heap_ptr;                                    |                  |    delete eobj_heap_ptr;                           |               |
|       std::cout << RED << "Destroying an object"|       |    eobj_heap_ptr = nullptr;                                 |                  |    eobj_heap_ptr = nullptr;                        |               |
|                  << "Object Name: " << YELLOW   |       |  return 0;                                                  |                  |  return 0;                                         |               |
|                  << this->eobjName              |       |  };                                                         |                  |  };                                                |   ------------+
|                  << " of EEnity Class " << RESET|       +-------------------------------------------------------------+                  +----------------------------------------------------+
|                  << std::endl;                  |                          +                                                                              +
|    }                                            |                          |                                                                              |
|};                                               |                          |                                                                              |
+-------------------------------------------------+                          |                                                                              |
                                                                             |                                                                              |
                                                                             v                                                                              ^
                                                        +----------------------------------------------------------------------------------------------+    |      // - We need to keep the pointer `eobj_heap_ptr` alive during the outer-scope
                                                        |                                        ON-Stack                                              |    |      // - Why, because we need to access its data during the outer-scope.
                                                        +----------------------------------------------------------------------------------------------+    |      // - We first declare it, and initialize it to a nullptr (optional btw)
                                                            - First eobj_stack_ptr pointer got destroyed                                                    |      // - Later the memory gets freed and the pointer set to nullptr to ensure no one can use it.
                                                            - You cannot print it using std::cout out of the inner-scope                                    |
                                                        +----------------------------------------------------------------------------------------------+    |
                                                        |                                        ON-HEAP                                               |    |
                                                        +----------------------------------------------------------------------------------------------+    |
                                                        |    - Declare and define and initialized the eobj_heap_ptr in the inner-scope                 |    |
                                                        |    - You call the delete for a pointer which is not existed in the outer-scope anymore       |    |
                                                        |    - The data of eobj_heap_ptr is still existed but unreachable                              |    |
                                                        |    - Leading to a memory leaking                                                             |    |
                                                        |    - The delete is not working properly as no-pointer to be deleted.                         |    |
                                                        |    - Therefore, the data of `eobj_heap_ptr` is not freed.                                    |    |
                                                        +----------------------------------------------------------------------------------------------+    |
                                                                                                  |                                                         |
                                                                                                  V                                                         |
                                                                                                  |                                                         |
                                                                                                  +------------------------------->-------------------------+
                                                                              - This is because any pointer, whether on the stack or the heap, gets destroyed
                                                                                after exiting the scope in which it was created.
                                                                                - The reason for this is that pointers are typically 64-bit integers (8 bytes)
                                                                                  on a x64 system. As an integer is a primitive type, it gets freed from memory
                                                                                  once it goes out of scope in the function or block where it was declared.

```

### More Insight

To illustrate the scenario where an object allocated on the heap has its
lifetime extended beyond the scope in which it was created, and compare it to an
object allocated on the stack (whose lifetime is limited to the scope it's
created in), let's modify the `object_life_time_concpet` function accordingly.

#### Modified Function with Explanation

```cpp
#include <iostream>

class A_Entity {
public:
    A_Entity() { std::cout << "A_Entity Created" << std::endl; }
    ~A_Entity() { std::cout << "A_Entity Destroyed" << std::endl; }
};

void object_life_time_concpet() {
    A_Entity* heapEntity = nullptr; // Pointer for heap allocation
    A_Entity* stackEntityPtr = nullptr; // Pointer to hold address of stack object

    // Inner scope
    {
        A_Entity stackEntity; // Stack object, lifetime limited to this scope
        stackEntityPtr = &stackEntity; // Save address of stack object (unsafe to use outside this scope)

        heapEntity = new A_Entity(); // Heap object, lifetime managed manually

        // At this point, both objects are alive.
    } // Exiting scope: stackEntity is destroyed, but heapEntity remains alive.

    // stackEntityPtr is now a dangling pointer, as stackEntity's lifetime has ended.
    // heapEntity is still valid, as it was allocated on the heap and not yet deleted.

    // It's safe to use heapEntity here
    delete heapEntity; // Manually delete heap object to prevent memory leak
    heapEntity = nullptr; // Prevent dangling pointer

    std::cout << "Exited the hypothetical inner-scope." << std::endl;
}

int main() {
    object_life_time_concpet();
    return 0;
}
```

#### Key Points and Comparison

- **Stack Allocation (`A_Entity stackEntity;`)**: The object `stackEntity` is
  created on the stack within the inner scope. Its lifetime is automatically
  managed by the C++ runtime, which means it is constructed when the block is
  entered and destroyed when the block is exited. Attempting to access it
  outside its scope (e.g., via `stackEntityPtr`) leads to undefined behavior
  because it no longer exists after the scope ends.

- **Heap Allocation (`heapEntity = new A_Entity();`)**: The object pointed to by
  `heapEntity` is allocated on the heap. Unlike the stack object, its lifetime
  is not tied to the scope it's created in. It remains alive until it is
  explicitly deleted using `delete`. This allows the object's lifetime to be
  extended beyond the scope of its creation, giving you more control over its
  lifetime. However, it also introduces the responsibility of manually managing
  the object's lifetime to avoid memory leaks.

#### Conclusion

This example demonstrates that objects allocated on the heap have lifetimes that
can extend beyond the scope they were created in, provided they are not deleted.
In contrast, objects allocated on the stack are automatically destroyed when
their defining scope ends. Managing heap-allocated objects requires careful
attention to when they are deleted to prevent memory leaks and dangling
pointers.

### How about this

We have captured a key point about memory management and scope in C++. If you
allocate an object on the heap within a scope and don't maintain a pointer to
that object outside of the scope, you lose the ability to access or delete that
object once you exit the scope. This results in a memory leak because the memory
allocated for the object remains occupied, and you have no way to free it. The
object itself is still "alive" in the sense that its memory is allocated, but it
becomes unreachable, making it impossible to interact with or delete properly.

Here's a simplified example to illustrate this:

```cpp
void createLeak() {
    // Inner scope
    {
        A_Entity* localHeapEntity = new A_Entity(); // Heap object allocated
        // localHeapEntity is accessible and usable within this scope.
    } // Exiting scope

    // At this point, localHeapEntity goes out of scope.
    // The allocated A_Entity object on the heap is now a memory leak.
    // We cannot access or delete the A_Entity object anymore.
}

int main() {
    createLeak();
    // The leaked memory remains allocated until the program terminates.
    return 0;
}
```

#### How to Avoid Memory Leaks

To prevent such memory leaks, ensure that you maintain access to heap-allocated
objects as long as you need them, and then delete them when they are no longer
required. If an object's lifetime should extend beyond its current scope, you
can:

- Return the pointer from the function.
- Store the pointer in a data structure that persists beyond the scope of the
  allocation.
- Pass the pointer to another function or object that takes over responsibility
  for it.

Here's how you might modify the function to return the heap-allocated object:

```cpp
A_Entity* createAndReturnEntity() {
    A_Entity* heapEntity = new A_Entity(); // Heap object allocated
    return heapEntity; // Return pointer to the allocated object
}

int main() {
    A_Entity* myEntity = createAndReturnEntity();
    // Use myEntity...

    delete myEntity; // Clean up when done
    myEntity = nullptr; // Prevent dangling pointer
    return 0;
}
```

In this revised example, the heap-allocated object is returned to the caller of
`createAndReturnEntity()`, allowing the caller to manage the object's lifetime,
use it, and ultimately delete it to prevent a memory leak.

## Lifetime - Introduction

In C++, the concept of "lifetime" refers to the duration during which an object
or variable exists in memory and is valid to use. This concept is crucial for
understanding memory management, avoiding bugs, and optimizing the performance
of your programs. When discussing the lifetime of objects on the stack, we're
focusing on automatic storage duration, which is one of the storage durations
defined by the C++ standard.

### What is it?

The lifetime of an object on the stack begins when its declaration is
encountered during the execution of a block of code and ends when the block is
exited, either by the normal control flow reaching the end of the block or by
other means such as a return statement or an exception being thrown. Objects on
the stack are automatically constructed and destroyed, hence the term "automatic
storage duration."

### Why We Need It

1. **Resource Management**: Automatic management of object lifetimes helps
   ensure that resources such as memory and system handles are properly released
   when they are no longer needed, preventing resource leaks.
2. **Deterministic Destruction**: Knowing exactly when an object will be
   destroyed (at the end of its scope) allows for deterministic resource
   cleanup, making the program more predictable and easier to understand.
3. **Performance**: Stack allocation is generally faster than heap allocation,
   as it involves merely moving the stack pointer. Automatic deallocation helps
   keep the stack usage efficient and minimizes memory fragmentation.

### How to Use It

Using stack memory in C++ is straightforward. Variables and objects declared
within a function or block scope are automatically allocated on the stack.
Here's a simple example:

```cpp
void myFunction() {
    int myStackVariable = 42; // Begins life here
    // Use myStackVariable
} // Ends life here, as the function scope ends
```

### Common Things to Consider

- **Lifetime**: Ensure that you do not access variables out of their scope.
  Accessing a variable after its lifetime has ended results in undefined
  behavior.
- **Automatic Destruction**: Be aware that objects with automatic storage
  duration will have their destructors called automatically when their lifetime
  ends. This is particularly important for objects that manage resources like
  file handles or mutexes.
- **Stack Size Limit**: The stack has a limited size, determined by the
  operating system. Large allocations should be made on the heap to avoid stack
  overflow.
- **Temporary Objects**: Be mindful of the lifetime of temporary objects, as
  they can be destroyed at the end of the expression in which they were created,
  which might be earlier than you expect.

### Examples

**Correct Use:**

```cpp
void exampleFunction() {
    std::string greeting = "Hello, World!"; // Allocation on the stack
    std::cout << greeting << std::endl; // Safe to use greeting here
} // greeting is automatically destroyed here
```

**Potential Mistake:**

```cpp
std::string* dangerousFunction() {
    std::string localString = "I'm on the stack";
    return &localString; // Dangerous: returning address of a stack-allocated object
} // localString is destroyed here, leaving a dangling pointer
```

In the second example, returning a pointer to a stack-allocated object leads to
undefined behavior because the object `localString` is destroyed when
`dangerousFunction` returns. This illustrates the importance of understanding
object lifetimes and scopes when working with stack memory in C++.

## Stack Frame

A stack frame, in the context of programming, particularly in C++, is
essentially a block of memory on the call stack that contains all the
information needed to execute a function. Let's simplify this concept with an
easy-to-understand analogy and then explain its components.

### Analogy: A Box for Each Task

Imagine you're working on various tasks at your desk, and for each task, you use
a box to keep all the items you need—documents, tools, notes. When you start a
task, you take a new box (create a stack frame), place everything you need for
this task inside (variables, return address, etc.), and work on it. If a task
requires you to start another task, you pause the current one, put its box aside
(but keep it within reach), and start a new box for the new task. Once a task is
completed, you remove the box from your desk (destroy the stack frame), and if
there was a previous task paused, you bring back its box and continue where you
left off.

### Components of a Stack Frame

When a function is called in C++, a stack frame is created for that function
call on the call stack. This stack frame includes:

1. **Function Parameters**: The inputs to the function.
2. **Return Address**: The point in the program to return to once this function
   call is completed.
3. **Local Variables**: Variables declared within the function. They exist only
   as long as the function's stack frame is active.
4. **Bookkeeping Information**: This can include things like the previous stack
   frame's base pointer, which helps in navigating back to the caller's stack
   frame.

### How It Works

When a function is called:

- A stack frame is pushed onto the call stack.
- It includes space for the function's parameters, its local variables, and the
  return address.
- The function executes using the information in its stack frame.
- Once the function completes, its stack frame is popped off the stack, and
  control returns to the return address specified in the stack frame.

### Simplified Example

```cpp
void sayHello() {
    std::string message = "Hello, World!"; // Local variable in sayHello's stack frame
    std::cout << message << std::endl;
}

int main() {
    sayHello(); // A stack frame is created for sayHello()
    return 0; // Returning to the OS. main's stack frame is popped off the stack.
}
```

In this example:

- Calling `sayHello()` from `main` creates a new stack frame for `sayHello`.
- This stack frame contains the local variable `message`.
- After `sayHello` is executed, its stack frame is removed, returning to `main`.

The stack frame is crucial for managing function calls, parameters, and local
variables, ensuring that each function has its own isolated environment to
operate in, without interfering with other functions.

## Important - Delete a heap-pointer?

Heap pointer means a pointer (address) to a data allocated on the heap, which
can be either primitive, class-object, other structures ..etc. allocated using
the `new` keyword.

- When you delete a pointer to an object that was allocated on the heap in C++,
  several things happen to ensure the proper cleanup of the object and the
  reclamation of the memory it used. Here's a step-by-step breakdown:

1. **Destructor Call**: First, the destructor of the object is called. The
   destructor is a special member function of the class that is designed to
   perform cleanup tasks specific to the object, such as releasing resources,
   closing file handles, or freeing up any dynamically allocated memory that the
   object itself might have allocated during its lifetime. This step ensures
   that the object has a chance to properly tidy up its state before the memory
   is reclaimed.
2. **Memory Deallocation**: After the destructor has completed its work, the
   memory that was allocated for the object on the heap is deallocated and
   returned to the heap, making it available for future allocations. This means
   that the actual memory location that the object occupied is now considered
   free, and the heap memory manager can reuse it for subsequent `new`
   operations.
3. **Pointer Becomes Dangling**: The pointer that was used to delete the object
   now points to a memory location that has been deallocated. Such a pointer is
   known as a dangling pointer. Accessing or dereferencing a dangling pointer is
   undefined behavior because the memory it points to is no longer valid for use
   by that object. It's good practice to set the pointer to `nullptr` after
   deletion to avoid accidental use.

### Is All Data Deleted?

Yes, all the data associated with the object itself, including its member
variables, is destroyed once the object's destructor has been called and the
memory has been deallocated. However, it's important to note a few things:

- **Dynamically Allocated Member Data**: If the object has pointers to other
  dynamically allocated memory (for example, it allocated memory in its
  constructor or during its life), it's the responsibility of the object's
  destructor to `delete` or deallocate that memory. If the destructor does not
  properly clean up this memory, it will result in a memory leak, even though
  the original object itself is destroyed.

- **Static and External Resources**: Static member variables are not stored in
  the same memory area as the object itself (they are not part of the object's
  heap memory allocation), so they are not deleted when an individual object is
  deleted. Similarly, resources external to the program (such as files, network
  connections, etc.) are not automatically cleaned up by deleting an object;
  such cleanup must be explicitly managed by the destructor or other means.

In summary, deleting a pointer to an object on the heap triggers the object's
destructor to perform cleanup and then deallocates the memory used by the
object. Proper management of resources and memory in the destructor is crucial
to prevent leaks and undefined behavior.

## Caution about assign a pointer on Heap

It's not true that you cannot assign a pointer to another object or value before
deleting the object it originally pointed to when using raw pointers in C++.
However, doing so without properly deleting the original object first can lead
to problems such as memory leaks. Let's break down the concerns and practices
related to this scenario:

### Memory Leaks

If you have a pointer pointing to dynamically allocated memory (allocated on the
heap using `new` in C++) and you reassign that pointer to another address
without first deleting the originally allocated memory, you lose your reference
to the originally allocated memory. This means you no longer have a way to
`delete` that memory, leading to a memory leak. Memory leaks occur when your
program loses track of memory allocations, resulting in wasted memory resources
that cannot be reclaimed until the program terminates.

### Proper Management

To avoid memory leaks, you should ensure that you properly manage the lifetime
of dynamically allocated objects. If you need to reassign a pointer to point to
something else, you should `delete` the original object (assuming it was
allocated with `new`) before reassignment:

```cpp
int* ptr = new int(10); // Dynamically allocated memory
// Use ptr
delete ptr; // Delete the allocated memory
ptr = new int(20); // Reassign ptr to a new address
// Use ptr again
delete ptr; // Clean up the new allocation
```

### Safety Measures

To avoid dangling pointers (pointers pointing to deallocated or invalid memory
regions), it's good practice to set pointers to `nullptr` after deleting the
memory they point to:

```cpp
delete ptr;
ptr = nullptr;
```

This practice helps prevent accidental dereferencing or deletion of already
deleted memory, which can lead to undefined behavior.

### Conclusion

You can reassign a raw pointer to point to another object or memory location
before deleting the memory it originally pointed to, but doing so without proper
deletion of the original memory leads to memory leaks. Proper resource
management, including deleting dynamically allocated memory before reassignment
and setting pointers to `nullptr` after deletion, is crucial when working with
raw pointers in C++ to ensure the robustness and reliability of your programs.
