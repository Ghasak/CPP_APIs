# Interfaces in C++ - Pure Virtual Functions
<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Interfaces in C++ - Pure Virtual Functions](#interfaces-in-c---pure-virtual-functions)
    - [What are Pure Virtual Functions?](#what-are-pure-virtual-functions)
        - [Why We Need Them?](#why-we-need-them)
        - [How to Use Them?](#how-to-use-them)
        - [Common Code Practices](#common-code-practices)
        - [Things to Be Considered](#things-to-be-considered)
        - [Examples](#examples)

<!-- markdown-toc end -->

Pure virtual functions in C++ are foundational to understanding abstract classes
and interfaces, playing a crucial role in object-oriented design. Here's a
comprehensive overview to guide you through the concepts, usage, best practices,
and considerations, including examples.

- Pure virtual function is similar to `abstract` method or `interface` in other
  programming laguages.

## What are Pure Virtual Functions?

A pure virtual function is a function that is declared in a base class but is
intended to be overridden in a derived class. It doesn't have its implementation
in the base class. Instead, it only provides a function signature. A class
containing at least one pure virtual function is considered an abstract class,
and it cannot be instantiated.

- In C++, a pure virtual function is declared by assigning `0` to the function
  declaration in the class definition.

### Why We Need Them?

- **Polymorphism**: They enable polymorphism, allowing objects of different
  classes to be treated as objects of a common base class.
- **Interface Definition**: They provide a way to define interfaces, ensuring
  that derived classes implement the specific behavior.
- **Design Flexibility**: They allow for flexible and dynamic design, where
  derived classes can have different implementations for the same function.

### How to Use Them?

To declare a pure virtual function, you use the following syntax:

```cpp
class AbstractClass {
public:
    virtual ReturnType functionName(Parameters) = 0;
    // Other members...
};
```

And then in a derived class, you override the pure virtual function:

```cpp
class DerivedClass : public AbstractClass {
public:
    ReturnType functionName(Parameters) override {
        // Implementation code here
    }
    // Other members...
};
```

### Common Code Practices

- **Use Abstract Classes as Interfaces**: If a class has only pure virtual
  functions, it behaves like an interface. This is a common practice in
  designing system architecture.
- **Document the Interface**: Document what each pure virtual function is
  expected to do, as it serves as a contract for the derived classes.
- **Prefer Virtual Destructors**: If a class has virtual functions, its
  destructor should also be virtual. This ensures proper cleanup of derived
  class resources.

### Things to Be Considered

- **Instantiation**: Abstract classes cannot be instantiated directly.
- **Destructors**: Even if a class is abstract, it can have a destructor, which
  should be virtual to ensure proper cleanup.
- **Default Implementations**: Sometimes, it's useful for a pure virtual
  function to have an implementation. This can be done outside the class
  definition.

### Examples

**Abstract Class with Pure Virtual Function**

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
    virtual ~Shape() {}      // Virtual destructor
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};
```

**Usage**

```cpp
std::vector<Shape*> shapes;
shapes.push_back(new Circle());
shapes.push_back(new Rectangle());

for (Shape* shape : shapes) {
    shape->draw(); // Polymorphic call
}

// Clean up
for (Shape* shape : shapes) {
    delete shape;
}
shapes.clear();
```

This example illustrates how abstract classes and pure virtual functions
facilitate polymorphism and dynamic dispatch in C++. By defining a common
interface (`Shape`) with a pure virtual function (`draw`), we ensure that each
derived class (`Circle`, `Rectangle`) provides its own implementation, thus
allowing for flexible and extendable designs.
