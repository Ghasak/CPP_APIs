# Tips and Tricks in C++

The following tips and tricks are generally common for professional C++ code writing.
## Rule of Functions/methods

- Don't try to return `pointer` to a stack data structure of a local variable
  (within the body of the function). This include `reference` as well.


## Convension in Coding

Here's a table summarizing the common C++ naming conventions mentioned, along
with their descriptions and examples:

| Prefix/Scheme          | Description                                                                                            | Example                                                                                            |
| ---------------------- | ------------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------- |
| `m_`                   | Indicates a member variable of a class. Used to differentiate instance variables from local variables. | `m_age` (member variable storing the age of an instance)                                           |
| `s_`                   | Denotes a static variable within a class, shared by all instances of the class.                        | `s_instanceCount` (tracks the number of class instances)                                           |
| `g_`                   | Used for global variables to differentiate them from local and class member variables.                 | `g_appConfig` (global variable for application configuration)                                      |
| `c_`                   | Occasionally used for constant variables. Constants are more commonly written in uppercase.            | `c_MaxConnections` (constant value for maximum connections)                                        |
| `p_`                   | Indicates a pointer variable.                                                                          | `p_nextNode` (pointer to the next node in a linked list)                                           |
| CamelCase              | Used for naming functions, classes, and methods. The first letter of each word is capitalized.         | `MyClass` (class name), `calculateTotal` (method name)                                             |
| lowercase / snake_case | Used for local variables and function parameters, with words separated by underscores.                 | `local_variable` (local variable), `calculate_total(number_of_items)` (function and its parameter) |

This table provides a quick reference to the naming conventions discussed,
offering both a description of their intended use and concrete examples to
illustrate each convention.

In C++, naming conventions are a set of guidelines that programmers follow to
name their variables, functions, classes, and other identifiers in a consistent
and meaningful way. These conventions are not enforced by the C++ language
itself but are adopted by developers to improve code readability and
maintainability. Among the various naming conventions, the prefixes `m_` and
`s_` are commonly used to indicate the scope or usage of a variable within a
class. Here's a brief overview of these and other commonly used naming
conventions in C++:

1. **`m_` Prefix**: The `m_` prefix stands for "member" and is used to name
   instance variables (also known as member variables) of a class. This
   convention helps to distinguish instance variables from local variables and
   parameters within class methods. Example:
   - `m_age` might refer to a member variable that stores the age of an instance
     of a class.
2. **`s_` Prefix**: The `s_` prefix denotes a static variable within a class.
   Static variables are shared by all instances of a class and belong to the
   class itself rather than any particular object instance. Example:
   - `s_instanceCount` could be used to keep track of the number of instances
     that have been created for a given class.
3. **`g_` Prefix**: Sometimes used for global variables to differentiate them
   from local and class member variables. It stands for "global." Example:
   - `g_appConfig` might refer to a global variable that holds configuration
     settings for an application.
4. **`c_` Prefix**: Occasionally used for constant variables, though it's more
   common to see constants written in uppercase with underscores between words.
   Example:
   - `const int c_MaxConnections` could represent a constant value indicating
     the maximum number of connections.
5. **`p_` Prefix**: This can be used for pointer variables to indicate that the
   variable holds a pointer to a certain type. Example:
   - `p_nextNode` could be used in a linked list implementation to point to the
     next node.
6. **CamelCase**: Used for naming functions, classes, and methods where the
   first letter of each word is capitalized, and there is no underscore between
   words. This is common for class names and method names. Example:
   - `MyClass` for a class name.
   - `calculateTotal` for a method name.
7. **lowercase or snake_case**: Used for local variables and function
   parameters, with words separated by underscores. Example:
   - `local_variable` for a local variable.
   - `calculate_total(int number_of_items)` for a function and its parameter.

These conventions can vary between projects and development teams. Some teams
might use different prefixes or prefer other conventions altogether, like
entirely using `camelCase` or `snake_case` for naming. It's important to follow
the specific guidelines provided for a project or to be consistent with the
conventions established within your team or codebase.

## Allocation on Heap

1. To allocate a `cstyle` list on the heap, we use the pointer obtained through
   the `keyword`, and this also applies to any other data structure or
   container that is memory-managed, such as `std::vector` and `std::string`.

- There are so many benefits of allocating variables on heap, Here is a list of
  the one I know so far:

  - I don't know the size of the array at compilation time, hence I need to
    prepare the size as a user input during runtime. Then, the program will accept
    any user input size if the user chooses to enter it manually.

  - Create your data container (array, string..etc.) to still alive out of the
    scope that it is been created in, which will offer us more contorl

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

2. In regards to references, always return a reference of an entity, such as a
   variable, object, or similar, that is created outside the function/method body
   to avoid creating a dangling reference.



## Rules of OPP

1. Always pass your object as `const type&` , for example

```cpp
// Assume you have an object called e extensionated from a class called Entity.
void my_function_caller(const &Entity e){}
```
