# My Ideal Class

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [My Ideal Class](#my-ideal-class)
  - [Without Template](#without-template)
    - [Example -1-](#example--1-)
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

## With Template
