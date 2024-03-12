# STD::MOVE and the MOVE Assignment Operator in C++

This is the the last part of the mini-series of implementing the move semantics in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [STD::MOVE and the MOVE Assignment Operator in C++](#stdmove-and-the-move-assignment-operator-in-c)
    - [My understanding](#my-understanding)
        - [std::move concept](#stdmove-concept)
        - [Move assignement operator](#move-assignement-operator)
    - [More Details - Depth](#more-details---depth)
        - [1. `std::move`:](#1-stdmove)
        - [2. Move Assignment Operator:](#2-move-assignment-operator)
        - [Scenarios That Trigger the Move Assignment Operator:](#scenarios-that-trigger-the-move-assignment-operator)
        - [Common Practices, Pitfalls, and Notes:](#common-practices-pitfalls-and-notes)

<!-- markdown-toc end -->

## My understanding

As part of our `rule-of-five`, we can see the full picutre of this topic and its relation to other concpets.

1. **Constructor**
2. **Destructor**
3. **Copy Constructor**
4. **Copy Assignment Operator**
5. **Move Constructor**
6. **Move Assignment Operator** (Technically, the Rule of Three becomes the Rule
   of Five with the addition of move semantics.)

```sh

+--------------------+                   +--------------------+
|  COPY CONSTRUCTOR  |    <---------     |   OBJECT LIFETIME  |
+--------------------+                   +--------------------+
         |
         |
         V
+--------------------+                    +--------------------+                        +--------------------+
| LVALUES & RVALUES  |    ---------->     |  MOVE SEMANTICS    |     ------------->     |   MOVE ASSIGNMENT  |
+--------------------+                    +--------------------+                        +--------------------+
         +                                         +                                             +
         |                                         |                                             |
         |                                         |                                             +--- Assignment (=)
         |                                         +--- move constructor
         |                                              concept, std::move
         +--<--- Using lvalue-references
                 and rvalue-reference.

```


- We have to cover in this module the assignment operator. What will happen when
  we want to move an object to another object with the assignment operator.

In general, moving refers to transferring the exact data from the source object
to the destination object, thereby simply reassigning pointers. This is highly
advantageous when dealing with large objects as it minimizes the need for
excessive copying. For instance, consider a 1-million `std::string` object
stored in a `std::vector`. Moving allows us to avoid unnecessary duplication of
this object during transfers.

### std::move concept
We usually when we use the assignment operator `=`, we ended up with creating a
new copy for our object. Lets start from our previous example and build on top
of it. Assume we have a `StringK` and `EntityK` classes this time which is same
as:

```cpp

+-------------------------------------------------------------+
|                     STRING CLASS                            |
+-------------------------------------------------------------+
|class StringG {                                              |
|  public:                                                    |
|      // Default constructor                                 |                                                          +--------------------------------------+
|      StringG() = default;                                   |                                                          |             ENTITY CLASS             |
|      // Constructor with initialization                     |                                                          +--------------------------------------+
|      /*The object gets created first time*/                 |                                                          |  class EntityG {                     |
|      StringG(const char* string) {                          |                                                          |  public:                             |
|          printf("Object is Created!\n");                    |                                                          |      EntityG(const StringG& name)    |
|          m_Size = strlen(string);                           |                                                          |          : m_Name{name} {}           |
|          m_Data = new char[m_Size + 1];                     |                                                          |                                      |
|          memcpy(m_Data, string, m_Size + 1);                |                                                          |      EntityG(StringG&& name)         |
|      }                                                      |                                                          |          : m_Name{(StringG&&)name} {}|
|                                                             |                                                          |      void Print() { m_Name.Print(); }|
|      /* copy constructor - lvalue-reference*/               |                                                          |                                      |
|      StringG(const StringG& other) {                        |                                                          |                                      |
|          printf("Object is Copied!\n");                     |                                                          |  private:                            |
|          m_Size = other.m_Size;                             |                                                          |      StringG m_Name;                 |
|          m_Data = new char[m_Size + 1];                     |                                                          |  };                                  |
|          memcpy(m_Data, other.m_Data, m_Size + 1);          |                      + ===========================       +--------------------------------------+
|      }                                                      |                      |
|                                                             |                      |
|      // move constructor - rvalue-reference                 |                      |
|      StringG(StringG&& other) noexcept {                    |                      v                        +--------------------------------------------+
|          printf("Object is Moved!\n");                     +|               ===================>            |               MAIN FUNCTION                |
|          m_Size = other.m_Size;                             |                                               +--------------------------------------------+
|          m_Data = other.m_Data;                             |                                               | int main(int argc, char* argv[]) {         |
|          other.m_Size = 0;                                  |                                               |         EntityG e = EntityG("GAME ENGINE");|
|          other.m_Data = nullptr;                            |                                               |         StringG string = "Hello";
|                                                             |                                               |         StringG dest = string;       <--------- Here you trigger the copy assignment operator
|                                                             |                                               |
|      }                                                      |                                               +--------------------------------------------+
|                                                             |
|      ~StringG() {                                           |
|          printf("Destroying object with size %u\n", m_Size);|
|          delete[] m_Data;                                   |
|      }                                                      |
|      void Print() {                                         |
|          for (uint32_t i = 0; i < m_Size; i++) {            |
|              printf("%c", m_Data[i]);                       |
|              if (m_Data[i] == '\0') {                       |
|                  LOG(INFO) << RED << "WOW, set i<=m_Size to |see this message" << RESET;
|              }                                              |
|          }                                                  |
|          printf("\n");                                      |
|      }                                                      |
|                                                             |
|  private:                                                   |
|      char* m_Data;                                          |
|      uint32_t m_Size;                                       |
|  };                                                         |
+-------------------------------------------------------------+
```
- std::move() is a utiltiy function provided by the standard C++ library to move the resources of an object to another object.
  - Its an template function that can work with any data type

```cpp


 +--------------------------------------------+
 |              MAIN FUNCTION                 |
 +--------------------------------------------+
 | int main(int argc, char* argv[]) {         |
 |         EntityG e = EntityG("GAME ENGINE");|
 |         StringG string = "Hello";          |
 |         StringG dest = string;             |    <--- If we want to move the object string to dest we can use.
 |         StringG dest  = (StringG&&)string; |    <--- here we use casting, but this is not prefered compared to std::move().       ----------------+
 |         StringG dest = std::move(string);  |    <--- Here, we use the std::move() instead and its much nicer and easily to be understood.         |
 |                                            |                                                                                                      |
 +--------------------------------------------+       NOTE: The assignment operator is doing a implicit conversion and                <--------------+
                                                            call into this specific string constructor, meaning it wil turn
                                                           +-----------------------------------+             +-----------------------------------+
                                                           | StringG dest = (StringG&&)string; |   ------>   | StringG dest((StringG&&)string);  |
                                                           +-----------------------------------+             +-----------------------------------+
```

### Move assignement operator

Let's explore how we can address this in modern C++. I have added a move
assignment operator (`=`) which differs from the copy assignment operator (=).
- This move assignment operator will be triggered every time we use `std::move()` or use an `rvalue-reference`, such as `T&&`.
- The structure of this assignment operator (which can be considered just a method) consists of the following:
  - We are here stealing the data from the assigned object to the assignee, meaning that we have to handle both objects.
  - We first check if our assigned object is not of the same type as our class-object (not an object created from the same class).
  - Then we handle the original object (see the digram below)


```cpp
                           Move Assignment Operator
+----------------------------+         =          +-----------------------------+
|     Destination Object     |         =          |        Source Object        |
+----------------------------+                    +-----------------------------+
     T destination_object              =               T source_object


T& operator=(T&& other) noexcept {
    std::cout << "Move Assignment operator is called." << std::endl;

    if (this != &other) { // Check for self-assignment
        // Release the existing resources of the destination object
        delete[] m_Data;

        // Transfer the ownership of resources from the source object (other)
        m_Size = other.m_Size; // Copy the size from source to destination
        m_Data = other.m_Data; // Transfer the data pointer from source to destination

        // Leave the source object in a valid but empty state
        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    return *this; // Return a reference to the current object
}

```

- Lets see how we can adjust our class based on the information above.

```cpp
+---------------------------------------------------------------------------------------------------+                                                                +-------------------------------------------------------------------------+
|                                      STRING CLASS                                                 |                                                                |                        MAIN FUNCTION                                    |
+---------------------------------------------------------------------------------------------------+                                                                +-------------------------------------------------------------------------+
|       namespace MoveAssignemntConcept {                                                           |                                                                |                                                                         |
|                                                                                                   |                                                                |  int main(int argc , char* argv[]){                                     |
|       class String {                                                                              |                                                                |      // Example -1-                                                     |
|       public:                                                                                     |                                                                |      MoveAssignemntConcept::String string = "Hello";                    |
|           String() noexcept = default;                                                            |                                                                |      MoveAssignemntConcept::String destx = std::move(string);           |
|           String(const char* string)                                                              |                                                                |      string = std::move(destx);                                         |
|               : m_Data(new char[strlen(string) + 1]),                                             |                                                                |      // Example -2-                                                     |
|                 m_Size(strlen(string) + 1) {                                                      |                                                                |      MoveAssignemntConcept::String apple = "Apple";                     |
|               std::memcpy(m_Data, string, m_Size + 1);                                            |                                                                |      MoveAssignemntConcept::String dest;                                |
|           }                                                                                       |                                                                |                                                                         |
|           String(const String& other) {                                                           |                 We are calling the                             |      std::cout << "Apple: ";                                            |
|               m_Size = other.m_Size;                                                              |         =====================================>                 |      apple.Print();                                                     |
|               m_Data = new char[m_Size];                                                          |                move assign operator                            |      std::cout << "Dest: ";                                             |
|               std::memcpy(m_Data, other.m_Data, m_Size);                                          |                                                                |      dest.Print();                                                      |
|           }                                                                                       |                                                                |                                                                         |
|           String(String&& other) noexcept {                                                       |                                                                |      dest = std::move(apple);  // we are calling the move equal operator|
|               m_Size = other.m_Size;                                                              |                                                                |                                                                         |
|               m_Data = other.m_Data;                                                              |                                                                |      std::cout << "Apple: ";                                            |
|               other.m_Size = 0;                                                                   |                                                                |      apple.Print();                                                     |
|               other.m_Data = nullptr;                                                             |                                                                |      std::cout << "Dest: ";                                             |
|           }                                                                                       |                                                                |      dest.Print();                                                      |
|           String& operator=(String&& other) noexcept {                                            |                                                                |                                                                         |
|               std::cout << "Move Assignment operator is called " << std::endl;                    |                                                                |      return 0;                                                          |
|               if (this != &other) { /* Here we ensure that we are not copy to same object */      |                                                                |  }                                                                      |
|                                     /* This is the most important point,                          |                                                                +-------------------------------------------------------------------------+
|                                        to ensure our current object is empty                      |                                                                                                        |
|                                      */                                                           |                                                                 +--------------------------------------+
|                   delete[] m_Data;                                                                |                                                                 |
|                                                                                                   |                                                                 |
|                   m_Size = other.m_Size;                                                          |                                                                 V
|                   m_Data = other.m_Data;                                                          |                                                +-----------------------------------+
|                                                                                                   |                                                |             RESULTS               |
|                   other.m_Size = 0;                                                               |                                                +-----------------------------------+
|                   other.m_Data = nullptr;                                                         |                                                | Move Assignment operator is called|
|               }                                                                                   |                                                | Apple: Apple                      |
|               return *this;                                                                       |                                                | Dest:                             |
|           }                                                                                       |                                                | Move Assignment operator is called|
|                                                                                                   |                                                | Apple:                            |
|           ~String() { delete[] m_Data; }                                                          |                                                | Dest: Apple                       |
|           void Print() {                                                                          |                                                +-----------------------------------+
|               for (size_t i = 0; i < m_Size; i++) {                                               |
|                   std::cout << m_Data[i];                                                         |
|               }                                                                                   |
|               std::cout << std::endl;                                                             |
|           }                                                                                       |
|                                                                                                   |
|       private:                                                                                    |
|           char* m_Data = nullptr;                                                                 |
|           uint32_t m_Size = 0;                                                                    |
|       };                                                                                          |
+---------------------------------------------------------------------------------------------------+
```

## More Details - Depth

Understanding `std::move` and the Move Assignment Operator in C++ requires a
clear grasp of C++'s approach to resource management, particularly in the
context of object copying and moving. Here's an in-depth look at these concepts:

### 1. `std::move`:

- **Explanation**: `std::move` is a standard library function that allows
  developers to request the conversion of an object to an r-value reference.
  This operation signals that it's safe for the compiler to transfer resources
  from the source object to another, rather than copying. It's crucial to
  understand that `std::move` doesn't actually move anything by itself; it
  merely casts its argument to an r-value reference, enabling move semantics.

- **Example**:

  ```cpp
  #include <utility> // for std::move
  #include <vector>

  int main() {
      std::vector<int> vec1 = {1, 2, 3};
      std::vector<int> vec2 = std::move(vec1); // vec1 is "moved" to vec2
      // After the move, vec1 is in a valid but unspecified state
  }
  ```

### 2. Move Assignment Operator:

- **Explanation**: The move assignment operator is used to transfer the
  resources of one object to another, avoiding unnecessary copying. This
  operator is automatically defined for most classes, but for classes managing
  resources (like dynamic memory), defining a custom move assignment operator
  can optimize performance by transferring ownership of resources.

- **Example**:

  ```cpp
  class Resource {
  public:
      Resource& operator=(Resource&& other) noexcept {
          if (this != &other) { // Prevent self-assignment
              delete[] data; // Free existing resource
              data = other.data; // Transfer resource ownership
              other.data = nullptr; // Leave moved-from object in a safe state
          }
          return *this;
      }

  private:
      int* data;
  };
  ```

### Scenarios That Trigger the Move Assignment Operator:

- Assigning a temporary object to an existing object.
- Using `std::move` on an object when assigning it to another object.
- Returning a local object by value from a function, under certain compiler
  optimizations.

### Common Practices, Pitfalls, and Notes:

- **Use `std::move` cautiously**: While `std::move` can optimize resource usage,
  it leaves the moved-from object in an unspecified state. Ensure the moved-from
  object is not used in a way that assumes it still owns the resources.

- **Check for self-assignment in custom move assignment**: When implementing a
  custom move assignment operator, guard against self-assignment to avoid
  resource leaks or other unintended behaviors.

- **Noexcept specifier**: It's good practice to declare move constructors and
  move assignment operators as `noexcept`. This improves performance in certain
  contexts, like when objects are stored in containers that may reallocate
  memory, such as `std::vector`.

- **Resource ownership transfer**: Understand that the move semantics is
  essentially about transferring ownership of resources. Ensure that only one
  object owns a resource at any given time to avoid double-free errors or memory
  leaks.

- **Automatic generation of move operations**: The compiler can automatically
  generate move constructors and move assignment operators for classes that do
  not define move operations, copy operations, or a destructor. However, for
  classes managing resources manually, it's often necessary to define these
  operations explicitly to ensure proper resource management.

By leveraging `std::move` and properly implementing the move assignment
operator, you can significantly optimize resource management in your C++
applications, making them more efficient and performant.
