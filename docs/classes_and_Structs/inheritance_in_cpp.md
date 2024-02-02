# Inheritance in C++

Inheritance allows us to create a hierarchical structure of parent and child
classes to prevent code duplication..

```cpp

+--------------------------------------+                  +--------------------------------------+
|             Parent Class             |                  |             Child Class              |
+--------------------------------------+                  +--------------------------------------+
|                                      |                  | class PlayerChild {                  |
|  class Person {                      |                  |  public:                             |
|  public:                             |                  |    float X, Y;                       |
|      float X, Y;                     | <-- Similar -->  |    const char* Name;                 |
|      void Move(float xa, float ya) { |                  |    void Move(float xa, float ya) {   |
|          this->X += xa;              |                  |        X += xa;                      |
|          this->Y += ya;              |                  |        Y += ya;                      |
|      }                               |                  |    }                                 |
|  };                                  |                  |};                                    |
+--------------------------------------+                  +--------------------------------------+

```

The way to do `inheritance` is:

```cpp
+--------------------------------------+                  +--------------------------------------+
|            Parent Class              |                  |             Child Class              |
+--------------------------------------+                  +--------------------------------------+
|                                      |                  | class PlayerChild:Person             |
|  class Person {                      |                  |{ public:                             |
|  public:                             |                  |    //float X, Y;                     |
|      float X, Y;                     | <-- Similar -->  |    const char* Name;                 |
|      void Move(float xa, float ya) { |                  |    //void Move(float xa, float ya) { |
|          this->X += xa;              |                  |    //    X += xa;                    |
|          this->Y += ya;              |                  |    //    Y += ya;                    |
|      }                               |                  |    //}                               |
|  };                                  |                  |};                                    |
+--------------------------------------+                  +--------------------------------------+

```

- Child class can access all `public` parent class methods and attributes.
- Lets see the size of the object that we can create from the the `Child` class

```cpp
int main(int argc , char* [] argv){ // or char** argv
    PlayerChild e;
    std::cout << "Examine the size of "<<
    "object created from a child class -> " << sizeof(PlayerChild) << std::endl;
}
```

- We think of this as:

```cpp
We have `int X`, `int Y ` and `char*`
in a x64 system, int is 4-bytes of memeory, char* is a pointer with a 8-bytes on x64 by the complier.
So, we have
                                   -e- as an object
                                          |
                                          |
                                          V
<---------- X ------------>   <---------- Y ------------>    <---------- Char* --------->
[0][0]-[0][0]-[0][0]-[0][0] | [0][0]-[0][0]-[0][0]-[0][0] | [0][0]-[0][0]-[0][0]-[0][0] |

The output should be 16-bytes in our `macOS-x64`, given the `char*` pointer is an `int` of `double` with 8-bytes.

-------- output --------
Size of our e from PlayerChild object -> 16
Size of our e from Person object      -> 8

```

- Thinking of a class just a group of other types of data including:
  - From the starndard libraries
    - Primitive such as `int` , `double`, string ..etc.
    - Data Containers such as `array`, `list`, `vector`
    - Enum, structs
    - Other classes as a datatype (you create a class with a complex structure
      and use it as an attribute to your consturcted class).
  - Other types from other libraries

## Inheritance Introduction

Inheritance is a fundamental concept in object-oriented programming (OOP) that
allows a class (derived or child class) to inherit properties and behaviors
(methods and fields) from another class (base or parent class). This mechanism
promotes code reuse and establishes a relationship between classes through
generalization and specialization.

### Characteristics of Inheritance

- **Reusability:** Inheritance supports the reuse of existing code. The derived
  class inherits all the public and protected members of the base class.
- **Hierarchy:** It establishes a hierarchy between the base class and derived
  classes.
- **Overriding:** Derived classes can override or extend the functionalities of
  base class methods.
- **Types of Inheritance:** C++ supports several types of inheritance, including
  single, multiple, and multilevel inheritance.

