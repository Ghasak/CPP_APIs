# Rule of Five in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Rule of Five in C++](#rule-of-five-in-c)
  - [How Rule of Five Works](#how-rule-of-five-works)
    - [1. Destructor](#1-destructor)
    - [2. Copy Constructor](#2-copy-constructor)
    - [3. Copy Assignment Operator](#3-copy-assignment-operator)
    - [4. Move Constructor](#4-move-constructor)
    - [5. Move Assignment Operator](#5-move-assignment-operator)
  - [Example of std::string similar - with Rule of Five](#example-of-stdstring-similar---with-rule-of-five)
    - [Class Definition for Context](#class-definition-for-context)
    - [1. Destructor](#1-destructor-1)
    - [2. Copy Constructor](#2-copy-constructor-1)
    - [3. Copy Assignment Operator](#3-copy-assignment-operator-1)
    - [4. Move Constructor](#4-move-constructor-1)
    - [5. Move Assignment Operator](#5-move-assignment-operator-1)
  - [Example - 1 move insights](#example---1-move-insights)
    - [Implementation](#implementation)
    - [Main Function Example](#main-function-example)
  - [Example - 2](#example---2)

<!-- markdown-toc end -->

Let's create a simple example to illustrate the Rule of Five with move semantics
in action. We'll use a class named `Resource`, which manages a dynamic array.
The Rule of Five consists of the following:

1. **Constructor**
2. **Destructor**
3. **Copy Constructor**
4. **Copy Assignment Operator**
5. **Move Constructor**
6. **Move Assignment Operator** (Technically, the Rule of Three becomes the Rule
   of Five with the addition of move semantics.)

## How Rule of Five Works

What I'm aiming for now—a clearer representation of how the `this`
and `other` objects interact in each of the Rule of Five methods, focusing
specifically on how their `m_Data` and `m_Size` members are involved. Let's
detail each with this approach.

- Rember in the rule of 5, the constructor itself is not mentioned. but its the heart of the class
  - Creating and construct a class with a constructor can also:
    - defatul constructor
    - constructor with specific inputs
    - constructor with specific input but different types
    - constrcutor which handle different logic for logging ...etc.
- Now, we will cover the `rule-of-five` in C++ by implementing the idea behind each method and most common coding practice in moder C++.

### 1. Destructor

The destructor doesn't involve another object, so it's just about `this` object releasing its resources.

```cpp
Destructor (~T())
+-----------------------------+
|      this (Object T)        |
|    .m_Data -> [data]        |  // Dynamic array to be deleted
|    .m_Size                  |  // Size of the array
+-----------------------------+
Code:
~T() {
    delete[] m_Data; // Frees allocated memory
}
```

### 2. Copy Constructor

This constructor creates a deep copy of the `other` object's resources into a newly constructed object.

```cpp
Copy Constructor (T(const T& other))
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |         this (Destination)  |
|    .m_Data -> [data]        | ---> |    .m_Data -> [new data]    |
|    .m_Size = X              |      |    .m_Size = X              |
+-----------------------------+      +-----------------------------+
Code:
T(const T& other) : m_Data(new int[other.m_Size]), m_Size(other.m_Size) {
    std::copy(other.m_Data, other.m_Data + m_Size, m_Data);
}
```

### 3. Copy Assignment Operator

This operator replaces the destination object's resources with a copy of the source object's resources.

```cpp
Copy Assignment Operator (operator=(const T& other))
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |         this (Destination)  |
|    .m_Data -> [data]        | ---> |    .m_Data -> [new data]    |
|    .m_Size = X              |      |    .m_Size = X              |
+-----------------------------+      +-----------------------------+
Code:
T& operator=(const T& other) {
    if (this != &other) {
        delete[] m_Data; // Frees existing memory
        m_Data = new int[other.m_Size];
        m_Size = other.m_Size;
        std::copy(other.m_Data, other.m_Data + m_Size, m_Data);
    }
    return *this;
}
```

### 4. Move Constructor

Transfers resources from `other` (source) to `this` (newly constructed object), without copying.

```cpp
Move Constructor (T(T&& other) noexcept)
+-----------------------------+      +----------------------------+
|        other (Source)       |      |       this (Destination)   |
|    .m_Data -> [data]        | -x-> |    .m_Data -> [data]       |
|    .m_Size = X              |      |    .m_Size = X             |
+-----------------------------+      +----------------------------+
                                   (other.m_Data set to nullptr)
Code:
T(T&& other) noexcept : m_Data(other.m_Data), m_Size(other.m_Size) {
    other.m_Data = nullptr;
    other.m_Size = 0;
}
```

### 5. Move Assignment Operator

Similar to the move constructor, but `this` (destination) releases its current resources before taking over `other`'s.

```cpp
Move Assignment Operator (operator=(T&& other) noexcept)
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |         this (Destination)  |
|    .m_Data -> [data]        | -x-> |    .m_Data -> [freed]->[data]|
|    .m_Size = X              |      |    .m_Size = X              |
+-----------------------------+      +-----------------------------+
                                   (other.m_Data set to nullptr)
Code:
T& operator=(T&& other) noexcept {
    if (this != &other) {
        delete[] m_Data; // Frees existing memory
        m_Data = other.m_Data;
        m_Size = other.m_Size;
        other.m_Data = nullptr;
        other.m_Size = 0;
    }
    return *this;
}
```

This approach visualizes the direct interaction between `this` and `other` in
terms of resource management (represented by `m_Data` and `m_Size`) for each
method in the Rule of Five, offering clarity on how each operation affects the
objects involved.

## Example of std::string similar - with Rule of Five

For a class designed to mimic the behavior of `std::string` without using smart
pointers or templates, let's call this class `SimpleString`. This class will
manage a dynamically allocated array of characters (`char*`) to store its text
content and an integer (`size_t`) to track the length of the string. We'll
implement the Rule of Five to manage the resources properly:

### Class Definition for Context

```cpp
class SimpleString {
private:
    char* data;
    size_t length;

public:
    // Destructor
    ~SimpleString();
    // Copy Constructor
    SimpleString(const SimpleString& other);
    // Move Constructor
    SimpleString(SimpleString&& other) noexcept;
    // Copy Assignment Operator
    SimpleString& operator=(const SimpleString& other);
    // Move Assignment Operator
    SimpleString& operator=(SimpleString&& other) noexcept;

    // Additional methods...
};
```

### 1. Destructor

Ensures proper cleanup of dynamically allocated memory when a `SimpleString`
object is destroyed.

```cpp
Destructor (~SimpleString())
+----------------------------+
|      this (SimpleString)   |
|    .data -> ["Hello"]      |  // Dynamically allocated array
|    .length = 5             |
+----------------------------+
Code:
~SimpleString() {
    delete[] data;
}
```

### 2. Copy Constructor

Initializes a new `SimpleString` object as a deep copy of an existing object.

```cpp
Copy Constructor (SimpleString(const SimpleString& other))
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |    this (New SimpleString)  |
|    .data -> ["World"]       | ---> |    .data -> ["World"]       |
|    .length = 5              |      |    .length = 5              |
+-----------------------------+      +-----------------------------+
Code:
SimpleString(const SimpleString& other) : length(other.length), data(new char[other.length + 1]) {
    std::copy(other.data, other.data + other.length + 1, data);
}
```

### 3. Copy Assignment Operator

Assigns a new value to an existing `SimpleString` object by deep copying another object.

```cpp
Copy Assignment Operator (operator=(const SimpleString& other))
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |     this (SimpleString)     |
|    .data -> ["Copy"]        | ---> |    .data -> ["Copy"]        |
|    .length = 4              |      |    .length = 4              |
+-----------------------------+      +-----------------------------+
Code:
SimpleString& operator=(const SimpleString& other) {
    if (this != &other) {
        delete[] data; // Free existing data
        length = other.length;
        data = new char[other.length + 1];
        std::copy(other.data, other.data + other.length + 1, data);
    }
    return *this;
}
```

### 4. Move Constructor

Initializes a new `SimpleString` object by transferring the resources of a temporary object to it, without copying.

```cpp
Move Constructor (SimpleString(SimpleString&& other) noexcept)
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |    this (New SimpleString)  |
|    .data -> ["Move"]        | -x-> |    .data -> ["Move"]        |
|    .length = 4              |      |    .length = 4              |
+-----------------------------+      +-----------------------------+
                                  (other.data set to nullptr)
Code:
SimpleString(SimpleString&& other) noexcept : data(other.data), length(other.length) {
    other.data = nullptr;
    other.length = 0;
}
```

### 5. Move Assignment Operator

Transfers the resources of one `SimpleString` object to another, replacing its content without copying.

```cpp
Move Assignment Operator (operator=(SimpleString&& other) noexcept)
+-----------------------------+      +-----------------------------+
|        other (Source)       |      |     this (SimpleString)     |
|    .data -> ["Assign"]      | -x-> |    .data -> ["Assign"]      |
|    .length = 6              |      |    .length = 6              |
+-----------------------------+      +-----------------------------+
                                  (other.data set to nullptr)
Code:
SimpleString& operator=(SimpleString&& other) noexcept {
    if (this != &other) {
        delete[] data; // Free existing data
        data = other.data;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
    }
    return *this;
}
```

This implementation details how `SimpleString` manages its dynamically allocated
character array (`data`) and its

length (`length`) through the Rule of Five, ensuring proper resource management
across construction, destruction, and assignment operations.

## Example - 1 move insights

### Implementation

```cpp
#include <iostream>
#include <algorithm> // std::copy
#include <cstring>   // std::strlen, std::strcpy

class Resource {
private:
    char* data;
    size_t length;

public:
    // Constructor
    Resource(const char* data) {
        length = std::strlen(data);
        this->data = new char[length + 1];
        std::strcpy(this->data, data);
    }

    // Destructor
    ~Resource() {
        delete[] data;
    }

    // Copy Constructor
    Resource(const Resource& other) : length(other.length), data(new char[other.length + 1]) {
        std::copy(other.data, other.data + other.length + 1, data);
        std::cout << "Copy constructor called\n";
    }

    // Copy Assignment Operator
    Resource& operator=(const Resource& other) {
        if (this == &other) return *this; // Self-assignment check
        delete[] data; // Free the existing resource
        length = other.length;
        data = new char[length + 1];
        std::copy(other.data, other.data + other.length + 1, data);
        std::cout << "Copy assignment operator called\n";
        return *this;
    }

    // Move Constructor
    Resource(Resource&& other) noexcept : data(other.data), length(other.length) {
        other.data = nullptr; // Leave the moved-from object in a valid state
        other.length = 0;
        std::cout << "Move constructor called\n";
    }

    // Move Assignment Operator
    Resource& operator=(Resource&& other) noexcept {
        if (this == &other) return *this; // Self-assignment check
        delete[] data; // Free the existing resource
        data = other.data;
        length = other.length;
        other.data = nullptr; // Leave the moved-from object in a valid state
        other.length = 0;
        std::cout << "Move assignment operator called\n";
        return *this;
    }

    // Helper function to display the data
    void printData() const {
        if (data) {
            std::cout << "Data: " << data << std::endl;
        } else {
            std::cout << "Data is null." << std::endl;
        }
    }
};
```

### Main Function Example

Now, let's see how each rule is called in practice:

```cpp
int main() {
    // Constructor
    Resource res1("Hello, World!");
    res1.printData();

    // Copy Constructor
    Resource res2 = res1;
    res2.printData();

    // Copy Assignment Operator
    Resource res3("Goodbye!");
    res3 = res1;
    res3.printData();

    // Move Constructor
    Resource res4 = std::move(res2);
    res4.printData();
    res2.printData(); // res2 is now in a moved-from state

    // Move Assignment Operator
    Resource res5("Moving!");
    res5 = std::move(res3);
    res5.printData();
    res3.printData(); // res3 is now in a moved-from state

    return 0;
}
```

In this example, you'll see the constructor being called when `res1` is created.
The copy constructor is triggered when `res2` is directly initialized from
`res1`. The copy assignment operator is used when `res3`, already initialized,
is assigned a new value from `res1`. The move constructor is used for `res4`,
initialized with `std::move(res2)`, indicating that `res2`'s resources should be
moved, not copied. Finally, the move assignment operator is called when `res5`
is assigned a new value from `res3` using `std::move(res3)`.

This example clearly demonstrates how move semantics optimize resource
management by transferring ownership of resources instead of copying them,
especially for temporary objects or in scenarios where copying is unnecessary or
expensive.

## Example - 2

The "moved-from state" refers to the state of an object after it has had its
resources taken (moved) by another object. The C++ standard does not specify
exactly what this state should be, only that the object must remain in a valid
state, meaning it must be safe to destroy and assign to, but its exact value or
state is not defined and can vary depending on the implementation of the move
operations.

The term "hollow object" is less commonly used but can refer to the same concept
as a "moved-from state," describing an object that has been emptied of its
resources and thus is "hollow" or devoid of its previous value or content.

Here's an example demonstrating the Rule of Five, which includes the following
methods:

1. **Constructor**
2. **Destructor**
3. **Copy Constructor**
4. **Copy Assignment Operator**
5. **Move Constructor**
6. **Move Assignment Operator** (Technically, the Rule of Five becomes the Rule
   of Six with both move operations considered).

```cpp
#include <iostream>
#include <utility> // For std::move

class RuleOfFive {
private:
    int* data;
public:
    // Constructor
    RuleOfFive(int value) : data(new int(value)) {
        std::cout << "Constructor\n";
    }

    // Destructor
    ~RuleOfFive() {
        std::cout << "Destructor\n";
        delete data;
    }

    // Copy Constructor
    RuleOfFive(const RuleOfFive& other) : data(new int(*other.data)) {
        std::cout << "Copy Constructor\n";
    }

    // Copy Assignment Operator
    RuleOfFive& operator=(const RuleOfFive& other) {
        std::cout << "Copy Assignment Operator\n";
        if (this == &other) return *this;
        *data = *other.data;
        return *this;
    }

    // Move Constructor
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data) {
        std::cout << "Move Constructor\n";
        other.data = nullptr; // Leave moved-from object in a valid but unspecified state
    }

    // Move Assignment Operator
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        std::cout << "Move Assignment Operator\n";
        if (this == &other) return *this;
        delete data; // Free the existing resource
        data = other.data; // Transfer ownership
        other.data = nullptr; // Leave moved-from object in a valid state
        return *this;
    }
};

int main() {
    RuleOfFive obj1(10); // Constructor
    RuleOfFive obj2 = obj1; // Copy Constructor
    RuleOfFive obj3(20); // Constructor
    obj3 = obj1; // Copy Assignment Operator
    RuleOfFive obj4 = std::move(obj1); // Move Constructor
    RuleOfFive obj5(30); // Constructor
    obj5 = std::move(obj3); // Move Assignment Operator

    return 0;
}
```

In this code, each of the Rule of Five methods is demonstrated:

- The **constructor** is called for `obj1`, `obj3`, and `obj5`.
- The **copy constructor** is called when `obj2` is initialized with `obj1`.
- The **copy assignment operator** is used when `obj3` is assigned the value of
  `obj1`.
- The **move constructor** is called when `obj4` is initialized with
  `std::move(obj1)`, transferring `obj1`'s resources to `obj4` and leaving
  `obj1` in a moved-from state.
- The **move assignment operator** is used when `obj5` is assigned the value of
  `std::move(obj3)`, transferring `obj3`'s resources to `obj5` and leaving
  `obj3` in a moved-from state.

**Output for the main function** would look something like this, demonstrating
the calls to the constructor, copy constructor, copy assignment operator, move
constructor, and move assignment operator, in that order. The destructor will be
called for each object (`obj1`, `obj2`, `obj3`, `obj4`, `obj5`) at the end of
their scope, which is at the end of `main` function:

```sh
Constructor
Copy Constructor
Constructor
Copy Assignment Operator
Move Constructor
Constructor
Move Assignment Operator
Destructor
Destructor
Destructor
Destructor
Destructor
```

The exact sequence of destructor calls depends on the objects' scopes and the
order of their creation and destruction, but each object's destructor will be
called once. The "moved-from" objects (`obj1` and `obj3`) are in valid but
unspecified states after being moved from, meaning their internal data pointer
is null and they safely do nothing when their destructors are called.
