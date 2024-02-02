# Constructors

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Constructors](#constructors)
    - [-](#-)
    - [How to Use Constructors: Syntax and Examples](#how-to-use-constructors-syntax-and-examples)
        - [Default Constructor](#default-constructor)
        - [Parameterized Constructor](#parameterized-constructor)
        - [Copy Constructor](#copy-constructor)
        - [Things to Avoid and Take Care When Dealing with Constructors](#things-to-avoid-and-take-care-when-dealing-with-constructors)
        - [Additional Facts About Constructors](#additional-facts-about-constructors)
        - [Summary Table](#summary-table)

<!-- markdown-toc end -->

A C++ constructor is a special member function of a class that is executed
whenever we create new objects of that class. It can be used to initialize the
class's objects. Constructors have the same name as the class and may be
parameterized to allow passing values to the object upon creation. They do not
return any value, not even `void`.

```cpp
class Enitity {

private:
    float X, Y;

public:
    //Enitity(X, Y ): X{X}, Y{Y}{}; <- This is our constructor
    void Print() { std::cout << X << ", " << Y << std::endl; }
};


int main(int argc, char** argv){

    Enitiy e;
    e.Print();
    // output
    // It will print what left over in memeory because we didnt initialized the variables of e.X and e.Y
    // Thats why we need a constructor
return 0
}

```

### Why We Need Constructors

Constructors are essential for several reasons:

- **Initialization:** They ensure that an object begins life in a consistent
  state.
- **Resource Allocation:** Constructors can allocate resources that the object
  will use, such as dynamic memory.
- **Automatic Invocation:** They are automatically called when an object is
  created, making initialization seamless and intuitive.

### How to Use Constructors: Syntax and Examples

#### Default Constructor

A default constructor does not take any arguments. If no constructor is defined, C++ automatically generates a default constructor.

```cpp
class MyClass {
public:
    MyClass() {
        // Initialization code here
    }
};
```

#### Parameterized Constructor

A constructor with parameters can be used to initialize an object with specific values.

```cpp
class Rectangle {
    int width, height;
public:
    Rectangle(int x, int y) : width(x), height(y) {}
};
```

#### Copy Constructor

A copy constructor initializes an object using another object of the same class.

```cpp
class MyClass {
public:
    MyClass(const MyClass& other) {
        // Copy initialization code here
    }
};
```

### Things to Avoid and Take Care When Dealing with Constructors

1. **Avoid Complex Logic in Constructors:** Constructors should not contain
   complex logic or operations that can fail if they are not absolutely
   necessary for object initialization.
2. **Be Careful with Dynamic Memory Allocation:** If your constructor allocates
   memory dynamically, ensure to deallocate it in the destructor to avoid memory
   leaks.
3. **Avoid Calling Virtual Functions in Constructors:** Virtual function calls
   in constructors will not behave as expected because the object is not yet
   fully formed.
4. **Explicit Keyword:** Use `explicit` keyword with constructors to prevent
   automatic type conversion.

   Example:

   ```cpp
   class MyClass {
   public:
       explicit MyClass(int a) {}
   };
   ```

   This prevents accidental conversions from `int` to `MyClass`.

### Additional Facts About Constructors

- **Delegating Constructors:** C++11 introduced the concept of delegating
  constructors, allowing one constructor to call another constructor in the same
  class to avoid code duplication.

  ```cpp
  class MyClass {
  public:
      MyClass() : MyClass(0) {} // Delegating constructor
      MyClass(int value) {}    // Target constructor
  };
  ```

- **Initializer Lists:** Use initializer lists to efficiently initialize member
  variables and for initializing base class members.
- **Defaulted and Deleted Constructors:** C++11 allows explicitly defaulting or
  deleting constructors, which can be useful for controlling object creation and
  assignment behaviors.

  ```cpp
  class MyClass {
  public:
      MyClass() = default;           // Default constructor
      MyClass(const MyClass&) = delete; // Prevent copying
  };
  ```

### Summary Table

| Concept                        | Description                                                                                      |
| ------------------------------ | ------------------------------------------------------------------------------------------------ |
| Default Constructor            | Automatically generated if no constructors are defined; initializes objects with default values. |
| Parameterized Constructor      | Takes parameters and initializes objects with specified values.                                  |
| Copy Constructor               | Initializes an object using another object of the same class.                                    |
| Explicit Constructors          | Prevents automatic type conversion to avoid unintended conversions.                              |
| Delegating Constructors        | Allows a constructor to call another constructor within the same class.                          |
| Initializer Lists              | Efficiently initializes member variables and base class members.                                 |
| Defaulted/Deleted Constructors | Allows specifying default behavior or preventing certain operations (e.g., copying).             |
| Avoid Complex Logic            | Constructors should be simple and not contain complex or failure-prone operations.               |
| Dynamic Memory                 | If using dynamic memory, ensure to manage it properly to avoid leaks.                            |
| Virtual Functions              | Avoid calling virtual functions in constructors.                                                 |

Constructors are a foundational concept in C++ that enable object-oriented
programming by ensuring objects are properly initialized when they are created.
Understanding their nuances and best practices is essential for effective C++
programming.
