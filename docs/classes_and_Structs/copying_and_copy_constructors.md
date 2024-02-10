# Copying and Copy-Constructors in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Copying and Copy-Constructors in C++](#copying-and-copy-constructors-in-c)
    - [Intro - Copying & Copy Constructor](#intro---copying--copy-constructor)
    - [My Understanding](#my-understanding)
        - [Assign operator with copying](#assign-operator-with-copying)
        - [Demo - Creating a string class to demonstrate the copying](#demo---creating-a-string-class-to-demonstrate-the-copying)
    - [References](#references)
    - [More Insight on Copying & Copy-Constructor](#more-insight-on-copying--copy-constructor)
        - [What is Copying?](#what-is-copying)
        - [How is it Used?](#how-is-it-used)
        - [Things to Consider When Copying](#things-to-consider-when-copying)
        - [Examples](#examples)
    - [Basics string class from Scratch - Similar to std::string](#basics-string-class-from-scratch---similar-to-stdstring)

<!-- markdown-toc end -->

## Intro - Copying & Copy Constructor

Copying refers to us copying data copying memory when we literally want to copy
one object or primitive or just a piece of data from kind of one place into
another

- We literally have two copies of it a lot of the time we want to
  copy objects that we can modify them in certain ways but if if we can avoid
  copying if we can avoid unnecessary copying.

- because we just want to read the
  value or we want to actually modify an existing object we absolutely want to do
  that because copying takes time.

- Copying can be both a really useful thing
  that we actually need to make our program work the way that we wanted to but on
  the flip side unnecessary copying is bad and we want to avoid that as much as
  possible because it wastes performance.

- So understanding how copying actually
  works in C++ and how to get it to work and also how to avoid getting it to work
  or avoid copying when you don't want to copy is very important to understanding
  the language and being able to write C++ code efficiently and correctly.

- Demonstrate this in an effective way I'm actually going to write a full on
  example window write a class it's gonna be a string class and we're gonna talk
  about how copying affects that and what we can do to to both remove copying when
  we don't want copying but also even you know add copying so that we can copy
  correctly so first of all let's jump Copying

## My Understanding

```cpp

 struct Vector2{
     float x, y;
 }

 +-------------------------------+
 |         main function         |
 +-------------------------------+
   int main(int argc , char* argv[]){
           int a = 2;                             <--  Let's declare a
                                                       variable a primitive type like a
           int b = a;                             <--  then I declare another primitive type
                                                        called B and I assign it to a and what
                                                        I'm actually doing is I'm creating a
                                                        copy of it so a and B are two separate
                                                        variables ( which have different memory addresses)

          // Alloacted on stack
          // Similarly the copying is happening here as well
          Vector2 v1(10,20);
          Vector2 v2 = v1;

           std::cin::get();
   }

```

- How about copying a vector allocated on heap?

```cpp

 struct Vector2{
     float x, y;
 }


 +-------------------------------+
 |         main function         |
 +-------------------------------+
   int main(int argc , char* argv[]){

          // Similarly the copying is happening here as well
          Vector2 v1 = new Vector2(10,20);
          Vector2 v2 = v1; // Here we copy the pointer not the ojbect of v1 itself.

           std::cin::get();
    }
```

### Assign operator with copying

1. You almost always copy an object when you are using the `assign operator`
   `=`. But with two exceptions:

- When you copy a pointer, you are copying it not the object which it refers to
  (see the example above).

- When you are using `references`, you are not doing a copying

```cpp
int a = 10;
int& ref_a = a;     <-- Here you are now copying rather than create a reference.
```

### Demo - Creating a string class to demonstrate the copying

We will create a `string` class similar to the one in C++ but only to understand
the concept behind the language. We won't worry about optimizing this class with
other tools and features offered by C++, such as std::vector or smart pointers.
Instead, we will concentrate on the idea of copying and copy constructors.

1. [Shallow copy] Default Copy Constructor in C++ In `C++` a default copy
   constructor will be provided to any class you create (even if you don't
   include it), which is just a copy of your `class-attributes`.

   - What we did here is we copied the string and when we copy the string what
     C++ does for us automatically is it just takes whatever members there are
     here which is basically what what this class is made up it's made but it's
     made up of a child pointer and an on side end and it takes those values and
     it copies them into a new memory address which contains this string the
     second string of ours now here's the problem what we have now in memory is
     two strings and since they did it did a direct copy something called a
     shallow copy what it did is it copied this pointer so we have two strings in
     memory which of course have the exact same child pointer value in other words
     the memory address the memory address of this buffer is the same for both of
     these strings.

```cpp


+-------------------------------------------+
|              Class String                 |
+-------------------------------------------+
| #include <iostream>                       |
| #include <string>                         |
|                                           |
| class String{                             |--------------------------------------> Automatically a hidden copy-constructor is created
|     private:                              |                                        (will be called when you use for example =)                  like:   String(const String& string):m_Buffer(string.m_Buffer), m_Size{m_Size}{}
|         char* m_Buffer;                   |
|         unsigned int m_Size;              |
|     public:                               |
|         String(const char* string){       |    <-- Our constructor accepting a char pointer string
|            m_Size = strlen(string);       |    <-- We use the method strlen to measure the size we want to allocate
|            m_Buffer = new[m_size+1];      |    <-- Allocating a CStyle Array with null-termination character (\0)
|            memcpy(m_Buffer, string, m_size);   <-- Each character is 1-byte in memory.
|         }                                 |
|         ~String(){                        |    <-- Destrctur to delete the object
|            delete[] m_Buffer;             |    <-- once it goes out of scope m_Buffer pointer is deleted.
|         }                                 |
          friend std::ostream& operator<<(std::ostream& stream, const String& string);
| }                                         |
+-------------------------------------------+

// Operator for output the object
std::ostream& operator<<(std::ostream& stream, const String& string){
    stream << string.m_Buffer;
    return stream;
}


+------------------------------------------+
|            Main function                 |        <----- This program will crash, why?
+------------------------------------------+               because we have a shallow copy, as we
| int main(int argc, char* argv[]){        |               just copied the `m_Buffer` and `m_Size` from str1 to str2
|                                          |               When we reach to end of the scope, the destructor will be called twich but for same object
|                                          |               (which at first wil be deleted), then we delete it again cause the prgram to undefined-behaviour, also known as `double deletion`.
|         String str1 = "My First String"; |        <--  this is our first string
|         String str2 = str1;              |        <-- Based on the class definition above,
|                                          |            here a default copy-constructor will be called,
|         std::cout.get();                 |            which is just copying the `m_Buffer` and `m_Size` from the object we passed
|         return 0;                        |
| }                                        |
+------------------------------------------+


```

- You can see this block of code crashes by tracking using a debugger or simply,
  add the indexing operator to your class to see that both `str1` and `str2` and
  both pointers refer to same object (char\* string) by doing the following.

- In another word, and we get the crash because when we come over here to the
  end of this scope and both of these strings get destroyed the destructor gets
  called and we end up deleting this buffer twice

- so we're trying to free the same block of memory twice that's why we get a
  crash because the memory has already been freed it's not ours we can't free it
  again

```cpp

char& operator[](unsigned int index){
    return m_Buffer[index];
}

// at main

String str1 = "My First String";
String str2 = str1;
str2[0] = 'K';    // out put will be for both str1 and str2 the modifiction,
                 //  which means both str1 and str2 two pointers refer to same block of memory.
```

2. [Deep copy] We will solve the problem by using a `copy-constructor` which we
   are here will copy the `m_Buffer` by allocating a new memory to the new
   string which is being copied.

   - Actually need to do is allocate a new char array to store the copied string
     right because what we're doing now is we're copying the the pointer and what
     we have is two string objects pointing to the exact same buffer of memory
     which means that when,

   - we either try and change one of them it changes both of
     them because they're pointing to the same block of memory or when we delete
     one of them it's gonna delete both of them because well they're pointing to
     the same block of memory we want to actually copy that block of memory.

   - we want the second string to have its own pointer to have its own unique
     block of memory that's pointing to so that when we either modify or delete
     the second string it doesn't touch the first string and vice versa and the
     way that we can do that is by performing something called a deep copy.

   - meaning we're actually copying the entire object not just the kind of
     shallow like features that we see on the very top such as what actually makes
     up the object because if you look at the object in memory it's a pointer and
     an int that's all it is but a shallow copy is not gonna go to the contents of
     the pointer or where the point is pointing to and actually copy that as well
     a deep copy is by definition going to copy the object in its entirety so how
     do we make a perform a deep copy.

   - Well of course we could write our own clone like method or function on it,
     but this is not the way to do it.

- The way that you do it is you write a copy constructor and a copy constructor
  is a constructor that gets called for that second string when you actually copy
  it so when you assign a string to an object that is also a string when you try
  to create a new variable and you assign it with another variable which has the
  `same type` as a variable that you're actually creating you're copying that
  variable and thus you're calling something called the copy constructor let's
  write one of Copy constructor.

First let's examine what is the default constructor that `C++` is providing which is hidden in our `String` class

```cpp


+-------------------------------------------+
|              Class String                 |
+-------------------------------------------+
| #include <iostream>                       |
| #include <string>                         |
|                                           |
| class String{                             |
|     private:                              |
|         char* m_Buffer;                   |
|         unsigned int m_Size;              |
|     public:                               |
|         String(const char* string){       |
|            m_Size = strlen(string);       |
|            m_Buffer = new[m_size+1];      |
|            memcpy(m_Buffer, string, m_size);
|         }                                 |
|        // default constructor             |
|        // created behind the scences      |
|        String(const String& other)        |   -------> If you want to be more exciting             String(const String& other)
|         :m_Buffer(other.m_Buffer),        |                                                        {memcpy(this, &other,sizeof(String))}; //memcpy includes the null-termination
|          m_Size(other.m_Size){            |
|          }                                |
|         ~String(){                        |
|            delete[] m_Buffer;             |
|         }                                 |
|         friend std::ostream& operator<<(std::ostream& stream, const String& string);
|         &char operator[](unsigned int index){
|             return m_Buffer[index];       |
|         }                                 |
| }                                         |
+-------------------------------------------+



```

- If you decided to not allow a copy-constructor by default you can declare the
  copy-constructor just equal to 0;

```cpp
         String(const String& other) = delete;           // or            String(const String& other) = delete;

```

- Then you cannot use this in main anymore:

```cpp
String str1 = "FirstString";j
String str2 = st1;   // <- won't work as you don't allow the copy to occur
```

- What we want to do here is to find our own copying instructor which does that
  deep copy so what I'll do over here is I'll copy size because well that is
  that is an integer we can just shallow copy.

- What I'm going to do is just simply allocate a new buffer we already know how
  big it needs to be it needs to be M size which we've already signed up here
  plus one we know that we're copying from another string object so what we
  really need to do here is simply copy the other buffer.

```cpp
String (const String& other)
    : m_Size(other.m_Size)
    {
         m_Buffer = new char[m_Size + 1]; // with null-termination
         memcpy(m_Buffer, other.m_Buffer, m_Size + 1); // We already know the other
                                                       // is null-terminated by the constructor that we did above
    }


```

3. How about passing to a function

- If you decide to actually write a function here that prints our string so I'll
  just write void print string

- What what we're actually doing is we're
  actually needlessly copying this if we
  come over here to the copy constructor

```cpp

void PringString(String string){
   std::cout << string  << std::endl;
}


String str1 = "FirstString";
String str2 = str1;   // first-copy
PrintString(str1);  // <-- [second-copy] Passing by value (means a new copy occur)
PrintString(str2);  // <-- [third-copy] Passing by value (means a new copy occur)
```

- you can see that we get three string copies happening ridiculous because when
  we don't want to be doing that what's actually happening is every time we copy a
  string we allocate memory on the heap copy all that memory and then at the end
  of it we free it that's completely unnecessary.

4. Better handling passing to function with copy-constructor For the reason that
   we mentioned at `point 3`, what we actually want to do is just pass the
   existing string into this print string function because we know that we're
   not going to need to copy we don't need another copy of it we can just
   reference the existing one and Staking a reference

   - The way that we do that is by passing this by reference which we can do by
     staking a reference here now this class will actually not be modifying the
     string so what we should do really is market as a Const reference.

   - If we don't mark it as Const not only does that mean that we can actually
     edit this so in other words I can just do write code like this if it wasn't
     marked as Const maybe let's make us a character just so it's clearer but because
     if it if it's not constant I can actually edit the existing string and if it's
     constant con means that we can't pass temporary our values into the actual
     function we'll talk about L values and our values soon

```cpp

void PringString(const String& string){
  std::cout << string  << std::endl;
}

String str1 = "FirstString";
String str2 = str1;   // first-copy
PrintString(str1);  // <-- no copy passing by reference
PrintString(str2);  // <-- no copy passing by reference
```

- You can see we only have one copy and that one copy happens over here when we
  assign a second with the value of string because that actually needs to be a
  copy because we're trying to create two different strings if we suddenly

5. Summary, for copy-constructors

- Decide in the print string function oh actually I do want to copy guess what
  we can actually do that just by typing in code like this so what I'm trying to
  tell you is always pass your objects by constant reference always we'll talk
  about really kind of being depth optimization about that in the future because
  maybe in some situations it actually might be faster to copy but for all intents
  and purposes is better than a basic level always pass your objects by constant
  reference.

- Because the function itself that you're writing you can decide if you want to
  copy in that function but there's no reason for you just to be throwing around
  copies all the time that's close it program down it's stupid whenever you pass a
  string doesn't matter if it's your own string class or if this is just STD
  string always always plus that by constants.

6. Best Coding Practise:

- kind of keep that in mind, Always pass by `const object reference`, if you
  want a copy inside your function, just do this.

```cpp

void PringString(const String& string){
   String copy_string = string;  // We are calling the assignment
                                 // (copy-constructor here, be our defintion
                                 // the copy-constructor accepting a const Strign&)
  std::cout << string  << std::endl;
}

String str1 = "FirstString";
String str2 = str1;   // first-copy
PrintString(str1);  // <-- no copy passing by reference
PrintString(str2);  // <-- no copy passing by reference
```

## References

- [Copying and Copy Constructors in C++ - The Cherno](https://www.youtube.com/watch?v=BvR1Pgzzr38&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=44)

## More Insight on Copying & Copy-Constructor

Copying in C++ is a fundamental concept that involves creating a new object as a
duplicate of an existing object. This concept is essential in C++ programming
because it allows developers to create copies of objects, whether they are
simple data types or complex class instances. Copying is used in various
scenarios, such as passing objects to functions by value, returning objects from
functions, or explicitly creating a copy of an object.

### What is Copying?

Copying, in the context of C++, means creating a new object with the same state
or value as an existing object. The process involves allocating memory for the
new object and then copying the values of the existing object's members to the
new object.

### How is it Used?

Copying is used in several key scenarios:

- **Passing Objects by Value**: When a function takes a parameter by value, a
  copy of the argument is made and passed to the function. This ensures that
  modifications inside the function do not affect the original argument.
- **Returning Objects from Functions**: When a function returns an object by
  value, a copy of the object is returned to the caller. This can involve copy
  construction or move construction in C++11 and later.
- **Explicit Copying**: Developers can explicitly create a copy of an object by
  using the assignment operator or a copy constructor.

### Things to Consider When Copying

When implementing copying in C++, there are several important considerations:


- **Deep vs. Shallow Copy**: A shallow copy duplicates the top-level structure
  but doesn't copy the underlying data for pointers or dynamic resources. A deep
  copy duplicates everything, ensuring that the new object is entirely
  independent of the original. Choosing between them depends on the resources
  managed by the object.
- **Resource Management**: If an object manages resources (like dynamic memory),
  simply copying pointers can lead to issues like double free errors or memory
  leaks. Proper resource management (copying the resource, not just the pointer)
  is crucial.
- **Copy Constructor and Assignment Operator**: Implementing custom copy
  constructors and assignment operators is necessary for classes that manage
  resources to ensure that copies are made correctly.
- **Copy Elision and Optimization**: Modern C++ compilers can optimize
  unnecessary copies away in certain situations, a feature known as copy
  elision. This can improve performance significantly.

### Examples

**Simple Copying Example:**

```cpp
int a = 5;
int b = a; // Copying the value of 'a' into 'b'
```

**Class Copying Example:**

```cpp
class Example {
public:
    int value;
    // Copy constructor
    Example(const Example& other) : value(other.value) {
        // Here, we make a copy of 'other' by copying its 'value'
    }
};

Example obj1;
obj1.value = 10;
Example obj2 = obj1; // Using the copy constructor
```

**Custom Copy Constructor for Deep Copy:**

```cpp
class StringWrapper {
    char* data;
public:
    StringWrapper(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Custom copy constructor for deep copy
    StringWrapper(const StringWrapper& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    ~StringWrapper() {
        delete[] data;
    }
};
```

In this example, the `StringWrapper` class manages a dynamic memory allocation.
The custom copy constructor ensures that when an object is copied, the
underlying data is also copied, preventing potential issues with shared resource
management. This is an example of implementing a deep copy to ensure that each
object manages its own resources independently.

## Basics string class from Scratch - Similar to std::string

Creating a basic class similar to `std::string` in C++ without using templates
or smart pointers involves focusing on dynamically allocated arrays of
characters and implementing fundamental functionalities like constructing,
destructing, copying, and managing the memory for the string data. The class
will provide basic operations such as constructing a string, destructing it,
assigning a new value, and accessing the string content. Here's a simplified
version:

```cpp
#include <cstring>
#include <iostream>

class SimpleString {
private:
    char* data;
    size_t length;

    void copyData(const char* str) {
        // Allocate memory for the new string, including null terminator
        length = strlen(str);
        data = new char[length + 1];
        // Copy the passed string into the newly allocated memory
        strcpy(data, str);
    }

public:
    // Default constructor
    SimpleString() : data(nullptr), length(0) {}

    // Constructor from a C-string
    SimpleString(const char* str) {
        copyData(str);
    }

    // Copy constructor for deep copying
    SimpleString(const SimpleString& other) {
        copyData(other.data);
    }

    // Assignment operator for deep copying
    SimpleString& operator=(const SimpleString& other) {
        if (this != &other) { // Protect against self-assignment
            // Delete the existing data
            delete[] data;
            // Deep copy the data from the other object
            copyData(other.data);
        }
        return *this;
    }

    // Destructor
    ~SimpleString() {
        delete[] data;
    }

    // Accessor for the C-string
    const char* c_str() const {
        return data;
    }

    // Accessor for the length of the string
    size_t size() const {
        return length;
    }
};

int main() {
    SimpleString str("Hello, World!");
    std::cout << "String: " << str.c_str() << ", Length: " << str.size() << std::endl;

    SimpleString strCopy = str; // Copy constructor
    std::cout << "Copied String: " << strCopy.c_str() << ", Length: " << strCopy.size() << std::endl;

    SimpleString strAssigned;
    strAssigned = str; // Assignment operator
    std::cout << "Assigned String: " << strAssigned.c_str() << ", Length: " << strAssigned.size() << std::endl;

    return 0;
}
```

This class includes:

- A constructor that takes a C-style string (`const char*`) and initializes the
  object with the provided string.
- A copy constructor and an assignment operator to handle deep copying, ensuring
  that each `SimpleString` object manages its own copy of the string data.
- A destructor to free the dynamically allocated memory, preventing memory
  leaks.
- Member functions `c_str()` and `size()` to provide access to the string data
  and its length, respectively.

This implementation is a simplified model and lacks many features and
optimizations of `std::string`, such as capacity management, string manipulation
functions (append, insert, find, etc.), and iterator support. However, it
captures the essence of dynamic memory management and object copying, which are
crucial aspects of a string class implementation.