### Access Levels in Inheritance

In C++, there are three access specifiers: `public`, `protected`, and `private`.
How a derived class can access the members of a base class depends on both the
access specifier of the members and the mode of inheritance.

#### Modes of Inheritance

- **Public Inheritance:** Public and protected members of the base class become
  public and protected members of the derived class, respectively.
- **Protected Inheritance:** Public and protected members of the base class
  become protected members of the derived class.
- **Private Inheritance:** Public and protected members of the base class become
  private members of the derived class.

#### Accessible Members to Child Class

- **Public Members:** Always accessible from the derived class if the
  inheritance is public.
- **Protected Members:** Accessible within the derived class but not accessible
  directly from objects of the derived class.
- **Private Members:** Not accessible directly by the derived class, but can be
  accessed through public or protected methods of the base class.

### How to Use Inheritance: Syntax and Examples

#### Basic Syntax

```cpp
class BaseClass {
public:
    void baseMethod() {}
};

class DerivedClass : public BaseClass {
    // Derived class can use baseMethod()
};
```

#### Example: Public Inheritance

```cpp
class Animal {
public:
    void eat() { std::cout << "Eating..." << std::endl; }
protected:
    int age;
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Barking..." << std::endl; }
    void setAge(int a) { age = a; } // Can access protected member 'age'
};
```

### Things to Consider in Inheritance

- **Constructor and Destructor Calls:** Constructors of the base class are
  called before the derived class's constructor. Destructors are called in the
  reverse order.
- **Virtual Functions:** Use virtual functions to enable polymorphism. This
  allows derived classes to override base class methods.
- **Access Control:** Be mindful of the access levels and inheritance modes to
  ensure proper encapsulation and access to class members.
- **Diamond Problem:** With multiple inheritance, the diamond problem can occur
  when two base classes have a common base. Use virtual inheritance to prevent
  multiple instances of the common base class.

### Summary Table

| Concept                  | Description                                                                              |
| ------------------------ | ---------------------------------------------------------------------------------------- |
| Reusability              | Inheritance allows derived classes to use members of the base class.                     |
| Hierarchy                | Establishes a parent-child relationship between classes for specialization.              |
| Overriding               | Derived classes can override base class methods for specialized behavior.                |
| Access Levels            | Determines how base class members are accessed in the derived class.                     |
| Public Inheritance       | Base class's public and protected members are public and protected in the derived class. |
| Protected Inheritance    | Base class's public and protected members become protected in the derived class.         |
| Private Inheritance      | Base class's public and protected members become private in the derived class.           |
| Constructors/Destructors | Base class constructors are called before derived class constructors.                    |
| Virtual Functions        | Allow derived classes to override base class methods for polymorphism.                   |
| Diamond Problem          | A problem in multiple inheritance that can be solved with virtual inheritance.           |

Inheritance in C++ enables powerful and flexible object-oriented designs by
allowing classes to inherit and refine functionalities from other classes.
Understanding the nuances of inheritance, including access specifiers and
inheritance modes, is crucial for designing effective C++ applications.


## Example - 1
This example shows the power of inheritance, as we don't need to define same field/attribute if we have it already in the parent class

```cpp

/*************************************
 * Class Entity
 * This is the parent class
 *************************************/
class Entity {
private:
    std::string m_Name;

public:
    // Constructor method for Entity
    Entity(const std::string& name)
        : m_Name{name} {
        std::cout << "Entity Object is created .." << std::endl;
    }
    std::string GetName() { return std::string("Entity Object"); }
};

/*************************************
 * Class Player
 * This is the child class
 *************************************/
class Player : public Entity {
private:
    std::string m_ChildName; // this is not need anymore

public:
    // Constructor method for Player
    Player(const std::string& child_name)
        : Entity{child_name} {  // Inhertance from Entity
        std::cout << "Player Object is created .." << std::endl;
    }
};


```
