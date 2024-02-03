# Friend Methods in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Friend Methods in C++](#friend-methods-in-c)
  - [My Understanding](#my-understanding)
  - [Introduction](#introduction)
    - [What are Friend Methods?](#what-are-friend-methods)
    - [Why We Need Them](#why-we-need-them)
    - [How to Use Them](#how-to-use-them)
    - [Common Code Practices](#common-code-practices)
    - [Things to Be Considered](#things-to-be-considered)
    - [Examples](#examples)
  - [Friend with I/O stream](#friend-with-io-stream)
    - [Example 1: Using a Class](#example-1-using-a-class)
    - [Example 2: Without a Class (Global Function)](#example-2-without-a-class-global-function)
    - [How `friend` Works with `ostream` Operator](#how-friend-works-with-ostream-operator)
    - [ASCII Chart for Calling Class Methods with Friends](#ascii-chart-for-calling-class-methods-with-friends)
  - [What is I/O-stream](#what-is-io-stream)
    - [When You Use `friend` with `ostream`](#when-you-use-friend-with-ostream)
    - [Explanation and Examples](#explanation-and-examples)
    - [Important Considerations](#important-considerations)
  - [istream as a friend](#istream-as-a-friend)
    - [Class Definition with `std::istream` Operator](#class-definition-with-stdistream-operator)
    - [Description and Expected Output](#description-and-expected-output)
      - [Expected Interaction and Output](#expected-interaction-and-output)
    - [Understanding the Process](#understanding-the-process)

<!-- markdown-toc end -->

## My Understanding

- Friend is just a declaration of a function that can access the private
  memebers of the defined class.
- There are mainly three types that I am aware of, these are:

  - Friend Cunctions
  - Friend Class
  - Friend Class Method
    When declaring a function as a friend within a class in a header file, it is not
    necessary to declare it again in the same header file as it has already been
    declared.

### Friend Function Explanation

- Check the example `4` of the file `Classes.cpp -> 4. Using ostream friend method operator <<`.
  - Using `operator<<` for the `Person` class involves a
    **friend function**. It's not a method of a class or a friend class. In C++, a
    friend function is a function that is not a member of a class but has access to
    its private and protected members. This access is granted by the class itself
    via the `friend` keyword.

- In the context of overloading the `operator<<`, the function is defined
  outside of any class but is declared as a friend inside the class it needs to
  access. This setup allows the function to stream private data from the class
  directly to an output stream (like `std::cout`), which wouldn't be possible if
  it were a regular function without access to the class's private or protected
  members.

### Signature of `operator<<`

The signature of the `operator<<` in the previous example is as follows:

```cpp
std::ostream& operator<<(std::ostream& stream, const Person& p);
```

- **Arguments/Parameters:**

  - `std::ostream& stream`: The first parameter is a reference to an instance of
    `std::ostream`. This is the stream to which the data will be output. It's
    passed by reference to avoid copying the stream object, which is not only
    inefficient but also semantically incorrect since stream objects represent
    unique resources like files or console output.
  - `const Person& p`: The second parameter is a constant reference to the
    `Person` object that we want to output to the stream. It's constant because
    we don't want to modify the `Person` object during the operation, and it's a
    reference to avoid unnecessary copying.

- **Return Type:**
  - `std::ostream&`: The function returns a reference to the same `std::ostream`
    instance passed to it. This design allows chaining of `<<` operator calls.
    For example, you can do something like `std::cout << person1 << person2;`,
    where each `operator<<` call returns the stream itself, allowing the next
    item to be output seamlessly.

### Summary

The `operator<<` in this context is a **friend function** of the `Person` class,
which allows it to access the class's private data for output purposes. The
function takes a reference to an `std::ostream` object and a constant reference
to a `Person` object as parameters, and returns a reference to an `std::ostream`
object to enable the chaining of output operations.

## Friend Concept Introduction

Friend methods in C++ are a powerful feature that allows functions or classes to
access private and protected members of another class. This feature enhances
flexibility and efficiency in certain scenarios but must be used judiciously to
maintain the encapsulation principle of object-oriented programming. Here's a
comprehensive guide on friend methods in C++, covering their definition,
purpose, usage, best practices, considerations, and examples.

### What are Friend Methods?

Friend methods are functions that, although not members of a class, have the
right to access the class's private and protected members. This includes both
free functions (non-member functions) and member functions of other classes. The
`friend` keyword is used to declare such functions.

### Why We Need Them

- **Access Control**: Friend methods provide controlled access to the internals
  of a class for functions or other classes that require such access, without
  exposing those internals more widely through public member functions.

- **Functionality Extension**: They allow external functions or classes to
  extend the functionality of a class without modifying its source code.

- **Operator Overloading**: They are particularly useful in operator
  overloading, especially for operators that need access to private data but are
  logically considered external to the class, such as stream insertion (`<<`)
  and extraction (`>>`) operators with `std::ostream` and `std::istream`.

### How to Use Them

To declare a friend method, you use the `friend` keyword inside the class
definition where access is to be granted. This can be for a standalone function
or a member function of another class.

### Common Code Practices

- **Minimize Use**: Use friend methods sparingly, as they break the
  encapsulation principle by allowing external functions or classes to access a
  class's private parts.

- **Clear Design Justification**: Implement friend methods when there's a clear,
  justified need for tight coupling between classes or functions, ensuring it
  doesn't compromise the design.

- **Encapsulation Over Friend**: Prefer maintaining encapsulation through public
  or protected members when possible. Friend methods should be a considered
  decision, not a first resort.

### Things to Be Considered

- **Encapsulation Violation**: Friend methods can potentially violate the
  encapsulation principle, making maintenance and understanding of the codebase
  harder.

- **Dependency**: Overuse of friend methods can lead to a tightly coupled
  system, making the code less modular and more difficult to change or extend.

- **Access Scope**: Friend declarations cannot be inherited, meaning subclasses
  do not automatically gain friend status with the classes their parent classes
  are friends with.

### Examples

1. **Friend Function Example**

```cpp
class Box {
    double width;
public:
    Box(double w) : width(w) {}
    friend void printWidth(Box b);
};

void printWidth(Box b) {
    std::cout << "Width of box: " << b.width << std::endl;
}

int main() {
    Box box(10);
    printWidth(box);
    return 0;
}
```

2. **Friend Class Example**

```cpp
class Box {
    double width;
public:
    Box(double w) : width(w) {}
    friend class Printer;
};

class Printer {
public:
    void printWidth(Box& b) {
        std::cout << "Width of box: " << b.width << std::endl;
    }
};

int main() {
    Box box(10);
    Printer printer;
    printer.printWidth(box);
    return 0;
}
```

3. **Friend Method of Another Class**

```cpp
class YourClass;

class MyClass {
public:
    void showYourClass(YourClass& y);
};

class YourClass {
    int secret = 0;
    friend void MyClass::showYourClass(YourClass& y);
};

void MyClass::showYourClass(YourClass& y) {
    std::cout << "YourClass secret: " << y.secret << std::endl;
}

int main() {
    YourClass yc;
    MyClass mc;
    mc.showYourClass(yc);
    return 0;
}
```

These examples illustrate how friend functions and classes can be used to access
private and protected members of another class. Remember, while friend methods
can be powerful, they should be used judanely to ensure that the principles of
object-oriented programming are not compromised.

## Friend with I/O stream

Using the `friend` method with the `ostream` operator `<<` allows for direct
access to private members of a class, facilitating the implementation of custom
output formatting. This is especially useful for classes where encapsulation of
data is essential, yet there's a need to print object states conveniently. I'll
show you two examples: one using a class and another without explicitly defining
a class, and then explain how `friend` works in these contexts. Lastly, I'll
provide an ASCII chart to illustrate the concept in action.

### Example 1: Using a Class

Let's start with a simple `Person` class that uses a friend function to
implement the `<<` operator.

```cpp
#include <iostream>
#include <string>

class Person {
    std::string name;
    int age;
public:
    Person(std::string n, int a) : name(n), age(a) {}
    // Declaring the ostream << operator as a friend
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

// Implementation of the friend function
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person(Name: " << p.name << ", Age: " << p.age << ")";
    return os;
}

int main() {
    Person person("John Doe", 30);
    std::cout << person << std::endl;
    return 0;
}
```

### Example 2: Without a Class (Global Function)

In scenarios where you don't have control over a class or for built-in types,
you'd typically not use friend functions because they inherently require access
to private members of a class. For basic types or when extending classes you
control, you always define the operator outside any class without needing it to
be a friend.

For instance, for a standalone function that outputs a custom format for a date
(assuming we're dealing with a structure or class we can access directly), you'd
simply do:

```cpp
// This example assumes a more open design, not applicable for friend demonstration.
```

In practice, this second scenario diverges from the use of friend functions as
it's more about defining global functions or methods that don't need private
access, hence not fitting the "friend method with `ostream` operator" scenario
precisely.

### How `friend` Works with `ostream` Operator

When you declare an `ostream` operator function (`operator<<`) as a friend of a
class, you enable it to access the class's private and protected members. This
is necessary for outputting the state of an object because the function needs to
read the object's internal state, which is often kept private to maintain
encapsulation.

- In the `Person` example, the `operator<<` function can directly access the
  `name` and `age` members of a `Person` object. This direct access is what the
  `friend` keyword grants. Without it, the function would need to rely on public
  getters, which might not always be available or could lead to inefficient or
  cumbersome code.

### ASCII Chart for Calling Class Methods with Friends

Here's an ASCII chart illustrating a scenario where a class `A` has a friend
function `F` and how it interacts:

```
+----------------+           +----------------+
|     Class A    |           |    Function    |
|----------------|           |       F        |
| - privateData  | Friend    |                |
| + publicMethod |<----------| + operator<<   |
+----------------+ Access    +----------------+
       ^                             |
       | Calls                       |
       |                             |
       +-----------------------------+
                     Uses
```

In this chart:

- `Class A` has private data (`privateData`) and a public method
  (`publicMethod`).
- `Function F` (in this case, `operator<<`) is declared as a friend of `Class A`
  and can access its private members.
- `Function F` can be called independently (like when used with `std::cout << objectA`) and will internally access `Class A`'s private data for its
  operations, facilitated by its friend status.

This direct access granted by the `friend` keyword allows `Function F` to read
and use `Class A`'s private data, which it outputs or processes according to its
definition (in our examples, for custom formatting with `std::cout`).

## What is I/O-stream

`ostream` is not a function or a method; it is a class within the C++ Standard
Library. Specifically, it is part of the I/O stream library and represents an
output stream, which is used to perform output operations, typically to standard
output (such as the console), files, or string streams. The `std::ostream` class
provides support for various types of output, including formatted and
unformatted output.

- When you use `ostream` in conjunction with the `friend` keyword for a class, you
  are typically defining an `operator<<` function that can access the private and
  protected members of the class. This operator function is then able to output
  the contents of an object of that class to an output stream, like so:

```cpp
std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    // Access private members of MyClass directly
    os << obj.privateData;
    return os;
}
```

In this context:

- **`std::ostream`**: It's a class that represents an output stream.
- **`operator<<`**: This is a function, often a global function or a static
  member function, which is made a friend of another class so it can access that
  class's private and protected members. It is overloaded to handle objects of
  custom classes, allowing those objects to be output to a stream like
  `std::cout` directly.

### When You Use `friend` with `ostream`

By declaring the `operator<<` function as a friend of your class, you allow it
to access all the private and protected members of your class. This is essential
for output operations where encapsulation must be maintained (i.e., keeping
class members private), but you still want to provide a way to output the class
members, typically for debugging or informational purposes.

- In summary, when you use `friend` with `ostream` in this way, you're granting a
  specific function (`operator<<`) the ability to access the internals of your
  class for the purpose of outputting its contents to an output stream, such as
  `std::cout` for console output. This pattern is widely used in C++ to implement
  custom output behaviors for user-defined types.

- Using friend methods from the standard library (STD) involves granting access to
  your class's private members for specific purposes, commonly for input/output
  operations. Apart from the `ostream` operator (`operator<<`) for output, another
  common friend method is the `istream` operator (`operator>>`) for input. Below
  is a table outlining these and other potential friend methods or functions you
  might use from the standard library in similar contexts:

| Friend Method/Function        | Description                                                                                 | Common Use Cases                                                  |
| ----------------------------- | ------------------------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| `std::ostream& operator<<`    | Allows outputting objects of a class to output streams (e.g., console, files).              | Custom formatting of class objects for output.                    |
| `std::istream& operator>>`    | Enables inputting values into objects of a class from input streams (e.g., console, files). | Custom parsing or initialization of class objects from input.     |
| `std::swap` (Custom Overload) | Provides a way to swap two objects of a class efficiently, often used in algorithms.        | Custom implementation of swap to handle class-specific resources. |

### Explanation and Examples

1. **`std::ostream& operator<<` (Output Stream Operator)**: This is used to
   implement custom output formatting for your class objects, allowing them to
   be outputted using streams like `std::cout`.

   ```cpp
   friend std::ostream& operator<<(std::ostream& os, const MyClass& obj);
   ```

2. **`std::istream& operator>>` (Input Stream Operator)**: Similar to the
   `operator<<` but for input, allowing your class to initialize or modify
   objects based on input from streams like `std::cin`.

   ```cpp
   friend std::istream& operator>>(std::istream& is, MyClass& obj);
   ```

3. **`std::swap` (Custom Overload)**: While not as common as stream operators,
   overloading `std::swap` for your class as a friend function allows you to
   efficiently swap two instances of your class, especially when they manage
   resources that can be swapped without copying (e.g., pointers).

   ```cpp
   namespace std {
       template<>
       void swap<MyClass>(MyClass& a, MyClass& b) noexcept {
           // Custom swap logic here
       }
   }
   ```

### Important Considerations

- **Encapsulation**: Using friend functions should be done cautiously as they
  break encapsulation to some extent by allowing external functions direct
  access to a class's private and protected members.
- **Design**: Prefer member functions for operations that are logically part of
  the class's interface. Use friend functions for operators or functions that
  must appear as though they are external to the class but still require access
  to its internals.
- **Efficiency**: For `std::swap`, implementing it as a friend allows swapping
  members of two objects without unnecessary copies, which can be crucial for
  performance-sensitive applications or when dealing with resources like file
  handles or network connections.

In summary, while `operator<<` and `operator>>` are the most commonly used
friend methods for I/O operations, the concept of friend functions is applicable
wherever you need controlled access to a class's internals without exposing them
publicly.

## istream as a friend

Let's create a simple `Person` class that demonstrates the use of the
`std::istream` operator `>>` within a class. This class will have two private
members, `name` and `age`, and we'll implement the `operator>>` to input these
properties from an input stream such as `std::cin`.

### Class Definition with `std::istream` Operator

```cpp
#include <iostream>
#include <string>

class Person {
    std::string name;
    int age;
public:
    // Constructor
    Person() : name(""), age(0) {}

    // Friend declaration for istream operator>>
    friend std::istream& operator>>(std::istream& is, Person& p);

    // Method to display the Person object
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

// Implementation of the friend istream operator>>
std::istream& operator>>(std::istream& is, Person& p) {
    std::cout << "Enter name: ";
    is >> p.name;
    std::cout << "Enter age: ";
    is >> p.age;
    return is;
}

int main() {
    Person person;
    std::cin >> person; // Using the >> operator to input person details
    person.display(); // Displaying the person details

    return 0;
}
```

### Description and Expected Output

When the `>>` operator is used with an object of the `Person` class, the
`operator>>` function is called. This function prompts the user to enter the
`name` and `age` for the person, which are then stored in the private members of
the `Person` object.

Here's what happens step-by-step:

1. The program starts and creates a `Person` object named `person`.
2. The `std::cin >> person;` line is executed, triggering the `operator>>`
   function.
3. The user is prompted to enter the name and age, which are read into the
   `person` object's `name` and `age` fields, respectively.
4. The `person.display();` call prints the details of the `person` object to the
   standard output.

#### Expected Interaction and Output

Assuming the user enters "John Doe" for the name and "30" for the age, the
interaction would look like this:

```
Enter name: John Doe
Enter age: 30
Name: John Doe, Age: 30
```

### Understanding the Process

The `>>` operator provides a convenient way to input data directly into an
object's private members without exposing those members via public setter
methods. This approach maintains encapsulation while allowing comprehensive
control over the input process, including error checking or validation if
needed. The use of `friend` here permits the `operator>>` to access private
members of `Person`, which wouldn't be possible if it were implemented as a
member function without exposing the private data publicly.
