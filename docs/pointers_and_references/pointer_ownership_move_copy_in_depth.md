# Pointers OwnerShip - Move and Copy

## General Info about ownership

Understanding ownership in C++ is fundamental, especially as it relates to
memory management and the way variables and objects are accessed and
manipulated. Let's break this down using the analogy you suggested, where we
consider data (like a house) and keys (which grant access to that house), and
explore ownership across different types in C++.

### Primitive Types

Primitive types in C++ include basic data types such as `int`, `float`, `char`,
etc. When you declare a variable of a primitive type, you're essentially
claiming a piece of land (memory) to build your house (store your data).

**Analogy**: You have a house (data) on a piece of land. The deed (variable
declaration) to this land makes you the direct owner of the house. You hold the
key (access to the variable) to the front door, allowing you to modify the house
directly.

```cpp
int age = 30; // You own a piece of land with a house named 'age' valued at 30.
```

### Pointers

Pointers are variables that store the address of another variable, rather than
data itself. They can be thought of as having a map or address to a house,
rather than owning the house directly.

**Analogy**: You don't own the house directly; you own a piece of paper with the
address (pointer) to the house. Whoever holds this piece of paper can find and
access the house, but the ownership of the house itself depends on who owns the
land.

```cpp
int age = 30;
int* ptr = &age; // ptr is like having a map to the 'age' house. You can use ptr to find and access age.
```

### Object of Class

When you create an object of a class, it's akin to building a house (the object)
with multiple rooms (member variables and functions). Ownership of the object
means you have the keys to all rooms and can modify or access them as you wish.

**Analogy**: Owning a complex house directly. You have a master key that opens
all doors within the house, allowing you to access and modify any room.

```cpp
class Person {
public:
    int age;
};

Person john; // You've built a house named 'john', and you own it directly, including all its rooms (like 'age').
```

### Pointers to Class Objects on Heap

When you dynamically allocate an object on the heap using pointers, you're
essentially buying a house at a dynamic location. The pointer is your key to
that house. However, because the house isn't on your immediate property (stack),
you need to make sure to hand the keys back (delete the pointer) when you're
done, or else the house will remain unclaimed (memory leak).

**Analogy**: You own a key (pointer) to a house (object) in a vacation area
(heap). Only with the key can you access or modify the house. If you lose the
key (forget to `delete` the pointer), the house is lost (memory leak), even
though it still exists.

```cpp
class Person {
public:
    int age;
};

Person* ptr = new Person(); // You've bought a house on the heap and ptr is the key to that house.
// Remember to hand back the key when you're done.
delete ptr; // Handing the keys back, the house is demolished.
```

### Smart Pointers and Ownership

C++ introduces smart pointers (`std::unique_ptr`, `std::shared_ptr`,
`std::weak_ptr`) to help manage ownership and the life cycle of heap-allocated
objects more safely and automatically.

**Analogy**: Smart pointers are like having a property management service. For
example, `std::unique_ptr` is like having a security service that automatically
locks up and demolishes the house when you're done with it. No need to manually
return the keys; it's all handled for you.

```cpp
#include <memory>

class Person {
public:
    int age;
};

std::unique_ptr<Person> ptr = std::make_unique<Person>(); // ptr acts as an automatic key. The house will be demolished automatically when ptr goes out of scope.
```

This analogy helps illustrate the concept of ownership in C++: owning data
directly, owning the means to access data, managing the lifecycle of dynamically
allocated objects, and the modern approach to ownership with smart pointers.

## OwnerShip another anology

Let's use a new analogy involving a popular book to explain ownership in C++,
focusing on the case where two pointers refer to the same object, particularly
illustrating the concept of a shared pointer.

### The Popular Book Analogy

Imagine a popular book that everyone wants to read. This book represents an
object in C++, and the various ways people can access, own, or share this book
parallel the concepts of ownership with primitive types, pointers, and smart
pointers in C++.

### Primitive Types

A primitive type is like owning a copy of the book outright. It's yours, you
keep it on your bookshelf, and you can read or modify it (if it were a notebook,
for example) whenever you like.

```cpp
int pageCount = 300; // You own a book with 300 pages.
```

### Pointers

A pointer to an object is akin to having a library card that lets you borrow the
book from the library. The library card doesn't give you ownership of the book,
but it allows you to access and read the book. If you give the library card
(pointer) to someone else, they can also access the book.

```cpp
int* libraryCard = &pageCount; // The library card points to your book, allowing you to access its page count.
```

### Object of Class

Creating an object of a class is like buying a special edition of the book. This
edition might come with extra features (methods) and content (member variables)
not found in the standard edition. Owning this book means you can access all its
content and features directly.

