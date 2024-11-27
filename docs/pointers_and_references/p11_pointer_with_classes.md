# Pointers with Classes

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Pointers with Classes](#pointers-with-classes)
    - [Intro](#intro)
    - [1. Pointer and Object of a Class in C++](#1-pointer-and-object-of-a-class-in-c)
    - [2. Why Use Pointers for Class Members?](#2-why-use-pointers-for-class-members)
    - [3. Usage Scenarios with Examples](#3-usage-scenarios-with-examples)
        - [3.1. Dynamic Memory Management](#31-dynamic-memory-management)
        - [3.2. Implementing Polymorphism](#32-implementing-polymorphism)
        - [3.3. Efficiently Managing Large Objects](#33-efficiently-managing-large-objects)
        - [3.4. Complex Data Structures](#34-complex-data-structures)
    - [4. Pointers allocated on Heap](#4-pointers-allocated-on-heap)
        - [4.1 Pointer Storage Practices](#41-pointer-storage-practices)
        - [4.2 Common Scenarios](#42-common-scenarios)
        - [4.3. Is It Common for a Pointer to Be on the Heap?](#43-is-it-common-for-a-pointer-to-be-on-the-heap)

<!-- markdown-toc end -->

## Intro

Here, we will talk about the situation which we will have a pointer as a memeber
of a class. It can be an attribute which is just a poiinter to a piece of data
on memory, or could be a method which passes or return a pointer.

In object-oriented programming, particularly in languages like C++ and Java,
pointers and objects are fundamental concepts that allow for dynamic memory
management, polymorphism, and more complex data structures.

In C++, pointers and objects are crucial for managing memory, implementing
polymorphism, and facilitating complex data structures and algorithms. Here's a
deeper dive into these concepts specifically in C++.

## 1. Pointer and Object of a Class in C++

- **Object:** In C++, an object is an instance of a class. A class defines a
  blueprint for its objects, specifying their attributes (data members) and
  behaviors (member functions or methods). When you create an object, C++
  allocates memory for that object and initializes it according to the class
  definition.

- **Pointer:** A pointer in C++ is a variable that stores the memory address of
  another variable. For class objects, a pointer can store the address of an
  object. This allows you to indirectly access and manipulate the object.

## 2. Why Use Pointers for Class Members?

Pointers are used as class members for several reasons:

1. **Dynamic Memory Management:** You can allocate and deallocate memory at
   runtime using pointers. This is useful for creating data structures whose
   size changes during execution, such as linked lists, trees, and graphs.

2. **Polymorphism:** Pointers to base class types can be used to refer to
   objects of derived classes. This allows for dynamic polymorphism, where the
   decision about which method to invoke is made at runtime based on the
   object's actual type.

3. **Efficiency:** Storing a pointer to an object instead of the object itself
   can be more memory efficient, especially for large classes or structures. It
   also enables the sharing of instances among multiple parts of a program,
   avoiding unnecessary duplication.

4. **Flexibility:** Pointers can be used to implement complex data structures,
   facilitate dynamic memory allocation, and enable polymorphism, making the
   code more flexible and reusable.

## 3. Usage Scenarios with Examples

### 3.1. Dynamic Memory Management

```cpp
class MyClass {
public:
    int data;
    MyClass(int val) : data(val) {}
};

int main() {
    MyClass* objPtr = new MyClass(10); // Dynamically allocated object
    std::cout << objPtr->data << std::endl; // Accessing object's member
    delete objPtr; // Freeing memory
}
```

### 3.2. Implementing Polymorphism

```cpp
class Base {
public:
    virtual void show() { std::cout << "Base class\n"; }
};

class Derived : public Base {
public:
    void show() override { std::cout << "Derived class\n"; }
};

int main() {
    Base* basePtr;
    Derived d;
    basePtr = &d;
    basePtr->show(); // Displays "Derived class"
}
```

### 3.3. Efficiently Managing Large Objects

```cpp
class LargeObject {
    // Assume this class has a lot of data and methods
};

class Manager {
    LargeObject* largeObjPtr; // Pointer to avoid copying large object
public:
    Manager(LargeObject* obj) : largeObjPtr(obj) {}
    void operate() {
        // Operations on largeObjPtr
    }
};
```

### 3.4. Complex Data Structures

```cpp
class Node {
public:
    int value;
    Node* next; // Pointer to the next node in the list
    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
    Node* head; // Pointer to the head of the list
public:
    LinkedList() : head(nullptr) {}
    void add(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
};
```

In each scenario, pointers are used to provide flexibility in memory management,
enable dynamic polymorphism, manage large objects efficiently, and implement
complex data structures. These capabilities make pointers an essential feature
of C++.

## 4. Pointers allocated on Heap

Allocating an object on the heap typically means that the memory for the object
itself is allocated on the heap. The pointer used to access this object,
however, is usually stored on the stack, not on the heap. This is a common
practice in C++ and other languages that use manual memory management. The
distinction between where the pointer is stored and where the object it points
to is stored is crucial for understanding memory management in such languages.

### 4.1 Pointer Storage Practices

- **Pointer on the Stack**: When you declare a pointer variable in a function to
  point to a heap-allocated object (using `new`, for example), the pointer
  variable itself is usually stored on the stack. This is the most common case,
  such as when you do something like: `cpp Entity* ptr = new Entity(); `
  Here, `ptr` is stored on the stack, while the `Entity` object it points to is
  stored on the heap.

- **Pointer on the Heap**: A pointer can also be stored on the heap, but this
  typically happens in a different context. For instance, when you have an
  object that contains a pointer to another object, and the first object is
  allocated on the heap, then the pointer (as part of the first object's data)
  is also on the heap. Another scenario is when you dynamically allocate an
  array of pointers; the pointers themselves are stored on the heap:

  ```cpp
  Entity** ptrArray = new Entity*[10]; // Array of pointers on the heap
  ```

### 4.2 Common Scenarios

- **Local Variables and Function Calls**: Pointers declared as local variables
  in functions are stored on the stack. These pointers can point to objects
  allocated on the heap.
- **Class Members and Dynamic Arrays**: When an object contains pointer members
  and the object is allocated on the heap, those pointers are part of the
  object's memory layout on the heap. Similarly, when you create dynamic arrays
  of pointers, the array (and thus the pointers within it) is stored on the
  heap.
- **Nested Objects**: If a heap-allocated object contains other objects as
  members (not pointers, but actual objects), those nested objects are also
  stored on the heap as part of the enclosing object's memory space.

### 4.3. Is It Common for a Pointer to Be on the Heap?

Yes, in certain contexts:

- When the pointer is part of a heap-allocated object's data.
- When dynamically allocating arrays of pointers.

However, in the straightforward case of allocating a single object and keeping a
reference to it in a local variable, the pointer itself is typically stored on
the stack, while the object it points to is stored on the heap. This distinction
allows for efficient management of the pointer's lifecycle, which is typically
tied to the scope of the function or block in which it is declared, contrasting
with the manually managed lifecycle of the heap-allocated object.
