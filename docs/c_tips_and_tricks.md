# Tips and Tricks in C++

The following tips and tricks are generally common for professional C++ code writing.

## Pointers

1.  It does not make sense to perform a pointer-arithmetics on an `object pointer` as it
    encloses multiple data elements and carrying out arithmetic on pointer
    variables is error-prone (check more about pointers types).

2.  When you create a pointer for a heap alloacted data, you have to free the
    memmory, but that doeesn't mean the pointer address is gone, for that
    reason, you have to also ensure to remove the pointer (momeory address) by
    assign it to `nullptr` so you will be sure it will not be used again.

    - Check this code it is wrong:
    - You have assigned the pointer `ptr` to another address before you clean
      (delete) the allocated on heap integer.

    ```cpp
     int val_on_stack = 10;
     int* ptr = new int(10);  // Allocate memory for an int on the heap and initialize it to 10
     std::cout << "Value: " << *ptr << std::endl;  // Use the allocated memory
     //ptr = nullptr;  // Set the pointer to nullptr to avoid dangling pointer
     ptr = &val_on_stack;
     // Now, ptr is a nullptr and cannot be accidentally used to access invalid memory
     if (ptr == nullptr) {
         std::cout << "Pointer is safely nullified." << std::endl;
     }

     delete ptr;     // Free the memory
    ```

    - Either, we know we should not assign this `ptr` to another value until we
      are are done and delete the memmory by using the `delete` before the
      assignment,
    - Or, we use the `ptr = nullptr`, which tells the user to never ever use
      this pointer and avoiding assign it to something else accidenlty.
      - The correct syntax is to use

    ```cpp

     int val_on_stack = 10;
     int* ptr = new int(10);  // Allocate memory for an int on the heap and initialize it to 10
     std::cout << "Value: " << *ptr << std::endl;  // Use the allocated memory
     //ptr = nullptr;  // Set the pointer to nullptr to avoid dangling pointer
     delete ptr;     // Free the memory
     ptr = &val_on_stack;
     // Now, ptr is a nullptr and cannot be accidentally used to access invalid memory
     ptr = nullptr; //now we will not use it again.
     if (ptr == nullptr) {
         std::cout << "Pointer is safely nullified." << std::endl;
     }
    ```

    - It worth to mention that the `Clang` complier will not complain and this
      leak will be undiscovered unless we use some specific tool for
      memeory-leaking detection.

      ```sh
      Value: 10
      main(77406,0x1dc6a1000) malloc: **_ error for object 0x16ddadfcc: pointer being freed was not allocated
      main(77406,0x1dc6a1000) malloc: _** set a breakpoint in malloc_error_break to debug
      make: \*\*\* [debug_using_ninja] Abort trap: 6
      ```

## References

1. References in nutshell:
   - References are actually aliases for variable_name.
   - You can do everything with references that you can also do with pointers,
     pointers are much powerful than references.
   - Whenever possible, try to use references as they provide clean code and a
     convenient way to manage object resource usage.
   - Passing an alias for a function in function/method calling is similar to
     passing the variable itself (this is different from Rust and I feel it lacks
     consistency).

## Rules of OPP

1. Always pass your object as `const type&` , for example

```cpp
// Assume you have an object called e extensionated from a class called Entity.
void my_function_caller(const &Entity e){}
```
