# This in C++

It is a pointer to the object `Read more about the RVO` concept.

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [This in C++](#this-in-c)
    - [My Understanding](#my-understanding)
    - [This Pointer Introduction](#this-pointer-introduction)
        - [Why We Need It](#why-we-need-it)
        - [How to Use It](#how-to-use-it)
        - [Common Considerations](#common-considerations)
        - [Examples](#examples)
        - [Const Version](#const-version)
        - [Returning Object vs. Returning Reference Using `this`](#returning-object-vs-returning-reference-using-this)
        - [Example](#example)
        - [Returning by Reference](#returning-by-reference)
        - [Returning by Object (Copy)](#returning-by-object-copy)
    - [More clarification of returing this](#more-clarification-of-returing-this)
        - [Understanding `this` Pointer](#understanding-this-pointer)
        - [Correct Usage](#correct-usage)
        - [Why Not `return this;`](#why-not-return-this)

<!-- markdown-toc end -->

## My Understanding

```cpp

+------------------------------+                      +------------------------------+
|       Entity Class           |                      |       Entity Class           |
+------------------------------+                      +------------------------------+
|  class Entity{               |                      |  class Entity{               |
|    public:                   |                      |    public:                   |
|        int x, y;             |                      |        int x, y;             |
|        Entity(int x, int y){ |      --------->      |        Entity(int x, int y){ |
|            x = x;            |                      |            this->x = x;      |
|            y = y;            |                      |            this->y = y;      |
|        }                     |                      |        }                     |
|  }                           |                      |  }                           |
+------------------------------+                      +------------------------------+

      Under the hood       +------  Enitity* e = this; ----->
      Techinically, if you hover of `this` you will see it is a `Entity* const this` which means
      the pointer itself is a constant and you cannot assign it to another thing (check constant).

      Entity* const e = this; Means you cannot assign it for example like
      Entity* const e = nullptr;   <--- Not allowed as we marked this pointer is a constant value.
      You can also not allow  the referece to be assigned using
      Entity* const &e = this;

                             +----------------------------------------+
                             |          Things we can do              |
                             +----------------------------------------+
                             |     e->x = x;                          |
                             |     e->y = y;                          |
                             |     //or                               |
                             |  this->x = x;  Equal to (*this).x = x; |
                             |  this->y = y;  Equal to (*this).y = y; |
                             +----------------------------------------+

 How about a const method
+------------------------------+
|       Entity Class           |
+------------------------------+
|   class Entity{
|     public:
|         int x, y;
|         Entity(int x, int y){
|             this->x = x;
|             this->y = y;
|         }
|          int GetX() const{
|              const Entity* e = this;  // const for the content not the pointer
|             // e->x = x; NOT ALLOWED
|          }
|   }


```

- Another useful case for using `this` in a class is when you want to access an outside function inside your class.

```cpp
  +------------------------------+        passing as pointer        +------------------------------+       or passing as const refer          +------------------------------+
  |       Entity Class           |          ------->                |       Entity Class           |           ------------>                  |       Entity Class           |
  +------------------------------+             |                    +------------------------------+                 |                        +------------------------------+
 // Declaration of external function           |                    // Declaration of external function              |                        // Declaration of external function
 void PrintEntity(Entity* e);                  |                    void PrintEntity(Entity* e);                     |                        void PrintEntity(const Entity& e);
 class Entity                                  |                    class Entity                                     |                        class Entity
 {                                             |                    {                                                |                        {
     public:                                   |                        public:                                      |                            public:
         int x, y;                             |                            int x, y;                                |                                int x, y;
         Entity(int x, int y)                  |                            Entity(int x, int y)                     |                                Entity(int x, int y)
         {                                     |                            {                                        |                                {
             this->x = x;                      |                                this->x = x;                         |                                    this->x = x;
             this->y = y;                      |                                this->y = y;                         |                                    this->y = y;
// <<- I want to pass the instance here        |                           // <<- We just passing the pointer        |                               // <<- We just dereference it as
             PrintEntity();                    |                           PrintEntity(this);                        |                                    PrintEntity(*this);
         }                                     |                            }                                        |                                }
         int GetX() const                      |                            int GetX() const                         |                                int GetX() const
         {                                     |                            {                                        |                                {
         }                                     |                            }                                        |                                }
 }                                             |                    }                                                |                        }
 // Defintion of external function             |                    // Defintion of external function                |                        // Defintion of external function
 void PrintEntity(Entity* e)                   |                    void PrintEntity(Entity* e)                      |                        void PrintEntity(Entity* e)
 {                                             |                    {                                                |                        {
     // print some stuff here                  |                        // print some stuff here                     |                            // print some stuff here
 }                                             |                    }                                                |                        }
                                       --------+---------                                                    --------+---------
                                                                                                                                                            +
                                                                                                                                                            |
                                                                                                                                                            | depending on the external function signture const or no const
                                                                                                                                                            |
                                                                                                                                  +-------------------------+
                                                                                                                                  |
                                                                                                                                  v
                                                                                                        +-------------------------------------+
                                                                                                        |          IMPORTANT NOTE             |
                                                                                                        +-------------------------------------+
                                                                                                        |    // Reference of an instance      |
                                                                                                        |    Entity& e = *this;               |
                                                                                                        |    // const reference of an instance|
                                                                                                        |    const Entity& e = *this;         |
                                                                                                        +-------------------------------------+

```

- Do not use `delete this`, as it is not a good coding practice as it deletes all
  instances after calling it and frees memory. This means that you cannot access
  any instance after calling `delete this`.

## This Pointer Introduction

In C++, `this` is a special keyword that represents a pointer to the instance of
the class in which it appears. It's automatically passed as a hidden argument to
all non-static member function calls and is available as a local variable within
the body of all non-static functions. `this` pointer is used to refer to the
calling object in a member function.

### Why We Need It

1. **To distinguish between member variables and function parameters when they
   have the same name**. Using `this` helps to clarify which variable is the
   member variable.
2. **To implement method chaining**. By returning `*this` from a member
   function, you can chain function calls on the same object.
3. **To pass the current object as a parameter to another method or function**.
4. **For dynamic memory allocation and deallocation** within member functions,
   to manage resources owned by the class instance.

### How to Use It

- **Accessing Members**: You can use `this` to explicitly access member
  variables and methods.
- **Method Chaining**: By returning `this` from a method, you enable the
  chaining of method calls on the same object.

### Common Considerations

- **`this` is only usable within non-static member functions**. Static member
  functions do not have a `this` pointer because they are not called on an
  instance of the class.
- **The `this` pointer is not modifiable**. It is a constant pointer to the
  current object.

### Examples

```cpp
class MyClass {
    int attribute;

public:
    MyClass(int value) : attribute(value) {}

    // Using 'this' to access a member variable
    void setValue(int value) {
        this->attribute = value;
    }

    // Returning *this for method chaining
    MyClass& increment() {
        ++attribute;
        return *this;
    }

    void print() const {
        std::cout << attribute << std::endl;
    }
};

int main() {
    MyClass obj(5);
    obj.setValue(10);
    obj.increment().increment().print(); // This will print 12
}
```

### Const Version

When a member function is marked as `const`, the type of `this` pointer becomes
a pointer to const. This means you cannot modify the object's member data in a
const member function.

```cpp
class MyClass {
    int attribute;

public:
    MyClass(int value) : attribute(value) {}

    void print() const {
        // Here, 'this' is a const pointer to a const object
        std::cout << attribute << std::endl;
    }
};
```

### Returning Object vs. Returning Reference Using `this`

- **Returning by Object**: When a member function returns `*this` by value, it
  returns a copy of the object. This is often unnecessary and can lead to
  performance overhead due to copying.
- **Returning by Reference**: When a member function returns `*this` by
  reference (i.e., `MyClass&`), it returns the current object itself, allowing
  for efficient method chaining without unnecessary copying.

### Example

```cpp
class MyClass {
public:
    // Return by reference using 'this'
    MyClass& setX(int val) {
        // some operations
        return *this;
    }

    // Return by object (copy) using 'this'
    MyClass setY(int val) {
        // some operations
        return *this;
    }
};
```

- Returning `*this` by reference is typically preferred for method chaining, as it
  avoids the overhead of copying the object. Returning by value (copy) is less
  common and usually only done if you specifically need a copy of the object for
  some reason.

- In both cases—whether returning by reference or returning by object (copy)—the
  syntax involves `return *this;`. The key difference lies in the function's
  return type, which dictates whether the function returns a reference to the
  object or a copy of the object. Here's a closer look at both cases:

### Returning by Reference

When the function's return type is a reference to the class (e.g., `MyClass&`),
`return *this;` returns the current object itself by reference. This means no
copying is involved, and any changes made to the returned object will affect the
original object. It's efficient and commonly used for method chaining.

```cpp
class MyClass {
public:
    // Function returning a reference to the object
    MyClass& setX(int val) {
        // Some operations
        return *this; // Returns the current object by reference
    }
};
```

### Returning by Object (Copy)

When the function's return type is the class itself (e.g., `MyClass`), `return
*this;` returns a copy of the object. This involves invoking the copy
constructor of the class to create a new object that is a copy of the current
object. This can be useful in certain scenarios but is generally less efficient
due to the overhead of copying.

```cpp
class MyClass {
public:
    // Function returning a copy of the object
    MyClass setY(int val) {
        // Some operations
        return *this; // Returns a copy of the current object
    }
};
```

In summary, although the syntax `return *this;` is the same in both cases, the
effect and efficiency can vary significantly based on whether the return type is
a reference or a copy of the object.


## More clarification of returing this

The syntax `return this;` does not work for returning the object itself (by
value or by reference) in the way you might expect in C++. Here's why:

### Understanding `this` Pointer

- `this` is a pointer to the current object. It provides the address of the
  object on which the member function is called.
- When you use `return this;`, you're attempting to return a pointer to the
  object, not the object itself or a reference to it.

### Correct Usage

1. **For Returning by Reference (`MyClass&`)**: When you want to return the
   current object by reference, you use `return *this;`. Here, `*this`
   dereferences the `this` pointer, returning the object itself by reference.

    ```cpp
    MyClass& setY(int val) {
        // Operation
        return *this;  // Correct: Returns a reference to the current object
    }
    ```

2. **For Returning by Value (`MyClass`)**: If you aim to return a copy of the
   object, `return *this;` is also used. The dereference operation `*this`
   returns the object itself, and since the return type is by value, a copy of
   the object is made and returned.

    ```cpp
    MyClass setY(int val) {
        // Operation
        return *this;  // Correct: Returns a copy of the current object
    }
    ```

### Why Not `return this;`

- `return this;` would attempt to return a pointer to `MyClass` (`MyClass*`),
  not an object or a reference to an object. This is a different type than what
  the function signature specifies (`MyClass` or `MyClass&`) and would result in
  a compilation error.

    ```cpp
    MyClass* setY(int val) {
        return this;  // Correct only if you actually want to return a pointer to the object
    }
    ```

In summary, to return the object itself (either by reference or by value), you
use `return *this;` because it correctly dereferences the `this` pointer to
obtain the object that `this` points to. Using `return this;` would only be
appropriate if the function's return type is a pointer to the class type
(`MyClass*`), which is a different use case (returning a pointer to the object,
not the object itself or a reference to it).
