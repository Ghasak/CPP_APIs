# Virtual Functions

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Virtual Functions](#virtual-functions)
  - [1. My Understanding](#1-my-understanding)
    - [1.1. Without Using Virtual](#11-without-using-virtual)
    - [1.2. Using Virtual](#12-using-virtual)
  - [2. Introduction to Virtual Functions](#2-introduction-to-virtual-functions)
    - [2.1. Why Use Virtual Methods?](#21-why-use-virtual-methods)
    - [2.2. Common Practices and Notes](#22-common-practices-and-notes)
    - [2.3. Example Without Virtual Methods](#23-example-without-virtual-methods)
    - [2.4. Example With Virtual Methods](#24-example-with-virtual-methods)
    - [2.5. Allocation on Heap and Dereferencing](#25-allocation-on-heap-and-dereferencing)
    - [2.6. Expected Results](#26-expected-results)
  - [3. Why we need Virtual Functions Clarification](#3-why-we-need-virtual-functions-clarification)
    - [3.1 Polymorphism](#31-polymorphism)
    - [3.2. Code Reusability and Extensibility](#32-code-reusability-and-extensibility)
    - [3.3. Decoupling](#33-decoupling)
    - [3.4. Design Patterns](#34-design-patterns)
    - [3.5. Dynamic Binding](#35-dynamic-binding)
    - [3.6. Example Scenario:](#36-example-scenario)
    - [3.7. Conclusion](#37-conclusion)
  - [4. Efficent way to use Virtual Methods](#4-efficent-way-to-use-virtual-methods)
    - [4.1. C++ Code Example:](#41-c-code-example)
    - [4.2. Explanation:](#42-explanation)
    - [4.3. Expected Output:](#43-expected-output)
  - [5. Dynamic Dispatch and Virtual (V) Table](#5-dynamic-dispatch-and-virtual-v-table)
    - [5.1. Virtual Table (v-table)](#51-virtual-table-v-table)
    - [5.2. Dynamic Dispatch](#52-dynamic-dispatch)
    - [5.3. Correcting Understanding](#53-correcting-understanding)

<!-- markdown-toc end -->

## 1. My Understanding

Virtual functions stem from the concept of polymorphism, and when there are
similar function names between a parent class and a child class, we want to
access the child class method rather than the parent's similar name method.

- This occurs consistently, as far as I know, when we create something that
  involves both ChildClass and ParentClass, which share a similarly named method
  called SimilarMethod().
  - Suppose both ChildClass and ParentClass possess a method named SimilarMethod,
    which share similar characteristics.
  - We want to make our ParentClass objects called method (virtual method) to
    follow the method for the ChildClass. Thats why you will see, it is common
    to find `ChildClass c = ChildClass(); ParentClass* ptr = &c;` and access
    using `c->SimilarMethod()`.

```cpp
ChildClass* child_ptr = new ChildClass();
ParentClass* parent_ptr = child_ptr;
std::cout << parent_ptr->SimilarMethod() << std::endl; <--- [ Without Virtual] This will give us the Parent method `SimilarMethod()`
std::cout << parent_ptr->SimilarMethod() << std::endl; <--- [ Virtual] This will give us the child method `SimilarMethod()`
```
- Some developers prefer to now use them as it has some cost for calling the
  `V-table` to check which method to call.
- Let see how we do that with and without a `Virtual`

### 1.1. Without Using Virtual

```cpp
+---------------------------------------------+         +--------------------------------------+
|         Parent Class - Entity               |         |         Child  Class - Player        |
+---------------------------------------------+         +--------------------------------------+
|                                             |         |                                      |
| class Entity {                              |         | class Player : public Entity {       |
| private:                                    |         | private:                             |
|     std::string m_Name;                     |         |     std::string m_ChildName;         |
|                                             |         |                                      |
| public:                                     |         | public:                              |
|       std::string GetName(){                |         |     Player(const std::string& name)  |
|         return std::string("Entity Object");|         |         : m_ChildName{name} {};      |
|     }                                       |         |     std::string GetName() {          |
| };                                          |         |          return m_ChildName;         |
+---------------------------------------------+         |            }                         |
                                                        | };                                   |
                                                        +--------------------------------------+


+-------------------------------------------------+                     + ---- OUTPUT ---- +
|                 Main                            |                     |  Entity Object   |
+-------------------------------------------------+                     |  Player Object   |
| int main(int argc, char* argv[]) {              |   ----> OUTPUT      |  Entity Object   |
|     // Create the objects - on stack            |                     |  Player Object   |
|     Entity e1;                                  |                     |  Entity Object   |  <---- Here, We want to access the child method not the parent method
|     Player p1(std::string("Player Object"));    |                     + ---------------- +
|     // Accessing the methods directly           |
|     // won't make a problem - no confusion      |
|     std::cout << e1.GetName() << std::endl;     |
|     std::cout << p1.GetName() << std::endl;     |
|                                                 |
|     // Create a pointer for an object on stack  |                // Allocate on Heap (you need to clean them manually)
|     Entity* ptr1 = &e1;                         |                Entity* ptr1 = new Player();
|     Player* ptr2 = &p1;                         |                std::cout << ptr1->GetName()  << std::endl;
|     // Dereferencing the pointer and            |
|     // access the methods also no confusion     |
|     std::cout << ptr1->GetName() << std::endl;  |
|     std::cout << ptr2->GetName() << std::endl;  |
|                                                 |
|     // The problem occur for calling            |
|     // with parent - child                      |
|     Entity* ptr3 = &p1;                         |
|     std::cout << ptr3->GetName() << std::endl;  |
| return 0;                                       |
| }                                               |
+-------------------------------------------------+

```

### 1.2. Using Virtual

```cpp
+---------------------------------------------+         +--------------------------------------+
|         Parent Class - Entity               |         |         Child  Class - Player        |
+---------------------------------------------+         +--------------------------------------+
|                                             |         |                                      |
| class Entity {                              |         | class Player : public Entity {       |
| private:                                    |         | private:                             |
|     std::string m_Name;                     |         |     std::string m_ChildName;         |
|                                             |         |                                      |
| public:                                     |         | public:                              |
|     virtual  std::string GetName(){         |         |     Player(const std::string& name)  |
|         return std::string("Entity Object");|         |         : m_ChildName{name} {};      |
|     }                                       |         |     std::string GetName() overrid{   |  <- Adding override is Optional
| };                                          |         |          return m_ChildName;         |
+---------------------------------------------+         |            }                         |
          ^                                             | };                                   |
          |                                             +--------------------------------------+
          |
          +-- We add virtual keyword here


+-------------------------------------------------+                     + ---- OUTPUT ---- +
|                 Main                            |                     |  Entity Object   |
+-------------------------------------------------+                     |  Player Object   |
| int main(int argc, char* argv[]) {              |   ----> OUTPUT      |  Entity Object   |
|     // Create the objects - on stack            |                     |  Player Object   |
|     Entity e1;                                  |                     |  Player Object   |  <---- Now we access the corresponding child method
|     Player p1(std::string("Player Object"));    |                     + ---------------- +
|     // Accessing the methods directly           |
|     // won't make a problem - no confusion      |
|     std::cout << e1.GetName() << std::endl;     |
|     std::cout << p1.GetName() << std::endl;     |
|                                                 |
|     // Create a pointer for an object on stack  |
|     Entity* ptr1 = &e1;                         |
|     Player* ptr2 = &p1;                         |
|     // Dereferencing the pointer and            |
|     // access the methods also no confusion     |
|     std::cout << ptr1->GetName() << std::endl;  |
|     std::cout << ptr2->GetName() << std::endl;  |
|                                                 |
|     // The problem occur for calling            |
|     // with parent - child                      |
|     Entity* ptr3 = &p1;                         |
|     std::cout << ptr3->GetName() << std::endl;  |
| return 0;                                       |
| }                                               |
+-------------------------------------------------+


```

## 2. Introduction to Virtual Functions

Virtual methods in C++, marked with the `virtual` keyword, are a fundamental
concept of object-oriented programming (OOP) that allows for polymorphism. When
a method is declared as virtual in a base class, it can be overridden in any
derived class. The key feature of virtual methods is that they enable the
runtime system to call the overridden method on a derived class object, even
when accessed through a pointer or reference to the base class. This capability
is crucial for achieving polymorphism, where the exact method to be invoked is
determined at runtime, based on the actual type of the object.

### 2.1. Why Use Virtual Methods?

1. **Polymorphism**: They enable polymorphism, allowing objects of different
   classes to be treated as objects of a common base class, with behavior
   determined by the actual derived class type.
2. **Extensibility**: Virtual methods make it easier to add new classes that
   inherit from existing ones without modifying existing code, fostering an
   extensible design.
3. **Overriding**: They allow derived classes to provide specific
   implementations of a method that is defined in a base class.

### 2.2. Common Practices and Notes

- **Use virtual destructors** in base classes. If a class has virtual
  functions, its destructor should also be virtual. This ensures that the
  destructor of the derived class is called when an object is deleted through a
  pointer to the base class.
- **Override keyword**: Since C++11, it's good practice to use the `override`
  keyword when overriding a virtual method in a derived class. This helps catch
  errors at compile time if the method signature does not match the base class
  method.
- **Final specifier**: C++11 introduced the `final` specifier, which prevents
  further overriding of a method or prevents inheritance from a class.
- **Avoid calling virtual methods in constructors/destructors**: Virtual method
  calls within constructors or destructors will not behave polymorphically. The
  method from the class being constructed or destructed will be called, not an
  override from a derived class.

### 2.3. Example Without Virtual Methods

Let's start with an example without virtual methods:

```cpp
#include <iostream>
#include <string>

class Base {
public:
    std::string GetName() { return "Base"; }
};

class Derived : public Base {
public:
    std::string GetName() { return "Derived"; }
};

int main() {
    Base* b = new Derived();
    std::cout << b->GetName() << std::endl; // Without virtual, this will output "Base"
    delete b;
}
```

### 2.4. Example With Virtual Methods

Now, let's modify the example to use virtual methods:

```cpp
#include <iostream>
#include <string>

class Base {
public:
    virtual std::string GetName() { return "Base"; }
};

class Derived : public Base {
public:
    std::string GetName() override { return "Derived"; }
};

int main() {
    Base* b = new Derived();
    std::cout << b->GetName() << std::endl; // With virtual, this will output "Derived"
    delete b;
}
```

### 2.5. Allocation on Heap and Dereferencing

In both examples above, the objects are allocated on the heap using `new`. To
access methods or members of these objects, you use the `->` operator. The key
difference in behavior between virtual and non-virtual methods is observed when
methods are called on a base class pointer that points to a derived class
object:

- **Without virtual**: The method of the class that the pointer type belongs to
  is called.
- **With virtual**: The method of the class that the object actually is, is
  called, enabling polymorphism.

### 2.6. Expected Results

- **Without virtual functions**, the output is "Base" because the call to
  `GetName()` is resolved at compile time based on the type of the pointer
  `Base*`, not the actual object type it points to.
- **With virtual functions**, the output is "Derived" because the call to
  `GetName()` is resolved at runtime based on the actual object's type, which is
  `Derived`.

This demonstrates the power of virtual functions in supporting runtime
polymorphism, allowing for more flexible and dynamic behavior in C++
applications.

## 3. Why we need Virtual Functions Clarification

The question is as follows: why do we declare `Base* b = new Derived();`
instead of directly declaring `Derived* b = new Derived()`, eliminating the
need for the `Virtual` concept?

- Current observation touches on a fundamental aspect of object-oriented programming
  (OOP).
  - The decision between using base class pointers (or references) versus
    derived class pointers directly. The choice to use `Base* b = new Derived();`
    instead of `Derived* b = new Derived();` relates to design flexibility and the
    principle of polymorphism. While it's true that using a `Derived*` pointer
    directly would eliminate the immediate need for virtual functions in this
    specific scenario, there are several reasons why one might choose to use a base
    class pointer instead Explanation thorugh the following points.

### 3.1 Polymorphism

Polymorphism is a cornerstone of OOP, allowing objects of different classes to
be treated through the same interface. A base class pointer to a derived class
object enables you to write code that works with objects of any class derived
from the base class, without needing to know the exact derived type. This is
especially useful in complex systems where behavior can be extended or modified
by adding new derived classes.

### 3.2. Code Reusability and Extensibility

Using base class pointers to manipulate objects of derived classes makes your
code more reusable and easier to extend. You can add new classes derived from
the base class without changing the code that uses the base class interface.
This adheres to the Open/Closed Principle, one of the SOLID principles of
object-oriented design, which states that software entities should be open for
extension but closed for modification.

### 3.3. Decoupling

Working with base class interfaces reduces dependencies between different parts
of a system. This decoupling means that changes in the implementation of
derived classes do not require changes in the parts of the system that use
these objects through the base class interface. This can significantly simplify
maintenance and evolution of a system.

### 3.4. Design Patterns

Many design patterns rely on the ability to work with objects through
interfaces or abstract classes. For example, the Factory Method pattern creates
objects without specifying the exact class of object that will be created. The
Strategy pattern allows the algorithm to vary independently from the context
using it. Both rely on polymorphism and the use of base class pointers or
references.

### 3.5. Dynamic Binding

The concept of virtual functions and dynamic binding (determining the method to
call at runtime rather than at compile time) is what allows C++ programs to
utilize polymorphism. Without virtual functions, you cannot achieve runtime
polymorphism, which is essential for designing flexible and dynamically
adaptable systems.

### 3.6. Example Scenario:

Imagine a graphics application with a `Shape` base class and various derived
classes like `Circle`, `Rectangle`, and `Triangle`. You might have a collection
(e.g., a vector) of `Shape*` pointers and want to call a `draw()` method on
each shape. With virtual methods, each shape draws itself correctly, regardless
of the shape's actual type. Without using base class pointers and virtual
functions, you'd need separate collections or switch-case statements to handle
each specific type, which is less efficient and harder to extend.

### 3.7. Conclusion

While using `Derived* b = new Derived();` is straightforward and suitable for
scenarios where the exact type is known and fixed, the flexibility,
extensibility, and decoupling offered by using base class pointers and virtual
functions are invaluable in many programming scenarios, particularly when
designing systems that need to scale and evolve over time.

## 4. Efficent way to use Virtual Methods

Let's create a simple C++ example demonstrating the use of virtual functions
with a `Shape` base class and derived classes for `Circle`, `Rectangle`, and
`Triangle`. Each derived class will override a virtual `draw()` method to "draw"
itself by printing a message to the console.

- This example will illustrate how virtual functions enable polymorphism,
  allowing us to treat all shapes uniformly through base class pointers while
  still getting behavior specific to each derived class.

### 4.1. C++ Code Example:

```cpp
#include <iostream>
#include <vector>
#include <memory>

// Base class
class Shape {
public:
    virtual void draw() const {
        std::cout << "Drawing a shape" << std::endl;
    }
    virtual ~Shape() = default;
};

// Derived class: Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a rectangle" << std::endl;
    }
};

// Derived class: Triangle
class Triangle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a triangle" << std::endl;
    }
};

int main() {
    // Creating a vector of Shape pointers
    std::vector<std::unique_ptr<Shape>> shapes;

    // Adding shapes to the vector
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Rectangle>());
    shapes.push_back(std::make_unique<Triangle>());

    // Iterating over the vector and calling the draw method
    for (const auto& shape : shapes) {
        shape->draw();
    }

    return 0;
}
```

### 4.2. Explanation:

- The `Shape` class is a base class with a virtual `draw()` method, which can be
  overridden by derived classes.
- `Circle`, `Rectangle`, and `Triangle` are derived classes that override the
  `draw()` method to provide specific implementations.
- We use a vector of `std::unique_ptr<Shape>` to store pointers to `Shape`
  objects. This allows us to treat all shapes uniformly through base class
  pointers. `std::unique_ptr` is a smart pointer that manages the lifetime of
  the objects, ensuring they are properly deleted when no longer needed,
  preventing memory leaks.
- We iterate over the vector and call the `draw()` method on each shape. Due to
  polymorphism, the correct `draw()` method is called for each object, based on
  its actual type, even though we're using base class pointers.

### 4.3. Expected Output:

```
Drawing a circle
Drawing a rectangle
Drawing a triangle
```

This output demonstrates that each shape "draws" itself correctly, according to
its type, even though we're invoking the `draw()` method through pointers to the
base class. This is the power of virtual functions and polymorphism in C++,
allowing for flexible and extendable designs without the need for explicit type
checks or casting.

## 5. Dynamic Dispatch and Virtual (V) Table

The inquiry touches on some core concepts of object-oriented programming in C++
and other languages that support polymorphism through virtual methods. Let's
clarify these concepts:

### 5.1. Virtual Table (v-table)

A virtual table, or v-table, is an implementation detail used by C++ compilers
to support dynamic dispatch (runtime method binding) for classes with virtual
functions. When a class has one or more virtual functions:

- A v-table is created by the compiler for that class. This v-table contains
  pointers to the virtual functions defined or inherited by the class.
- Each object of a class with virtual functions has a hidden pointer (often
  called the v-pointer) that points to the v-table of its class. This ensures
  that method calls can be correctly dispatched at runtime.
- When a class is derived from a base class with virtual functions, its v-table
  is constructed by replacing pointers to base class methods with pointers to
  overridden methods in the derived class, if any.

This mechanism allows C++ to support runtime polymorphism. When a virtual
function is called on a pointer or reference to a base class, the actual
function that gets called is determined at runtime based on the v-table of the
object's actual class.

### 5.2. Dynamic Dispatch

Dynamic dispatch is the process by which a call to an overridden virtual
function is resolved at runtime. This contrasts with static dispatch, where the
function call is resolved at compile time. Dynamic dispatch is essential for
implementing polymorphism, where the exact method to be called is determined not
by the type of the pointer or reference, but by the actual type of the object it
points to or references.

Here’s how dynamic dispatch is related to virtual functions and the v-table:

- **When a virtual function is called**: The compiler generates code to look up
  the function pointer in the v-table of the object's class.
- **Resolution of the function call**: This lookup happens at runtime, and the
  function that the pointer in the v-table refers to is called. This is how the
  correct overridden method is invoked on a derived class object, even when the
  call is made through a base class pointer or reference.

### 5.3. Correcting Understanding

My current understanding of the relationship between virtual methods, the
v-table, and dynamic dispatch seems largely accurate. Here are a few
clarifications to ensure precision in how these concepts interrelate:

- **Virtual methods** are declared with the `virtual` keyword in C++ and
  indicate that dynamic dispatch should be used for these methods.
- **The v-table** is an underlying mechanism used to implement dynamic dispatch.
  It's not part of the C++ language itself but a common technique used by
  compilers to support runtime method resolution.
- **Dynamic dispatch** is the runtime mechanism that allows C++ programs to call
  the correct method implementation in a hierarchy of classes with overridden
  methods. It relies on the v-table to determine the actual function to call.

In summary, the v-table and dynamic dispatch are closely related: the v-table
enables dynamic dispatch, and dynamic dispatch is the mechanism that allows
polymorphic behavior in object-oriented systems, facilitated by virtual methods
in classes. Your understanding aligns well with these concepts, emphasizing the
importance of these mechanisms in supporting runtime polymorphism in C++.
