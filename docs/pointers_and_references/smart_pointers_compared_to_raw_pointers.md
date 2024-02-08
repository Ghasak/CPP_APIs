# Smart Pointers compared to Raw Pointers

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Smart Pointers compared to Raw Pointers](#smart-pointers-compared-to-raw-pointers)
    - [Unique Pointers](#unique-pointers)
    - [Shared Pointers - Example](#shared-pointers---example)
        - [Using Raw Pointer](#using-raw-pointer)
        - [Using `std::shared_ptr`](#using-stdshared_ptr)
    - [For previous Example why not unique pointer](#for-previous-example-why-not-unique-pointer)
        - [Using `std::unique_ptr`](#using-stdunique_ptr)
        - [Comparison and When to Use Each](#comparison-and-when-to-use-each)
    - [Demo the shared ownership based on previous example:](#demo-the-shared-ownership-based-on-previous-example)
        - [Example with `std::shared_ptr` and Shared Ownership](#example-with-stdshared_ptr-and-shared-ownership)
    - [Demo for previous example as a raw pointer](#demo-for-previous-example-as-a-raw-pointer)
        - [Manual Shared Ownership with Raw Pointers](#manual-shared-ownership-with-raw-pointers)
    - [Demo - but we don't care about the reference count](#demo---but-we-dont-care-about-the-reference-count)
        - [Simplified Shared Ownership with Raw Pointers](#simplified-shared-ownership-with-raw-pointers)
    - [Another Comparison - Shared vs Unique vs Raw pointer](#another-comparison---shared-vs-unique-vs-raw-pointer)
        - [Raw Pointer Example](#raw-pointer-example)
        - [Unique Pointer Example](#unique-pointer-example)
        - [Shared Pointer Example](#shared-pointer-example)
        - [Why `std::shared_ptr` Over `std::unique_ptr` or Raw Pointers?](#why-stdshared_ptr-over-stdunique_ptr-or-raw-pointers)
    - [Demo Unique Pointer - Transfer Ownership](#demo-unique-pointer---transfer-ownership)
        - [Example with `std::unique_ptr` and Ownership Transfer](#example-with-stdunique_ptr-and-ownership-transfer)
        - [Key Points](#key-points)
    - [Demo Same Like Previous Example - Raw pointer](#demo-same-like-previous-example---raw-pointer)
        - [Example with Raw Pointer and Manual Management](#example-with-raw-pointer-and-manual-management)
        - [Key Points](#key-points-1)
    - [Demo Class Object - Raw Pointer then Unique Pointer](#demo-class-object---raw-pointer-then-unique-pointer)
        - [Using a Raw Pointer](#using-a-raw-pointer)
        - [Using `std::unique_ptr`](#using-stdunique_ptr-1)
    - [Demo Passing A pointer of an object to a function - Raw pointer](#demo-passing-a-pointer-of-an-object-to-a-function---raw-pointer)
    - [Demo Same Example - Unique Pointer](#demo-same-example---unique-pointer)
    - [[important] Demo Shared Smart Pointer - Reference Count increament up to 4-times](#important-demo-shared-smart-pointer---reference-count-increament-up-to-4-times)
    - [Demo - Same Example above but using - Unique Pointers](#demo---same-example-above-but-using---unique-pointers)
    - [Demo - Same Example above but using - Raw Pointers I](#demo---same-example-above-but-using---raw-pointers-i)
    - [Demo - Same Example above but using - Raw Pointers II](#demo---same-example-above-but-using---raw-pointers-ii)
    - [Demo - Same Example above but using - Unique Pointers III](#demo---same-example-above-but-using---unique-pointers-iii)

<!-- markdown-toc end -->

## Unique Pointers

## Shared Pointers - Example

I'll demonstrate both approaches for managing dynamic memory allocation in C++:
first using a raw pointer and then using a `std::shared_ptr`. The example will
include creating an integer on the heap, managing its lifetime, and passing it
to a function.

### Using Raw Pointer

```cpp
#include <iostream>

void processValue(int* ptr) {
    if (ptr != nullptr) {
        std::cout << "Processing value: " << *ptr << std::endl;
    }
}

int main() {
    // Allocate an integer on the heap
    int* rawPtr = new int(10);

    // Use the raw pointer
    processValue(rawPtr);

    // Clean up the allocated memory
    delete rawPtr;

    return 0;
}
```

In this example, `processValue` is a simple function that takes a pointer to an
integer. We manually manage memory using `new` and `delete`. It's crucial to
remember to `delete` the allocated memory to avoid memory leaks.

### Using `std::shared_ptr`

```cpp
#include <iostream>
#include <memory>

void processSharedPtr(std::shared_ptr<int> ptr) {
    if (ptr) {
        std::cout << "Processing value: " << *ptr << std::endl;
    }
}

int main() {
    // Allocate an integer on the heap using std::shared_ptr
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(10);

    // Use the shared pointer
    processSharedPtr(sharedPtr);

    // Memory is automatically cleaned up when the shared_ptr goes out of scope
    return 0;
}
```

In this version, we use `std::shared_ptr` from the C++ standard library, which
automatically handles memory deallocation when the `shared_ptr`'s reference
count drops to zero. This means there's no need to manually `delete` the
allocated memory, reducing the risk of memory leaks.

`processSharedPtr` is a function that takes a `std::shared_ptr<int>` as its
argument, showcasing how you can pass shared pointers to functions. This is
useful for shared ownership scenarios, where multiple parts of a program need to
access the same resource without worrying about its lifetime.

## For previous Example why not unique pointer

Why not unique pointer expand the example to distinguish the usage of shared vs smart?
Certainly! `std::unique_ptr` and `std::shared_ptr` are two smart pointer types
provided by the C++ Standard Library that manage dynamic memory. The main
difference between them is their ownership model:

- `std::unique_ptr` provides _exclusive_ ownership of the resource. There can
  only be one `std::unique_ptr` for a given resource, and when that `unique_ptr`
  goes out of scope, the resource is automatically freed. It's lighter weight
  compared to `std::shared_ptr` and should be used when only one owner of the
  resource is needed.
- `std::shared_ptr` allows for _shared_ ownership of a resource. Multiple
  `std::shared_ptr` instances can own the same resource, and the resource is
  only freed when the last `shared_ptr` owning it is destroyed or reset. It uses
  reference counting to keep track of how many `shared_ptr` instances own a
  resource, which adds some overhead.

Let's expand the previous examples to include `std::unique_ptr` and highlight
the difference in usage.

### Using `std::unique_ptr`

```cpp
#include <iostream>
#include <memory>

void processUniquePtr(std::unique_ptr<int> &ptr) {
    if (ptr != nullptr) {
        std::cout << "Processing value: " << *ptr << std::endl;
    }
    // The unique_ptr continues to own the resource.
}

int main() {
    // Allocate an integer on the heap using std::unique_ptr
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(20);

    // Use the unique pointer
    processUniquePtr(uniquePtr);

    // Memory is automatically cleaned up when the unique_ptr goes out of scope
    return 0;
}
```

In this example, `processUniquePtr` takes a reference to a
`std::unique_ptr<int>` to avoid transferring ownership. This demonstrates that
`unique_ptr` is suitable for situations where only one owner of the resource is
necessary or desired, but it can still be "borrowed" or accessed by other parts
of the program without transferring ownership.

### Comparison and When to Use Each

- **Use `std::unique_ptr`** when you need exclusive ownership of a resource,
  such as when an object is owned by a single owner at any point in its
  lifetime. This is the preferred default for managing dynamic memory due to its
  lower overhead compared to `std::shared_ptr`.
- **Use `std::shared_ptr`** when shared ownership is required, such as when an
  object's lifetime needs to be managed across multiple parts of a program and
  it's not clear when it should be deleted. `std::shared_ptr` is also useful for
  implementing complex data structures like graphs or when implementing a cache
  where multiple parts of a program need to maintain a reference to an object in
  the cache.

Choosing between `std::unique_ptr` and `std::shared_ptr` depends on your
specific ownership and lifetime management needs. Use `unique_ptr` for most
cases for efficiency and `shared_ptr` when shared ownership semantics are
necessary.

## Demo the shared ownership based on previous example:

To demonstrate shared ownership with `std::shared_ptr`, let's expand the example
to include a scenario where multiple `std::shared_ptr` instances share ownership
of an integer. This will illustrate how `std::shared_ptr` manages the resource's
lifetime across multiple owners.

### Example with `std::shared_ptr` and Shared Ownership

```cpp
#include <iostream>
#include <memory>

void processSharedPtr(std::shared_ptr<int> ptr) {
    // Increment the value pointed to by ptr
    if (ptr) {
        std::cout << "Before processing: " << *ptr << std::endl;
        (*ptr)++;
        std::cout << "After processing: " << *ptr << std::endl;
    }
}

void shareOwnership(std::shared_ptr<int> ptr) {
    std::cout << "Shared ownership count: " << ptr.use_count() << std::endl;
    // The shared_ptr ptr shares ownership of the resource.
    processSharedPtr(ptr);
    // When ptr goes out of scope here, the ownership count is decremented but the resource is not freed.
}

int main() {
    // Allocate an integer on the heap using std::shared_ptr
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(10);

    std::cout << "Initial ownership count: " << sharedPtr.use_count() << std::endl;
    // Share the ownership of the resource
    shareOwnership(sharedPtr);

    // After shareOwnership returns, sharedPtr still owns the resource.
    std::cout << "Ownership count after sharing: " << sharedPtr.use_count() << std::endl;
    std::cout << "Final value: " << *sharedPtr << std::endl;

    // Memory is automatically cleaned up when all shared_ptr instances go out of scope
    return 0;
}
```

In this example:

- We initially create a `std::shared_ptr<int>` that owns an integer.
- We pass this `shared_ptr` to `shareOwnership`, which then also passes it to
  `processSharedPtr`, demonstrating how multiple functions can share ownership
  of the resource.
- Inside `shareOwnership`, we print the use count of the shared pointer using
  `use_count()`, which shows how many `shared_ptr` instances currently own the
  resource. This count increases when we pass the `shared_ptr` and decreases
  when each `shared_ptr` goes out of scope or is reset.
- `processSharedPtr` modifies the integer, demonstrating that both the original
  and the copied `shared_ptr` instances point to the same resource.
- After `shareOwnership` returns, the ownership count decreases, but the
  integer's modified value persists, accessible via the original `shared_ptr`.

This example highlights the key advantage of `std::shared_ptr`: it allows
multiple parts of a program to share ownership of a resource, automatically
managing the resource's lifetime based on ownership count, thereby preventing
premature deletion or memory leaks.

## Demo for previous example as a raw pointer

Replicating the shared ownership mechanism with raw pointers in C++ requires
manual reference counting, which is both error-prone and cumbersome. However,
for educational purposes, I'll provide an example that simulates shared
ownership using raw pointers. This involves manually increasing and decreasing a
reference count to decide when to free the allocated memory.

### Manual Shared Ownership with Raw Pointers

```cpp
#include <iostream>

class ManualSharedInt {
private:
    int* data;
    int* count; // Reference count

public:
    ManualSharedInt(int value) : data(new int(value)), count(new int(1)) {
        std::cout << "Resource allocated with value: " << *data << std::endl;
    }

    // Copy constructor to simulate shared ownership
    ManualSharedInt(const ManualSharedInt& other) : data(other.data), count(other.count) {
        ++(*count);
    }

    // Destructor handles resource deallocation based on the reference count
    ~ManualSharedInt() {
        --(*count);
        if (*count == 0) {
            std::cout << "Resource deallocated with final value: " << *data << std::endl;
            delete data;
            delete count;
        }
    }

    // Overload dereference operator to access the value
    int& operator*() const { return *data; }

    // Function to display the current reference count
    void displayRefCount() const {
        std::cout << "Current reference count: " << *count << std::endl;
    }
};

void processValue(ManualSharedInt ptr) {
    // Increment the value pointed to by ptr
    std::cout << "Before processing: " << *ptr << std::endl;
    (*ptr)++;
    std::cout << "After processing: " << *ptr << std::endl;
    ptr.displayRefCount();
}

int main() {
    ManualSharedInt sharedValue(10);
    sharedValue.displayRefCount(); // Initial reference count

    // Simulate shared ownership
    processValue(sharedValue); // Pass by value to increase reference count

    sharedValue.displayRefCount(); // Final reference count after processValue() completes

    // Automatic cleanup when sharedValue and the copy in processValue go out of scope
    return 0;
}
```

In this example:

- We simulate shared ownership through a manual reference count, stored as an
  `int` pointer within the `ManualSharedInt` class.
- The constructor initializes the resource and sets the reference count to 1.
- The copy constructor is used to simulate sharing the resource. It increases
  the reference count for each new copy.
- The destructor checks the reference count; if it's zero (meaning no more
  owners), it deallocates the resource.
- The `processValue` function takes a `ManualSharedInt` instance by value, which
  increases the reference count due to the copy constructor. When the function
  exits, the destructor for the local copy is called, decrementing the reference
  count.

This manual approach to shared ownership is risky and generally not recommended
because it's easy to introduce bugs related to memory management, such as double
deletions, memory leaks, and dangling pointers. The C++ Standard Library's
`std::shared_ptr` is a much safer and more efficient way to manage shared
resources, as it handles these complexities automatically.

## Demo - but we don't care about the reference count

If we simplify the example by not implementing manual reference counting, and
just focus on using raw pointers to achieve a form of "shared ownership" without
explicit reference count management, it becomes a straightforward demonstration
of using and passing raw pointers. However, keep in mind, without reference
counting, we lose the automatic memory management and risk memory leaks or
double deletion.

Here's a simplified version of the previous example using raw pointers, without
any form of manual reference counting. This version will demonstrate passing the
pointer to functions but will not safely manage memory without explicit
deallocation, illustrating the need for careful memory management.

### Simplified Shared Ownership with Raw Pointers

```cpp
#include <iostream>

void processValue(int* ptr) {
    if (ptr != nullptr) {
        std::cout << "Before processing: " << *ptr << std::endl;
        (*ptr)++;
        std::cout << "After processing: " << *ptr << std::endl;
    }
}

int main() {
    // Allocate an integer on the heap
    int* sharedValue = new int(10);

    // Simulate "sharing" the pointer by passing it to a function
    processValue(sharedValue);

    // Use the shared value again in main
    std::cout << "Final value in main: " << *sharedValue << std::endl;

    // Manually deallocate the shared resource
    delete sharedValue;

    // After deletion, set the pointer to nullptr to avoid dangling pointer
    sharedValue = nullptr;

    return 0;
}
```

In this example:

- An integer is dynamically allocated on the heap and assigned to a raw pointer
  `sharedValue`.
- The pointer is passed to `processValue`, which simulates a shared use case by
  modifying the pointed-to value.
- After the function call, the main function still has access to the updated
  value via `sharedValue`.
- Finally, the dynamically allocated memory is manually freed using `delete`,
  and `sharedValue` is set to `nullptr` to prevent dangling pointer access.

This approach highlights the basic use of raw pointers for dynamic memory
management and function passing but lacks the safety and convenience of
automatic reference counting and resource cleanup provided by smart pointers
like `std::shared_ptr`. It's crucial to always ensure that every `new` is
matched with a `delete` to prevent memory leaks, and to avoid accessing or
deleting the pointer multiple times, which can lead to undefined behavior.

## Another Comparison - Shared vs Unique vs Raw pointer

To clarify the differences between raw pointers, `std::unique_ptr`, and
`std::shared_ptr`, I'll provide three examples using a simple scenario. Each
will dynamically allocate an integer, modify it, and then show an appropriate
use case that highlights why and when `std::shared_ptr` might be necessary over
`std::unique_ptr` or raw pointers.

### Raw Pointer Example

This example uses a raw pointer to allocate an integer, modify it, and then
manually deallocate the memory.

```cpp
#include <iostream>

void increment(int* ptr) {
    if (ptr) (*ptr)++;
}

int main() {
    int* rawPtr = new int(10); // Allocation
    increment(rawPtr);
    std::cout << "Raw Pointer Value: " << *rawPtr << std::endl;
    delete rawPtr; // Deallocation
    rawPtr = nullptr; // Avoid dangling pointer
}
```

**Drawbacks**: Manual memory management (allocation and deallocation), risk of
memory leaks, and dangling pointers.

### Unique Pointer Example

This example uses `std::unique_ptr` for automatic memory management. It shows
how to work with unique ownership.

```cpp
#include <iostream>
#include <memory>

void increment(std::unique_ptr<int>& ptr) {
    if (ptr) (*ptr)++;
}

int main() {
    auto uniquePtr = std::make_unique<int>(10);
    increment(uniquePtr);
    std::cout << "Unique Pointer Value: " << *uniquePtr << std::endl;
}
```

**Drawbacks**: `std::unique_ptr` cannot be copied to another `std::unique_ptr`,
limiting its use to scenarios where a single owner is sufficient.

### Shared Pointer Example

This example uses `std::shared_ptr` to demonstrate shared ownership. It will
show a scenario where shared ownership is necessary.

```cpp
#include <iostream>
#include <memory>
#include <vector>

void increment(std::shared_ptr<int> ptr) {
    if (ptr) (*ptr)++;
}

std::shared_ptr<int> createSharedInt() {
    return std::make_shared<int>(10);
}

void sharedExample() {
    auto sharedPtr = createSharedInt();
    increment(sharedPtr);
    std::cout << "Shared Pointer Value after increment: " << *sharedPtr << std::endl;
    // The sharedPtr can be safely used here and elsewhere.
}

int main() {
    sharedExample();
    // Memory is automatically managed and freed when the last shared_ptr is destroyed.
}
```

**Scenario for Shared Pointer**: Imagine a situation where you have a resource
that needs to be accessed and modified by multiple parts of your application.
For instance, if you're implementing a publisher/subscriber model where multiple
subscribers need to read or modify a shared piece of data, `std::shared_ptr` is
ideal because it allows multiple owners (subscribers) and ensures that the
resource is deallocated only when all references to it are gone.

### Why `std::shared_ptr` Over `std::unique_ptr` or Raw Pointers?

- **Raw pointers** require manual memory management and do not provide any
  mechanism for shared ownership.
- **`std::unique_ptr`** provides automatic memory management but restricts you
  to a single owner of the resource. This makes it unsuitable for scenarios
  where an object needs to be accessed or modified by multiple owners.
- **`std::shared_ptr`** allows for shared ownership of a resource, making it
  ideal for cases where a resource needs to be accessed by multiple parts of a
  program. It automatically handles the memory management, ensuring the resource
  is only freed when all `std::shared_ptr` instances that own it are destroyed
  or reset. This prevents memory leaks and simplifies memory management in
  complex applications.

## Demo Unique Pointer - Transfer Ownership

To adapt the previous example for `std::unique_ptr`, we must change the design
because `std::unique_ptr` does not allow shared ownership or easy copying.
Instead, we'll demonstrate transferring ownership between functions or objects,
which is one of the unique capabilities of `std::unique_ptr`. Since a
`std::unique_ptr` can only have one owner at a time, we'll simulate a scenario
where the document's ownership is transferred between users instead of being
shared.

### Example with `std::unique_ptr` and Ownership Transfer

```cpp
#include <iostream>
#include <memory>

// A simple Document class
class Document {
public:
    std::string content;
    Document(const std::string& initialContent) : content(initialContent) {}
    void append(const std::string& newText) {
        content += newText;
    }
};

// User class that takes ownership of a Document temporarily to edit it
class User {
public:
    // User edits the document by taking ownership
    void edit(std::unique_ptr<Document>& doc, const std::string& addition) {
        doc->append(addition);
    }
    // User views the document without taking ownership
    void view(const std::unique_ptr<Document>& doc) const {
        std::cout << "Document content: " << doc->content << std::endl;
    }
};

int main() {
    // Create a unique Document
    std::unique_ptr<Document> uniqueDoc = std::make_unique<Document>("Initial content. ");

    // Create a user
    User alice;

    // Alice edits the document
    alice.edit(uniqueDoc, "Alice's addition. ");

    // Alice views the updated document
    alice.view(uniqueDoc);

    // Ownership could be transferred if needed
    // Example: std::unique_ptr<Document> newOwner = std::move(uniqueDoc);

    // The Document is automatically deleted when uniqueDoc goes out of scope
    return 0;
}
```

### Key Points

- In this example, `User::edit` now requires a non-const reference to a
  `std::unique_ptr<Document>` for editing. This allows the `User` to modify the
  document through the `unique_ptr` without taking permanent ownership. This
  design simulates a temporary transfer of access rather than ownership.
- The `view` method demonstrates that a `std::unique_ptr` can be passed by
  reference to const for operations that don't modify the owned object, allowing
  read-only access without transferring ownership.
- The actual ownership transfer (giving the `Document` to another owner) would
  involve using `std::move` to transfer ownership of the `unique_ptr` to another
  `unique_ptr`, reflecting the unique ownership model. This is commented out in
  `main` as an example but is not executed to maintain the flow of the example.
- The example shows that `std::unique_ptr` enforces unique ownership semantics,
  which can be more restrictive than `std::shared_ptr` but also more efficient
  in scenarios where resource ownership is clear and does not need to be shared.

This adaptation underscores `std::unique_ptr`'s utility for cases with clear,
single ownership and the ability to transfer ownership safely and efficiently,
contrasting with `std::shared_ptr`'s shared ownership model.

## Demo Same Like Previous Example - Raw pointer

Adapting the shared document example to use raw pointers involves manual memory
management and careful consideration to avoid memory leaks or dangling pointers.
Unlike `std::unique_ptr` or `std::shared_ptr`, raw pointers do not automatically
manage the lifetime of the objects they point to. In this scenario, we'll
simulate a single user modifying a document and ensure proper deletion of the
document to clean up the allocated memory.

### Example with Raw Pointer and Manual Management

```cpp
#include <iostream>

// A simple Document class
class Document {
public:
    std::string content;
    Document(const std::string& initialContent) : content(initialContent) {}
    void append(const std::string& newText) {
        content += newText;
    }
};

// User class that modifies a Document
class User {
public:
    // User edits the document
    void edit(Document* doc, const std::string& addition) {
        if (doc) {
            doc->append(addition);
        }
    }
    // User views the document
    void view(const Document* doc) const {
        if (doc) {
            std::cout << "Document content: " << doc->content << std::endl;
        }
    }
};

int main() {
    // Create a Document dynamically
    Document* rawDoc = new Document("Initial content. ");

    // Create a user
    User alice;

    // Alice edits the document
    alice.edit(rawDoc, "Alice's addition. ");

    // Alice views the updated document
    alice.view(rawDoc);

    // Manual deallocation of the Document
    delete rawDoc;

    return 0;
}
```

### Key Points

- The `Document` is allocated on the heap using `new`, and a raw pointer is used
  to manage access to this memory.
- The `User` class methods `edit` and `view` take raw pointers to a `Document`.
  These methods can modify or read the document without taking ownership, as
  ownership is not a concept inherent to raw pointers.
- After use, the `Document` must be explicitly deleted with `delete` to prevent
  a memory leak. This manual cleanup is a critical step that is automatically
  handled by smart pointers (`std::unique_ptr` and `std::shared_ptr`).
- Care must be taken not to use the `rawDoc` pointer after it has been deleted,
  as this would lead to undefined behavior due to accessing freed memory
  (dangling pointer).

This example illustrates the simplicity and potential hazards of using raw
pointers for dynamic memory management. The manual allocation and deallocation
require diligent management to ensure memory safety, contrasting with the
automatic and safer memory management provided by smart pointers in C++.

## Demo Class Object - Raw Pointer then Unique Pointer

Let's start by creating a simple example of a class named `Vec2b` which
represents a 2D vector with basic integer coordinates `x` and `y`. We will first
show how to handle dynamic memory allocation for this class using a raw pointer,
and then how to manage it using `std::unique_ptr` from the C++ standard library
for better memory management and safety.

### Using a Raw Pointer

Here is how you might define the `Vec2b` class and allocate an instance of it on
the heap using a raw pointer:

```cpp
#include <iostream>

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    Vec2b* vec = new Vec2b(10, 20); // Allocation on the heap using raw pointer
    vec->print(); // Access and use

    delete vec; // It's crucial to manually delete to avoid memory leaks
}
```

### Using `std::unique_ptr`

Now, let's refactor the example to use `std::unique_ptr` for automatic memory
management. This approach eliminates the need for explicit `delete`, as the
`std::unique_ptr` will automatically release the allocated memory when it goes
out of scope or is otherwise destroyed.

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    std::unique_ptr<Vec2b> vec = std::make_unique<Vec2b>(10, 20); // Allocation on the heap using unique_ptr
    vec->print(); // Access and use

    // No need for explicit delete; memory will be automatically released
}
```

In the second example, `std::make_unique<Vec2b>(10, 20)` creates a new instance
of `Vec2b` on the heap and returns a `std::unique_ptr<Vec2b>` that owns this
newly allocated instance. The `std::unique_ptr` takes care of deallocating the
memory when it is destroyed or when its ownership is transferred, which
significantly reduces the risk of memory leaks and makes the code cleaner and
safer.

## Demo Passing A pointer of an object to a function - Raw pointer

Sure, let's demonstrate this concept by defining a simple function that takes a
raw pointer to a `Vec2b` object as its parameter. This function will simply call
the `Print` method of the `Vec2b` object to which it points.

First, using a raw pointer:

```cpp
#include <iostream>

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

// Function taking a raw pointer to Vec2b
void PrintVec2b(const Vec2b* vec) {
    if (vec) { // Always check if the pointer is not null before dereferencing
        vec->Print();
    } else {
        std::cout << "Null pointer provided." << std::endl;
    }
}

int main() {
    Vec2b* vec = new Vec2b(10, 20); // Allocation on the heap using raw pointer
    PrintVec2b(vec); // Pass raw pointer to function

    delete vec; // Clean up to avoid memory leak
}
```

In this example, the `PrintVec2b` function takes a raw pointer to a `Vec2b`
object and calls its `Print` method. The `main` function creates a `Vec2b`
object on the heap and passes a pointer to this object to `PrintVec2b`. After
using the object, `main` properly cleans up by deleting the allocated object to
prevent a memory leak.

## Demo Same Example - Unique Pointer

To modify the example to use a `std::unique_ptr`, we'll adjust the function to
accept a reference to a `std::unique_ptr<Vec2b>` instead. This allows us to
maintain ownership semantics while still being able to use the object within the
function. Note that functions typically take `std::unique_ptr` by reference if
they don't intend to take ownership, or by value if they need to take ownership.
Since the goal here is just to use the object without transferring ownership,
we'll use a reference.

Here's how you do it with a `std::unique_ptr`:

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

// Function taking a reference to a unique_ptr to Vec2b
void PrintVec2b(const std::unique_ptr<Vec2b>& vec) {
    if (vec) { // The unique_ptr overrides the bool operator for null check
        vec->Print();
    } else {
        std::cout << "Null pointer provided." << std::endl;
    }
}

int main() {
    std::unique_ptr<Vec2b> vec = std::make_unique<Vec2b>(10, 20); // Allocation on the heap using unique_ptr
    PrintVec2b(vec); // Pass unique_ptr by reference to function

    // No need for explicit delete; memory will be automatically released
}
```

In this version, the `PrintVec2b` function accepts a reference to a
`std::unique_ptr<Vec2b>`. This means that when you call `PrintVec2b`, you're not
transferring ownership of the `Vec2b` object; you're merely allowing the
function to access the object via the smart pointer. The smart pointer ensures
that the memory is automatically managed, making this approach safer and
avoiding memory leaks without needing an explicit `delete`.

## [important] Demo Shared Smart Pointer - Reference Count increament up to 4-times

To demonstrate the use of a `std::shared_ptr` with a reference count going up to
4, we'll create a scenario where a `std::shared_ptr` is copied multiple times,
each copy incrementing the internal reference count.

The `std::shared_ptr` type is a smart pointer that retains shared ownership of
an object through a pointer. Several `shared_ptr` objects may own the same
object, and the object is destroyed and its memory deallocated when either the
last remaining `shared_ptr` owning the object is destroyed or reset.

Here's an example:

```cpp
#include <iostream>
#include <memory> // For std::shared_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {
        std::cout << "Vec2b(" << x << ", " << y << ") constructed" << std::endl;
    }

    ~Vec2b() {
        std::cout << "Vec2b(" << x << ", " << y << ") destroyed" << std::endl;
    }

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

void PrintRefCount(const std::shared_ptr<Vec2b>& vec) {
    std::cout << "Reference count: " << vec.use_count() << std::endl;
}

int main() {
    std::shared_ptr<Vec2b> vec1 = std::make_shared<Vec2b>(10, 20);
    PrintRefCount(vec1); // Count = 1

    {
        std::shared_ptr<Vec2b> vec2 = vec1; // Copy #1
        PrintRefCount(vec1); // Count = 2

        {
            std::shared_ptr<Vec2b> vec3 = vec1; // Copy #2
            PrintRefCount(vec1); // Count = 3

            std::shared_ptr<Vec2b> vec4 = vec1; // Copy #3, Total copies including original = 4
            PrintRefCount(vec1); // Count = 4
        } // vec3 and vec4 are destroyed here, but vec1 and vec2 still alive

        PrintRefCount(vec1); // Count back to 2
    } // vec2 is destroyed here

    PrintRefCount(vec1); // Count back to 1, only vec1 remains
}
```

In this example:

- We start by creating `vec1`, a `std::shared_ptr<Vec2b>`, with a reference
  count of 1.
- We then create three more shared pointers (`vec2`, `vec3`, `vec4`) that share
  ownership of the same `Vec2b` instance as `vec1`, increasing the reference
  count to 4 at its peak.
- As each of these additional shared pointers goes out of scope, they are
  destroyed, and the reference count decrements accordingly.
- Finally, when `vec1` is the only remaining owner, the reference count goes
  back down to 1.

This behavior demonstrates the automatic management of the reference count and
the object's lifetime based on ownership shared between multiple
`std::shared_ptr` instances.

## Demo - Same Example above but using - Unique Pointers

Using `std::unique_ptr` in a manner similar to `std::shared_ptr` to increment a
reference count isn't directly possible, because `std::unique_ptr` enforces
unique ownership of the managed object. This means you cannot simply copy a
`std::unique_ptr` to increase a reference count, as you can with
`std::shared_ptr`. Instead, `std::unique_ptr` must be explicitly moved to
transfer ownership from one unique pointer to another, and at any given time,
only one `std::unique_ptr` can own the object.

However, to demonstrate a scenario that involves transferring ownership multiple
times with `std::unique_ptr`, we can create an example. Keep in mind, this won't
increase a reference count (since `std::unique_ptr` doesn't use one), but it
will show how ownership is transferred:

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {
        std::cout << "Vec2b(" << x << ", " << y << ") constructed" << std::endl;
    }

    ~Vec2b() {
        std::cout << "Vec2b(" << x << ", " << y << ") destroyed" << std::endl;
    }

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

void TransferOwnership(std::unique_ptr<Vec2b>&& vec) {
    std::cout << "Transferred Vec2b object:" << std::endl;
    vec->Print();
    // Ownership will be destroyed when this function ends and vec goes out of scope
}

int main() {
    std::unique_ptr<Vec2b> vec1 = std::make_unique<Vec2b>(10, 20);
    vec1->Print(); // Initially owned by vec1

    // Transfer ownership from vec1 to another scope/function
    TransferOwnership(std::move(vec1));
    // At this point, vec1 no longer owns the object

    if (!vec1) {
        std::cout << "vec1 no longer owns the Vec2b object." << std::endl;
    }
}
```

In this example:

- We start by creating `vec1`, a `std::unique_ptr<Vec2b>`.
- We then transfer ownership of the `Vec2b` object from `vec1` to the
  `TransferOwnership` function using `std::move(vec1)`. This is necessary
  because `std::unique_ptr` cannot be copied, only moved.
- Inside `TransferOwnership`, the transferred `std::unique_ptr` takes temporary
  ownership of the `Vec2b` object, and it's automatically destroyed when the
  function ends.
- After the transfer, `vec1` becomes `nullptr`, indicating it no longer owns the
  object.

This demonstrates the unique ownership model of `std::unique_ptr`, contrasting
with the shared ownership model of `std::shared_ptr` where a reference count is
maintained.

## Demo - Same Example above but using - Raw Pointers I

Replicating the shared ownership scenario with raw pointers directly isn't
straightforward because raw pointers don't have built-in reference counting or
automatic memory management. However, you can simulate a form of "transfer of
access" (not ownership, since all raw pointers can point to the same object
without ownership semantics) by passing the raw pointer between functions.
Remember, without a proper reference counting mechanism, you must be very
careful to avoid memory leaks or double deletion.

Here's an example demonstrating passing a raw pointer between functions, similar
to transferring `std::unique_ptr` ownership but without actual ownership
transfer semantics:

```cpp
#include <iostream>

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {
        std::cout << "Vec2b(" << x << ", " << y << ") constructed" << std::endl;
    }

    ~Vec2b() {
        std::cout << "Vec2b(" << x << ", " << y << ") destroyed" << std::endl;
    }

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

void UseRawPointer(Vec2b* vec) {
    std::cout << "Using Vec2b object through raw pointer:" << std::endl;
    if (vec) {
        vec->Print();
    } else {
        std::cout << "Null pointer provided." << std::endl;
    }
    // No ownership transfer semantics, just access
}

int main() {
    Vec2b* vec1 = new Vec2b(10, 20); // Manually managing Vec2b object
    vec1->Print(); // Accessing directly

    UseRawPointer(vec1); // Passing raw pointer to function for use

    // Manual deletion required to avoid memory leak
    delete vec1;
    vec1 = nullptr;

    if (!vec1) {
        std::cout << "vec1 pointer is now null after deletion." << std::endl;
    }
}
```

In this example:

- A `Vec2b` object is dynamically allocated and its pointer is stored in `vec1`.
- The `vec1` pointer is passed to the `UseRawPointer` function, which uses the
  object.
- After using the object in `UseRawPointer`, the ownership (i.e., the
  responsibility to delete the object) still lies with the original pointer
  `vec1`. The function merely accesses the object without any form of ownership
  transfer.
- Finally, `vec1` is manually deleted to prevent a memory leak, and then set to
  `nullptr` to signify it no longer points to a valid object.

This illustrates raw pointer usage and manual memory management without any form
of automatic cleanup or reference counting, highlighting the benefits of smart
pointers for managing ownership and lifetime in more complex scenarios.

## Demo - Same Example above but using - Raw Pointers II

Maintain same inner scoped numbers for the example you showed me for shared
pointer and do it now for a raw pointer. Replicating the shared ownership and
reference count behavior with raw pointers directly is challenging, as raw
pointers do not inherently support reference counting. However, to mimic the
behavior of a shared pointer with raw pointers and manual reference counting,
you would need to manually implement reference counting logic.

This is not a common practice due to the complexity and risk of errors (such as
memory leaks or double frees), but for educational purposes, I'll show you an
example that simulates increasing and decreasing a reference count manually for
raw pointers within nested scopes. Keep in mind, this is a simplified example to
demonstrate the concept:

```cpp
#include <iostream>

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {}

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

void PrintRefCount(int count) {
    std::cout << "Reference count: " << count << std::endl;
}

int main() {
    Vec2b* vec = new Vec2b(10, 20); // Dynamically allocate Vec2b
    int* refCount = new int(1); // Dynamically allocate reference count, initialize to 1

    PrintRefCount(*refCount); // Initial count = 1

    {
        Vec2b* vec2 = vec; // Copy #1
        (*refCount)++;
        PrintRefCount(*refCount); // Count = 2

        {
            Vec2b* vec3 = vec; // Copy #2
            (*refCount)++;
            PrintRefCount(*refCount); // Count = 3

            Vec2b* vec4 = vec; // Copy #3, Total copies including original = 4
            (*refCount)++;
            PrintRefCount(*refCount); // Count = 4
        } // vec3 and vec4 go out of scope, but we manually decrease reference count

        (*refCount)--;
        PrintRefCount(*refCount); // Count = 3
        (*refCount)--;
        PrintRefCount(*refCount); // Count = 2
    } // vec2 goes out of scope, manually decrease reference count

    (*refCount)--;
    PrintRefCount(*refCount); // Count = 1

    if (*refCount == 1) {
        delete vec; // Only delete when refCount is 1, indicating last owner
        delete refCount; // Also delete the reference count itself
        vec = nullptr;
        refCount = nullptr;
    }

    if (!vec) {
        std::cout << "Vec object and reference count successfully deleted." << std::endl;
    }
}
```

In this example:

- We manually manage a `Vec2b` object and its reference count using raw
  pointers.
- As we "copy" the pointer (really just assigning the same address to another
  pointer variable), we manually increment the reference count.
- When each pointer goes out of scope, we manually decrement the reference
  count.
- We only delete the `Vec2b` object and the reference count when the reference
  count goes back down to 1, indicating that no more pointers are "referring" to
  the object.

This example demonstrates the concept but lacks the safety and convenience of
`std::shared_ptr`, which automates reference counting and resource cleanup. It's
a good illustration of why smart pointers are preferred in modern C++ for
managing dynamically allocated resources.

## Demo - Same Example above but using - Unique Pointers III

Implementing the exact scenario with `std::unique_ptr` as we did with manual
reference counting for raw pointers or the automatic reference counting of
`std::shared_ptr` isn't feasible due to the unique ownership model of
`std::unique_ptr`. By design, `std::unique_ptr` allows only a single owner for
the managed object at any time, which means you cannot have multiple
`std::unique_ptr`s pointing to the same object and thus cannot manually increase
a reference count like with `std::shared_ptr`. However, to demonstrate a
scenario that involves transferring `std::unique_ptr` ownership while
maintaining the same inner scope structure, we can show how ownership is passed
but without incrementing reference counts. This example will transfer ownership
of an object through nested scopes using `std::unique_ptr`:

```cpp
#include <iostream>
#include <memory> // For std::unique_ptr

class Vec2b {
public:
    int x, y;

    Vec2b(int x, int y) : x(x), y(y) {
        std::cout << "Vec2b(" << x << ", " << y << ") constructed" << std::endl;
    }

    ~Vec2b() {
        std::cout << "Vec2b(" << x << ", " << y << ") destroyed" << std::endl;
    }

    void Print() const {
        std::cout << "Vec2b(" << x << ", " << y << ")" << std::endl;
    }
};

std::unique_ptr<Vec2b> CreateAndTransferOwnership() {
    std::unique_ptr<Vec2b> vec = std::make_unique<Vec2b>(200, 300);
    vec->Print(); // Use before transferring
    return vec; // Transfer ownership out of the function
}

int main() {
    std::unique_ptr<Vec2b> vec1 = CreateAndTransferOwnership(); // Ownership transferred to vec1

    // Attempt to demonstrate similar nested scope structure but with unique_ptr
    {
        std::unique_ptr<Vec2b> vec2 = std::move(vec1); // Transfer ownership to vec2
        if (!vec1) {
            std::cout << "vec1 no longer owns the object." << std::endl;
        }

        {
            std::unique_ptr<Vec2b> vec3 = std::move(vec2); // Transfer ownership to vec3
            if (!vec2) {
                std::cout << "vec2 no longer owns the object." << std::endl;
            }

            std::unique_ptr<Vec2b> vec4 = std::move(vec3); // Transfer ownership to vec4
            if (!vec3) {
                std::cout << "vec3 no longer owns the object." << std::endl;
            }
            // vec4 is the current owner
        }
        // Ownership ends with vec4, which will be automatically destroyed here
    }

    // At this point, vec1, vec2, and vec3 are all nullptr, and vec4 has been destroyed.
}
```

This example demonstrates transferring ownership of a `std::unique_ptr<Vec2b>`
from one scope to another. Unlike with `std::shared_ptr`, there's no reference
counting involved. Each transfer of ownership results in the previous owner
being set to `nullptr`, ensuring that at any time, only one `std::unique_ptr`
owns the object. Once the final owner (`vec4` in this case) goes out of scope,
the `Vec2b` object is automatically destroyed.
