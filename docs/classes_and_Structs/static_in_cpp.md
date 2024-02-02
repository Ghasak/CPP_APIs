# Static In C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Static In C++](#static-in-c)
    - [NOTEs To be taken](#notes-to-be-taken)
    - [1. Within a Translation Unit - (Varaibles and Functions)](#1-within-a-translation-unit---varaibles-and-functions)
        - [1.1. Static Main Usage (same for both variables and functions )](#11-static-main-usage-same-for-both-variables-and-functions-)
        - [1.2. Using Extern](#12-using-extern)
    - [2. Within Classes](#2-within-classes)
        - [2.1. with class varaibles, methods](#21-with-class-varaibles-methods)
            - [2.1.1. Why We Need Static Methods](#211-why-we-need-static-methods)
            - [2.1.2. Considerations for Creating Static Methods](#212-considerations-for-creating-static-methods)
            - [2.1.3. Common Use Cases for Static Methods](#213-common-use-cases-for-static-methods)
            - [2.1.4. Common Code Practice for Using and Creating Static Methods](#214-common-code-practice-for-using-and-creating-static-methods)
            - [2.1.5. Summary Table](#215-summary-table)
        - [2.2. Examples](#22-examples)
            - [2.2.1 General - Example using static variable](#221-general---example-using-static-variable)
            - [2.2.2 General - Static Method in C++](#222-general---static-method-in-c)
            - [2.2.3. Accessing Non-static Members from a Static Method](#223-accessing-non-static-members-from-a-static-method)

<!-- markdown-toc end -->

In C++, there are two ways to use static:

1. Definition for a translation unit (Cpp file)
2. Within the class itself

We will talk about both of them right now:

## NOTEs To be taken

- Within the translation unit:
  - It is convent to use `s_<object_name>` (e.g.,
    s_VariableG, s_MyMethod) to refer to them inside the code as a `static`
    varaibles/functions.
  - "Extern" is a useful way to organize global variables as it allows for their
    definition in a single header file that can be easily shared among all other
    translation units. This practice, commonly known as external linkage or simply
    "extern," helps in better organizing and managing global variables across
    multiple source files in a project."
- Within Class:
- Use `static` only when you are

## 1. Within a Translation Unit - (Varaibles and Functions)

It solely restricts the scope of the specified `object` (for instance, int var =
10;) to be utilized inside the provided translation unit `cpp-file` during its
definition.

- Why we need such thing? simply for given us a private object which will not be
  linked outside of the given `CPP-file`.

### 1.1. Static Main Usage (same for both variables and functions )

- General case:
  - When defining a variable as `int VariableG = 10;` in `tu.cpp` and you have set
    up your headers along with the `CMakelists.txt`, the variable `VariableG` can be
    accessed directly in `main.cpp`.
  - However, if you want to use another variable with the same name, `int VariableG = 20;`, within `main.cpp`, it will result in a compiler error as
    the variable has already been defined at `tu.cpp` and this is not allowed.

```sh
                          [NOT ALLOWED]
+---------------------+                     +-------------------+
|      main.cpp       |                     |      tu.cpp       |
+---------------------+     <-----------    +-------------------+
int VariableG = 20;                         int VariableG = 10;


```

- static at the translation unit level `top of the file tu.cpp` will help us to
  define two variables with same name given two linked translation unit
  `main.cpp` and `tu.cpp`.
  - This is the primary usage of the `static` keyword as it allows us to inform
    the compiler that any `static` variable will be initialized only once and be
    accessible within "tu.cpp" for use. This helps in reducing the amount of
    memory required by avoiding multiple copies of the same variable in
    different instances of a function or class..

```sh
                          [ALLOWED]
+---------------------+                     +-------------------+
|      main.cpp       |                     |      tu.cpp       |
+---------------------+     <-----------    +-------------------+
int VariableG = 20;                         static int VariableG = 10;

```

- NOTE: It functions like declaring a variable as private, which cannot be seen
  by other translation units. The linker will not see this in the global scope.

### 1.2. Using Extern

My understanding about the usage of `Extern` was unclear as I already knew that
the variable `VariableG` would automatically be available in `main.cpp`.
Therefore, I wondered why we need to explicitly declare it with `extern` when it
is already coming from `tu.cpp`. But, Now I know its just a simple way to manage
your `Global` variables, lets dive deep into why we need `Extern`.

The `extern` keyword in C++ is indeed useful, even in the scenario you
described. The main purpose of `extern` is to indicate that a variable or
function has external linkage, meaning it is defined in another translation unit
(TU). In the context of your example, here's why it's useful:

1. **Clarifying Intent**: By declaring `extern int VariableG;` in `main.cpp`,
   you explicitly indicate that `VariableG` is not a local variable to
   `main.cpp` but is defined elsewhere (in this case, in `tu.cpp`). This makes
   your code more readable and easier to understand, especially in larger
   projects where it might not be immediately obvious where a variable is
   defined.
2. **Preventing Multiple Definitions**: Without `extern`, if you inadvertently
   define `VariableG` in both `tu.cpp` and `main.cpp`, you'll end up with
   multiple definition errors during linking. The `extern` keyword in `main.cpp`
   ensures that the compiler knows `VariableG` is defined in another file,
   preventing such issues.
3. **Linkage Across Multiple Files**: In a larger project with multiple source
   files, `extern` is crucial for sharing variables across these files. While in
   small projects or examples, it might seem redundant, its utility becomes
   apparent in larger, more complex codebases.
4. **Managing Global Variables**: `extern` is commonly used for managing global
   variables. It allows you to define global variables in one file and use them
   across multiple files. This can be particularly useful in modular
   programming, where different modules (source files) need to access shared
   data.

In out case, since we're using `CMakeLists.txt` to compile the project, it
manages the linking of `tu.cpp` and `main.cpp`. The presence of `extern` in
`main.cpp` is a way to inform the compiler about the existence of `VariableG` in
a different translation unit (in `tu.cpp`). Even though the linking is handled
by CMake, the `extern` keyword is still necessary for proper declaration and to
avoid compilation errors related to unresolved symbols.

- **NOTE**: This called external-linkage (or external linking)

```sh
                          [ALLOWED]
+---------------------+                     +-------------------+
|      main.cpp       |                     |      tu.cpp       |
+---------------------+     <-----------    +-------------------+
extern int VariableG;                       int VariableG = 10;

```

- If you want to use `static` with extern, this will not work, as the `Linker`
  will not see the `VariableG` in the `tu.cpp` when it called in `main.cpp`.

```sh
                          [NOT-ALLOWED]
+---------------------+                     +-------------------+
|      main.cpp       |                     |      tu.cpp       |
+---------------------+     <-----------    +-------------------+
extern int VariableG;                       static int VariableG = 10;
        ^
        |
[Cannot see VaraibleG]
```

## 2. Within Classes

Now, within a class, we have `static`, which hold a similar
significance across almost every object-oriented programming language.

### 2.1. with class varaibles, methods

Static methods in C++ are functions that belong to a class rather than any
particular object instance. They can be called on the class itself rather than
on instances of the class. Here's a comprehensive overview addressing your
queries about static methods in C++.

- When we define a `attribute` inside a class a `static`, It means that it is
  going to be one instance of that variable across all instances. Same goes for
  class-methods:

  - It is useful for haveing an `object/entity` (variable/method) to be shared
    across all instances.
  - The `static` method cannot access the internal `class-attributes` as they are
    related more to the `instance` of the class not to the whole class, for
    example `x` and `y` both will not be seen in the `Print` static class-method
    in the following example:

    ```cpp
    class Entity{
    private:
        int x, y;

        static void Print(){
            std::cout << x << ", " << y << std::endl;   // <- Won't compile, k

        }

    public:
    }
    ```

#### 2.1.1. Why We Need Static Methods

1. **Global Functionality**: They provide a way to implement functionality that
   is relevant to all instances of a class but does not require access to
   instance-specific data.
2. **Utility Functions**: Useful for utility or helper functions that can
   operate independently of object instances.
3. **Performance**: Since they don't require an object instance to be invoked,
   calling a static method can be slightly faster when you don't need access to
   non-static members.

#### 2.1.2. Considerations for Creating Static Methods

- **Access to Class Attributes**: Static methods cannot access instance
  variables (non-static members) directly. This is because static methods are
  called without an object, and non-static members require an instance to exist.
- **Accessing Static Members**: They can only access static variables or other
  static methods directly. If you need to access non-static members, you must do
  so through an instance of the class.
- **Use Cases**: They are not meant for manipulating object-specific data but
  rather for operations that are relevant to the class as a whole.

#### 2.1.3. Common Use Cases for Static Methods

1. **Factory Methods**: Creating objects of a class. A static method can act as
   a factory method to return objects of the class.
2. **Utility Functions**: For operations that don't require access to the
   instance variables but are closely related to the class's domain, like
   mathematical operations or formatting.
3. **Singleton Pattern**: Ensuring a class has only one instance and providing a
   global point of access to it through a static method.
4. **Access Control**: Managing access to global mutable state in a controlled
   manner.

#### 2.1.4. Common Code Practice for Using and Creating Static Methods

1. **Declaration and Definition**: Static methods are declared within a class
   definition and are marked with the `static` keyword. They are defined outside
   the class body, usually in a .cpp file.
2. **Calling Static Methods**: They are called using the class name and the
   scope resolution operator (`ClassName::methodName()`), not through an
   instance of the class.
3. **Relevance**: Ensure the method is relevant to the class's concept and not
   just a convenient place to put unrelated functionality.
4. **State Management**: Be cautious with static methods that alter static
   variables. They can affect the state in ways that are hard to track and
   debug.

#### 2.1.5. Summary Table

| Aspect                | Detail                                                                                                        |
| --------------------- | ------------------------------------------------------------------------------------------------------------- |
| **Purpose**           | Implement functionality relevant to the class, not an instance.                                               |
| **Access to Members** | Can only access static members (variables/methods).                                                           |
| **Use Cases**         | Factory methods, utility functions, singleton pattern, access control.                                        |
| **Considerations**    | Cannot access instance variables or methods. Ideal for operations that don't require object state.            |
| **Common Practices**  | Declared with `static` keyword, called with `ClassName::methodName()`, used for class-relevant functionality. |

Static methods in C++ offer a way to encapsulate functionality that is relevant
to the class as a whole rather than to individual instances. They provide a
means to organize utility functions and shared behavior in a way that's
accessible without needing to create an object, making them a powerful feature
for certain use cases.

### 2.2. Examples

#### 2.2.1 General - Example using static variable

- To create a class in C++ that keeps track of the number of objects created and
  provides a class method to access this count, you can follow these steps:

1. **Declare a Static Member Variable:** This variable will keep count of the
   number of objects created. It's static, so it belongs to the class, not to
   any individual object.
2. **Increment the Counter in the Constructor:** Every time an object is
   created, the constructor is called, so increment the counter there.
3. **Provide a Static Method to Access the Count:** This method will be callable
   on the class itself, not on an instance of the class.

Here's how you could implement this:

```cpp
#include <iostream>

class MyClass {
private:
    static int objectCount; // Static member to keep track of the number of objects

public:
    // Constructor
    MyClass() {
        // Increment the static member variable each time an object is created
        objectCount++;
    }

    // Static method to get the number of objects created
    static int getObjectCount() {
        return objectCount;
    }
};

// Initialize static member variable
int MyClass::objectCount = 0;

int main() {
    MyClass obj1; // Creating the first object
    MyClass obj2; // Creating the second object

    // Accessing the static method without an object
    std::cout << "Number of objects created: " << MyClass::getObjectCount() << std::endl;

    return 0;
}
```

In this example:

- The `objectCount` static variable is incremented each time a `MyClass` object
  is created.
- The `getObjectCount` static method is used to access the count. It's called on
  the class itself (`MyClass::getObjectCount()`), not on an instance of the
  class.

This is a basic example demonstrating the use of static members and methods in
object-oriented programming in C++.

#### 2.2.2 General - Static Method in C++

Let's start with a simple example demonstrating a static method within a class.

```cpp
#include <iostream>

class MathUtils {
public:
    // Static method that calculates the square of a number
    static int square(int number) {
        return number * number;
    }
};

int main() {
    // Calling the static method without creating an instance of the class
    int result = MathUtils::square(5);
    std::cout << "Square of 5 is: " << result << std::endl;
    return 0;
}
```

In this example, `square` is a static method that can be called using the class
name (`MathUtils::square`) without needing to instantiate the `MathUtils` class.
It's ideal for utility operations like mathematical calculations that don't
depend on the state of a class instance.

#### 2.2.3. Accessing Non-static Members from a Static Method

Accessing non-static members (instance variables and methods) from a static
method requires an instance of the class. Here's how you can do it:

```cpp
#include <iostream>

class Counter {
private:
    int count; // Non-static member variable

public:
    Counter() : count(0) {} // Constructor to initialize count

    void increment() { count++; } // Non-static method to increment count
    int getCount() const { return count; } // Non-static method to get count

    // Static method
    static void displayCount(Counter& c) {
        std::cout << "Count: " << c.getCount() << std::endl; // Accessing non-static member through an instance
    }
};

int main() {
    Counter c;
    c.increment();
    c.increment();

    // Calling a static method and passing an instance of Counter
    Counter::displayCount(c);
    return 0;
}
```

In this example, the `displayCount` static method accesses the non-static
`getCount` method of the `Counter` class through an instance `c` that is passed
to it. This demonstrates how a static method can interact with instance-specific
data by operating on an instance of the class. This approach allows static
methods to perform operations that involve both static and non-static members,
provided they have access to an instance of the class.
