# Classes with RVO Concept
<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Classes with RVO Concept](#classes-with-rvo-concept)
    - [Example Class Definition](#example-class-definition)
        - [Explanation of Differences](#explanation-of-differences)
        - [Special Consideration for Returning References](#special-consideration-for-returning-references)
    - [Demonstration](#demonstration)
        - [Enhanced Example with Method Chaining](#enhanced-example-with-method-chaining)
        - [Explanation](#explanation)
        - [Demonstrating Chaining in Action](#demonstrating-chaining-in-action)
        - [Key Points](#key-points)
    - [Other Concepts Related](#other-concepts-related)
        - [1. Rule of Three/Five](#1-rule-of-threefive)
        - [2. Smart Pointers](#2-smart-pointers)
        - [3. Copy Elision and Return Value Optimization (RVO)](#3-copy-elision-and-return-value-optimization-rvo)
        - [4. Fluent Interface Design](#4-fluent-interface-design)
        - [5. Immutability](#5-immutability)
        - [6. Lambda Expressions and Functional Programming](#6-lambda-expressions-and-functional-programming)
        - [7. Const Correctness](#7-const-correctness)
        - [8. Exception Safety and Strong Guarantee](#8-exception-safety-and-strong-guarantee)
    - [RVO in Action](#rvo-in-action)
        - [Modified `ChainableClass` Example Demonstrating RVO](#modified-chainableclass-example-demonstrating-rvo)
        - [Expected Output Without RVO](#expected-output-without-rvo)
        - [Expected Output With RVO](#expected-output-with-rvo)
        - [Note on Compilers and RVO](#note-on-compilers-and-rvo)

<!-- markdown-toc end -->


Let's start with creating a simple C++ class that includes two methods, one
returning the object itself and the other returning a reference to the object.
We'll use a basic example of a class named `ExampleClass` for clarity. Then,
I'll explain the difference between returning an object and returning a
reference to an object.

## Example Class Definition

```cpp
class ExampleClass {
private:
    int value;

public:
    ExampleClass(int v) : value(v) {} // Constructor to initialize `value`

    // Method returning a new object of ExampleClass
    ExampleClass returnObject() {
        return ExampleClass(value);
    }

    // Method returning a reference to the current object
    ExampleClass& returnReference() {
        return *this;
    }

    // Setter method to demonstrate changes via reference
    void setValue(int v) {
        value = v;
    }

    // Getter method for demonstration
    int getValue() const {
        return value;
    }
};
```

### Explanation of Differences

1. **Returning an Object**: When a method returns an object, it returns a new
   instance of the object. This involves creating a copy of the object. In the
   context of the `returnObject()` method, it creates and returns a new
   `ExampleClass` instance with the same value. This operation invokes the copy
   constructor of the class, leading to potentially costly operations if the
   object is large or complex.
2. **Returning a Reference to an Object**: When a method returns a reference to
   an object (using `ExampleClass&`), it returns a reference to the existing
   instance. No copy is made, and the caller can directly interact with the
   original object. The `returnReference()` method returns a reference to the
   object it is called on, allowing the caller to modify the original object.
   This is more efficient than returning a full object because it avoids the
   overhead of copying.

### Special Consideration for Returning References

Returning a reference is particularly useful when dealing with large data
structures or when you want to allow the caller to modify the object directly.
However, one must be cautious:

- Returning a reference to a local object within a method (a temporary object)
  is dangerous because the object will be destroyed when the method exits,
  leaving a dangling reference. This does not apply to the `returnReference()`
  method in the provided example because it returns a reference to the object on
  which the method was called, which exists outside the method's scope.
- When returning a reference, it’s crucial to ensure the lifetime of the
  referenced object extends beyond the use of the reference to prevent accessing
  invalidated memory.

In summary, choosing between returning an object or a reference depends on the
intended use case, performance considerations, and lifetime management of the
objects involved. Returning a reference avoids the cost of copying and allows
direct manipulation of the original object, but it requires careful management
of object lifetimes to avoid dangling references.

## Demonstration

To demonstrate method chaining using both approaches—returning an object and
returning a reference—I'll present an enhanced example. Method chaining allows
us to call multiple methods on an object in a single statement, which can lead
to more readable and concise code. It's commonly used in classes that are
designed to be used fluently, like builders or certain types of utility classes.

### Enhanced Example with Method Chaining

```cpp
class ChainableClass {
private:
    int value;
public:
    // Constructor to initialize `value`
    ChainableClass(int v = 0) : value(v) {}

    // Method chaining by returning a new object
    ChainableClass returnObjectWithNewValue(int newValue) const {
        return ChainableClass(newValue);
    }

    // Method chaining by returning a reference to the current object
    ChainableClass& addValue(int addValue) {
        value += addValue;
        return *this;
    }

    // Utility method to show the current value
    void printValue() const {
        std::cout << "Current Value: " << value << std::endl;
    }
};
```

### Explanation

- **Method Chaining with Return Object**: The `returnObjectWithNewValue` method
  returns a new `ChainableClass` object with a modified value. This does not
  modify the original object but provides a new modified instance. This approach
  does not support traditional chaining where the state of the original object
  is altered across the chain since it always produces a new object.

- **Method Chaining with Return Reference**: The `addValue` method returns a
  reference to the current object, allowing us to chain multiple calls on the
  same instance, modifying its state with each call. This is a more classic
  approach to method chaining, enabling fluent interfaces.

### Demonstrating Chaining in Action

```cpp
int main() {
    ChainableClass obj(10);

    // Demonstrating chaining with return reference
    obj.addValue(5).addValue(15).printValue(); // Output: Current Value: 30

    // Demonstrating "chaining" with return object
    // Note: This doesn't modify `obj` but creates a new object instead
    obj.returnObjectWithNewValue(20).printValue(); // Output: Current Value: 20

    // Original object remains unchanged when using returnObjectWithNewValue
    obj.printValue(); // Output: Current Value: 30

    return 0;
}
```

### Key Points

- **Method Chaining with References**: This is ideal for modifying and working
  with the same object across multiple method calls. It's efficient and directly
  manipulates the object's state.

- **Method Chaining with Objects**: While it technically allows for a form of
  chaining, it's more about creating and working with a series of new objects
  rather than chaining operations on the same object. This pattern can be useful
  in scenarios where immutability of objects is desired, similar to the builder
  pattern where each method call returns a new modified instance, but it's not
  "chaining" in the traditional sense of altering the same object.

Both techniques have their uses, but the choice between them depends on whether
you want to maintain the immutability of objects or prefer to modify the same
object across the chain.


## Other Concepts Related

When discussing method chaining and managing object lifetimes in C++, several
related concepts and best practices are worth understanding. These can help you
design more effective and robust classes:

### 1. Rule of Three/Five

When you manage resources (like dynamic memory, file handles, or network
connections) directly within a class, understanding the Rule of Three and Rule
of Five is crucial:

- **Rule of Three**: If your class defines one (or more) of the following, it
  should probably explicitly define all three: destructor, copy constructor, and
  copy assignment operator.
- **Rule of Five** (C++11 and beyond): Extends the Rule of Three to include the
  move constructor and move assignment operator. This rule applies when you want
  your class to support efficient move semantics, reducing the need for copies
  when objects can instead transfer ownership of resources.

### 2. Smart Pointers

In modern C++, raw pointer management (new/delete) is often replaced with smart
pointers (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`) to automate
resource management and prevent memory leaks. When returning references or
objects from methods, consider how smart pointers might be used to manage
lifetimes and ownership.

### 3. Copy Elision and Return Value Optimization (RVO)

C++ compilers can optimize returning objects from functions through copy elision
and RVO. These optimizations can eliminate or reduce the overhead associated
with copying objects, even if a method returns an object by value. Understanding
these optimizations can help you write more efficient code, especially in
contexts where returning by value might seem inefficient.

### 4. Fluent Interface Design

Method chaining is a key part of designing fluent interfaces, which allow for
writing code that is highly readable and expressive. Fluent interfaces are often
seen in builder patterns, DSLs (Domain Specific Languages), and various modern
C++ libraries. When designing such interfaces, consider how each method's return
type (object, reference, or smart pointer) affects usability and performance.

### 5. Immutability

In contrast to method chaining that modifies the object state, another design
consideration is immutability. Immutable objects are those whose state cannot be
changed after they are created. Returning new objects with modified state,
rather than modifying the original object, supports functional programming
patterns and can simplify concurrency and multithreading by avoiding mutable
shared state.

### 6. Lambda Expressions and Functional Programming

C++11 introduced lambda expressions, enabling more concise and flexible ways to
write inline functions. When combined with the Standard Template Library (STL),
lambdas can transform how you manipulate collections, allowing for chaining
operations like filtering, mapping, and reducing directly on containers.

### 7. Const Correctness

Using `const` correctly is vital for indicating which methods do not modify the
object state. This is not only a best practice for readability and maintenance
but also for ensuring that your objects can be used in contexts where
immutability is required or expected.

### 8. Exception Safety and Strong Guarantee

When methods modify objects or manage resources, consider the implications for
exception safety. The strong guarantee, in particular, states that operations
should either complete successfully or leave the program state unchanged. This
is relevant when designing methods that might throw exceptions, ensuring that
partial changes don't leave objects in an inconsistent state.

Understanding and applying these concepts will help you create more robust,
efficient, and maintainable C++ applications. Each plays a role in how you
design classes, manage resources, and implement interfaces for your objects.


## RVO in Action

Return Value Optimization (RVO) is a compiler optimization technique that
eliminates the temporary object created when an object is returned by value from
a function. This can significantly reduce overhead by avoiding unnecessary
copies. RVO can be easily demonstrated with a modified version of our earlier
`ChainableClass` example.

- In this example, we'll focus on a method that returns a new object by value.
  Thanks to RVO, even though it looks like it should create a temporary object
  that is then copied to the return value, the compiler is smart enough to
  construct the return object directly in the location where it is expected,
  eliminating the need for a copy.

### Modified `ChainableClass` Example Demonstrating RVO

```cpp
#include <iostream>

class ChainableClass {
private:
    int value;
public:
    ChainableClass(int v = 0) : value(v) {
        std::cout << "Constructor called for value: " << value << std::endl;
    }

    // Copy Constructor
    ChainableClass(const ChainableClass& other) : value(other.value) {
        std::cout << "Copy constructor called for value: " << value << std::endl;
    }

    // Move Constructor
    ChainableClass(ChainableClass&& other) noexcept : value(other.value) {
        std::cout << "Move constructor called for value: " << value << std::endl;
    }

    // Method that seems to return by value, triggering RVO
    ChainableClass createNewWithValue(int newValue) const {
        return ChainableClass(newValue);
    }
};

ChainableClass createObject(int value) {
    return ChainableClass(value);
}

int main() {
    // Demonstrating RVO
    std::cout << "Creating obj with RVO:\n";
    ChainableClass obj = createObject(10);

    // Demonstrating RVO from a method
    std::cout << "\nCreating newObj with RVO from method:\n";
    ChainableClass newObj = obj.createNewWithValue(20);

    return 0;
}
```

### Expected Output Without RVO

Without RVO, you would expect the output to include calls to the copy or move
constructor for each return operation:

```
Creating obj with RVO:
Constructor called for value: 10
Move constructor called for value: 10

Creating newObj with RVO from method:
Constructor called for value: 20
Move constructor called for value: 20
```

### Expected Output With RVO

With RVO, the compiler optimizes away these copy/move operations:

```
Creating obj with RVO:
Constructor called for value: 10

Creating newObj with RVO from method:
Constructor called for value: 20
```

### Note on Compilers and RVO

The actual output can depend on the compiler and optimization settings. Modern
C++ compilers are generally very good at applying RVO when possible, but it's
not guaranteed in every situation. The introduction of C++17 made this
optimization even more reliable with guaranteed copy elision for certain
scenarios, further reducing unnecessary copies.
