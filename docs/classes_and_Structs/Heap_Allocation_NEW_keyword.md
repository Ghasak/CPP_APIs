# Heap Allocation New Keyword

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Heap Allocation New Keyword](#heap-allocation-new-keyword)
    - [1. My Understanding](#1-my-understanding)
    - [2. Creating an object in C++](#2-creating-an-object-in-c)
        - [2.1 Stack Allocation](#21-stack-allocation)
        - [2.2. Heap Allocation](#22-heap-allocation)
        - [2.3. Why We Need Each Allocation](#23-why-we-need-each-allocation)
        - [2.4.Best Common Code Practices](#24best-common-code-practices)
        - [2.5. Things to Be Considered](#25-things-to-be-considered)
        - [2.6. Comparison Stack vs Heap](#26-comparison-stack-vs-heap)
    - [3. New keyword](#3-new-keyword)
        - [3.1. Entity of a heap array](#31-entity-of-a-heap-array)
        - [3.2. Accessing the elements of entity](#32-accessing-the-elements-of-entity)
            - [3.2.1. Using Array Indexing](#321-using-array-indexing)
            - [3.2.2. Using Pointer Arithmetic](#322-using-pointer-arithmetic)
            - [3.2.3. Using Dereference with Pointer Arithmetic](#323-using-dereference-with-pointer-arithmetic)
            - [3.3.4. Access only first element](#334-access-only-first-element)
                - [3.3.4.1. Using Array Indexing](#3341-using-array-indexing)
                - [3.3.4.2. Using Pointer Arithmetic with Arrow Operator](#3342-using-pointer-arithmetic-with-arrow-operator)
                - [3.3.4.3. Using Dereference with Pointer Arithmetic and Dot Operator](#3343-using-dereference-with-pointer-arithmetic-and-dot-operator)
            - [3.2.4. Summary](#324-summary)

<!-- markdown-toc end -->

## 1. My Understanding

Creating `stack` object is the fastest way and the most managed way in C++, but
why we need then the `heap` allocation:

- To extend the lifetime of an object beyond its point of creation.

- To create a larger-sized object with significant memory allocation, as the
  stack is limited in size, typically not exceeding a few megabytes per system
  (this can vary based on the platform and compiler), as your program may crash
  due to overflow if you use very large objects with excessive amounts of data.

- In Java, all classes reside on the heap and everything is allocated there. This
  differs from the concept of struct in Java, as it behaves differently compared
  to C++. In contrast, both Java and C# allocate everything on the heap similarly.
  However, C# introduces a construct called struct, which is a value-based type
  that is stack-allocated, even when using the new keyword.

- Everyone comes form a memory managed languages like `Java` or`C#` , they
  assume we should use `new` everywhere, But, you shouldn't for two reasons:
  1. Performance, as allocating on heap takes longer.
  2. When you allocate on heap, you have manually to free the memory you allocated.

```cpp

+----------------------------+                                +-----------------------------+
|          Entity Class      |                                |       Main function         |
+----------------------------+                                +-----------------------------+
                                                              | int main(int argc, char* argv[]){
class Entity{                                                 |     // Creating an object on stack
    private:                                                  |     // calling the default constructor
        std::string m_Name;                                   |     Entity entity;
    public:                                                   |     // Accessing the method
        // Default Constructor                                |     // of the stack object
        Entity(): m_Name{"Name"} {}                           |     entity.GetName();
        // Consturctor with parameters                        |
        Entity(const std::string& name)                       |     // Creating an object on heap
            : m_Name{name} {                                  | }
              // code goes here                               +-----------------------------+
        }
        // Getter function
        const std::string& GetName() const {
            return m_Name;
        }
};

//---------------------------------------------------------------------------------------------------------------------------------//
                                                              +-----------------------------+
                                                              |       Stack allocation      |
                                                              +-----------------------------+

        [first reason]                                                                                  [first reason - continue]
[object lives byond its own scope] Here we need heap                                            [object lives byond its own scope] Here we need heap
+--------------------------------+                                                              +--------------------------------+
|       Main function            |                                                              |       Main function            |
+--------------------------------+                                                              +--------------------------------+
|  void Function(){                                                                             |
|      Creating an object on stack                                                              |  int main(int argc, char* argv[]){
|      Entity entity = Entity("Name"); <--- this entity object is                               |           Entity* e;                                 <- create a pointer of a type Entity (refer to a stack object)
|                                           cleared once exiting the                            |           {                                          <--------+
|                                           fucntion scope                                      |                Entity entity = Entity("SomeName");            |
|  }                                                                                            |                e = &entity;                                   | <-- Assign it to the memory addres of our stack object
|                                                                             |---->            |                std::cout                                      | Inner-scope
|  int main(int argc, char* argv[]){                                                            |                    << entity.GetName()                        |
|      Function();                 <-- When we call Function()                                  |                    << std::endl;                              |
|      std::cout                       It will create a stack of                                |           }                                          <--------+  <---o Once you reac here this entity is gone,
|          << entity.GetName()         all members of it and it will                            |                                                                        the pointer will be dangled. We reached
|          << std::endl;               be cleared of memeory once it exit                       |  }                                                                     to the end of this stack-frame and it is
|      //                                                                                       |                                                                        the end of the object life `entity`.
|  }                                                                                            |                                                                        While the pointer still
+--------------------------------+                                                              |                                                                        refer to it.
                                                                                                |
                                                                                                |
                                                                                                +--------------------------------+


//---------------------------------------------------------------------------------------------------------------------------------//
                                                              +-----------------------------+
                                                              |       Heap allocation       |
                                                              +-----------------------------+
                                                                         [freeing memory]
+----------------------------+                                    +----------------------------+
|        Main function       |                                    |        Main function       |
+----------------------------+                                    +----------------------------+
                                                                  |
int main(int argc, char* argv[]){                                 | int main(int argc, char* argv[]){
    // Using defult constructor                                   |    Entity* e; // pointer to our class-object
    Entity* entity = new Entity();                                |    {                                                                                  <-----+
    // Using constructor with param                               |        // Create an object on heap means create a pointer refer                             |
    Entity* entity = new Entity("allocat on heap");               |        // to the data on heap and the pointer (entity) is just                              |
    return 0;                                                     |        // an integer to store the address which will be stored on stack usually             |
}                                                                 |        Entity* entity = new Entity("allocated on heap");                                    |
                                                                  |        e = entity; // entity is a pointer                                                   |
                                                                  |         std::cout << entity->GetName() << std::endl;                                        |  [entity is an integer got freed automatically once it exists the inner-scopee]
                                                                  |    }                                                                                  <-----+ Once we reach here, the pointer `entity` will be gone
                                                                  |                                                                                               but, we assigned it to another pointer which lives longer
                                                                  |                                                                                               (e) and it live to the end of the scope that it is being created (end of the main).
                                                                  |     std::cout << e->GetName() << std::endl;                                                   Accessing the object is still presver through the (e) pointer
                                                                  |     delete e;
                                                                  |    return 0;
                                                                  |    }


+----------------------------+                                                                                                     +----------------------------+
|        Main function       |                                                                                                     |        Main function       |
+----------------------------+                                                                                                     +----------------------------+
                                                                                                                                   |
int main(int argc , char* argv[]){                                                                                                 | int main(int argc , char* argv[]){
    Entity* e;                                                                                                                     |
                                                                                                                                   |     {
    {                                                                                                                              |         Entity* entity = new Entity("allocated on heap");
        Entity* entity = new Entity("allocated on heap");                                                                          |     }
        std::cout << entity->GetName() << std::endl;  // Here we accessed the data refered to by the pointer                       |     std::cout << entity->GetName() << std::end; // You cannot access the object throught the pointer
        delete entity // is ok to delete the entity here as we dont want to access the data anymore                                |     delete entity // You cannot delete the data as the pointer is no longer existed out of the inner-scope
    }                                                                                                                              | }
}                                                                                                                                                          +
                                                                                                                                                           |
                                                                                                                                                           |
                                                                                                                                                           |
                                                                                                                                                   +------ +
                                                                                                                                                   |
                                                                                                                                                   |
                                                                                                                                                   V
                                                                                                                            [xxx WRONG COMMON MISTAKE xx]
                                                                                                                            The data is still in memeory
                                                                                                                                (memory leaked)
                                                                                                                            but you cannot free it as no
                                                                                                                            pointer refer to it anymore
                                                                                                                            the pointer is dead as its just
                                                                                                                            an integer freed automatically
                                                                                                                            once it existed the inner-scope

```

## 2. Creating an object in C++

Creating objects in C++ can be done on either the stack or the heap, each having
its own use cases and implications for memory management, performance, and
lifecycle management. Here's a detailed explanation for both, including syntax,
access methods, best practices, and considerations.

### 2.1 Stack Allocation

Objects created on the stack are allocated within the function call stack. They
have automatic storage duration, meaning they are automatically created when the
enclosing block or function is entered and destroyed when it is exited. This
makes stack allocation very fast but limited by the stack size, which is smaller
compared to heap size.

**Syntax:**

```cpp
Type variableName;
Type variableName(arguments); // If the constructor requires arguments
```

**Example:**

```cpp
class MyClass {
public:
    MyClass() {}
    void myMethod() { /* ... */ }
};

void myFunction() {
    MyClass myObject; // Object created on the stack
    myObject.myMethod(); // Accessing method
}
```

**Pointer to Stack Object:**

```cpp
MyClass *myObjectPtr = &myObject;
myObjectPtr->myMethod(); // Accessing method using pointer (arrow syntax)
(*myObjectPtr).myMethod(); // Accessing method using pointer (dereference syntax)
```

### 2.2. Heap Allocation

Objects created on the heap are allocated at runtime and require manual
management. They have dynamic storage duration, which means they remain
allocated until explicitly deallocated. Heap allocation is more flexible and
allows for the allocation of large amounts of memory, but it is slower than
stack allocation and requires explicit deallocation to avoid memory leaks.

**Syntax:**

```cpp
Type* variableName = new Type;
Type* variableName = new Type(arguments); // If the constructor requires arguments
```

**Example:**

```cpp
class MyClass {
public:
    MyClass(int value) {}
    void myMethod() { /* ... */ }
};

void myFunction() {
    MyClass *myObject = new MyClass(5); // Object created on the heap
    myObject->myMethod(); // Accessing method
    delete myObject; // Important: deallocating heap memory
}
```

**Accessing Member and Method:**

For objects on the heap, you typically use the arrow operator (`->`) to access
members and methods. If you have a pointer to an object, you can also
dereference the pointer and use the dot operator.

```cpp
myObject->myMethod(); // Arrow syntax for pointers
(*myObject).myMethod(); // Dereference pointer and use dot syntax
```

### 2.3. Why We Need Each Allocation

- **Stack Allocation**: Fast and automatically managed. Ideal for small objects
  or variables whose lifetime is tied to the scope they are declared in.

- **Heap Allocation**: Offers flexibility for allocating large objects or for
  objects whose lifetime needs to extend beyond the scope in which they are
  created. Requires manual management.

### 2.4.Best Common Code Practices

- Prefer stack allocation when possible for simplicity and performance.
- Use heap allocation for large objects or when the object's lifetime must
  extend beyond its scope.
- Always ensure every `new` is matched with a `delete` to avoid memory leaks.
- Consider using smart pointers (`std::unique_ptr`, `std::shared_ptr`) to manage
  heap-allocated objects more safely and easily.

### 2.5. Things to Be Considered

- **Stack Allocation**:

  - Limited by stack size.
  - Automatic lifetime management can lead to objects being destroyed too early
    if not properly considered.

- **Heap Allocation**:

  - Potential for memory leaks.
  - Overhead of dynamic memory allocation (performance cost).
  - Manual management of object lifetime.

Using pointers and smart pointers wisely, understanding the lifetime of objects,
and managing resources correctly are crucial aspects of effective C++
programming.

### 2.6. Comparison Stack vs Heap

Here's a table summarizing the key differences between stack and heap
allocations in C++:

| Feature             | Stack                           | Heap                                                          |
| ------------------- | ------------------------------- | ------------------------------------------------------------- |
| Allocation Timing   | At compile time                 | At runtime                                                    |
| Memory Management   | Automatic                       | Manual                                                        |
| Lifetime            | Limited to scope                | Controlled by the programmer                                  |
| Size Limitation     | Limited (depends on the system) | Larger, limited by system's available memory                  |
| Speed               | Fast                            | Slower than stack                                             |
| Allocation Method   | Direct declaration              | Use of `new` operator                                         |
| Deallocation Method | Automatic when scope ends       | Must explicitly use `delete`                                  |
| Access Methods      | Direct or by reference          | Through pointers (`->` or dereferencing)                      |
| Use Case            | For small or temporary objects  | For large objects or those needing scope-independent lifetime |
| Management Overhead | Minimal                         | Requires careful management to avoid leaks                    |
| Example Declaration | `Type obj;`                     | `Type* obj = new Type;`                                       |
| Example Access      | `obj.method();`                 | `obj->method();` or `(*obj).method();`                        |
| Cleanup             | Not required by the programmer  | Programmer must use `delete`                                  |
| Suitability         | Simple and short-lived objects  | Complex, long-lived, or large objects                         |

This table highlights the fundamental differences in how memory is allocated,
managed, and accessed between stack and heap in C++. It's important for C++
developers to understand these differences to make informed decisions about
memory management and object lifecycle in their applications.

## 3. New keyword

You can allocate on heap any type of data whether it is a primitive or a complex
data (e.g., std::string, std::vector, list ..etc.).

```cpp
+-----------------------------+
|        Main - Function      |
+-----------------------------+

int a = 2;      // on stack
int* b = int(2) // on heap;
int* c = new int[50]; // 200 bytes of data alloacted (50 x 4-bytes)
Entity* e = new Entity();
Entity* e = new Entity[50]; // Here you allocate of 50 - entity objects on heap

+----------------------------+
| Entity* e = new Entity[50];|
+----------------------------+
```

### 3.1. Entity of a heap array

Let's take the last example, what dose it means?

```cpp
          +----------------------------+
          | Entity* e = new Entity[50];|
          +----------------------------+
```

- The statement `Entity* e = new Entity[50];` in C++ creates an array of 50
  `Entity` objects on the heap. This uses dynamic memory allocation to reserve
  space for 50 instances of `Entity`. Each object in this array is initialized
  using the default constructor `Entity()`, which sets `m_Name` to `"Name"` for
  each instance.

- Here's a breakdown of what happens:

  - **Dynamic Allocation**: The `new` operator is used for dynamic memory
    allocation, which allocates memory at runtime on the heap. This is necessary
    when the size of the array or the lifetime of the objects needs to extend
    beyond the scope in which they are created.

  - **Array of Objects**: The `[50]` specifies that you're creating an array
    with 50 elements, where each element is an object of type `Entity`.

  - **Default Constructor**: Since no specific constructor parameters are passed
    during this array creation, the default constructor `Entity()` is called for
    each of the 50 `Entity` objects, initializing `m_Name` to `"Name"`.

  - **Pointer to First Element**: The variable `e` is a pointer to `Entity` that
    holds the address of the first object in the array. You can access the
    individual objects using array indexing (e.g., `e[0]`, `e[1]`, ...,
    `e[49]`).

  - **Memory Management**: It's important to remember that memory allocated with
    `new[]` must be released using `delete[]` to avoid memory leaks. So, you
    would need to call `delete[] e;` when the array is no longer needed.

This approach is useful when you need multiple instances of an object and their
lifetime should extend beyond the current scope, or when the number of instances
is determined at runtime. However, managing dynamic memory manually like this is
error-prone, so modern C++ code often uses smart pointers (e.g.,
`std::unique_ptr<Entity[]>`) or containers from the Standard Template Library
(e.g., `std::vector<Entity>`) to handle memory more safely and conveniently.

### 3.2. Accessing the elements of entity

To access the elements of each `Entity` member in the array create with `Entiy*
e = new Entity[50];` you can use pointer `e` in several ways. Here are the
possible syntaxes to access the `GetName` method of each `Entity` object in the
array:

#### 3.2.1. Using Array Indexing

Array indexing is the most straightforward method to access elements in an
array. You can use the index operator `[]` with the pointer `e` to access each
`Entity` object, and then call the member functions or access member variables
(if public) directly.

**Syntax:**

```cpp
e[index].memberFunction();
```

**Example Accessing `GetName` Method:**

```cpp
for(int i = 0; i < 50; ++i) {
    std::string name = e[i].GetName();
    // Use name as needed
}
```

#### 3.2.2. Using Pointer Arithmetic

Pointer arithmetic allows you to navigate through arrays by incrementing the
pointer itself. The expression `*(e + i)` gives you the object at index `i` in
the array, which you can use to access members.

**Syntax:**

```cpp
(e + index)->memberFunction();
```

**Example Accessing `GetName` Method:**

```cpp
for(int i = 0; i < 50; ++i) {
    std::string name = (e + i)->GetName();
    // Use name as needed
}
```

#### 3.2.3. Using Dereference with Pointer Arithmetic

This method involves dereferencing the pointer to an object obtained through
pointer arithmetic and then using the dot operator to access members.

**Syntax:**

```cpp
(*(e + index)).memberFunction();
```

**Example Accessing `GetName` Method:**

```cpp
for(int i = 0; i < 50; ++i) {
    std::string name = (*(e + i)).GetName();
    // Use name as needed
}
```

#### 3.3.4. Access only first element

To access only the first element of the array pointed to by `e`, you can use any
of the methods described earlier but simplified for the first element (index 0).
Here's how you can do it:

##### 3.3.4.1. Using Array Indexing

For the first element, the index is `0`.

**Syntax:**

```cpp
e[0].GetName();
```

**Example:**

```cpp
std::string firstName = e[0].GetName();
```

##### 3.3.4.2. Using Pointer Arithmetic with Arrow Operator

For the first element, you don't need to add anything to the pointer, as it
already points to the first element.

**Syntax:**

```cpp
e->GetName();
```

**Example:**

```cpp
std::string firstName = e->GetName();
```

##### 3.3.4.3. Using Dereference with Pointer Arithmetic and Dot Operator

Similarly, dereferencing `e` directly gives you the first element.

**Syntax:**

```cpp
(*e).GetName();
```

**Example:**

```cpp
std::string firstName = (*e).GetName();
```

Each of these methods will give you access to the `GetName` method of the first
`Entity` object in the array. Whether you use array indexing, the arrow
operator, or dereferencing with the dot operator, you can easily access the name
of the first entity.

#### 3.2.4. Summary

- **Array Indexing (`e[index].GetName()`)**: Most straightforward, similar to
  accessing array elements.

- **Pointer Arithmetic with Arrow Operator (`(e + index)->GetName()`)**: Useful
  for iterating through an array with pointers.

- **Dereference with Dot Operator (`(*(e + index)).GetName()`)**: Another way to
  access elements, combines dereferencing with the familiar dot operator.

Each of these methods allows you to access the `GetName` method of each `Entity`
object in the array. Remember, accessing member variables directly would only be
possible if they are public; in the given `Entity` class, `m_Name` is private,
so you must use the public `GetName` method to access the name of each entity.
