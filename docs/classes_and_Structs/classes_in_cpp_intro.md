# Classes in C++ Introduction

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Classes in C++ Introduction](#classes-in-c-introduction)
  - [1. Types of Methods in OOP](#1-types-of-methods-in-oop)
    - [1.1 Methods in OOP - Python](#11-methods-in-oop---python)
    - [1.2. What are the all methds in OOP - C++](#12-what-are-the-all-methds-in-oop---c)
    - [1.3. Compare Python vs C++](#13-compare-python-vs-c)
  - [How to think of Class](#how-to-think-of-class)

<!-- markdown-toc end -->

We utilize classes as blueprints to encompass all data and functionality.

- Classes serve as a new type with a unique name.
- The primary difference between classes and structs lies in the visibility of
  their members. By default, struct members are public, while class members are
  private.

## 1. Types of Methods in OOP

### 1.1 Methods in OOP - Python

In Python's Object-Oriented Programming (OOP), there are indeed different types
of methods you can define in a class. These are:

1. **Instance Methods (Object Methods):**

   - These methods are the most common and operate on an instance of the class (an object).
   - They can access and modify the object's state since they take a self parameter, which refers to the instance.
   - Syntax: `def method_name(self, ...):`

2. **Class Methods:**

   - Class methods operate on the class itself rather than instances of the class.
   - They are marked with the `@classmethod` decorator and take `cls` as the first parameter, which refers to the class.
   - Useful for factory methods or when a method is relevant to the class but not necessarily to an instance.
   - Syntax: `@classmethod\ndef method_name(cls, ...):`

3. **Static Methods:**
   - Static methods do not take a `self` or `cls` parameter. They are bound neither to an instance nor to the class.
   - These are similar to regular functions but are included in the class's namespace.
   - Useful for utility or helper functions that could logically belong to the class but don't need access to the class or instance.
   - Marked with the `@staticmethod` decorator.
   - Syntax: `@staticmethod\ndef method_name(...):`

Here's a quick example to illustrate these method types:

```py
class MyClass:
    class_attribute = "I'm a class attribute"

    def __init__(self, value):
        self.instance_attribute = value

    def instance_method(self):
        return f"Instance method called, instance attribute: {self.instance_attribute}"

    @classmethod
    def class_method(cls):
        return f"Class method called, class attribute: {cls.class_attribute}"

    @staticmethod
    def static_method():
        return "Static method called"

# Usage:
obj = MyClass("Hello")
print(obj.instance_method())  # Accessing instance method
print(MyClass.class_method())  # Accessing class method
print(MyClass.static_method())  # Accessing static method
```

Each type of method serves a different purpose and helps in organizing code
based on whether the functionality pertains to individual objects, the class
itself, or a general utility that fits within the class's scope.

### 1.2. What are the all methds in OOP - C++

In C++, the concepts of methods are slightly different from Python, but we can
still draw parallels. The equivalent types of methods in C++ would be:

1. **Member Functions (Equivalent to Instance Methods):**

   - These functions operate on instances of the class.
   - They have access to the instance's data members and other member functions.
   - Syntax: `return_type method_name(arguments);` within the class declaration.

2. **Static Member Functions (Equivalent to Class Methods):**

   - Static member functions are tied to the class rather than an instance.
   - They can access only static data members or other static member functions of the class.
   - Syntax: `static return_type method_name(arguments);` within the class declaration.

3. **Free Functions (Similar to Static Methods):**
   - In C++, static methods in the Python sense are typically implemented as free functions, which are not part of any class.
   - They do not have access to the class's private or protected members unless declared as friends.
   - Syntax: `return_type function_name(arguments);` outside of the class.

Let's convert the Python example into C++:

```cpp
#include <iostream>
#include <string>

class MyClass {
private:
    std::string instance_attribute;

public:
    static std::string class_attribute;

    MyClass(std::string value) : instance_attribute(value) {}

    // Member Function (Instance Method)
    std::string instance_method() {
        return "Instance method called, instance attribute: " + instance_attribute;
    }

    // Static Member Function (Class Method)
    static std::string class_method() {
        return "Class method called, class attribute: " + class_attribute;
    }
};

// Define the static member
std::string MyClass::class_attribute = "I'm a class attribute";

// Free Function (Similar to Static Method)
std::string static_function() {
    return "Static function called";
}

int main() {
    MyClass obj("Hello");
    std::cout << obj.instance_method() << std::endl;  // Accessing member function
    std::cout << MyClass::class_method() << std::endl;  // Accessing static member function
    std::cout << static_function() << std::endl;  // Accessing free function
    return 0;
}
```

In this C++ example:

- `instance_method` is a member function, working with instance data.
- `class_method` is a static member function, accessing a static data member.
- `static_function` is a free function, not associated with any class.

C++ doesn't have a direct equivalent of Python's `@staticmethod` but achieves
similar functionality using free functions or static member functions, depending
on whether access to static members of the class is needed.

### 1.3. Compare Python vs C++

Sure, here's a table comparing the different types of methods in C++ and Python,
based on the information discussed:

| Feature                 | Python                                                                                                                             | C++                                                                                                                                                           |
| ----------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Instance Method         | Method that operates on an instance of the class (`self`). Can modify object state and access instance attributes.                 | Member Function. Works on an instance of the class. Can access and modify instance data members.                                                              |
| Class Method            | Uses `@classmethod` decorator. Operates on the class (`cls`) rather than instances. Can modify class state.                        | Static Member Function. Tied to the class rather than instances. Can access static data members of the class.                                                 |
| Static Method           | Uses `@staticmethod` decorator. Does not take `self` or `cls` parameter. Similar to regular functions but under the class's scope. | Free Function (not part of a class) or Static Member Function (if needing to access static class members). Does not operate on instances or the class itself. |
| Access to Instance Data | Can access and modify instance data and methods.                                                                                   | Can access and modify instance data and methods.                                                                                                              |
| Access to Class Data    | Can access and modify class variables.                                                                                             | Can access and modify static data members of the class.                                                                                                       |
| Typical Use Case        | Organizing methods logically within a class's namespace; instance-specific and class-wide behaviors.                               | Organizing methods logically within a class's namespace; instance-specific, class-wide behaviors, and utility functions.                                      |

This table outlines the main differences and similarities between how Python and
C++ handle instance methods, class methods, and static methods (or their C++
equivalents). Both languages use these concepts to manage object-oriented design
in a way that is appropriate to their respective programming paradigms and
capabilities.

## How to think of Class

In C++, a class is a blueprint for creating objects, encapsulating data for the
object and methods to manipulate that data. It can include various types of
member variables (also known as attributes or fields) and functions (methods).
These member variables can be of different data types, including:

- **Primitive Data Types:** Such as `int`, `double`, `char`, etc., which are the
  basic data types built into the language.
- **Standard Library Types:**
  - **String Types:** Like `std::string`, which is a part of the C++ Standard
    Library for representing and manipulating strings.
  - **Container Types:** Such as `std::array`, `std::list`, `std::vector`, etc.,
    which are part of the Standard Template Library (STL) and are used for
    storing collections of data.
  - **Enumerations (Enums):** User-defined types that consist of a set of named
    integral constants. C++ offers both scoped (`enum class`) and unscoped
    (`enum`) enumerations.
  - **Structures (Structs):** Similar to classes but with members public by
    default, used for grouping different data types.
- **User-Defined Classes:** A class can contain instances of other classes as
  members, allowing complex data structures to be built up through composition.
  This enables the creation of intricate object hierarchies and relationships.
- **Types from Other Libraries:** Besides the standard library, C++ can utilize
  types from external libraries, expanding the functionality available to a
  program. These can include GUI libraries, networking libraries, or any other
  third-party or user-created libraries.

A class in C++ thus acts as a comprehensive data type that can aggregate simple
and complex data types, including instances of other classes, to form
sophisticated and tailored data structures suited to the needs of a program.
