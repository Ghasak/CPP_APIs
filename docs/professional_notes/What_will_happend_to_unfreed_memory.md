# Memory Cleaning - allocated on Heap

## Q1: About unfreed memory

When I fail to deallocate memory allocated on the heap in C++ using a raw
pointer, what will happen to that memory during program execution and upon
termination, assuming I'm working on macOS?.

### Answer

When you allocate memory on the heap in C++ using a raw pointer and do not
delete it before your program ends, you create what is known as a memory leak.
Here's what happens to this memory both during the program's execution and after
its termination, especially considering you are using macOS:

### During the Program's Execution:

1. **Memory Remains Allocated**: The memory you allocated remains reserved for
   your program until it explicitly frees it (using `delete` or `delete[]` for
   arrays) or the program terminates. This means that the memory cannot be used
   by other parts of your program or by other applications, potentially reducing
   the available memory for other tasks.
2. **Potential for Memory Exhaustion**: If your program repeatedly allocates
   memory without freeing it (for example, inside a loop), it can lead to memory
   exhaustion, causing your program to use up the available memory. This can
   lead to performance degradation of your program and possibly affect other
   running applications or even the whole system.
3. **No Automatic Garbage Collection**: Unlike languages with garbage collection
   (e.g., Java, Python), C++ does not automatically reclaim memory that is no
   longer referenced. If you lose all pointers to an allocated memory block
   without freeing it, that memory is lost until the program ends, contributing
   to a memory leak.

### When the Program is Terminated:

1. **Operating System Reclaims Memory**: Upon program termination, modern
   operating systems like macOS will automatically reclaim the memory that was
   allocated to the program. This means that the memory leak will not persist
   beyond the lifetime of the program, and the leaked memory will eventually be
   made available again for other applications.
2. **Resources are Cleaned Up**: Besides memory, the operating system will also
   clean up other resources that were used by the program, such as file
   descriptors and network connections.

### Conclusion:

While memory leaks do not persist after a program has terminated on modern
operating systems like macOS, they can still cause problems during the program's
execution, especially in long-running applications or those that consume a lot
of resources. It's best practice to manage memory carefully in C++, ensuring
that every `new` is matched with a `delete` (or using smart pointers, which
automatically manage memory, reducing the risk of leaks).
