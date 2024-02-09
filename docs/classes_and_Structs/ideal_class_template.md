# My Ideal Class

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [My Ideal Class](#my-ideal-class)
  - [Without Template](#without-template)
    - [Example -1-](#example--1-)
  - [Class Allocate dynamically Data](#class-allocate-dynamically-data)
  - [Move the new to the constructor and no-static?](#move-the-new-to-the-constructor-and-no-static)
  - [Can I move the delete to the destructor?](#can-i-move-the-delete-to-the-destructor)
  - [With Template](#with-template)

<!-- markdown-toc end -->

## Without Template

Here is the class that I want to create always for my current working style

- Class has a tracking static variable for all the objects which are created
  since the begging of calling the constructor for each instance.

1. Constructor method that:

- Accepting parameters - initilzied to the passing parameters
- Without parameters - Initialized to default state
- with `explict` for restruction on how to establish the object (instance of a class).

2. object status method (similar to **str**)

- This method should accept the `i/o steam` for using `<<` and `>>` operator
- It should print the object_id, with the assoicated internal attributes

3. Static method for tracking number of objects which are currently running,

- This method doesnt count the objects (instances) that being destroyed with destrocter.

4. Destroctor

- This will print the instance/object id and show that it is destroied.
- It will decrease the counter of the tracking object numbers in the method -3-.

5. Moving constructor method
6. Assignment operator method
7. Copy constructor method

8. Show the return type relation to `&ClassName` using `*this` pointer, which
   one will change and not change the status of the instance (object).

9. Operators method for the object.
10. Static methods if needed.
11. Instance Method that does specific task with input and output based on passing by
    `pointer`, `reference` and by value.
12. Friend Methods:
    Use friend functions cautiously to grant non-member functions access to
    private or protected class members when absolutely necessary, such as for
    operator overloading (<< and >>) when they need to access internal state.
13. Rule of Five:
    If you define a custom destructor, copy constructor, or copy assignment
    operator, consider also defining a move constructor and move assignment
    operator to manage resources correctly (especially for classes managing
    dynamic memory or other resources).
14. Const Correctness:
    Ensure methods that do not modify the object state are declared as const to
    increase usability of your class with const objects or references.
15. Templates (if applicable):
    If your class can be designed to work with various data types, consider
    making it a template class for type flexibility.

### Example -1-

We can simplify the design by using a single static variable to serve both
as the unique identifier generator (`employeeId`) and as the total count of
employees created (`employeeCount`). However, to track the current number of
employees (excluding those that have been destroyed), we'll still need at least
one additional static variable. Here's how you can adjust the `Employee` class
to use `employeeCount` for both purposes:

```cpp
#include <iostream>
#include <string>

class Employee {
private:
    static int employeeCount; // Static variable to generate unique ID and track the total number of objects created
    static int currentEmployeeCount; // Static variable to track the current number of objects excluding destroyed ones

    int employeeId;
    std::string name;
    float salary;

public:
    // Explicit constructor
    explicit Employee(std::string name, float salary) : name(name), salary(salary) {
        employeeId = ++employeeCount; // Increment first, then assign to ensure unique ID starts from 1
        currentEmployeeCount++;
    }

    // Default constructor
    Employee() : Employee("Unknown", 0.0) {}

    // Destructor
    ~Employee() {
        currentEmployeeCount--; // Decrement current count when an object is destroyed
        std::cout << "Employee ID " << employeeId << " destroyed.\n";
    }

    // Copy constructor
    Employee(const Employee& other) : name(other.name), salary(other.salary) {
        employeeId = ++employeeCount; // Ensure the copied object gets a new unique ID
        currentEmployeeCount++;
    }

    // Move constructor
    Employee(Employee&& other) noexcept
    : name(std::move(other.name)), salary(other.salary), employeeId(other.employeeId) {
        // Note: The unique ID is transferred, not incremented
        other.employeeId = 0; // Invalidate the moved-from object
    }

    // Copy assignment operator
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            name = other.name;
            salary = other.salary;
            // Note: The unique ID is not changed on copy assignment
        }
        return *this;
    }

    // Move assignment operator
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            salary = other.salary;
            // The unique ID is transferred, not assigned a new value
            other.employeeId = 0; // Invalidate the moved-from object
        }
        return *this;
    }

    // Static method to get the total number of employees created
    static int getTotalEmployeeCount() {
        return employeeCount;
    }

    // Static method to get the current number of employees
    static int getCurrentEmployeeCount() {
        return currentEmployeeCount;
    }

    // Friend function to use the insertion operator for output
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp) {
        return os << "Employee ID: " << emp.employeeId << ", Name: " << emp.name << ", Salary: " << emp.salary;
    }
};

// Initialize static member variables
int Employee::employeeCount = 0;
int Employee::currentEmployeeCount = 0;

int main() {
    Employee e1("John Doe", 50000);
    Employee e2("Jane Smith", 60000);
    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;

    std::cout << "Total Employees Created: " << Employee::getTotalEmployeeCount() << std::endl;
    std::cout << "Current Employees: " << Employee::getCurrentEmployeeCount() << std::endl;

    // Demonstrating the destructor's impact on currentEmployeeCount
    {
        Employee e3("Temporary Employee", 45000);
        std::cout << "Current Employees (after adding temp): " << Employee::getCurrentEmployeeCount() << std::endl;
    }
    std::cout << "Current Employees (after temp destroyed): " << Employee::getCurrentEmployeeCount() << std::endl;

    return 0;
}
```

In this version:

- `employeeCount` serves a dual purpose: it increments with each object creation
  (including copies and moves), providing a unique `employeeId` for each
  `Employee` object, and it also tracks the total number of `Employee` objects
  created.
- `currentEmployeeCount` still tracks the number of `Employee` objects currently
  existing, excluding those destroyed.
- The `employeeId` is assigned by incrementing `employeeCount` in each
  constructor, ensuring uniqueness and reflecting the total number of `Employee`
  instances created over the lifetime of the application.

## Class Allocate dynamically Data

In the following demo, we will create a class that allocates memory on the heap
(dynamically) to store our object, with a pointer referring to it. Assuming the
following:.

1. Accept constructors with float arguments for x and y.
2. Will allocate the object dynamically using a class Vec2d pointer on the heap.
3. I do not want to utilize Templates or smart pointers.
4. as well, there is no need for std::Vector; it should consist of basic data
   structures only.

- Creating a simple `Vec2d` class in C++, which encapsulates a 2D vector with
  `float` components for `x` and `y`. This class will also include a constructor
  that dynamically allocates an instance of `Vec2d` on the heap and returns a
  pointer to this instance. We'll stick to basic C++ features and avoid using
  templates, smart pointers, or the `std::vector`.

Here's how you could define such a class:

```cpp
#include <iostream>

class Vec2d {
public:
    float x, y;

    // Constructor that initializes x and y
    Vec2d(float x, float y) : x(x), y(y) {}

    // Static method to create an instance on the heap
    static Vec2d* create(float x, float y) {
        return new Vec2d(x, y);
    }

    // Destructor
    ~Vec2d() {
        std::cout << "Vec2d destroyed\n";
    }
};

int main() {
    // Create an instance of Vec2d on the heap
    Vec2d* vec = Vec2d::create(1.0f, 2.0f);

    // Use the Vec2d
    std::cout << "Vec2d: x = " << vec->x << ", y = " << vec->y << std::endl;

    // Don't forget to delete the instance to avoid memory leak
    delete vec;

    return 0;
}
```

This code snippet includes:

- A `Vec2d` class with `float` members `x` and `y`.
- A constructor that initializes these members.
- A static method `create` that dynamically allocates an instance of `Vec2d` on
  the heap and returns a pointer to it. This allows for the encapsulation of
  dynamic allocation within the class's interface.
- A destructor that prints a message when a `Vec2d` object is destroyed. This is
  helpful for debugging and to ensure that objects are being properly deleted to
  avoid memory leaks.

Please remember to call `delete` on any objects created with `new` to release
the memory once you're done using them. In this example, `delete vec;` is called
before the program ends to ensure there's no memory leak.

## Move the new to the constructor and no-static?

- If you want to move the dynamic memory allocation to the constructor of the
  `Vec2d` class and avoid using a static method, you'll need to adjust the
  design slightly. However, since constructors themselves cannot return
  pointers, you can't directly use a constructor to return a new instance
  allocated on the heap. Instead, you typically create the object on the stack
  within the constructor and return it by value or reference, but that doesn't
  seem to be what you're asking for.

- Given your constraints, another approach to achieve encapsulation of dynamic
  allocation without using a static method or directly calling `new` outside the
  class might involve using a factory function or another class to handle the
  allocation. However, these approaches would inherently use either static
  methods or involve additional complexity that you wish to avoid.

- Since you're aiming to keep the class simple and without static methods or
  smart pointers, and direct dynamic allocation in the constructor isn't
  standard practice (the constructor's job is to initialize an object, not
  allocate it), the usual approach is to allocate the object outside the class
  and then manage it as needed.

- If you still wish to encapsulate object creation that involves heap allocation
  within the class without using static methods or smart pointers, you would
  typically end up with designs that are a bit unconventional or indirect for
  C++ practices.

- For instructional purposes, here's a slightly adjusted version where the
  allocation happens outside, which is the common practice. The class is
  designed for objects to be typically created on the stack, but you can still
  allocate them on the heap if needed:

```cpp
#include <iostream>

class Vec2d {
public:
    float x, y;

    // Constructor that initializes x and y
    Vec2d(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // Destructor
    ~Vec2d() {
        std::cout << "Vec2d destroyed\n";
    }
};

int main() {
    // Create an instance of Vec2d on the heap
    Vec2d* vec = new Vec2d(1.0f, 2.0f);

    // Use the Vec2d
    std::cout << "Vec2d: x = " << vec->x << ", y = " << vec->y << std::endl;

    // Don't forget to delete the instance to avoid memory leak
    delete vec;

    return 0;
}
```

This code creates a `Vec2d` object on the heap in the `main` function and uses
direct allocation with `new`. The responsibility to allocate and deallocate
memory is outside the class, which is a common practice for C++ classes not
managing their own memory directly.

## Can I move the delete to the destructor?

- In C++ and most other programming languages that use manual memory management,
  it is not possible to directly move the responsibility for calling `delete` on
  an object to the destructor of the same object. The destructor (`~Vec2d()`) is
  called automatically when an object of that class is destroyed, either because
  its scope ends (for stack-allocated objects) or because `delete` is called on
  a pointer to a heap-allocated object.

- If you move the `delete` operation into the destructor of the same class
  (`Vec2d` in your case), you would end up trying to delete the object from
  within its own destruction process, leading to undefined behavior, likely a
  program crash due to a double-free or similar memory corruption error.

- The responsibility for deleting a dynamically allocated object must remain
  outside the destructor, usually in the code that allocated the object. This
  ensures clear ownership and lifespan management for dynamically allocated
  resources.

- However, if your goal is to manage related resources that are part of the
  object (e.g., pointers to other dynamically allocated objects owned by this
  object), you would indeed handle those deletions in the destructor. This
  pattern is part of the RAII (Resource Acquisition Is Initialization)
  principle, where each object manages its own resources, acquiring them in the
  constructor and releasing them in the destructor.

- Given your example, the correct usage is as you've shown: the calling code
  (`main` in this case) is responsible for calling `delete` on the dynamically
  allocated `Vec2d` object to ensure proper resource cleanup.

- If you're looking for a way to automate memory management to avoid manual
  calls to `delete`, the recommended approach in modern C++ is to use smart
  pointers (like `std::unique_ptr` or `std::shared_ptr`) despite your preference
  to avoid them. These smart pointers automatically manage the lifetime of
  dynamically allocated objects, calling `delete` when the smart pointer goes
  out of scope or is otherwise destroyed. This is a safer and more idiomatic
  approach in C++ for resource management.

## Using Class with Struct as a data type

To address all your points and incorporate a `struct` as the input to your
`Vec2d` class, we will:

1. Define a simple `struct` named `Point2D` that contains two `float` members,
   `x` and `y`.
2. Modify the `Vec2d` class to accept a `Point2D` instance as the argument for
   its constructor, demonstrating how to use simple data structures for class
   initialization.
3. Adjust the memory management based on your requests, ensuring we stick to
   basic structures without using templates or smart pointers.

Here's how you can achieve this:

### Step 1: Define the `Point2D` Struct

```cpp
struct Point2D {
    float x, y;
};
```

### Step 2: Update the `Vec2d` Class

We'll update the `Vec2d` class to accept a `Point2D` object for initialization.
To address your concerns about memory management, we will demonstrate an
approach that uses the class in a way that aligns with common C++ practices,
without moving `delete` to the destructor, as that's not a viable option for the
reasons previously discussed.

### Full Example Incorporating `Point2D`

```cpp
#include <iostream>

struct Point2D {
    float x, y;
};

class Vec2d {
public:
    float x, y;

    // Constructor that initializes x and y using a Point2D struct
    Vec2d(const Point2D& point) : x(point.x), y(point.y) {}

    // Destructor
    ~Vec2d() {
        std::cout << "Vec2d destroyed\n";
    }
};

int main() {
    // Create a Point2D instance
    Point2D point = {1.0f, 2.0f};

    // Create an instance of Vec2d on the heap using Point2D
    Vec2d* vec = new Vec2d(point);

    // Use the Vec2d
    std::cout << "Vec2d: x = " << vec->x << ", y = " << vec->y << std::endl;

    // Properly delete the Vec2d instance to avoid memory leaks
    delete vec;

    return 0;
}
```

This example encapsulates the 2D point concept into a `Point2D` struct, which is
then used to initialize `Vec2d` objects. By accepting a `Point2D` instance in
the constructor, `Vec2d` demonstrates how to use composition of simple data
structures in C++.

Remember, while this method involves manual memory management (`new` and
`delete`), it's essential to ensure that every `new` operation has a
corresponding `delete` to prevent memory leaks. This practice is fundamental in
C++ for managing dynamic memory without smart pointers.

## [Solved] Using new in constructor and delete in destroctor

To create a `Vec2d` class that handles its resources similarly to the `String`
class you've shown, we need to focus on encapsulating the `Vec2d` data (the two
floats, `x` and `y`) and manage their memory allocation and deallocation
properly. Given the nature of `Vec2d` which typically stores simple float values
directly rather than dynamically allocated memory, the analogy will slightly
adjust towards demonstrating resource management rather than direct memory
allocation for the float members themselves.

Instead, we can demonstrate a `Vec2d` class that allocates its contents
dynamically to mimic the behavior of the `String` class, even though for
`Vec2d`, this isn't a common practice due to the primitive nature of its data.
This will help understand how to manage resources similarly.

Here's a conceptual adaptation for `Vec2d`:

```cpp
#include <iostream>
#include <cstring> // For memcpy

class Vec2d {
private:
    float* m_Data;
public:
    Vec2d(float x, float y) {
        m_Data = new float[2]; // Allocate dynamic memory for 2 floats
        m_Data[0] = x;
        m_Data[1] = y;
    }

    // Copy constructor to handle deep copy
    Vec2d(const Vec2d& other) : m_Data(new float[2]), m_Size(2) {
        memcpy(m_Data, other.m_Data, 2 * sizeof(float));
    }

    ~Vec2d() {
        delete[] m_Data; // Properly deallocate the dynamic memory
    }

    float getX() const { return m_Data[0]; }
    float getY() const { return m_Data[1]; }

    // Overload << operator to work with Vec2d objects
    friend std::ostream& operator<<(std::ostream& stream, const Vec2d& vec) {
        stream << "Vec2d(" << vec.getX() << ", " << vec.getY() << ")";
        return stream;
    }
};

int main() {
    Vec2d vec(1.0f, 2.0f);
    std::cout << vec << std::endl;
    return 0;
}
```

### Key Points:

- This `Vec2d` class dynamically allocates an array of two floats to store its
  `x` and `y` values, similar to how the `String` class allocates a char array.
- The destructor deallocates the dynamic memory to avoid memory leaks.
- A copy constructor is added to ensure a deep copy of the dynamically allocated
  memory. This is important for classes managing resources to prevent issues
  like double-free errors.
- The `<<` operator is overloaded to print `Vec2d` objects conveniently, similar
  to the `String` class example.
- This example introduces more complexity than typically necessary for a class
  managing primitive data types like floats. In real-world C++ applications,
  dynamically allocating memory for simple data types is uncommon unless there's
  a specific need for it, as it introduces overhead and complexity. The primary
  aim here is to illustrate how resource management concepts from the `String`
  class can be applied to a different type of class.

This adaptation serves as an educational example to understand manual resource
management in C++, rather than a best practice for implementing a vector class.

## Optimize the previous Class

To optimize the `Vec2d` class without using templates, smart pointers, or static
methods, and while still adhering to C++ best practices, we can simplify its
design by avoiding dynamic memory allocation for its simple float members.
Dynamic allocation is more suitable for handling large amounts of data or
resources whose size might change at runtime, neither of which applies to a 2D
vector with two fixed-size float components.

Here’s a more straightforward and efficient `Vec2d` class design, focusing on
performance and simplicity:

```cpp
#include <iostream>

class Vec2d {
private:
    float x, y;

public:
    // Constructor that initializes x and y
    Vec2d(float x, float y) : x(x), y(y) {}

    // Copy constructor for deep copy - not strictly necessary here as we deal with simple types
    Vec2d(const Vec2d& other) : x(other.x), y(other.y) {}

    // Accessors for x and y
    float getX() const { return x; }
    float getY() const { return y; }

    // Setter for x and y
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }

    // Overload << operator to work with Vec2d objects
    friend std::ostream& operator<<(std::ostream& stream, const Vec2d& vec) {
        stream << "Vec2d(" << vec.x << ", " << vec.y << ")";
        return stream;
    }
};

int main() {
    Vec2d vec(1.0f, 2.0f);
    std::cout << vec << std::endl;
    return 0;
}
```

### Key Points of This Approach:

- **Efficiency**: This version of the `Vec2d` class directly stores its `x` and
  `y` components as private member variables, eliminating the need for dynamic
  memory allocation. This is more efficient because accessing these variables
  does not involve dereferencing pointers, and there's no overhead from heap
  allocation.

- **Simplicity**: The class interface remains simple and focused, with methods
  to get and set the vector components, alongside a constructor for
  initialization and a copy constructor for creating deep copies, which, in this
  case, just copies the values of `x` and `y`.

- **Safety**: By avoiding dynamic memory allocation, this version also sidesteps
  potential issues like memory leaks or the need for a custom assignment
  operator to handle deep copying (the default assignment operator is sufficient
  for this class, given its simplicity).

- **No need for custom destructor**: Since there's no dynamic allocation, the
  default destructor is adequate, simplifying memory management.

This optimized approach provides a clean, efficient, and easy-to-maintain
implementation suitable for a `Vec2d` class without compromising functionality.
It's a good example of how, in many cases, simpler is better, especially when
dealing with small, fixed-size data structures in C++.

## With Template
