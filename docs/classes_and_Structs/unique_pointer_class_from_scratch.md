# Unique Pointer Class from Scratch

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Unique Pointer Class from Scratch](#unique-pointer-class-from-scratch)
    - [Some Facts](#some-facts)
    - [Our Objective](#our-objective)
    - [Class Building](#class-building)
        - [Explicity new](#explicity-new)
        - [Implicitly using New](#implicitly-using-new)
        - [Note on constructing object](#note-on-constructing-object)
    - [More examples](#more-examples)
        - [Smart Timer Pointer](#smart-timer-pointer)
            - [From scratch](#from-scratch)
            - [Using Smart Pointers](#using-smart-pointers)
        - [Mutex Locking](#mutex-locking)
            - [Implementation](#implementation)
            - [More insight - Why we need Mutex?](#more-insight---why-we-need-mutex)

<!-- markdown-toc end -->

Here, we will create our own unique pointer class from scratch to understand how
we can automatically free heap allocated memory. The implementation should
resemble the `unique_ptr` from the standard library, but it will not be as
sophisticated as the `unique_ptr` from SDL. Our goal is to learn how it works.

## Some Facts

- In memory management, the "heap" refers to a region used for dynamic
  allocation, with variables accessed via pointers. Pointers store memory
  addresses pointing to data on the heap.

- The stack is used for static memory allocation, where variables and control
  blocks (e.g., for std::string or std::vector) are stored. This includes
  metadata like capacity and length, alongside a pointer to the heap for dynamic
  data.

- Complex data structures manage memory on the heap internally. They adjust size
  at runtime, with their control information (metadata and pointers) stored
  within the object itself. Whether this information is on the stack or heap
  depends on the object's allocation (static on the stack or dynamic on the
  heap).

- [VERY IMPORTANT] For dynamic structures like std::vector or std::string, the
  actual elements or characters are stored on the heap, while the structure's
  control information could be on the stack (for local variables) or on the heap
  (if the object is dynamically allocated).

## Our Objective

- The class that we will create is:
  - A scoped classes such as smart unique pointer (a scoped pointer), or
    like a scoped lock.
  - It is a class that's a wrapper over a pointer which upon construction heap
    allocates the data.
  - And, then upon destruction deletes the pointer and all the data which it
    refer (which is located on the heap).
  - We will kind of automate the `new` and `delete` these things.
  - Stack based variables get destoryed is very helpful.

## Class Building

### Explicity new

```cpp


+-------------------------------+                +-------------------------------+
|          Entity Class         |                |        ScopedPtr Class        |         <-- This class identical to the smart pointer `unique_pointer`
+-------------------------------+                +-------------------------------+

class Entity{                                    class ScopedPtr{
    public:                                          private:
        // constructor                                   Entity* m_Ptr;
        Entity(){                                    public:
            std::cout                                   // Constructor
            << "Created Entity!"                         ScopedPtr(Entity* ptr)
            << std::endl;                                    :m_Ptr{ptr}{
        }                                                    }
        // destruction                                  // Destructor
        ~Entity(){                                       ~ScopedPtr(){
            std::cout                                        delete m_Ptr;
            << "Destroyed Entity!"                       }
            << std::endl;                        }
        }
};


           [BEFORE]                                                                             [AFTER]
+----------------------------------+                                                  +-------------------------------+
|          Main Function           |                                                  |         Main Function         |
+----------------------------------+                                                  +-------------------------------+
|                                  |                                                  |
| int main(){                      |                                                  |  int main(){
|      // Inner-scope              |                                                  |       // Inner-scope
|     {                            |                                                  |      {
|         Entity* e = new Entity();|  //<--- This heap I want to call                 |          ScopedPtr e = ScopedPtr(new Entity()); // or ScopedPtr e(new Entity());
|                                  |  //     new automatically upon                   |          //Entity* e = new Entity();
|                                  |  //     constructing this pointer (object).      |
|                                  |                                                  |      }                                    // <-- Once we reached here (e) gets destroyed even thought
|     }                            |  //<--- I want to deallocate                     |                                           //     its a (heap) allocated with (new), furthermore,
|                                  |  //     the e from heap upon reaching this scope.|                                           //     we didn't use (delete) to free it from memeory.
|                                  |                                                  |      std::cin.get();
|     std::cin.get();              |                                                  |  }
| }                                |                                                  |
+----------------------------------+                                                  +-------------------------------+

```

The code you've written aims to demonstrate an RAII (Resource Acquisition Is
Initialization) pattern in C++, using a custom wrapper class (`ScopedPtr`) to
manage the lifetime of dynamically allocated objects. This pattern ensures
resources such as memory and file handles are properly released when they're no
longer needed, which is indeed similar to what smart pointers like
`std::unique_ptr` in the C++ Standard Library do. However, there are a few
corrections and improvements that can be made to your example:

1. **Syntax Correction**: The line `ScopedPtr e = new Entity();` will not
   compile because the `ScopedPtr` constructor expects a pointer to an `Entity`
   object, but the assignment syntax used is incorrect for initialization. The
   correct way to write it would be using direct initialization: `ScopedPtr e(new Entity());`

2. **Similarity to `std::unique_ptr`**: Your `ScopedPtr` is conceptually similar
   to `std::unique_ptr` in that it takes ownership of a dynamically allocated
   object and ensures its deletion when the `ScopedPtr` object is destroyed.
   However, `std::unique_ptr` is more feature-rich, providing functionalities
   like move semantics, custom deleters, and compatibility with conditionals and
   algorithms that your `ScopedPtr` does not.

3. **Improvements**:
   - **Rule of Three/Five**: If you're managing resources like dynamically
     allocated memory, you should properly implement the rule of three (copy
     constructor, copy assignment operator, and destructor) or the rule of five
     (including move constructor and move assignment operator) to handle copy
     and move operations safely. Your `ScopedPtr` lacks these, making it
     potentially unsafe to use in cases where objects might be copied or moved.
   - **Explicit Constructor**: Marking the constructor of `ScopedPtr` as
     `explicit` prevents implicit conversions and makes the intentions clearer.
   - **Support for Move Semantics**: Implementing move constructor and move
     assignment operator can make your `ScopedPtr` more efficient by allowing
     transfer of ownership without deep copying, similar to `std::unique_ptr`.

Here's an improved version of your `ScopedPtr` that addresses the syntax correction:

```cpp
#include <iostream>

class Entity {
public:
    Entity() {
        std::cout << "Created Entity!" << std::endl;
    }
    ~Entity() {
        std::cout << "Destroyed Entity!" << std::endl;
    }
};

class ScopedPtr {
private:
    Entity* m_Ptr;
public:
    explicit ScopedPtr(Entity* ptr) : m_Ptr(ptr) {}
    ~ScopedPtr() {
        delete m_Ptr;
    }
    // Delete copy constructor and copy assignment to prevent copying
    ScopedPtr(const ScopedPtr&) = delete;
    ScopedPtr& operator=(const ScopedPtr&) = delete;
    // Implement move constructor and move assignment for efficiency
    ScopedPtr(ScopedPtr&& other) noexcept : m_Ptr(other.m_Ptr) {
        other.m_Ptr = nullptr;
    }
    ScopedPtr& operator=(ScopedPtr&& other) noexcept {
        if (this != &other) {
            delete m_Ptr;
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
        }
        return *this;
    }
};

int main() {
    {
        ScopedPtr e(new Entity());
    } // <-- Entity gets destroyed here, automatically by ScopedPtr's destructor

    std::cin.get();
    return 0;
}
```

This code now safely manages the `Entity` instance, ensuring it is deleted when
the `ScopedPtr` goes out of scope, similar to `std::unique_ptr`. Including move
semantics makes it more efficient in contexts where objects might be
transferred, providing an advantage over simple manual memory management.

### Implicitly using New

Creating an implicit heap-allocated structure within a constructor, as shown in
your `ScopedPtr` example, deviates from common best practices and design
principles in C++.

```cpp
class ScopedPtr{
    private:
        Entity* m_Ptr;
    public:
       // Constructor
        ScopedPtr(Entity* ptr)
            {
              // allocate on heap upon constructing
              m_Ptr = new Entity();
            }
       // Destructor
        ~ScopedPtr(){
            delete m_Ptr;
        }
}

```

Here’s why this approach is generally not recommended:

1. **Lack of Flexibility**: By hardcoding `new Entity()` inside the `ScopedPtr`
   constructor, you're tightly coupling `ScopedPtr` to the `Entity` class and
   limiting its usability. A key benefit of a smart pointer or any pointer
   wrapper class is its ability to manage different types of resources, not just
   a single predefined type.

2. **Unexpected Behavior**: Users of your `ScopedPtr` class might expect that it
   takes ownership of the pointer they pass to its constructor. The current
   design, however, ignores the passed-in pointer and instead always creates a
   new `Entity`. This can lead to confusion, memory leaks (if users dynamically
   allocate an `Entity` and pass it to `ScopedPtr` expecting it to take
   ownership), and makes the class less intuitive to use.

3. **Resource Management Principle Violation**: The primary goal of a smart
   pointer or resource management class is to encapsulate the ownership and
   lifecycle management of a resource (e.g., memory, file handles). A
   well-designed resource management class should be transparent about what it
   owns and should not perform unexpected actions like allocating a new resource
   when it's supposed to take ownership of an existing one.

4. **Single Responsibility Principle (SRP)**: According to SRP, a class should
   have only one reason to change. By embedding the creation of the `Entity`
   inside `ScopedPtr`, you're giving it two reasons to change: changes to the
   resource management logic and changes to how `Entity` objects are created.
   This makes the class more complex and harder to maintain.

A better approach is to pass the already created object to the `ScopedPtr` and
let it manage the lifetime of that object. If you need to create objects on the
heap within a controlled environment, consider using factory functions or
methods that clearly indicate the creation of a new object, and then pass that
object to your resource manager class.

Here’s a revised version of your class that better aligns with common practices:

```cpp
class ScopedPtr {
private:
    Entity* m_Ptr;
public:
    // Constructor takes ownership of the passed pointer
    explicit ScopedPtr(Entity* ptr) : m_Ptr(ptr) {
    }

    // Destructor releases the owned resource
    ~ScopedPtr() {
        delete m_Ptr;
    }

    // Delete copy semantics to prevent multiple ownership issues
    ScopedPtr(const ScopedPtr&) = delete;
    ScopedPtr& operator=(const ScopedPtr&) = delete;

    // Optionally implement move semantics to allow transfer of ownership
    ScopedPtr(ScopedPtr&& other) noexcept : m_Ptr(other.m_Ptr) {
        other.m_Ptr = nullptr;
    }

    ScopedPtr& operator=(ScopedPtr&& other) noexcept {
        if (this != &other) {
            delete m_Ptr;
            m_Ptr = other.m_Ptr;
            other.m_Ptr = nullptr;
        }
        return *this;
    }
};
```

In summary, while the mechanism of allocating a new `Entity` within the
`ScopedPtr` constructor is technically possible, it's not a good practice due to
its lack of flexibility, potential for confusion, and violation of fundamental
design principles.

To use the improved version of the `ScopedPtr` class in a `main` function, you'd
typically follow these steps:

1. Dynamically create an instance of the `Entity` class.
2. Initialize a `ScopedPtr` object with the pointer to the `Entity` instance.
3. The `ScopedPtr` object will take ownership of the `Entity` instance, ensuring
   its deletion when the `ScopedPtr` goes out of scope.

Here is an example of how you might use it in a `main` function:

```cpp
#include <iostream>

// Assume Entity and ScopedPtr classes are defined here as previously discussed.

int main() {
    // Create an Entity instance on the heap.
    Entity* myEntity = new Entity();

    // Pass the pointer to ScopedPtr to take ownership.
    {
        ScopedPtr scopedPtr(myEntity);
        // At this point, scopedPtr owns the myEntity instance.
        // No need for explicit deletion of myEntity; scopedPtr will handle it.
    } // scopedPtr goes out of scope here, and myEntity is automatically deleted.

    // Wait for user input before closing to see the output clearly.
    std::cin.get();

    return 0;
}
```

In this example, `ScopedPtr` is being used to manage the lifetime of an `Entity`
object. When `scopedPtr` goes out of scope at the end of the block, its
destructor is called, which in turn deletes the `Entity` object it owns. This
demonstrates the RAII (Resource Acquisition Is Initialization) principle, which
is a best practice for resource management in C++ to avoid memory leaks and
ensure exception safety.

Note that in real-world applications, especially in modern C++, you would
typically use standard smart pointers (`std::unique_ptr` or `std::shared_ptr`)
to manage dynamic resources because they are well-tested, highly optimized, and
provide a clear indication of ownership semantics. The custom `ScopedPtr` class
serves as an educational example of how such mechanisms work under the hood.

### Note on constructing object

The syntax `ScopedPtr e = ScopedPtr(new Entity());` is correct and will work as
intended in C++. This line creates a temporary `ScopedPtr` object initialized
with a pointer to a new `Entity` instance, and then uses copy initialization to
construct `e` with that temporary object. However, since `ScopedPtr` has its
copy constructor deleted (or should have, to follow good resource management
practices), what actually happens under the hood is a bit different due to the
concept known as "copy elision" or more specifically in this context, "NRVO"
(Named Return Value Optimization) and "RVO" (Return Value Optimization).

With modern C++ compilers, copy elision is a standard optimization technique
that allows the compiler to eliminate or combine redundant copy and move
operations. In the case of `ScopedPtr e = ScopedPtr(new Entity());`, the
compiler is allowed (and likely) to elide the temporary `ScopedPtr` object and
construct `e` directly with the new `Entity` instance, avoiding any need for a
copy or move constructor altogether. This is why even if the class doesn’t
explicitly support copying or moving (because both the copy and move
constructors are deleted or not defined), this line of code can still work.

However, relying on compiler optimizations for fundamental aspects of code
correctness and behavior is not a best practice. It's clearer and more reliable
to directly initialize the `ScopedPtr` object like so:

```cpp
ScopedPtr e(new Entity());
```

This direct initialization does not rely on copy or move semantics and makes the
code's intentions explicit, ensuring that the `ScopedPtr` takes ownership of the
`Entity` object without relying on compiler optimizations for correctness.

Additionally, employing direct initialization is more efficient because it
avoids even the conceptual creation of a temporary object, making the code's
behavior clearer to readers and potentially avoiding pitfalls related to copy
and move operations, especially in more complex scenarios where copy elision
cannot be applied.

## More examples

There are so many other examples we can create, for example how about:

### Smart Timer Pointer

- Create a smart pointer with a timer which:
  - The timer will start upon constructing the data.
  - The time will stop upon destruction .
  - print the time and other features.

#### From scratch

Creating a custom smart pointer with embedded timing functionality from scratch
requires managing the resource directly, similar to the earlier `ScopedPtr`
example, but with added timing logic. This version will not use any existing
smart pointer classes (`std::unique_ptr` or `std::shared_ptr`) from the C++
Standard Library. Instead, it will manage the resource allocation and
deallocation explicitly, and incorporate timing functionality directly into the
class.

Here's how you can implement it:

```cpp
#include <iostream>
#include <chrono>

class Entity {
public:
    Entity() {
        std::cout << "Entity created\n";
    }
    ~Entity() {
        std::cout << "Entity destroyed\n";
    }
    void doSomething() {
        std::cout << "Entity is doing something\n";
    }
};

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> duration;

public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer ran for " << ms << " ms\n";
    }
};

class TimedScopedPtr {
private:
    Entity* m_Ptr;
    Timer timer; // Embed a Timer object to automatically start/stop timing.

public:
    explicit TimedScopedPtr(Entity* ptr) : m_Ptr(ptr) {
        std::cout << "TimedScopedPtr created\n";
    }

    ~TimedScopedPtr() {
        delete m_Ptr;
        std::cout << "TimedScopedPtr destroyed\n";
    }

    // Prevent copying and assignment.
    TimedScopedPtr(const TimedScopedPtr&) = delete;
    TimedScopedPtr& operator=(const TimedScopedPtr&) = delete;

    // Allow access to Entity's methods.
    Entity* operator->() const {
        return m_Ptr;
    }
};

int main() {
    {
        TimedScopedPtr timedPtr(new Entity());
        timedPtr->doSomething();
        // Timer is automatically running from the point of creation...
    } // timedPtr goes out of scope here, Entity is destroyed, and timer stops & prints duration.

    std::cin.get();
    return 0;
}
```

This implementation defines a `Timer` class that starts timing upon construction
and prints the elapsed time upon destruction. The `TimedScopedPtr` class manages
an `Entity` pointer and includes a `Timer` object as a member, ensuring that the
timer starts when a `TimedScopedPtr` object is created and stops when the object
is destroyed, automatically printing the duration.

By embedding the `Timer` within `TimedScopedPtr`, we ensure that the timing
lifecycle is tightly coupled with the managed object's lifecycle, providing a
clear demonstration of how long the managed object existed. This approach shows
how to implement custom behavior (in this case, timing) in resource management
classes without relying on the standard smart pointers, giving you full control
over both resource management and additional functionalities.

#### Using Smart Pointers

To create a smart pointer that incorporates a timer functionality, you can
design a class that not only manages the lifetime of a dynamically allocated
object (like `ScopedPtr`) but also records the time duration for which the
object was alive. This class will start a timer when the object is constructed
and stop the timer when the object is destroyed, printing the elapsed time along
with some custom messages for pretty printing.

Here's an example implementation in C++:

```cpp
#include <iostream>
#include <chrono>
#include <memory>

// Simple class to demonstrate functionality.
class Entity {
public:
    Entity() {
        std::cout << "Entity created\n";
    }
    ~Entity() {
        std::cout << "Entity destroyed\n";
    }
    void doSomething() {
        std::cout << "Entity is doing something\n";
    }
};

// Smart pointer class with a timer.
class TimedScopedPtr {
private:
    std::unique_ptr<Entity> m_Ptr;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point endTime;

    // Private method to start the timer.
    void startTimer() {
        startTime = std::chrono::steady_clock::now();
    }

    // Private method to stop the timer and print the duration.
    void stopTimerAndPrint() {
        endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Duration: " << duration << " ms\n";
    }

public:
    // Constructor starts the timer and takes ownership of the pointer.
    explicit TimedScopedPtr(Entity* ptr) : m_Ptr(ptr) {
        std::cout << "TimedScopedPtr created and timer started\n";
        startTimer();
    }

    // Destructor stops the timer and prints the duration.
    ~TimedScopedPtr() {
        stopTimerAndPrint();
        std::cout << "TimedScopedPtr destroyed and timer stopped\n";
    }

    // Access underlying object methods
    Entity* operator->() const {
        return m_Ptr.get();
    }
};

int main() {
    {
        TimedScopedPtr timedPtr(new Entity());
        timedPtr->doSomething();
        // Timer is running...
    } // timedPtr goes out of scope here, timer stops, and duration is printed.

    std::cin.get();
    return 0;
}
```

This example uses `std::unique_ptr` for memory management within
`TimedScopedPtr`, simplifying the resource management aspect and focusing on the
timing functionality. When `TimedScopedPtr` is instantiated with a new `Entity`,
it starts the timer. Upon destruction, it stops the timer, calculates the
elapsed time, and prints it alongside the destruction messages.

This approach demonstrates how you can extend smart pointer functionality to
include custom behaviors, such as timing the lifespan of the managed object. It
leverages `std::chrono` for high-precision time measurements. The `doSomething`
method in the `Entity` class is just an example of how you might interact with
the managed object through the smart pointer.

### Mutex Locking

If you want to lock a function so the muliple threads can't access it and caused
an explosionn you can have an automatic scoped lock which is at the begging of a
function locks and at the end of the function unlocks it.

#### Implementation

To create an automatic scoped lock that ensures mutual exclusion for critical
sections in a multi-threaded environment, you can utilize RAII (Resource
Acquisition Is Initialization) by designing a class that acquires a lock upon
construction and releases it upon destruction. This pattern is particularly
useful for managing concurrency in a safe and efficient manner, preventing
"explosions" or, more technically, race conditions, deadlocks, and other
concurrency issues.

Here's a basic implementation of a `ScopedLock` class that uses a mutex to
manage access to a critical section. This example will demonstrate how to use
such a class to automatically lock and unlock a mutex in a multi-threaded
program:

```cpp
#include <iostream>
#include <mutex>
#include <thread>

class ScopedLock {
private:
    std::mutex& m_Mutex;

public:
    explicit ScopedLock(std::mutex& mutex) : m_Mutex(mutex) {
        m_Mutex.lock();
        std::cout << "Locked by thread " << std::this_thread::get_id() << std::endl;
    }

    ~ScopedLock() {
        m_Mutex.unlock();
        std::cout << "Unlocked by thread " << std::this_thread::get_id() << std::endl;
    }

    // Delete copy constructor and copy assignment to prevent copying.
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
};

// Example function that uses ScopedLock to protect its execution.
void criticalFunction(std::mutex& mutex) {
    ScopedLock lock(mutex);
    // Critical section goes here.
    // For example, modifying a shared resource.
    std::cout << "Executing critical section in thread " << std::this_thread::get_id() << std::endl;
    // Lock is automatically released when lock goes out of scope.
}

int main() {
    std::mutex mutex;

    // Create multiple threads to demonstrate the ScopedLock.
    std::thread t1(criticalFunction, std::ref(mutex));
    std::thread t2(criticalFunction, std::ref(mutex));

    t1.join();
    t2.join();

    return 0;
}
```

In this example, the `ScopedLock` class takes a reference to a `std::mutex`
object as its constructor argument and locks it. The lock is held for the
duration of the `ScopedLock` object's lifetime, ensuring that only one thread
can enter the critical section at a time. When the `ScopedLock` object is
destroyed (which happens automatically when the scope ends), the mutex is
unlocked, allowing other threads to acquire the lock and enter the critical
section.

This pattern is widely used in C++ for managing resources, especially in
multi-threaded applications where resource access needs to be synchronized. The
C++ Standard Library provides `std::lock_guard` and `std::unique_lock`, which
are scoped lock mechanisms designed to handle such use cases elegantly and
safely, following the same principles demonstrated with `ScopedLock`.

#### More insight - Why we need Mutex?

**NOTE**:I will try here to explain why we need `std::mutex`. and the following
implementation is not recommended.

Implementing a scoped lock mechanism without using `std::mutex` (or any other
standard synchronization primitives) requires creating a custom synchronization
mechanism. This approach is generally not recommended for production code
because it can be error-prone and less efficient compared to using well-tested
primitives provided by the standard library or the operating system. However,
for educational purposes or very specific scenarios, you might explore
alternatives like spinlocks for simple use cases.

A spinlock is a lock where the thread simply waits in a loop ("spins")
repeatedly checking until the lock becomes available. This can be efficient if
threads are only expected to be blocked for a short period, but it's wasteful if
the wait is long because it consumes CPU resources while waiting.

Here’s a basic example of a custom scoped lock mechanism using a simple
spinlock:

```cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class SpinLock {
private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (locked.test_and_set(std::memory_order_acquire)) {
            // Busy-wait (spin) until the lock is released
        }
    }

    void unlock() {
        locked.clear(std::memory_order_release);
    }
};

class ScopedSpinLock {
private:
    SpinLock& spinLock;

public:
    explicit ScopedSpinLock(SpinLock& lock) : spinLock(lock) {
        spinLock.lock();
        std::cout << "Locked by thread " << std::this_thread::get_id() << std::endl;
    }

    ~ScopedSpinLock() {
        spinLock.unlock();
        std::cout << "Unlocked by thread " << std::this_thread::get_id() << std::endl;
    }

    // Delete copy semantics
    ScopedSpinLock(const ScopedSpinLock&) = delete;
    ScopedSpinLock& operator=(const ScopedSpinLock&) = delete;
};

void criticalSection(SpinLock& spinLock) {
    ScopedSpinLock lock(spinLock);
    // Critical section
    std::cout << "In critical section: thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
}

int main() {
    SpinLock spinLock;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(criticalSection, std::ref(spinLock)));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

In this example, `SpinLock` uses an `std::atomic_flag` for the actual lock,
which provides an atomic boolean flag suitable for spinlock implementation. The
`ScopedSpinLock` class provides a RAII-style mechanism to automatically lock and
unlock the `SpinLock`. This ensures that the spinlock is acquired upon entering
a scope and released when exiting, similar to how you'd use `std::mutex` with
`std::lock_guard`.

Note: While this example demonstrates how to implement a basic spinlock and
scoped lock, it's crucial to understand that spinlocks can lead to high CPU
usage in waiting threads. For most applications, using standard synchronization
primitives like `std::mutex`, `std::unique_lock`, or `std::lock_guard` is
preferable due to their efficiency and the fact that they're designed to yield
the processor to other threads while waiting, making better use of system
resources.
