# Shared Pointers in depth

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Shared Pointers in depth](#shared-pointers-in-depth)
  - [Shared Smart Pointer Meaning](#shared-smart-pointer-meaning)
    - [Example Scenario:](#example-scenario)
  - [Smarter Shared Pointers in Essence](#smarter-shared-pointers-in-essence)
    - [std::shared_ptr](#stdshared_ptr)
    - [Ownership](#ownership)
    - [Copying](#copying)
    - [Moving](#moving)
    - [Copy Assignment and Move Assignment](#copy-assignment-and-move-assignment)
    - [Reset Method](#reset-method)
    - [Use Count](#use-count)
    - [Weak Pointers](#weak-pointers)
    - [Summary](#summary)
  - [Circular References Problem](#circular-references-problem)
    - [Example of Circular References](#example-of-circular-references)
    - [Solving Circular References with `std::weak_ptr`](#solving-circular-references-with-stdweak_ptr)
  - [Shared Widget - Example for using shared pointer](#shared-widget---example-for-using-shared-pointer)
    - [Step 1: Define a `Widget` Class](#step-1-define-a-widget-class)
    - [Step 2: Function to Create a `Widget`](#step-2-function-to-create-a-widget)
    - [Step 3: Function to Modify a `Widget`](#step-3-function-to-modify-a-widget)
    - [Step 4: Function to Use a `Widget`](#step-4-function-to-use-a-widget)
    - [Step 5: Main Function to Demonstrate Usage](#step-5-main-function-to-demonstrate-usage)
    - [Explanation](#explanation)
  - [Understanding passsing to a function several times as a references and as value](#understanding-passsing-to-a-function-several-times-as-a-references-and-as-value)
    - [Example Setup](#example-setup)
    - [Passing `std::shared_ptr` by Value](#passing-stdshared_ptr-by-value)
    - [Passing `std::shared_ptr` by Reference](#passing-stdshared_ptr-by-reference)
    - [Key Points:](#key-points)
  - [Same Example with three calls](#same-example-with-three-calls)
    - [Extended Example with Multiple Calls](#extended-example-with-multiple-calls)
    - [Explanation:](#explanation)
  - [Reference count when it get increased?](#reference-count-when-it-get-increased)
    - [1. Direct Copy](#1-direct-copy)
    - [2. Passing by Value to a Function](#2-passing-by-value-to-a-function)
    - [3. Storing in a Container](#3-storing-in-a-container)
    - [4. Assigning to Another `std::shared_ptr`](#4-assigning-to-another-stdshared_ptr)
    - [5. Capturing in a Lambda](#5-capturing-in-a-lambda)
    - [Demonstration](#demonstration)
  - [Why we need the shared pointer - Insight](#why-we-need-the-shared-pointer---insight)
    - [Case Where `std::shared_ptr` Is Needed](#case-where-stdshared_ptr-is-needed)
    - [Example Without `std::shared_ptr`](#example-without-stdshared_ptr)
    - [Example With `std::shared_ptr`](#example-with-stdshared_ptr)
    - [Advantages of Using `std::shared_ptr`:](#advantages-of-using-stdshared_ptr)
  - [Multiple Owners for same object](#multiple-owners-for-same-object)
    - [Example with Multiple Owners Sharing a `Document` Resource](#example-with-multiple-owners-sharing-a-document-resource)
    - [Explanation](#explanation-1)
  - [Shared Pointer Usages - Imporant](#shared-pointer-usages---imporant)
    - [1. Multiple Owners of Same Resource](#1-multiple-owners-of-same-resource)
    - [2. Returning Objects from Functions](#2-returning-objects-from-functions)
    - [3. Storing Shared Objects in Containers](#3-storing-shared-objects-in-containers)
    - [4. Implementing Graphs or Trees](#4-implementing-graphs-or-trees)
    - [5. Circular References](#5-circular-references)

<!-- markdown-toc end -->

## Shared Smart Pointer Meaning

A `std::shared_ptr` in C++ allows multiple `std::shared_ptr` instances to refer
to and share ownership of the same object. Here's how it works and why it's
useful:

1. **Shared Ownership**: When multiple `std::shared_ptr` instances refer to the
   same object, they share the ownership of that object. This means the object
   will remain alive as long as there is at least one `std::shared_ptr` pointing
   to it.

2. **Reference Counting**: `std::shared_ptr` uses an internal reference counting
   mechanism to keep track of how many `std::shared_ptr` instances currently own
   the shared object. The count increases whenever a new `std::shared_ptr` is
   created from another (copying or assigning) and decreases when a
   `std::shared_ptr` is destroyed or reassigned.

3. **Automatic Memory Management**: Once the last `std::shared_ptr` that points
   to the object is destroyed or reset, the reference count drops to zero. At
   this point, `std::shared_ptr` automatically deletes the object and frees the
   allocated memory, ensuring no leaks occur.

4. **Cycle Detection and Weak Pointers**: A potential downside of shared
   ownership is the risk of creating cyclic references (where two or more
   objects own each other directly or indirectly), which could prevent the
   reference count from ever reaching zero, thus leading to memory leaks.
   `std::shared_ptr` can be paired with `std::weak_ptr` to break these cycles.
   `std::weak_ptr` allows access to an object owned by a `std::shared_ptr`
   without increasing the reference count, thus not contributing to ownership
   and allowing cycles to be resolved.

### Example Scenario:

Imagine a scenario where two parts of a program must access and possibly modify
a shared configuration object:

- Multiple `std::shared_ptr<Configuration>` instances can be created and passed
  around to different components of the application that need access to the
  shared `Configuration` object.
- As long as at least one `std::shared_ptr` exists that points to the
  `Configuration` object, the object remains alive.
- When the last `std::shared_ptr` to the `Configuration` object is destroyed or
  reset, the `Configuration` object is automatically deleted.

This design pattern is particularly useful in complex systems where objects have
a shared lifecycle and are accessed from multiple places, making manual memory
management cumbersome and error-prone. `std::shared_ptr` simplifies these
scenarios by managing the object's lifetime automatically, based on the
ownership shared by multiple pointers.

## Smarter Shared Pointers in Essence

Shared pointers are smart pointers that allow multiple threads to access a
resource simultaneously. However, their implementation in some libraries can
have drawbacks such as excessive memory allocation and unnecessary
synchronization. This essay will discuss the essence of smarter shared pointers,
which address these issues by implementing lazy initialization and reference
counting algorithms.

In traditional shared pointer implementations, a new shared pointer is created
with a constructor that takes an object as its argument. The object's destructor
is called when all shared pointers pointing to it are destroyed, freeing the
memory allocated for the object. This works well in many cases but can lead to
issues such as excessive memory allocation and unnecessary synchronization.

Consider the following example:

```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class Resource {
public:
    void DoSomething() const { std::cout << "Doing something\n"; }
};

std::shared_ptr<Resource> CreateResources() {
    std::vector<std::shared_ptr<Resource>> resources;
    for (int I = 0; I < 10000; ++i) {
        auto resource = std::make_shared<Resource>();
        resources.push_back(resource);
    }
    return std::make_shared<std::vector<std::weak_ptr<Resource>>>(resources);
}

void UseResources(const std::shared_ptr<std::vector<std::weak_ptr<Resource>>>& weakVector) {
    for (auto& weak : *weakVector) {
        auto resource = weak.lock();
        if (resource) {
            resource->DoSomething();
        }
    }
}

int main() {
    std::thread t1(UseResources, CreateResources().get());
    std::thread t2(UseResources, CreateResources().get());
    t1.join();
    t2.join();
    return 0;
}
```

In this example, the `CreateResources()` function creates 10,000 resources and
returns a shared pointer to a vector of weak pointers to those resources. This
vector is then passed to two threads that each iterate over it and use the
resources if they are still available.

This implementation has some drawbacks:

- Each resource is allocated separately, leading to excessive memory allocation.
- The vector of weak pointers is also allocated separately, adding unnecessary
  synchronization overhead when accessing it concurrently.

A smarter shared pointer addresses these issues by implementing lazy
initialization and reference counting algorithms. In this approach, a single
instance of the resource is created on demand, eliminating excessive memory
allocation. Additionally, reference counting is used to keep track of the number
of pointers pointing to the resource, allowing for efficient destruction when
all pointers have been destroyed.

Here's an implementation of such a smarter shared pointer:

```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

class Resource {
public:
    void DoSomething() const { std::cout << "Doing something\n"; }
};

// The lazy initialization and reference counting class template
template<typename T>
class SmartResource {
public:
    // Constructor to initialize the resource on demand
    explicit SmartResource(std::function<T()> createResource) :
        weak_ptr_{ std::make_shared<ResourceHolder>(createResource()) },
        strong_refs_{} {}

    // Get a shared pointer to the underlying resource, incrementing the reference count
    std::shared_ptr<T> GetSharedPtr() {
        auto ptr = weak_ptr_.lock();
        if (ptr) {
            ++strong_refs_;
        }
        return ptr;
    }

    // Decrement the reference count and delete the resource if it reaches zero
    ~SmartResource() {
        --strong_refs_;
        auto ptr = weak_ptr_.lock();
        if (ptr && !strong_refs_) {
            std::cout << "Destroying resource\n";
            delete ptr;
        }
    }

private:
    // The ResourceHolder class is used to implement lazy initialization and reference counting
    struct ResourceHolder {
        ResourceHolder(T resource) : resource_{ std::move(resource) } {}
        std::weak_ptr<ResourceHolder> weak_ptr_;
        T resource_;
        int strong_refs_ = 0;
    };

    // The weak pointer to the underlying resource holder object
    std::weak_ptr<ResourceHolder> weak_ptr_{};
};

// Example usage
void UseResources() {
    SmartResource<Resource> resources(CreateResource);
    auto sharedPtr1 = resources.GetSharedPtr();
    auto sharedPtr2 = resources.GetSharedPtr();
}

int main() {
    std::thread t1(UseResources);
    std::thread t2(UseResources);
    t1.join();
    t2.join();
    return 0;
}
```

In this implementation, the `SmartResource` class template encapsulates a single
resource and provides lazy initialization and reference counting functionality
through its constructor, destructor, and `GetSharedPtr()` method. The
`ResourceHolder` struct is used to implement lazy initialization by storing both
the created resource and a weak pointer to it. Additionally, reference counting
is implemented using an integer member variable `strong_refs_`.

The `SmartResource` class template's constructor initializes its `weak_ptr_` and
`strong_refs_` members with the result of calling the provided
`createResource()` function and storing it in a new `ResourceHolder` object.
This lazy initialization approach eliminates excessive memory allocation as
resources are created only when needed.

The destructor decrements the reference count, deleting the resource if it
reaches zero. This allows for efficient destruction of the resource when all
pointers pointing to it have been destroyed.

In summary, smarter shared pointers provide a more efficient and memory-friendly
alternative to traditional shared pointer implementations by implementing lazy
initialization and reference counting algorithms. These features address issues
such as excessive memory allocation and unnecessary synchronization overhead,
making them an excellent choice for use in resource-intensive applications where
performance is critical.

### std::shared_ptr

`std::shared_ptr` is a smart pointer in C++ that manages shared ownership of a
dynamically allocated object. Multiple `std::shared_ptr` instances can own the
same object, and the object is destroyed when the last `std::shared_ptr` owning
it is destroyed or reset. Here's how it works in terms of ownership, moving,
copying, and other related concepts:

### Ownership

`std::shared_ptr` uses reference counting to keep track of how many
`std::shared_ptr` instances share ownership of the same object. When a
`std::shared_ptr` is copied or assigned to another `std::shared_ptr`, the
reference count is incremented. When a `std::shared_ptr` is destroyed or reset,
the reference count is decremented. If the reference count reaches zero, the
object is destroyed.

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1; // Now ptr1 and ptr2 share ownership. Reference count is 2.
```

### Copying

Copying a `std::shared_ptr` is straightforward and safe. It increases the
reference count to indicate another owner of the resource:

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1; // Copying. Both share ownership. Reference count becomes 2.
```

### Moving

`std::shared_ptr` supports move semantics, which transfers ownership from one
`std::shared_ptr` to another without changing the reference count of the managed
object. After the move, the source `std::shared_ptr` becomes null, and the
destination takes over its ownership.

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr3 = std::move(ptr1); // Moving. ptr3 takes ownership. ptr1 becomes null.
```

### Copy Assignment and Move Assignment

`std::shared_ptr` supports both copy assignment and move assignment operators.
Copy assignment increases the reference count, while move assignment transfers
ownership without altering the reference count.

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2;
std::shared_ptr<int> ptr3;

ptr2 = ptr1; // Copy assignment. Reference count is increased.
ptr3 = std::move(ptr2); // Move assignment. ptr2 is null after this operation.
```

### Reset Method

The `reset` method changes the object managed by the `std::shared_ptr`. If the
`std::shared_ptr` is the last owner of its current object, that object is
destroyed. After `reset`, the `std::shared_ptr` either becomes empty or takes
ownership of a new object.

```cpp
std::shared_ptr<int> ptr = std::make_shared<int>(10);
ptr.reset(new int(20)); // The old object is destroyed if no other shared_ptr owns it. ptr now owns the new object.
```

### Use Count

You can check how many `std::shared_ptr` instances share ownership of the same
object using the `use_count` method. This can be useful for debugging or for
conditional logic based on ownership.

```cpp
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::shared_ptr<int> ptr2 = ptr1; // Both share ownership.
std::cout << ptr1.use_count(); // Outputs 2
```

### Weak Pointers

`std::weak_ptr` is a companion to `std::shared_ptr` that allows access to an
object that is owned by one or more `std::shared_ptr` instances without
contributing to the reference count. This prevents circular references that
could lead to memory leaks.

```cpp
std::shared_ptr<int> sharedPtr = std::make_shared<int>(10);
std::weak_ptr<int> weakPtr = sharedPtr; // weakPtr does not increase the reference count.
```

### Summary

`std::shared_ptr` provides a powerful mechanism for shared ownership of
dynamically allocated resources, automatically managing the lifetime of the
resource through reference counting. It supports copying and moving, allowing
flexible ownership semantics while ensuring that resources are properly cleaned
up when no longer needed. This makes `std::shared_ptr` an essential tool for
managing dynamic memory in C++ with safety and ease.

## Shared Widget - Example for using shared pointer

To demonstrate the use of `std::shared_ptr` in functions, including passing it
to and returning it from functions, let's work with a simple example. We'll
define a class `Widget` and functions that create a `Widget` instance, modify
it, and use it in various ways. This will showcase how `std::shared_ptr` enables
shared ownership and safe memory management across function calls.

### Step 1: Define a `Widget` Class

First, we define a simple `Widget` class:

```cpp
#include <iostream>
#include <memory>

class Widget {
public:
    int data;
    Widget(int data) : data(data) {}
    void display() const { std::cout << "Widget data: " << data << std::endl; }
};
```

### Step 2: Function to Create a `Widget`

This function creates a `Widget` and returns a `std::shared_ptr` to it:

```cpp
std::shared_ptr<Widget> createWidget(int data) {
    return std::make_shared<Widget>(data);
}
```

### Step 3: Function to Modify a `Widget`

This function accepts a `std::shared_ptr<Widget>` and modifies the `Widget` it
points to:

```cpp
void modifyWidget(std::shared_ptr<Widget> widget, int newData) {
    widget->data = newData;
}
```

### Step 4: Function to Use a `Widget`

This function demonstrates using a `Widget` without modifying ownership
semantics:

```cpp
void useWidget(const std::shared_ptr<Widget>& widget) {
    widget->display();
}
```

### Step 5: Main Function to Demonstrate Usage

Here's how you can use these functions together:

```cpp
int main() {
    // Create a Widget instance
    std::shared_ptr<Widget> myWidget = createWidget(10);
    useWidget(myWidget); // Use the widget

    // Modify the widget
    modifyWidget(myWidget, 20);
    useWidget(myWidget); // Use the widget again to see the updated data

    // Create another widget and demonstrate shared ownership
    auto anotherWidget = myWidget; // Both myWidget and anotherWidget share ownership
    useWidget(anotherWidget); // Use the second shared pointer

    std::cout << "Use count: " << myWidget.use_count() << std::endl; // Display the use count

    return 0;
}
```

### Explanation

1. **createWidget**: Creates a `Widget` object and returns a
   `std::shared_ptr<Widget>` to it. This `std::shared_ptr` manages the lifetime
   of the `Widget` instance.

2. **modifyWidget**: Demonstrates passing a `std::shared_ptr<Widget>` to a
   function to modify the object it points to. Since `modifyWidget` receives a
   copy of the `std::shared_ptr`, the reference count is temporarily incremented
   during the function call, ensuring the `Widget` remains managed and won't be
   destroyed even if other owners release it during this operation.

3. **useWidget**: Takes a `std::shared_ptr<Widget>` by const reference to use
   the `Widget` without affecting its reference count. This is efficient for
   read-only operations where ownership and lifetime management aren't altered.

4. **Main Function**: Creates a `Widget` managed by a `std::shared_ptr`,
   modifies it, and demonstrates shared ownership by copying the
   `std::shared_ptr`. The use count reflects the number of `std::shared_ptr`
   instances managing the same object.

This example illustrates the flexibility and safety of using `std::shared_ptr`
for shared ownership and dynamic memory management in C++.

Given the provided main function and the definitions of `createWidget`,
`modifyWidget`, and `useWidget`, here's what you can expect as the output when
running the program:

1. Initially, a `Widget` instance is created with `data = 10` via the
   `createWidget` function, and a `std::shared_ptr<Widget>` pointing to it is
   returned and stored in `myWidget`.

2. The `useWidget` function is called with `myWidget`, which displays the
   initial state of the `Widget`'s data:

   ```
   Widget data: 10
   ```

3. The `Widget`'s data is then modified to `20` by calling
   `modifyWidget(myWidget, 20)`.

4. The `useWidget` function is called again with `myWidget`, now displaying the
   updated data:

   ```
   Widget data: 20
   ```

5. The `myWidget` `std::shared_ptr` is copied to `anotherWidget`, demonstrating
   shared ownership. Since both `myWidget` and `anotherWidget` share ownership
   of the same `Widget` instance, the reference count increases to 2.

6. The `useWidget` function is called with `anotherWidget`, which points to the
   same `Widget` as `myWidget`, and so it displays the same updated data:

   ```
   Widget data: 20
   ```

7. Finally, the program prints the use count of `myWidget`, which is `2` because
   there are two `std::shared_ptr<Widget>` instances (`myWidget` and
   `anotherWidget`) sharing ownership of the same `Widget` object:

   ```
   Use count: 2
   ```

So, the expected output of the main function is:

```
Widget data: 10
Widget data: 20
Widget data: 20
Use count: 2
```

This sequence demonstrates creating a shared object, modifying it through one
owner, sharing ownership, and observing the effects of these operations across
multiple shared pointer instances.

## Understanding passsing to a function several times as a references and as value

Sure, let's dive into a straightforward C++ example involving a
`std::shared_ptr` of a primitive type (e.g., `int`). We will create a function
that adds two values: one from the shared pointer and another passed directly to
the function. We'll demonstrate how to pass the shared pointer both by reference
and by value.

### Example Setup

First, let's include the necessary header and declare our function for adding
values:

```cpp
#include <iostream>
#include <memory>

// Function to add a value to the value pointed to by a shared_ptr<int>
void addToValue(std::shared_ptr<int> ptr, int addValue) {
    *ptr += addValue;
}

// Function to add a value to the value pointed to by a shared_ptr<int>, passed by reference
void addToValueRef(std::shared_ptr<int>& ptr, int addValue) {
    *ptr += addValue;
}
```

### Passing `std::shared_ptr` by Value

Here, we'll create a `std::shared_ptr<int>`, pass it to `addToValue` (which
takes the shared pointer by value), and observe the effect.

```cpp
int main() {
    auto ptr = std::make_shared<int>(10); // Create a shared_ptr pointing to int with value 10
    std::cout << "Original value: " << *ptr << std::endl;

    addToValue(ptr, 5); // Pass by value
    std::cout << "After addToValue (pass by value): " << *ptr << std::endl;

    return 0;
}
```

### Passing `std::shared_ptr` by Reference

Now, we'll use the same `ptr` and pass it to `addToValueRef` (which takes the
shared pointer by reference) to see the difference.

```cpp
int main() {
    // Assuming the previous setup from the main function
    addToValueRef(ptr, 5); // Pass by reference
    std::cout << "After addToValueRef (pass by reference): " << *ptr << std::endl;

    return 0;
}
```

### Key Points:

- In both cases, the `std::shared_ptr` successfully adds the value to the
  pointed-to integer. The difference lies in the reference count manipulation
  and copy overhead:
  - **Pass by Value**: The shared pointer's reference count is incremented
    when passed to the function, and decremented once the function scope ends.
    This incurs a slight overhead due to the copy operation but ensures the
    lifetime management of the pointed-to object is correctly handled.
  - **Pass by Reference**: The reference count remains unchanged. This
    approach is more efficient because it avoids the copy overhead, but it
    offers the same functionality in terms of modifying the pointed-to value.

In practice, choosing between these two methods depends on your specific
requirements for efficiency and how you intend to manage the lifetime of shared
resources.

## Same Example with three calls

Sure, I'll extend the previous example to include three calls for passing the
`std::shared_ptr` by reference and five calls for passing it by value, along
with printing the reference count after each set of operations.

### Extended Example with Multiple Calls

```cpp
#include <iostream>
#include <memory>

void addToValue(std::shared_ptr<int> ptr, int addValue) {
    *ptr += addValue;
    // Print the current reference count using use_count()
    std::cout << "Current ref count (by value): " << ptr.use_count() << std::endl;
}

void addToValueRef(std::shared_ptr<int>& ptr, int addValue) {
    *ptr += addValue;
    // Reference count is not directly affected by this function; it's shown outside.
}

int main() {
    auto ptr = std::make_shared<int>(10); // Create a shared_ptr pointing to int with value 10
    std::cout << "Original value: " << *ptr << std::endl;

    // Pass by value 5 times
    for (int i = 0; i < 5; ++i) {
        addToValue(ptr, 5); // This will also print the ref count (which will always be 1 here)
    }
    std::cout << "After addToValue (pass by value) 5 times: " << *ptr << std::endl;
    std::cout << "Final ref count (after pass by value): " << ptr.use_count() << std::endl;

    // Pass by reference 3 times
    for (int i = 0; i < 3; ++i) {
        addToValueRef(ptr, 5);
        // Print the current reference count after each call
        std::cout << "Current ref count (by reference): " << ptr.use_count() << std::endl;
    }
    std::cout << "After addToValueRef (pass by reference) 3 times: " << *ptr << std::endl;
    std::cout << "Final ref count (after pass by reference): " << ptr.use_count() << std::endl;

    return 0;
}
```

### Explanation:

- **Pass by Value**: Each call to `addToValue` creates a temporary copy of the
  shared pointer, which increases the reference count internally within the
  function. However, since this temporary shared pointer is destroyed at the end
  of each function call, the reference count you see printed inside the function
  will always be 2 (1 for the original `ptr` and 1 for the copy within the
  function scope). The count returns to 1 outside the function scope.
- **Pass by Reference**: The `addToValueRef` function modifies the original
  shared pointer without creating a copy, so the reference count remains
  constant throughout these calls. The calls to `addToValueRef` do not affect
  the reference count, which should consistently print as 1.

This example illustrates how passing a `std::shared_ptr` by value vs. by
reference affects the reference count and, implicitly, the management of the
shared object's lifetime. Note that in real scenarios, passing by reference is
more efficient when you don't need to increase the object's lifetime beyond the
caller's scope.

## Reference count when it get increased?

So when the count will increase? When there is a copy? Demonstrate all scenarios
that increase the count of the shared smart pointer? Yes, the count of a
`std::shared_ptr` increases when it is copied. Each copy of a `std::shared_ptr`
shares ownership of the object, and the internal reference count tracks how many
`std::shared_ptr` instances are currently owning the object. The count will
increase in several scenarios, which I'll illustrate with examples.

### 1. Direct Copy

When you directly copy a `std::shared_ptr`, the reference count is incremented
to reflect the new owner of the shared object.

```cpp
auto ptr1 = std::make_shared<int>(10); // ref count = 1
auto ptr2 = ptr1; // ref count = 2
```

### 2. Passing by Value to a Function

Passing a `std::shared_ptr` by value to a function creates a temporary copy for
the duration of the function call, increasing the reference count for that
duration.

```cpp
void useSharedPtr(std::shared_ptr<int> ptr) {
    // Inside this function, ptr is a copy, so the ref count is increased.
}

auto ptr = std::make_shared<int>(10); // ref count = 1
useSharedPtr(ptr); // ref count increases to 2 inside useSharedPtr
// After useSharedPtr returns, the ref count goes back to 1.
```

### 3. Storing in a Container

Storing a `std::shared_ptr` in a container such as `std::vector` increases the
reference count because the container now owns a copy.

```cpp
std::vector<std::shared_ptr<int>> vec;
auto ptr = std::make_shared<int>(10); // ref count = 1
vec.push_back(ptr); // ref count = 2
```

### 4. Assigning to Another `std::shared_ptr`

Assigning an existing `std::shared_ptr` to another `std::shared_ptr` variable
increases the count as both will share ownership of the object.

```cpp
auto ptr1 = std::make_shared<int>(10); // ref count = 1
std::shared_ptr<int> ptr2;
ptr2 = ptr1; // ref count = 2
```

### 5. Capturing in a Lambda

Capturing a `std::shared_ptr` by value in a lambda function increases the
reference count because the lambda now holds a copy of the `std::shared_ptr`.

```cpp
auto ptr = std::make_shared<int>(10); // ref count = 1
auto lambda = [ptr]() { /* use ptr here */ }; // ref count = 2
```

### Demonstration

Let's demonstrate some of these scenarios with a simple example that shows the
reference count changes:

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

int main() {
    auto ptr = std::make_shared<int>(10); // ref count = 1
    std::cout << "Initial ref count: " << ptr.use_count() << std::endl;

    auto ptrCopy = ptr; // ref count = 2
    std::cout << "After copy: " << ptr.use_count() << std::endl;

    std::vector<std::shared_ptr<int>> vec;
    vec.push_back(ptr); // ref count = 3
    std::cout << "After storing in vector: " << ptr.use_count() << std::endl;

    // Lambda capturing ptr by value
    auto lambda = [ptr]() {}; // ref count = 4
    std::cout << "After capturing in lambda: " << ptr.use_count() << std::endl;

    // Clean up for clarity
    lambda = {}; // Clears the lambda, ref count should decrease
    vec.clear(); // Clears the vector, ref count should decrease
    ptrCopy = nullptr; // Clears the copy, ref count should decrease
    std::cout << "Final ref count (after cleanup): " << ptr.use_count() << std::endl;

    return 0;
}
```

This code sequentially demonstrates how the reference count increases as
`std::shared_ptr` is copied in various ways and then decreases as each copy is
removed or goes out of scope.

## Why we need the shared pointer - Insight

The necessity for `std::shared_ptr` in C++ arises primarily from the need to
manage dynamic memory safely and efficiently, especially in complex programs
where multiple parts of the code need to own or manage the lifetime of an
object. `std::shared_ptr` automates memory management, reduces the likelihood of
memory leaks, and handles the case where an object needs multiple owners.

### Case Where `std::shared_ptr` Is Needed

Consider a scenario in a graphical application where multiple widgets on the
screen need to access and possibly modify a shared configuration object. This
configuration object is dynamically allocated to allow for runtime determination
of its properties. Without `std::shared_ptr`, managing the lifetime of this
configuration object becomes complex and error-prone, especially if these
widgets can be created and destroyed at different times, potentially leaving the
configuration object dangling if not correctly deleted, or worse, deleted while
still in use.

### Example Without `std::shared_ptr`

Let's illustrate the scenario without using `std::shared_ptr`:

```cpp
class Configuration {
public:
    int brightness;
    // Other configuration properties
};

class Widget {
    Configuration* config;

public:
    Widget(Configuration* config) : config(config) {}
    void adjustBrightness(int value) {
        config->brightness = value;
    }
    // Destructor, other member functions...
};

// Application setup
Configuration* config = new Configuration{50}; // Initial brightness
Widget* widgetA = new Widget(config);
Widget* widgetB = new Widget(config);

// Use widgets...

// Cleanup
delete widgetA;
delete widgetB;
delete config; // Must ensure this is the last delete
```

In this non-`std::shared_ptr` version, you must manually manage the
`Configuration` object's memory, ensuring it's deleted after all widgets are
done using it. This approach is prone to errors, such as double deletion,
forgetting to delete, or use-after-free bugs.

### Example With `std::shared_ptr`

Now, let's refactor the example to use `std::shared_ptr`:

```cpp
#include <memory>

class Configuration {
public:
    int brightness;
    // Other configuration properties
};

class Widget {
    std::shared_ptr<Configuration> config;

public:
    Widget(std::shared_ptr<Configuration> config) : config(config) {}
    void adjustBrightness(int value) {
        config->brightness = value;
    }
    // Destructor is not needed; shared_ptr handles memory
};

// Application setup
auto config = std::make_shared<Configuration>();
config->brightness = 50; // Initial brightness
auto widgetA = std::make_shared<Widget>(config);
auto widgetB = std::make_shared<Widget>(config);

// Use widgets...

// Cleanup is automatic; shared_ptrs will properly manage the lifetime of Configuration and Widget objects
```

### Advantages of Using `std::shared_ptr`:

1. **Automatic Memory Management**: `std::shared_ptr` automatically deletes the
   managed object when the last `std::shared_ptr` owning it is destroyed or
   reset. This greatly reduces the risk of memory leaks.
2. **Shared Ownership**: Multiple `std::shared_ptr` instances can own the same
   object, making it ideal for use cases where an object's lifetime needs to be
   managed across multiple parts of a program.
3. **Safe Access**: It provides safe access to the object, even in concurrent
   environments, with additional utilities like `std::weak_ptr` to help manage
   cases where circular references might otherwise lead to memory leaks.

The transition from manual memory management to using `std::shared_ptr`
simplifies the code, making it more robust against common memory management
errors, thus illustrating the need and effectiveness of `std::shared_ptr` in C++
for managing shared resources.

## Multiple Owners for same object

To illustrate the concept of multiple owners sharing the same resource using
`std::shared_ptr`, let's create an example where multiple entities (owners) need
access to a shared resource. In this scenario, we'll simulate a small system
where several "User" objects share access to a "Document" object. Each user can
make modifications to the document, and the document should only be deleted when
no users are referencing it anymore.

### Example with Multiple Owners Sharing a `Document` Resource

```cpp
#include <iostream>
#include <memory>
#include <vector>

// A simple Document class
class Document {
public:
    std::string content;
    Document(const std::string& initialContent) : content(initialContent) {}
    void append(const std::string& newText) {
        content += newText;
    }
};

// User class that has access to a shared Document
class User {
    std::shared_ptr<Document> docPtr;
public:
    User(std::shared_ptr<Document> doc) : docPtr(doc) {}
    void edit(const std::string& addition) {
        docPtr->append(addition);
    }
    void view() const {
        std::cout << "Document content: " << docPtr->content << std::endl;
    }
};

int main() {
    // Create a shared Document
    auto sharedDoc = std::make_shared<Document>("Initial content. ");

    // Create users that share the same Document
    User alice(sharedDoc), bob(sharedDoc);

    alice.edit("Alice's addition. ");
    bob.edit("Bob's contribution. ");

    // Both users can view the updated document
    alice.view(); // Shows content including both Alice's and Bob's additions
    bob.view();   // Shows the same content as Alice views

    // The Document is automatically deleted when main exits and sharedDoc, Alice, and Bob's shared_ptr's are destroyed
    return 0;
}
```

### Explanation

- The `Document` class represents a simple document that can have text appended
  to it. It has a `content` member that stores the document's text.
- The `User` class represents a user that can edit (append text to) and view the
  document. Each user has a `std::shared_ptr<Document>` to the shared document,
  allowing multiple users to own the same document.
- In `main`, we create a shared `Document` instance and then create two `User`
  instances, `alice` and `bob`, both of which share the `Document`. This
  demonstrates shared ownership because both users have access to and modify the
  same `Document` instance.
- When `alice` and `bob` edit the document, they are modifying the same
  underlying `Document` object. This is evident when both users view the
  document and see the same content, including both their additions.
- The document's memory is managed automatically. It will only be freed when
  both `alice` and `bob` (and any other owners, such as the original `sharedDoc`
  pointer in `main`) are destroyed or go out of scope, effectively making the
  reference count go to zero.

This example clearly demonstrates the utility of `std::shared_ptr` for
implementing shared ownership, where multiple entities need to access and manage
the lifecycle of a shared resource collaboratively.

## Shared Pointer Usages - Imporant

I know now that several inner scope is one of them, how about others?

Shared pointers (`std::shared_ptr`) are particularly useful in scenarios where
objects need to be shared across different parts of a program, ensuring
automatic and safe deletion when no longer in use. Here are some common
scenarios where `std::shared_ptr` is especially useful:

1. **Multiple Owners of Same Resource**: When more than one part of a program
   must own and manage the lifetime of an object.
2. **Returning Objects from Functions**: When you need to return dynamically
   allocated objects from functions without transferring exclusive ownership.
3. **Storing Shared Objects in Containers**: When you need to store objects in
   STL containers that are shared across different parts of the program.
4. **Implementing Graphs or Trees**: When creating data structures where nodes
   may be shared or owned by multiple elements.
5. **Circular References**: When dealing with objects that refer to each other,
   potentially creating circular references which can be resolved using
   `std::weak_ptr` in conjunction with `std::shared_ptr`.

Let's demonstrate each scenario with an example and discuss the usage:

### 1. Multiple Owners of Same Resource

```cpp
#include <memory>
#include <iostream>

class SharedResource {
public:
    void use() { std::cout << "Using shared resource\n"; }
};

void functionA(std::shared_ptr<SharedResource> res) {
    res->use();
    // res goes out of scope here, but the SharedResource is not deleted
}

void functionB(std::shared_ptr<SharedResource> res) {
    res->use();
    // res goes out of scope here, but the SharedResource is only deleted if this is the last reference
}

int main() {
    auto resource = std::make_shared<SharedResource>();
    functionA(resource);
    functionB(resource);
}
```

### 2. Returning Objects from Functions

```cpp
#include <memory>
#include <iostream>

std::shared_ptr<SharedResource> createResource() {
    return std::make_shared<SharedResource>();
}

int main() {
    auto resource = createResource();
    resource->use();
}
```

### 3. Storing Shared Objects in Containers

```cpp
#include <memory>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::shared_ptr<SharedResource>> resources;
    resources.push_back(std::make_shared<SharedResource>());
    resources.push_back(std::make_shared<SharedResource>());

    for (auto& res : resources) {
        res->use();
    }
}
```

### 4. Implementing Graphs or Trees

```cpp
#include <memory>
#include <vector>

class Node {
public:
    int value;
    std::vector<std::shared_ptr<Node>> children;

    Node(int val) : value(val) {}
    void addChild(std::shared_ptr<Node> child) {
        children.push_back(child);
    }
};

int main() {
    auto root = std::make_shared<Node>(0);
    auto child1 = std::make_shared<Node>(1);
    auto child2 = std::make_shared<Node>(2);

    root->addChild(child1);
    root->addChild(child2);
}
```

### 5. Circular References

```cpp
#include <memory>
#include <iostream>

class B; // Forward declaration

class A { public: std::shared_ptr<B> b; ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a; // Use std::weak_ptr to avoid circular reference
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b = b;
    b->a = a;

    // Even if they refer to each other, they'll be properly destroyed
}
```

In the last example, `std::weak_ptr` is used to break the circular reference,
demonstrating how `std::shared_ptr` and `std::weak_ptr` can be used together to
manage complex ownership relationships without causing memory leaks.

## Smart Shared Pointer - From Scratch

To create a bare minimum class similar to a shared pointer in C++, we can
implement a template class that manages a resource, with reference counting to
keep track of how many such pointers are pointing to the same resource. When the
last pointer goes out of scope, the resource will be freed. This example will be
simplified and may not include all the robustness and features of
`std::shared_ptr` but will illustrate the basic mechanism.

Below is an example implementation:

```cpp
#include <iostream>

template <typename T>
class MySharedPtr {
private:
    T* ptr; // Actual pointer to the resource
    unsigned int* count; // Reference count

public:
    // Constructor
    explicit MySharedPtr(T* p = nullptr) : ptr(p), count(new unsigned int(1)) {
        std::cout << "Creating resource. Ref count is " << *count << std::endl;
    }

    // Copy Constructor
    MySharedPtr(const MySharedPtr<T>& sp) : ptr(sp.ptr), count(sp.count) {
        (*count)++;
        std::cout << "Copying resource. Ref count is " << *count << std::endl;
    }

    // Destructor
    ~MySharedPtr() {
        (*count)--;
        std::cout << "Deleting or decrementing. Ref count is " << *count << std::endl;
        if (*count == 0) {
            delete ptr;
            delete count;
            std::cout << "Resource and count fully deleted." << std::endl;
        }
    }

    // Overload dereference operator
    T& operator*() const {
        return *ptr;
    }

    // Overload arrow operator
    T* operator->() const {
        return ptr;
    }

    // Assignment operator
    MySharedPtr<T>& operator=(const MySharedPtr<T>& sp) {
        if (this != &sp) { // Avoid self-assignment
            if (--(*count) == 0) { // If no more references, delete the resource
                delete ptr;
                delete count;
            }
            ptr = sp.ptr;
            count = sp.count;
            (*count)++;
        }
        return *this;
    }
};

int main() {
    {
        MySharedPtr<int> sp1(new int(10));
        {
            MySharedPtr<int> sp2 = sp1;
            {
                MySharedPtr<int> sp3(sp2);
                std::cout << "In inner scope. Value is " << *sp3 << std::endl;
            }
            std::cout << "Exiting inner scope 3." << std::endl;
        }
        std::cout << "Exiting inner scope 2. Value is " << *sp1 << std::endl;
    }
    std::cout << "Exiting inner scope 1, all shared pointers should be destroyed." << std::endl;

    return 0;
}
```

This class, `MySharedPtr`, implements the basic functionality of a shared
pointer:

- Manages a resource through a raw pointer.
- Uses an integer to keep track of how many `MySharedPtr` instances share the
  same resource.
- Copies and assignments increase the reference count.
- Destructor decrements the reference count and deletes the resource if the
  count reaches zero.

In the `main` function, `sp1` is created and then copied to `sp2` and `sp3` in
nested scopes. As each `MySharedPtr` instance goes out of scope, the destructor
is called, decrementing the reference count each time. When `sp1`, the last
shared pointer to the resource, goes out of scope, the reference count becomes
zero, and the resource is freed.

### Expected results

Given the implementation of `MySharedPtr`, let's walk through the expected
console output when running the provided `main` function. The output reflects
how the reference count is managed as `MySharedPtr` instances are copied and
destroyed:

```
Creating resource. Ref count is 1
Copying resource. Ref count is 2
Copying resource. Ref count is 3
In inner scope. Value is 10
Deleting or decrementing. Ref count is 2
Exiting inner scope 3.
Deleting or decrementing. Ref count is 1
Exiting inner scope 2. Value is 10
Deleting or decrementing. Ref count is 0
Resource and count fully deleted.
Exiting inner scope 1, all shared pointers should be destroyed.
```

Here's the step-by-step explanation of the output:

1. **Creating resource. Ref count is 1**: The first `MySharedPtr` (`sp1`) is
   created, pointing to an integer with the value `10`. The reference count is
   initialized to `1`.

2. **Copying resource. Ref count is 2**: `sp1` is copied to `sp2`, which
   increments the reference count to `2`.

3. **Copying resource. Ref count is 3**: `sp2` is copied to `sp3`, further
   incrementing the reference count to `3`.

4. **In inner scope. Value is 10**: Inside the innermost scope, the value
   pointed to by `sp3` (which is `10`) is printed.

5. **Deleting or decrementing. Ref count is 2**: As `sp3` goes out of scope, its
   destructor is called. This decrements the reference count to `2`, but the
   resource is not yet deleted since there are still two references (`sp1` and
   `sp2`) alive.

6. **Exiting inner scope 3.**

7. **Deleting or decrementing. Ref count is 1**: `sp2` goes out of scope next,
   triggering its destructor. The reference count is decremented to `1`.

8. **Exiting inner scope 2. Value is 10**: Shows that `sp1` is still valid and
   points to the integer value `10`.

9. **Deleting or decrementing. Ref count is 0**: Finally, `sp1` goes out of
   scope. Its destructor decrements the reference count to `0`, indicating no
   more references to the resource exist.

10. **Resource and count fully deleted.**: Since the reference count has reached
    `0`, the resource (`int` allocated on the heap) and the reference count
    itself (also dynamically allocated) are deleted.

11. **Exiting inner scope 1, all shared pointers should be destroyed.**: This
    message confirms that the program is exiting the outermost scope, and all
    instances of `MySharedPtr` have been destroyed.

This output demonstrates how the custom shared pointer class manages the
resource's lifetime through reference counting, ensuring it is correctly freed
when no longer needed.

## Similar Class but without using Template

To simplify the example and make it more understandable, we'll create a similar
class to the previous `MySharedPtr` but without using templates. This class will
manage a specific type of resource, for example, an `int`. This way, the class
becomes specific to `int` pointers, removing the template complexity.

Here's the implementation of a simplified shared pointer class for `int` types:

```cpp
#include <iostream>

class MyIntSharedPtr {
private:
    int* ptr; // Actual pointer to the resource
    unsigned int* count; // Reference count

public:
    // Constructor
    explicit MyIntSharedPtr(int* p = nullptr) : ptr(p), count(new unsigned int(1)) {
        std::cout << "Creating resource. Ref count is " << *count << std::endl;
    }

    // Copy Constructor
    MyIntSharedPtr(const MyIntSharedPtr& sp) : ptr(sp.ptr), count(sp.count) {
        (*count)++;
        std::cout << "Copying resource. Ref count is " << *count << std::endl;
    }

    // Destructor
    ~MyIntSharedPtr() {
        (*count)--;
        std::cout << "Deleting or decrementing. Ref count is " << *count << std::endl;
        if (*count == 0) {
            delete ptr;
            delete count;
            std::cout << "Resource and count fully deleted." << std::endl;
        }
    }

    // Overload dereference operator
    int& operator*() const {
        return *ptr;
    }

    // Overload arrow operator is not applicable for int type as it's not a class or struct

    // Assignment operator
    MyIntSharedPtr& operator=(const MyIntSharedPtr& sp) {
        if (this != &sp) { // Avoid self-assignment
            if (--(*count) == 0) { // If no more references, delete the resource
                delete ptr;
                delete count;
            }
            ptr = sp.ptr;
            count = sp.count;
            (*count)++;
        }
        return *this;
    }
};

int main() {
    {
        MyIntSharedPtr sp1(new int(10));
        {
            MyIntSharedPtr sp2 = sp1;
            {
                MyIntSharedPtr sp3(sp2);
                std::cout << "In inner scope. Value is " << *sp3 << std::endl;
            }
            std::cout << "Exiting inner scope 3." << std::endl;
        }
        std::cout << "Exiting inner scope 2. Value is " << *sp1 << std::endl;
    }
    std::cout << "Exiting inner scope 1, all shared pointers should be destroyed." << std::endl;

    return 0;
}
```

The expected output for this program will be similar to the templated version,
but now specifically handling `int` types:

```
Creating resource. Ref count is 1
Copying resource. Ref count is 2
Copying resource. Ref count is 3
In inner scope. Value is 10
Deleting or decrementing. Ref count is 2
Exiting inner scope 3.
Deleting or decrementing. Ref count is 1
Exiting inner scope 2. Value is 10
Deleting or decrementing. Ref count is 0
Resource and count fully deleted.
Exiting inner scope 1, all shared pointers should be destroyed.
```

This output and class behavior follow the same logic as the template version,
demonstrating how a class can manage a resource (in this case, an `int`),
keeping track of how many instances share that resource and ensuring it's
deleted when the last shared pointer goes out of scope.

## Shared Smart Pointer - Handle CStyle Array

To create a class similar to the previous one but capable of managing a C-style
array, we need to adjust the destructor to use `delete[]` instead of `delete`,
as C-style arrays allocated with `new` require `delete[]` for deallocation. This
class will specifically manage arrays of `int`s.

Here's an implementation of a class designed to manage C-style arrays of `int`s:

```cpp
#include <iostream>

class MyIntArraySharedPtr {
private:
    int* ptr; // Actual pointer to the resource (array)
    unsigned int* count; // Reference count

public:
    // Constructor
    explicit MyIntArraySharedPtr(int* p = nullptr) : ptr(p), count(new unsigned int(1)) {
        std::cout << "Creating array resource. Ref count is " << *count << std::endl;
    }

    // Copy Constructor
    MyIntArraySharedPtr(const MyIntArraySharedPtr& sp) : ptr(sp.ptr), count(sp.count) {
        (*count)++;
        std::cout << "Copying array resource. Ref count is " << *count << std::endl;
    }

    // Destructor
    ~MyIntArraySharedPtr() {
        (*count)--;
        std::cout << "Deleting or decrementing array. Ref count is " << *count << std::endl;
        if (*count == 0) {
            delete[] ptr; // Use delete[] for array deletion
            delete count;
            std::cout << "Array resource and count fully deleted." << std::endl;
        }
    }

    // Overload dereference operator is not directly applicable for arrays.
    // Instead, provide array access via an index operator if needed.
    int& operator[](int index) const {
        return ptr[index];
    }

    // Assignment operator
    MyIntArraySharedPtr& operator=(const MyIntArraySharedPtr& sp) {
        if (this != &sp) { // Avoid self-assignment
            if (--(*count) == 0) { // If no more references, delete the resource
                delete[] ptr;
                delete count;
            }
            ptr = sp.ptr;
            count = sp.count;
            (*count)++;
        }
        return *this;
    }
};

int main() {
    {
        MyIntArraySharedPtr sp1(new int[3]{10, 20, 30});
        {
            MyIntArraySharedPtr sp2 = sp1;
            {
                MyIntArraySharedPtr sp3(sp2);
                std::cout << "In inner scope. Values are " << sp3[0] << ", " << sp3[1] << ", " << sp3[2] << std::endl;
            }
            std::cout << "Exiting inner scope 3." << std::endl;
        }
        std::cout << "Exiting inner scope 2. Values are " << sp1[0] << ", " << sp1[1] << ", " << sp1[2] << std::endl;
    }
    std::cout << "Exiting inner scope 1, all shared pointers should be destroyed." << std::endl;

    return 0;
}
```

Expected output for this program, managing an array of `int`s:

```
Creating array resource. Ref count is 1
Copying array resource. Ref count is 2
Copying array resource. Ref count is 3
In inner scope. Values are 10, 20, 30
Exiting inner scope 3.
Deleting or decrementing array. Ref count is 2
Exiting inner scope 2. Values are 10, 20, 30
Deleting or decrementing array. Ref count is 1
Exiting inner scope 1, all shared pointers should be destroyed.
Deleting or decrementing array. Ref count is 0
Array resource and count fully deleted.
```

This version specifically handles C-style arrays by using `delete[]` in the
destructor to ensure proper deallocation of the array. The addition of the index
operator (`operator[]`) allows array elements to be accessed and modified,
mimicking the behavior of a C-style array while managing its lifetime and
sharing mechanism via reference counting.

## Demo - Practicle Example Using Shared Pointer

Shared pointers in C++ (`std::shared_ptr`) are a type of smart pointer that
maintain reference counting for shared ownership of objects. They are useful in
several scenarios, especially when it comes to dynamic memory management,
ensuring that memory is properly deallocated when it is no longer in use. Below
is a simple, practical example followed by a list of scenarios where shared
pointers are particularly beneficial.

### Practical Example

Consider a scenario where multiple parts of your program need to access and
modify a shared resource, such as a dynamically allocated object, and you want
to ensure that the resource is automatically freed when it is no longer needed
by anyone.

```cpp
#include <iostream>
#include <memory> // For std::shared_ptr

class Sample {
public:
    int data;
    Sample(int d) : data(d) { std::cout << "Sample Created\n"; }
    ~Sample() { std::cout << "Sample Destroyed\n"; }
    void print() const { std::cout << "Data: " << data << std::endl; }
};

int main() {
    std::shared_ptr<Sample> ptr1;
    {
        std::shared_ptr<Sample> ptr2 = std::make_shared<Sample>(10);
        ptr1 = ptr2;
        std::cout << "Inside the scope, ptr1 and ptr2 share the Sample\n";
        ptr2->print();
    } // ptr2 goes out of scope here, but the Sample object is not destroyed because ptr1 is still pointing to it.
    std::cout << "Outside the scope, only ptr1 has the Sample\n";
    ptr1->print();
} // ptr1 goes out of scope here, and the Sample object is automatically destroyed.

// Expected output:
// Sample Created
// Inside the scope, ptr1 and ptr2 share the Sample
// Data: 10
// Outside the scope, only ptr1 has the Sample
// Data: 10
// Sample Destroyed
```

In this example, `Sample` objects are managed by `std::shared_ptr`, which takes
care of allocating and deallocating memory automatically. When `ptr2` goes out
of scope, the `Sample` object is not destroyed because `ptr1` is still pointing
to it. Only when `ptr1` also goes out of scope is the `Sample` object destroyed.

### Scenarios for Using `std::shared_ptr`

1. **Shared Ownership**: When an object's lifetime needs to be managed across
   multiple parts of a program without a clear single owner.

2. **Circular References**: In cases of circular references, where two objects
   refer to each other, `std::shared_ptr` together with `std::weak_ptr` can
   prevent memory leaks.

3. **Polymorphism**: When working with inheritance hierarchies, shared pointers
   can be used to ensure proper destruction of derived objects through base
   class pointers.

4. **Thread Safety**: When objects are accessed from multiple threads,
   `std::shared_ptr` can be safely copied across threads (though the object
   itself must be thread-safe for mutations).

5. **Returning Objects from Functions**: To avoid the cost and complexity of
   deep copying objects when returning them from functions, shared pointers can
   be used to efficiently share ownership of an existing object.

6. **Storing Objects in Containers**: When storing objects in STL containers
   that require shared access or when the lifetime of objects should extend
   beyond the scope in which they were created.

7. **Dynamic Resource Allocation**: For managing dynamic resources such as file
   handles, network connections, or other system resources that require explicit
   release.

8. **Factory Functions**: When objects are created inside factory functions and
   you want to ensure they are cleaned up properly without requiring the client
   code to manage memory explicitly.

Shared pointers provide a balance between automatic memory management and
flexibility, reducing the risks of memory leaks and dangling pointers. However,
it's important to use them judanetwork connectionsly, as unnecessary use of
`std::shared_ptr` can lead to performance overheads due to the reference
counting mechanism.

## Demo - Return an object form a function

Using a `std::shared_ptr` to return objects from functions is a common practice
in modern C++ to ensure efficient memory management and avoid memory leaks,
especially when the size or lifetime of the objects makes them unsuitable for
return by value. Here is a simple example that demonstrates how to use
`std::shared_ptr` for returning an object from a function:

```cpp
#include <iostream>
#include <memory> // Include for std::shared_ptr

class Widget {
public:
    Widget() { std::cout << "Widget created\n"; }
    ~Widget() { std::cout << "Widget destroyed\n"; }
    void display() const { std::cout << "Displaying Widget\n"; }
};

// Factory function that creates and returns a shared_ptr to a Widget
std::shared_ptr<Widget> createWidget() {
    return std::make_shared<Widget>();
}

int main() {
    std::shared_ptr<Widget> myWidget = createWidget();
    myWidget->display();
    // No need to delete myWidget; it will be automatically cleaned up when it goes out of scope.
    return 0;
}
```

### Explanation:

- **Class Definition**: The `Widget` class is a simple class that prints a
  message when it is created and destroyed, and has a `display` method that
  prints another message.

- **Factory Function (`createWidget`)**: This function creates a `Widget` object
  and returns a `std::shared_ptr<Widget>` pointing to it. The use of
  `std::make_shared<Widget>()` is a best practice for creating a shared pointer
  because it efficiently allocates memory for the `Widget` object and the
  reference count in a single operation.

- **Main Function**: The `main` function calls `createWidget` to obtain a
  `std::shared_ptr<Widget>` and then uses this pointer to call the `display`
  method on the `Widget`. The `std::shared_ptr` ensures that the `Widget` is
  automatically destroyed when `myWidget` goes out of scope, which is right at
  the end of the `main` function. This automatic management of the `Widget`'s
  lifetime makes it easy to avoid memory leaks without explicitly calling
  `delete`.

This example demonstrates how `std::shared_ptr` can simplify memory management
for dynamically allocated objects, especially when such objects are created
inside functions and returned to callers.

## Again - About Other usages of Shared Pointers

Let's create thorough examples to illustrate each of the mentioned scenarios
where `std::shared_ptr` can be particularly useful in C++.

### 1. Shared Ownership

Multiple parts of an application share ownership of an object.

```cpp
#include <iostream>
#include <memory>

class SharedResource {
public:
    void use() { std::cout << "Using shared resource\n"; }
};

void function1(std::shared_ptr<SharedResource> resource) {
    resource->use();
    // Resource is still available after function1 returns
}

void function2(std::shared_ptr<SharedResource> resource) {
    resource->use();
    // Resource is still available after function2 returns
}

int main() {
    auto resource = std::make_shared<SharedResource>();
    function1(resource);
    function2(resource);
}
```

### 2. Circular References (with `std::weak_ptr`)

Avoiding memory leaks in circular references.

```cpp
#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a; // Use std::weak_ptr to avoid circular reference
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->b = b;
    b->a = a;
}
```

### 3. Polymorphism

Using shared pointers with polymorphic types.

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Base {
public:
    virtual ~Base() { std::cout << "Base destroyed\n"; }
    virtual void doSomething() = 0;
};

class Derived : public Base {
public:
    void doSomething() override { std::cout << "Derived doing something\n"; }
    ~Derived() { std::cout << "Derived destroyed\n"; }
};

int main() {
    std::vector<std::shared_ptr<Base>> objects;
    objects.push_back(std::make_shared<Derived>());
    for (auto& obj : objects) {
        obj->doSomething();
    }
}
```

### 4. Thread Safety

Sharing an object across threads (simplified example, real multithreading
requires synchronization for object access).

```cpp
#include <iostream>
#include <memory>
#include <thread>

void useResource(std::shared_ptr<int> resource) {
    std::cout << "Using resource with value: " << *resource << std::endl;
}

int main() {
    auto resource = std::make_shared<int>(42);
    std::thread t1(useResource, resource);
    std::thread t2(useResource, resource);
    t1.join();
    t2.join();
}
```

### 5. Returning Objects from Functions

Factory function returning a shared pointer.

```cpp
std::shared_ptr<SharedResource> createSharedResource() {
    return std::make_shared<SharedResource>();
}
```

### 6. Storing Objects in Containers

Storing polymorphic objects in a container.

```cpp
std::vector<std::shared_ptr<Base>> vec;
vec.push_back(std::make_shared<Derived>());
```

### 7. Dynamic Resource Allocation

Managing dynamic resources such as file handles or network connections.

```cpp
#include <memory>
#include <fstream>

class FileWrapper {
    std::shared_ptr<std::fstream> file;
public:
    FileWrapper(const std::string& filename) :
        file(std::make_shared<std::fstream>(filename, std::fstream::out | std::fstream::app)) {}
    void write(const std::string& message) {
        if (file && file->is_open()) {
            *file << message << std::endl;
        }
    }
};
```

### 8. Factory Functions

Using shared pointers for objects created inside factory functions.

```cpp
class WidgetFactory {
public:
    static std::shared_ptr<Widget> createWidget() {
        return std::make_shared<Widget>();
    }
};
```

Each of these examples demonstrates a specific scenario where `std::shared_ptr`
is advantageous, from managing shared ownership and avoiding memory leaks in
circular references, to facilitating polymorphism, thread safety, object
storage, and dynamic resource management.

## Demo - Handling the previous example using - Unique Pointer

The specific code example provided could indeed use a `std::unique_ptr` instead
of a `std::shared_ptr` if the only consideration were the passing of the
resource to functions for transient use. The choice between `std::unique_ptr`
and `std::shared_ptr` often depends on the ownership semantics you want to
enforce in your application.

Here’s why `std::shared_ptr` might still be chosen in this scenario, and then
how you could adjust the example to use `std::unique_ptr` with an explanation of
when each is appropriate.

### Using `std::shared_ptr`

- **Shared Ownership**: The primary reason to use `std::shared_ptr` is when you
  want shared ownership of an object. Even if the functions `function1` and
  `function2` do not take permanent ownership, the use of `std::shared_ptr`
  implies that the resource could be owned by multiple owners at the same time.
  This is useful in scenarios where the object's lifetime should extend beyond
  the scope of a single owner and should be managed by all current stakeholders.

- **Flexibility for Future Changes**: Using `std::shared_ptr` may offer more
  flexibility if the design evolves to require shared ownership later, without
  significantly changing how the resource is passed around.

### Adjusting to Use `std::unique_ptr`

If you want to make it clear that there's a single owner of the resource at any
given time, you could use `std::unique_ptr` and pass references to the resource
to functions that temporarily use it:

```cpp
#include <iostream>
#include <memory>

class SharedResource {
public:
    void use() { std::cout << "Using shared resource\n"; }
};

void function1(SharedResource& resource) {
    resource.use();
    // Resource is still available after function1 returns
}

void function2(SharedResource& resource) {
    resource.use();
    // Resource is still available after function2 returns
}

int main() {
    auto resource = std::make_unique<SharedResource>();
    function1(*resource);
    function2(*resource);
}
```

### When to Use `std::unique_ptr` vs `std::shared_ptr`

- **`std::unique_ptr`**: Use it when you have a single owner for the resource at
  any point in time. It is more lightweight than `std::shared_ptr` because it
  doesn't involve reference counting. It's also useful for transferring
  ownership of a resource, thanks to its move semantics.

- **`std::shared_ptr`**: Choose this when an object needs to be shared by
  multiple owners, or when you need the object to have a longer lifetime than a
  single scope or owner. Remember that `std::shared_ptr` incurs a small overhead
  due to reference counting, especially in multi-threaded environments where
  atomic operations are required.

The initial example could indeed suggest an overuse of `std::shared_ptr` if true
shared ownership is not required. Using `std::unique_ptr` and passing references
or pointers to functions is a more efficient choice when you want to maintain
clear, singular ownership while still allowing other parts of your program
temporary access to the resource.

## Demo - Mandatory to use Shared Pointer

An example where it's mandatory to use `std::shared_ptr` is when you have an
object that must be accessed and potentially modified by multiple owners
throughout different parts of your program, and where the lifetime of the object
should be managed collectively by all of these owners. A common scenario is when
you have a shared resource in a collaborative system where multiple users or
components need to interact with the same object.

### Example: Collaborative Editing Application

Consider a simplified example of a collaborative editing application where
multiple editors can view and edit a shared document. The document needs to be
accessible as long as there is at least one editor interested in it. When the
last editor stops editing the document (i.e., the editor's object is destroyed),
the document should be automatically cleaned up.

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Document {
public:
    Document() { std::cout << "Document created\n"; }
    void edit(const std::string& change) { std::cout << "Editing document: " << change << std::endl; }
    ~Document() { std::cout << "Document destroyed\n"; }
};

class Editor {
    std::shared_ptr<Document> doc;
public:
    Editor(const std::shared_ptr<Document>& document) : doc(document) {}
    void editDocument(const std::string& change) {
        if (doc) {
            doc->edit(change);
        }
    }
};

int main() {
    auto sharedDoc = std::make_shared<Document>();
    Editor editor1(sharedDoc);
    Editor editor2(sharedDoc);

    editor1.editDocument("Editor1 made this change.");
    editor2.editDocument("Editor2 made another change.");

    // The Document will only be destroyed when both editor1 and editor2 are done with it.
    // In this case, at the end of the main function.
}
```

### Explanation

- **`Document` Class**: Represents the shared resource that needs to be edited.
  It's designed to be managed by `std::shared_ptr` to ensure its lifetime is
  extended across multiple editors.
- **`Editor` Class**: Represents a user editing the document. Each editor holds
  a `std::shared_ptr<Document>` to the shared document, ensuring they all share
  ownership of the document.
- **Lifetime Management**: The document is created at the start of `main()` and
  shared among `editor1` and `editor2` via `sharedDoc`. Both editors can make
  edits to the same document, demonstrating shared ownership and access. The
  document is automatically destroyed when `main()` ends, and with it, the last
  shared pointers (`editor1` and `editor2`'s `doc`) are destroyed, showing the
  automatic memory management capability of `std::shared_ptr`.

This example showcases the necessity of `std::shared_ptr` for scenarios
requiring multiple ownership, where an object's lifetime is dependent on the
collective scope of all its owners.

## Circular References Problem

Certainly! Circular references occur when two or more objects reference each
other directly or indirectly, creating a loop. This can lead to memory leaks if
not handled properly, especially when using `std::shared_ptr` for dynamic memory
management, as the reference count never drops to zero.

### Example of Circular References

Let's consider an example where two classes, `A` and `B`, reference each other:

```cpp
#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> bPtr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::shared_ptr<A> aPtr;
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->bPtr = b;
    b->aPtr = a;

    return 0;
}
```

In this scenario, `a` holds a `shared_ptr` to `b`, and `b` holds a `shared_ptr`
to `a`. When the `main` function exits, neither `A` nor `B` is destroyed because
each has a reference count of at least 1, leading to a memory leak.

### Solving Circular References with `std::weak_ptr`

To solve this issue, one of the references should be changed to `std::weak_ptr`,
which does not increase the reference count. This way, you can break the cycle
of references, allowing for proper resource cleanup. Here's how you can modify
the previous example:

```cpp
#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> bPtr;
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> aPtr; // Change to weak_ptr
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->bPtr = b;
    b->aPtr = a;

    return 0; // Now, both A and B will be properly destroyed.
}
```

In this revised version, `B` holds a `weak_ptr` to `A`. This means `B` can refer
to `A` without owning it, thus not affecting `A`'s reference count. When `main`
exits, `a` is destroyed because its reference count drops to zero (since `B`'s
reference is weak), and in turn, `b` is also destroyed because `A`'s destruction
removes the last reference to `B`.

This approach effectively prevents the memory leak that the circular reference
caused. It demonstrates the importance of understanding and correctly applying
smart pointers in C++ to manage dynamic memory safely and efficiently.

## More about Circular References

Circular references occur when two or more objects hold references to each
other, creating a cycle that can prevent automatic memory management mechanisms
like garbage collection or smart pointers from correctly freeing the memory,
potentially leading to memory leaks. Here's how you can handle circular
references using `std::weak_ptr` in C++ to prevent such leaks, followed by a
discussion on how it would be handled with raw pointers.

### Handling Circular References with `std::weak_ptr`

```cpp
#include <iostream>
#include <memory>

class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr; // A holds a shared_ptr to B
    ~A() { std::cout << "A destroyed\n"; }
};

class B {
public:
    std::weak_ptr<A> a_ptr; // B holds a weak_ptr to A to break the circular reference
    ~B() { std::cout << "B destroyed\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;

    // Without a weak_ptr, the shared ownership would prevent A and B from being freed.
}
```

In this example, `A` owns `B` through a `std::shared_ptr`, but `B` only holds a
`std::weak_ptr` back to `A`, preventing a strong circular reference. This setup
allows `A` to be automatically destroyed when its `std::shared_ptr` goes out of
scope, even though `B` has a link back to `A`, because `std::weak_ptr` does not
increase the reference count.

### Handling Circular References with Raw Pointers

With raw pointers, you manually manage memory, so you can still create a
circular reference but must ensure to break it yourself to prevent leaks.

```cpp
#include <iostream>

class B; // Forward declaration

class A {
public:
    B* b_ptr = nullptr; // A holds a raw pointer to B
    ~A() { std::cout << "A destroyed\n"; delete b_ptr; }
};

class B {
public:
    A* a_ptr = nullptr; // B holds a raw pointer back to A
    ~B() { std::cout << "B destroyed\n"; /* Do not delete a_ptr here to avoid double deletion */ }
};

int main() {
    A* a = new A();
    B* b = new B();

    a->b_ptr = b;
    b->a_ptr = a;

    delete a; // This deletes A and B, assuming A's destructor deletes B
    // No need to delete b, as it's already been deleted by A's destructor.
    // Be cautious to avoid double deletion or dangling pointers.
}
```

In the raw pointers scenario, you need to be very careful to avoid memory leaks
and ensure proper deletion of all dynamically allocated objects. This typically
involves manually deleting the created objects in the correct order and ensuring
no double deletions or dangling pointers occur. This example simplifies memory
management by only deleting `B` in `A`'s destructor, which requires careful
design to ensure `B` does not outlive `A`.

### Comparison and Best Practice

Using `std::weak_ptr` with `std::shared_ptr` for managing circular references is
safer and more automatic compared to using raw pointers. Smart pointers reduce
the risk of memory leaks and dangling pointers by automating memory management,
while raw pointers require careful, manual management and are prone to errors.

The raw pointer approach necessitates a clear understanding of ownership and
lifecycle of objects, manual memory deallocation, and can be error-prone due to
manual management. On the other hand, smart pointers like `std::shared_ptr` and
`std::weak_ptr` provide a higher-level abstraction that automatically manages
object lifetimes, making them a preferred choice in modern C++ for managing
complex object lifecycles and relationships.

## Demo - Shared Pointer Reference count decrease from 4 to 0

In C++, a shared pointer (`std::shared_ptr`) is a smart pointer that retains
shared ownership of an object through a pointer. Multiple `shared_ptr` instances
can own the same object, and the object is destroyed when the last remaining
`shared_ptr` owning it is destroyed or reset.

Let's create a hypothetical scenario with a class `Vec2d` where the reference
count of a `shared_ptr` to a `Vec2d` object decreases from 4 to 0, leading to
the object's destruction.

First, here's a simple definition of the `Vec2d` class:

```cpp
class Vec2d {
public:
    double x, y;
    Vec2d(double x, double y) : x(x), y(y) {}
    ~Vec2d() {
        std::cout << "Vec2d destroyed\n";
    }
};
```

Now, let's create a scenario where the reference count goes from 4 to 0:

1. **Creating the initial shared pointer:** We start by creating a `shared_ptr`
   to a `Vec2d` object. This is the first reference, so the count is 1.

   ```cpp
   auto v = std::make_shared<Vec2d>(1.0, 2.0);
   ```

2. **Increasing the reference count:** We create three more shared pointers that
   share ownership of the same `Vec2d` object, which brings the reference count
   to 4.

   ```cpp
   std::shared_ptr<Vec2d> v1 = v; // Count = 2
   std::shared_ptr<Vec2d> v2 = v; // Count = 3
   std::shared_ptr<Vec2d> v3 = v; // Count = 4
   ```

3. **Decreasing the reference count to 0:** We then reset or allow these
   pointers to go out of scope, decreasing the reference count back down to 0,
   which triggers the destruction of the `Vec2d` object.

   a. **First decrease:** We explicitly reset one of the pointers.

   ```cpp
   v1.reset(); // Count decreases to 3
   ```

   b. **Second decrease:** Another pointer goes out of scope or is reset.

   ```cpp
   v2.reset(); // Count decreases to 2
   ```

   c. **Third decrease:** The third shared pointer is reset.

   ```cpp
   v3.reset(); // Count decreases to 1
   ```

   d. **Final decrease:** Finally, the original shared pointer is reset or goes
   out of scope.

   ```cpp
   v.reset(); // Count decreases to 0, Vec2d is destroyed
   ```

Alternatively, the decrease could also occur by letting the pointers go out of
scope naturally, such as by exiting a block of code where they are defined. Once
the reference count hits 0, the `Vec2d` object is destroyed, and its destructor
is called, signaling the memory has been freed.

## Without using reset()

The code here is actually very clear in illustrating the concept of shared
pointers as it demonstrates how a scope function and pointer will be created
locally, and their reference count will be decremented (indicating destruction)
which refers to the object. Once the pointer (acting as a reference) reaches the
end of the local scope, it will also be destroyed. Finally, when all references
(shared pointers) that we have created referencing the same object, the last one
of them will be responsible for freeing (deallocating) the heap-allocated object
that all of them were pointing to.

Certainly! In the following C++ code example, we'll demonstrate how the
reference count of a `std::shared_ptr` decreases from 4 to 0 without explicitly
calling `reset()`. Instead, we'll let the shared pointers go out of scope, which
will naturally decrease the reference count and eventually lead to the
destruction of the managed object. We'll use the `Vec2d` class and print
statements to observe the changes in reference count and the destruction of the
object.

```cpp
#include <iostream>
#include <memory>

class Vec2d {
public:
    double x, y;
    Vec2d(double x, double y) : x(x), y(y) {
        std::cout << "Vec2d created\n";
    }
    ~Vec2d() {
        std::cout << "Vec2d destroyed\n";
    }
};

void createAdditionalSharedPointers(std::shared_ptr<Vec2d> v) {
    // Creating three more shared pointers. This increases the reference count to 4.
    std::shared_ptr<Vec2d> v1 = v;
    std::shared_ptr<Vec2d> v2 = v;
    std::shared_ptr<Vec2d> v3 = v;

    std::cout << "Inside function, reference count = " << v.use_count() << std::endl;
    // v1, v2, and v3 will be destroyed here as they go out of scope, reducing the reference count.
}

int main() {
    // Creating the initial shared pointer with a reference count of 1.
    auto v = std::make_shared<Vec2d>(1.0, 2.0);
    std::cout << "Initially, reference count = " << v.use_count() << std::endl;

    createAdditionalSharedPointers(v);
    // After returning from the function, the reference count is reduced as v1, v2, and v3 are out of scope.
    std::cout << "After function, reference count = " << v.use_count() << std::endl;

    // v will be destroyed here as it goes out of scope, reducing the reference count to 0 and destroying Vec2d.
    return 0;
}
```

Here's what happens in this program:

1. A `Vec2d` object is created and managed by a shared pointer `v`. This prints
   "Vec2d created" and sets the reference count to 1.
2. The `createAdditionalSharedPointers` function is called with `v` as an
   argument. Inside this function, three more shared pointers (`v1`, `v2`, `v3`)
   are created, all sharing ownership of the same `Vec2d` object. This increases
   the reference count to 4.
3. The function prints the current reference count (which should be 4),
   demonstrating that the reference count increased inside the function.
4. As the function ends, `v1`, `v2`, and `v3` go out of scope and are destroyed,
   which decreases the reference count each time they are destroyed. The output
   will not explicitly show these decreases, but you'll know it happened because
   the reference count will be 1 again once we exit the function.
5. Finally, the `main` function ends, and `v` goes out of scope. This reduces
   the reference count to 0, and the `Vec2d` object is destroyed, printing
   "Vec2d destroyed".

This code effectively demonstrates how shared pointers manage ownership and how
the reference count influences the lifetime of the managed object.

## Again, List all Scenarios which the reference count is droped (decreases)

The reference count of a `std::shared_ptr` in C++ decreases in several specific
scenarios, each involving the reduction of ownership or the destruction of
`shared_ptr` instances that share ownership of an object. Here's a comprehensive
list of those scenarios:

1. **Going out of scope:** When a `std::shared_ptr` goes out of scope, its
   destructor is called, and it releases its ownership of the object. If this
   `shared_ptr` was the last owner, the object is destroyed.

2. **Resetting the shared pointer:** Calling the `reset()` method on a
   `shared_ptr` without passing a new pointer makes it release its ownership of
   the current object and sets it to manage nothing. If it was the last owner,
   the object is destroyed.

3. **Assigning a new resource:** Assigning a new pointer or another `shared_ptr`
   managing a different resource to a `shared_ptr` causes it to release its
   current ownership. If it was the last owner of the previously managed object,
   that object is destroyed.

4. **Swapping with another shared pointer managing a different object:** When a
   `shared_ptr` is swapped with another that manages a different object (using
   `std::swap` or the member `swap` function), it releases ownership of its
   original object. If it was the last owner of that object, the object is
   destroyed.

5. **Assigning `nullptr`:** Assigning `nullptr` to a `shared_ptr` effectively
   resets it, causing it to release ownership of the object it was managing.
   This is a specific case of resetting the shared pointer.

6. **Destructing the last copy:** If a `shared_ptr` is copied several times, and
   all copies eventually are destroyed or reset (including going out of scope),
   the last destruction or reset operation will drop the reference count to
   zero, leading to the object's destruction.

7. **Using `std::move` to transfer ownership:** Moving a `shared_ptr` to another
   `shared_ptr` using `std::move` does not directly decrease the reference
   count. However, if the moved-from `shared_ptr` was the last owner of an
   object before the move, its destruction (when it goes out of scope or is
   explicitly reset after being moved from) will not affect the reference count,
   as it already relinquished ownership. The object's lifetime is then solely
   managed by the moved-to `shared_ptr`.

It's important to note that these scenarios involve the manipulation or
lifecycle events of `std::shared_ptr` instances themselves. The underlying
mechanism ensures that the managed object's lifetime is correctly tied to the
ownership status of all shared pointers managing it, ensuring deterministic and
automatic resource management.


##