```cpp
class Book {
public:
    int pageCount;
    void read() {}
};

Book specialEdition; // You own a special edition of the book.
```

### Pointers to Class Objects on Heap

Using pointers to dynamically allocate class objects on the heap is like using a
service that allows you to rent books online. You get access to the book for as
long as you maintain your subscription (keep the pointer), but once you end the
subscription (delete the pointer), you no longer have access to the book.

```cpp
Book* rentedBook = new Book(); // You've rented a book online.
delete rentedBook; // You end your subscription and lose access to the book.
```

### Two Pointers to the Same Object and Shared Pointer

When two pointers point to the same object, it's like two people sharing a copy
of a popular book because there's only one copy left in the bookstore. They
agree to share custody of the book, with each person having the right to read
it. However, coordination is needed to ensure they don't try to read it at the
same time and that the book is well cared for.

A `std::shared_ptr` in C++ automates this sharing process. It's like a book
sharing club that allows multiple members to share a book. Each member has
access to the book, and the club keeps track of how many members are currently
sharing the book. Once the last member is done reading and gives the book back,
the club knows nobody else is interested, and it can safely return the book to
the shelf.

```cpp
#include <memory>

std::shared_ptr<Book> sharedBook = std::make_shared<Book>(); // The book is now part of a sharing club.
std::shared_ptr<Book> anotherReader = sharedBook; // Another member also wants to read the book.
// Both can access the book, and it will only be "returned" once both are done with it.
```

This analogy helps illustrate the nuances of ownership in C++, emphasizing the
shared responsibility and automatic management of shared resources, like how a
shared pointer manages the lifecycle of an object when multiple owners are
involved.


## Pass the shared smart pointer to a function as a reference or as value? Who will be the owner and what will happen?

When you pass a shared smart pointer (`std::shared_ptr`) to a function, the
behavior and implications for ownership depend on whether you pass it by value
or by reference. Let's explore both scenarios using our book club analogy for
clarity.

### Passing by Value

Passing a shared smart pointer by value means you're giving a function a copy of
your library card that grants access to the shared book in the book club. Each
copy of the library card increases the club's count of members sharing the book.

**What Happens:**

- **Ownership**: Ownership is shared among all copies of the shared smart
  pointer, including the one passed to the function. The book (object) remains
  in the club (managed by `std::shared_ptr`) until the last library card (shared
  pointer) is returned or goes out of scope, at which point the book is returned
  to the shelf (object is destroyed).
- **Reference Count**: Each time a shared smart pointer is copied and passed by
  value, the internal reference count is incremented. This count tracks how many
  shared smart pointers currently own the resource.
- **Outcome**: The book remains available to all club members (owners). Only
  when the last member returns their card (the last `std::shared_ptr` is
  destroyed or reset) does the club decide that no one else needs the book, and
  it can safely be put away.

```cpp
void readBook(std::shared_ptr<Book> book) { // Passing by value
    // book is a copy of the shared_ptr. The reference count is incremented.
    // Function scope here...
} // The copy goes out of scope here, and the reference count is decremented.
```

### Passing by Reference

Passing a shared smart pointer by reference is akin to showing your library card
to a friend or a librarian without actually giving them a copy. They can see and
use the card (access the book) while you're there, but they don't increase the
count of people sharing the book.

**What Happens:**

- **Ownership**: The original owner retains full ownership, and the function
  merely has temporary access to the shared resource. There's no change in the
  actual ownership or the reference count of the shared smart pointer.
- **Reference Count**: Because the smart pointer is not copied (you're just
  passing a reference to it), the reference count does not change. The book
  club's record of how many people are sharing the book remains unchanged.
- **Outcome**: The function can access and use the shared book during its
  execution, but it doesn't affect the book's status in the club. Once the
  function execution completes, the book is still shared among the original
  members, with no impact on the overall management of the book.

```cpp
void readBook(std::shared_ptr<Book>& book) { // Passing by reference
    // book is the original shared_ptr. The reference count is unchanged.
    // Function scope here...
} // No change in ownership or reference count when the function exits.
```

### Summary

- **Passing by Value**: Increases the reference count, sharing ownership with
  the function's scope. More copies of the "library card" are created, and the
  book remains in circulation until the last card is returned.
- **Passing by Reference**: Does not change the reference count. The function
  has temporary access to the book through the original "library card," but no
  new ownership is created, and the book's shared status remains unchanged after
  the function completes.

This distinction is crucial in resource management, affecting how long resources
are kept alive and when they're cleaned up.
