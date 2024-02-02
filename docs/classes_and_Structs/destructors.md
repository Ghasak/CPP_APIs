# Destructors in C++

A C++ destructor is a special member function of a class that is executed
whenever an object of its class goes out of scope or is explicitly deleted. A
destructor will perform the necessary cleanup for an object, such as releasing
memory, closing file handles, or any other cleanup routines required to avoid
resource leaks. Like constructors, destructors have specific characteristics and
use cases:

### Characteristics of Destructors

- **Name:** The destructor's name is the same as the class name preceded by a
  tilde (~).
- **No Parameters and No Return Type:** Destructors do not accept parameters and
  do not return a value.
- **Automatic Invocation:** Destructors are called automatically by the C++
  runtime system when an object's lifetime ends.
- **One per Class:** A class can have only one destructor, and it cannot be
  overloaded.

### Why We Need Destructors

Destructors are essential for managing resources efficiently and ensuring robust
resource management in a C++ program. They are used to:

- **Release Resources:** Free any resources that were allocated by the object.
- **Avoid Memory Leaks:** Ensure that dynamically allocated memory is released.
- **Clean Up:** Perform any necessary finalization before an object is destroyed.

### How to Use Destructors: Syntax and Examples

#### Basic Syntax

```cpp
class MyClass {
public:
    ~MyClass() {
        // Cleanup code here
    }
};
```

#### Example: Releasing Dynamic Memory

```cpp
class MyClass {
    int* data;
public:
    MyClass(int size) { data = new int[size]; } // Allocate memory
    ~MyClass() { delete[] data; } // Release memory
};
```

### Things to Avoid and Take Care When Dealing with Destructors

1. **Avoid Throwing Exceptions:** Destructors should not throw exceptions. If a
   destructor throws an exception, and it is not handled, `std::terminate` will
   be called, and the program will exit.
2. **Be Wary of Virtual Destructors:** If a class is intended to be used as a
   base class, its destructor should be virtual to ensure that the destructor of
   the derived class is called when deleting an object through a base class
   pointer.

   ```cpp
   class Base {
   public:
       virtual ~Base() {} // Virtual destructor
   };
   ```

3. **Avoid Using Destructors for Logic:** Destructors are meant for cleanup.
   Business logic should not be implemented in destructors.
4. **Resource Management:** Ensure that all resources acquired are released.
   This includes memory, file handles, network sockets, etc.

### Additional Facts About Destructors

- **Rule of Three/Five:** If a class defines a destructor, it should likely also
  define a copy constructor and copy assignment operator (Rule of Three). With
  C++11, this extends to the move constructor and move assignment operator (Rule
  of Five).
- **Destructor in Inheritance:** In a class hierarchy, destructors should be
  virtual to ensure proper cleanup of derived class objects.
- **Defaulted and Deleted Destructors:** C++11 allows explicitly defaulting or
  deleting destructors to control class behavior.

  ```cpp
  class MyClass {
  public:
      ~MyClass() = default; // Default destructor
  };
  ```

### Summary Table

| Concept                       | Description                                                                                                           |
| ----------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| Basic Syntax                  | The destructor is named with a tilde (~) followed by the class name.                                                  |
| Automatic Invocation          | Destructors are called automatically when an object's scope ends.                                                     |
| Virtual Destructors           | Necessary for base classes to ensure derived class destructors are called.                                            |
| Avoid Exceptions              | Destructors should not throw exceptions; unhandled exceptions can cause program termination.                          |
| Resource Management           | Destructors should release all resources acquired by the object.                                                      |
| Rule of Three/Five            | If a class defines a destructor, it likely needs to define or delete copy/move constructors and assignment operators. |
| Defaulted/Deleted Destructors | C++11 feature allowing destructors to be explicitly defaulted or deleted.                                             |
| Use in Inheritance            | Virtual destructors are essential for proper cleanup in class hierarchies.                                            |

Destructors play a critical role in resource management and cleanup in C++
programming, ensuring that resources are properly released and that classes can
be extended safely through inheritance. Proper understanding and use of
destructors are fundamental to writing efficient, leak-free C++ code.
