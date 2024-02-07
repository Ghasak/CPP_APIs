# Classes In Action

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Classes In Action](#classes-in-action)
    - [Class Common Implementation](#class-common-implementation)
        - [Constructors](#constructors)
        - [Destructor](#destructor)
        - [Operator Overloads](#operator-overloads)
        - [Member Functions](#member-functions)
        - [Representation in `main` Function](#representation-in-main-function)
        - [Table Summary](#table-summary)
    - [Focus on Copy and Move](#focus-on-copy-and-move)
        - [Copy Constructor (`Vector(const Vector& other)`)](#copy-constructor-vectorconst-vector-other)
        - [Move Constructor (`Vector(Vector&& other) noexcept`)](#move-constructor-vectorvector-other-noexcept)
        - [Copy Assignment Operator (`Vector& operator=(const Vector& other)`)](#copy-assignment-operator-vector-operatorconst-vector-other)
        - [Move Assignment Operator (`Vector& operator=(Vector&& other) noexcept`)](#move-assignment-operator-vector-operatorvector-other-noexcept)
        - [Passing Objects to Functions](#passing-objects-to-functions)
        - [Summary](#summary)
    - [Classes Fundamental topics:](#classes-fundamental-topics)
    - [Classes Templates](#classes-templates)

<!-- markdown-toc end -->

## Class Common Implementation

Assuming we have the following Class prototype:

```cpp
class Vector {
public:
    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;
    ~Vector();
public:
    void push_back(int value);
    void insert(int index, int value);
    void remove(int index);
    int operator[](int index);
    int size() const;
    int capacity() const;
private:
    int size_;
    int capacity_;
    int* array_;
};
```

This class `Vector` is a simplified version of the STL (Standard Template
Library) vector in C++, designed to manage a dynamically allocated array. Let's
break down each part and explain the concepts behind them:

### Constructors

- **Default Constructor (`Vector();`):** Initializes a new instance of the
  class. It's used to set initial values for member variables.

  - Syntax: `Vector::Vector() : size_(0), capacity_(0), array_(nullptr) {}`

- **Copy Constructor (`Vector(const Vector&);`):** Initializes a new instance as
  a copy of an existing instance. It's necessary for deep copying the internal
  array.

  - Syntax: `Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), array_(new int[other.capacity_]) { std::copy(other.array_, other.array_ + other.size_, array_); }`

- **Move Constructor (`Vector(Vector&&) noexcept;`):** Transfers the resources
  of a temporary object to a new object. It improves performance by eliminating
  unnecessary copying.
  - Syntax: `Vector::Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), array_(other.array_) { other.array_ = nullptr; other.size_ = 0; other.capacity_ = 0; }`

### Destructor

- **Destructor (`~Vector();`):** Releases resources when an instance is destroyed. For this class, it deallocates the dynamically allocated array.
  - Syntax: `Vector::~Vector() { delete[] array_; }`

### Operator Overloads

- **Copy Assignment Operator (`Vector& operator=(const Vector&);`):** Assigns
  the contents of one object to another, replacing its current contents.

  - Syntax: `Vector& Vector::operator=(const Vector& other) { if (this != &other) { delete[] array_; size_ = other.size_; capacity_ = other.capacity_; array_ = new int[capacity_]; std::copy(other.array_, other.array_ + size_, array_); } return *this; }`

- **Move Assignment Operator (`Vector& operator=(Vector&&) noexcept;`):**
  Transfers the resources of one object to another, similar to the move
  constructor.

  - Syntax: `Vector& Vector::operator=(Vector&& other) noexcept { if (this != &other) { delete[] array_; size_ = other.size_; capacity_ = other.capacity_; array_ = other.array_; other.array_ = nullptr; other.size_ = 0; other.capacity_ = 0; } return *this; }`

- **Subscript Operator (`int operator[](int index);`):** Provides direct access
  to the internal array elements.
  - Syntax: `int Vector::operator[](int index) { return array_[index]; }`

### Member Functions

- **`push_back(int value);`** Adds a new element at the end of the vector.
- **`insert(int index, int value);`** Inserts a new element at the specified index.
- **`remove(int index);`** Removes the element at the specified index.
- **`size() const;`** Returns the number of elements.
- **`capacity() const;`** Returns the current capacity of the vector.

### Representation in `main` Function

```cpp
#include <iostream>
#include "Vector.h" // Assume Vector class is defined in this header

int main() {
    Vector vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.insert(1, 15); // Insert 15 at index 1
    std::cout << "Element at index 1: " << vec[1] << std::endl;
    vec.remove(1); // Remove the element at index 1
    std::cout << "Vector size: " << vec.size() << std::endl;

    // Copy and Move operations
    Vector vecCopy = vec; // Invokes copy constructor
    Vector vecMoved = std::move(vec); // Invokes move constructor
}
```

### Table Summary

| Method              | Syntax                                  | Purpose                                       | Concept                     |
| ------------------- | --------------------------------------- | --------------------------------------------- | --------------------------- |
| Default Constructor | `Vector();`                             | Initialize default state                      | Initialization              |
| Copy Constructor    | `Vector(const Vector&);`                | Initialize from another instance              | Deep copying                |
| Move Constructor    | `Vector(Vector&&) noexcept;`            | Transfer resources                            | Resource ownership transfer |
| Destructor          | `~Vector();`                            | Clean up resources                            | Resource management         |
| Copy Assignment     | `Vector& operator=(const Vector&);`     | Assign one instance to another                | Deep copying                |
| Move Assignment     | `Vector& operator=(Vector&&) noexcept;` | Transfer resources of one instance to another | Resource ownership transfer |
| `push_back`         | `void push_back(int value);`            | Add element at the end                        | Dynamic resizing            |
| `insert`            | `void insert(int index                  |

## Focus on Copy and Move

These methods are crucial for managing object resources efficiently in C++.
Let's dive deeper into each and explain the significance of `noexcept` and their
behavior in various scenarios, including passing objects by value.

### Copy Constructor (`Vector(const Vector& other)`)

This constructor creates a new object as a copy of an existing object. It's
essential for scenarios where you need to pass or return objects by value
without altering the original object.

```cpp
Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), array_(new int[other.capacity_]) {
    std::copy(other.array_, other.array_ + other.size_, array_);
}
```

**Example in main:**

```cpp
Vector v1;
v1.push_back(1);
Vector v2 = v1; // Copy constructor is called here
```

### Move Constructor (`Vector(Vector&& other) noexcept`)

The move constructor transfers resources (like dynamically allocated memory)
from a temporary object to a new object. The `noexcept` specifier is crucial
because it informs the compiler that this operation will not throw exceptions,
allowing optimizations like moving objects instead of copying when resizing
containers or when exceptions occur.

```cpp
Vector::Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), array_(other.array_) {
    other.array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}
```

**Example in main:**

```cpp
Vector v3;
v3 = Vector(); // Move constructor is called here due to temporary Vector object
```

### Copy Assignment Operator (`Vector& operator=(const Vector& other)`)

This operator replaces the current object's contents with a copy of another
object's contents. It's crucial for ensuring deep copies of resources to prevent
issues like dangling pointers.

```cpp
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = new int[capacity_];
        std::copy(other.array_, other.array_ + size_, array_);
    }
    return *this;
}
```

**Example in main:**

```cpp
Vector v4;
v4.push_back(2);
Vector v5;
v5 = v4; // Copy assignment operator is called here
```

### Move Assignment Operator (`Vector& operator=(Vector&& other) noexcept`)

Similar to the move constructor, this operator transfers resources from one
object to another, with the `noexcept` guarantee facilitating optimizations.
It's used when an object is assigned from a temporary object or a returned
value.

```cpp
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = other.array_;
        other.array_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}
```

**Example in main:**

```cpp
Vector v6;
v6 = std::move(v5); // Move assignment operator is called here
```

### Passing Objects to Functions

When you pass a `Vector` object to a function by value, the copy constructor is
invoked to create a copy of the object. This mechanism ensures that the function
operates on a copy rather than the original object, preserving the original's
state.

```cpp
void processVector(Vector v) {
    // Function body - operates on a copy of the object
}

Vector v7;
processVector(v7); // Copy constructor is invoked here
```

If the function returns a `Vector` object by value, and compiler optimizations
like Return Value Optimization (RVO) or Named Return Value Optimization (NRVO)
are not applied, the move constructor might be invoked for the returned object.

```cpp
Vector createVector() {
    Vector v;
    // Modify v
    return v; // Move constructor may be invoked here due to return by value
}

Vector v8 = createVector();
```

### Summary

- **Copy Constructor:** Ensures deep copies, used when passing/returning objects
  by value or explicitly copying.
- **Move Constructor (`noexcept`):** Transfers resources efficiently, `noexcept`
  optimizes its use in containers and exception handling.
- **Copy Assignment Operator:** Replaces an object's contents with a copy of
  another's.
- **Move Assignment Operator (`noexcept`):** Efficiently reassigns resources,
  with `noexcept` indicating safe use in containers and for exception safety.
- **Passing Objects by Value:** Invokes copy or move constructors, depending on
  context and compiler optimizations, ensuring object state is managed safely
  across function calls.

## Classes Fundamental topics:

The classes in C++ encompass the following concepts:
Sure, here's a list of fundamental concepts related to classes in C++:

1. **Class Definition:** The blueprint for creating objects. It defines a new
   data type which includes data members (attributes) and member functions
   (methods).
2. **Object:** An instance of a class. Each object has its own identity and
   attributes.
3. **Access Specifiers:** Define the access level of class members. The primary
   ones are `public`, `private`, and `protected`.
4. **Constructor:** A special member function that is automatically called when
   an object is created. It initializes the object's attributes.
5. **Destructor:** A special member function that is automatically called when
   an object is destroyed. It's used to clean up resources.
6. **Copy Constructor:** A constructor used to create a new object as a copy of
   an existing object.
7. **Assignment Operator:** Used to copy the values from one object to another
   existing object.
8. **this Pointer:** A pointer that refers to the object which invoked the
   member function.
9. **Inline Functions:** Functions defined inside the class declaration. They
   can speed up execution for small, frequently called functions.
10. **Friend Functions:** Functions that are not members of a class but can
    access the class's private and protected members.
11. **Static Members:** Class members that are shared by all objects of the
    class. There's only one copy of a static member for the entire class.
12. **Member Functions:** Functions that are declared and defined within a
    class.
13. **Inheritance:** A way to form new classes using classes that have already
    been defined.
14. **Polymorphism:** The ability of different classes to be treated as
    instances of the same class through inheritance.
15. **Virtual Functions:** Member functions which are expected to be redefined
    in derived classes. They enable runtime polymorphism.
16. **Abstract Classes and Pure Virtual Functions:** Classes that can't be
    instantiated. They are used to define interfaces.
17. **Operator Overloading:** The ability to redefine the meaning of an operator
    (like +, -, etc.) for user-defined types.
18. **Friend Classes:** A class that is declared as a friend of another class is
    able to access private and protected members of the other class.
19. **Encapsulation:** The bundling of data with the methods that operate on
    that data, and restricting direct access to some of an object's components.
20. **Inheritance Hierarchy:** The structure formed by classes inheriting from
    other classes.

These concepts form the basis of object-oriented programming in C++ and are
essential for effective use of the language.

## Classes Templates

Class templates in C++ are a powerful feature used for creating generic or
parameterized classes. Here are the key concepts associated with class
templates, presented as bullet points:

1. **Template Definition:** A way to define a class with a placeholder for data
   types. It allows the class to handle data of any type.
2. **Template Parameters:** These are placeholders for data types or values.
   They are specified within angle brackets (`< >`) after the `template`
   keyword.
3. **Instantiation of Template Classes:** Creating objects of a template class.
   The compiler generates a new class for each set of template arguments
   provided.
4. **Member Functions of Template Classes:** Just like regular classes, template
   classes can have member functions, which can also be templates.
5. **Default Template Arguments:** Similar to function templates, class
   templates can have default arguments, allowing some parameters to be
   optional.
6. **Template Specialization:** Creating a specific implementation of a template
   for a particular data type. This is useful when a generic implementation is
   not suitable.
7. **Partial Template Specialization:** Specializing only some parameters of a
   template class, while keeping others generic.
8. **Nested Template Classes:** Templates can be nested within other templates,
   allowing for complex data structures.
9. **Non-type Template Parameters:** Apart from types, template parameters can
   also be values like integers. This allows for more flexible and powerful
   templating.
10. **Template Template Parameters:** A template parameter can itself be a
    template, allowing for even more abstraction and flexibility.
11. **Template Metaprogramming:** An advanced use of templates to perform
    computations at compile-time, resulting in highly efficient runtime code.
12. **Type Traits and Type Manipulation:** Using templates to gather information
    about types or to manipulate types, often used in template metaprogramming.
13. **SFINAE (Substitution Failure Is Not An Error):** A principle in template
    metaprogramming where the failure of template argument substitution is not
    treated as an error but causes the template instantiation to be discarded in
    certain contexts.

Class templates are a fundamental tool in C++ for creating flexible and reusable
code. They are widely used in the Standard Template Library (STL), which is part
of the C++ standard library.
