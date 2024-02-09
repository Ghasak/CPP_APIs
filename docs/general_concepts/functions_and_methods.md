# Functions and Methods

In C++, the syntax for creating a function that takes input variables and
returns an output variable is quite straightforward. The basic structure
includes specifying the return type of the function, the name of the function,
and the parameters (input variables) within parentheses. Here's a general
outline:

## 1. My Understanding

- Input variables will be consumed inside the function/method if they are
  passed as they are, instead we can pass them as a pointer or reference.
- Any local variable inside the function will also die once we exit the
  function body (function scope).
- To keep the variable from not dying if its inputted to our `function/method`
  is by passing it as a pointer or reference.

```sh

[outside the function]
                --> +--+                                                                    +--+
                --> |  |                    +-------------------+                           |  |
int var_x = 10; --> |  |  o---- INPUT --->  |  Function/method  |    o---- OUTPUT --->      |  |
                --> |  |                    +-------------------+                           |  |
                --> |  |     [signature]   local defintion variables      [return]          |  |
                --> +--+ <----------------------  Scope  -------------------------------->  +--+
                                                      int var_y = 10;                       var_x still alive
                                                                                            var_y died at exit of the scope of the function/method
```

- In regards to references, always return a reference of an entity, such as a
  variable, object, or similar, that is created outside the function/method body
  to avoid creating a dangling reference.

- To avoid data corruption when returning a pointer or reference for a local
  variable, it is necessary to allocate the data on the heap and return ownership
  using the `return` statement. This should be assigned to the corresponding
  variable outside the method or function scope. This becomes crucial because
  local variables exist only within their respective blocks or scopes, and
  returning a pointer or reference to them could lead to undefined behavior as
  soon as the block is left. By allocating memory on the heap, we ensure that the
  data persists beyond the current scope, making it accessible outside the method
  or function.
  - The user is responsible to free the `heap` allocated data once it gets
    allocated (allocation is done using the `new` keyword).

## 2. Function/method syntax

```cpp
return_type function_name(param_type1 param_name1, param_type2 param_name2, ...) {
    // function body
    // ...
    return return_value; // this should match the return_type
}
```

### 2.1. Common Coding Practices for Function Creation in C++

1. **Naming Conventions**: Use meaningful and descriptive names for functions
   and parameters. Function names typically use camelCase or snake_case. 2.
   **Parameter Passing**: Prefer passing simple and small data types by value, and
   large or complex data types by reference or pointer. For non-modifying
   reference parameters, use `const` to prevent accidental changes.
2. **Return Type**: Choose an appropriate return type. If the function does not
   need to return a value, use `void`.
3. **Function Documentation**: Comment your functions to explain what they do,
   the meaning of each parameter, and what the function returns. This is
   crucial for maintainability and readability.
4. **Error Handling**: Include error handling within functions. This could be
   through return values, exceptions, or error codes, depending on your
   application's requirements.
5. **Avoid Global Variables**: Prefer passing parameters to using global
   variables for input to functions.
6. **Limit Function Length**: Functions should be concise and perform a single
   task. Long functions are harder to maintain and understand.
7. **Const Correctness**: Use `const` wherever applicable, especially with
   pointer or reference parameters that are not supposed to change the passed
   objects.

### 2.2. Example Function

Let's create a function that demonstrates these concepts. Suppose we have a
function that calculates the area of a rectangle. This function will take the
length and width as inputs (parameters) and return the area as the output.

```cpp
#include <iostream>

// Function to calculate the area of a rectangle
double calculateArea(double length, double width) {
    if (length < 0 || width < 0) {
        std::cerr << "Error: Length and width must be non-negative." << std::endl;
        return -1; // Return an error code for negative inputs
    }
    return length * width;
}

int main() {
    double length = 5.0;
    double width = 3.0;

    double area = calculateArea(length, width);
    if (area >= 0) {
        std::cout << "Area of the rectangle is " << area << std::endl;
    }

    return 0;
}
```

In this example, `calculateArea` is a function that returns a `double` (the
area). It takes two `double` parameters (length and width). The function
includes error handling for negative inputs and follows the common coding
practices mentioned earlier.

## 3. Return types of function signature

Re-evaluating the table to include all the return types possible for each
category in C++ requires considering not only the basic types but also more
complex return types such as pointers and references, including the more
advanced cases like returning a reference to an array. Here's the revised
table:

| **Data Type**           | **Return Type**                        | **Return Type with Reference**          | **Return Type with Pointer**            |
| ----------------------- | -------------------------------------- | --------------------------------------- | --------------------------------------- |
| **Primitive Types**     |                                        |                                         |                                         |
| int                     | `int functionName();`                  | `int& functionName();`                  | `int* functionName();`                  |
| double                  | `double functionName();`               | `double& functionName();`               | `double* functionName();`               |
| char                    | `char functionName();`                 | `char& functionName();`                 | `char* functionName();`                 |
| bool                    | `bool functionName();`                 | `bool& functionName();`                 | `bool* functionName();`                 |
| **String Types**        |                                        |                                         |                                         |
| String literal          | `const char* functionName();`          | N/A                                     | N/A                                     |
| std::string             | `std::string functionName();`          | `std::string& functionName();`          | `std::string* functionName();`          |
| char\* (C-style string) | `char* functionName();`                | N/A                                     | N/A                                     |
| **Container Types**     |                                        |                                         |                                         |
| std::vector             | `std::vector<T> functionName();`       | `std::vector<T>& functionName();`       | `std::vector<T>* functionName();`       |
| std::array              | `std::array<T, N> functionName();`     | `std::array<T, N>& functionName();`     | `std::array<T, N>* functionName();`     |
| C-style array           | `T* functionName();`                   | `T (&functionName())[ArraySize]`        | N/A                                     |
| std::list               | `std::list<T> functionName();`         | `std::list<T>& functionName();`         | `std::list<T>* functionName();`         |
| **Other Common Types**  |                                        |                                         |                                         |
| std::map                | `std::map<Key, Value> functionName();` | `std::map<Key, Value>& functionName();` | `std::map<Key, Value>* functionName();` |
| std::set                | `std::set<T> functionName();`          | `std::set<T>& functionName();`          | `std::set<T>* functionName();`          |
| std::pair               | `std::pair<T1, T2> functionName();`    | `std::pair<T1, T2>& functionName();`    | `std::pair<T1, T2>* functionName();`    |
| std::tuple              | `std::tuple<Types...> functionName();` | `std::tuple<Types...>& functionName();` | `std::tuple<Types...>* functionName();` |

### 3.1. Points to Note:

- **Returning C-Style Arrays**: The syntax for returning a reference to a
  C-style array is more complex and less common, but it's represented in the
  table as `T (&functionName())[ArraySize]`. This is a function returning a
  reference to an array of `T` of size `ArraySize`.
- **Pointers**: Returning pointers is common in C++, but care must be taken to
  ensure that the pointer does not point to a local variable that will go out of
  scope when the function returns.
- **Return by Reference**: This is useful for avoiding unnecessary copies, but
  it's crucial to ensure that the referenced object has a lifetime that extends
  beyond the function scope.
- **Const Correctness**: For return types with references and pointers,
  applying `const` where appropriate is important for indicating whether the
  caller is allowed to modify the returned object.
- **String Literals and C-Style Strings**: These are typically returned as
  pointers (`const char*` or `char*`). It's important to ensure that the string
  remains valid after the function returns.
- **Modern C++ Practices**: While these return types are all valid, modern C++
  practices favor using standard library containers like `std::vector`,
  `std::array`, and smart pointers over raw pointers and C-style arrays for
  better safety and functionality.

## 4. Passing arguments to parameters

In function or method signatures, arguments can be managed in three primary
ways when passed. When an argument is passed by value to a function or method,
a copy of the argument is created within the function scope, and this copy is
referred to as a `parameter`. However, if the argument is passed by reference
or as a pointer, the corresponding parameter inside the function directly
refers to the original argument's memory location, allowing the function to
access and modify the original value.

- In C++, you can pass arguments to a function in three primary ways: by value,
  by pointer, or by reference. Each method has its own characteristics and use
  cases. Let's go through each of them with examples.

1. **Pass by Value**: In this method, a copy of the actual argument is passed to
   the function. Changes made to the parameter inside the function do not
   reflect in the actual argument.

   ```cpp
   void modifyValue(int a) {
       a = 10; // Modifying the copy, not the original variable
   }

   int main() {
       int x = 5;
       modifyValue(x);
       // x will still be 5 here, as the function modifies a copy of x
   }
   ```

2. **Pass by Pointer**: Here, a pointer to the actual argument is passed.
   Changes made to the parameter (dereferenced pointer) inside the function will
   affect the actual argument.

   ```cpp
   void modifyPointer(int *a) {
       *a = 10; // Modifying the value pointed by the pointer, affects the original variable
   }

   int main() {
       int x = 5;
       modifyPointer(&x);
       // x will be 10 here, as the function modifies the value at the address of x
   }
   ```

3. **Pass by Reference**: In this method, a reference to the actual argument is
   passed. Like passing by pointer, changes made to the parameter will affect
   the actual argument, but the syntax is more straightforward as it doesn't
   require dereferencing.

   ```cpp
   void modifyReference(int &a) {
       a = 10; // Modifying the reference, affects the original variable
   }

   int main() {
       int x = 5;
       modifyReference(x);
       // x will be 10 here, as the function modifies the reference to x
   }
   ```

- Each of these methods has its use. Pass by value is typically used for small or
  primitive data types where the overhead of copying is negligible. Pass by
  pointer and pass by reference are used when you need to modify the original data
  or when passing large objects (to avoid the overhead of copying), with the
  latter providing a cleaner syntax and avoiding some issues pointers might have
  (like null pointers).

- Remember that passing by reference and pointer also helps in reducing memory
  usage, as they avoid making copies of large objects. However, they can lead to
  side-effects if not used carefully, as the original data can be modified
  unintentionally.

- Here's a single table that consolidates the information for the three methods
  of passing arguments in C++ – pass by value, pass by pointer, and pass by
  reference:

| Passing Method    | Function Signature             | Function Calling     | Function Declaration                       |
| ----------------- | ------------------------------ | -------------------- | ------------------------------------------ |
| Pass by Value     | `void modifyValue(int a)`      | `modifyValue(x)`     | `void modifyValue(int a) { a = 10; }`      |
| Pass by Pointer   | `void modifyPointer(int *a)`   | `modifyPointer(&x)`  | `void modifyPointer(int *a) { *a = 10; }`  |
| Pass by Reference | `void modifyReference(int &a)` | `modifyReference(x)` | `void modifyReference(int &a) { a = 10; }` |

- **Pass by Value**: A copy of the argument is passed. Modifications inside the
  function do not affect the original variable.
- **Pass by Pointer**: A pointer to the argument is passed. Modifications to the
  dereferenced pointer affect the original variable.
- **Pass by Reference**: A reference to the argument is passed. Direct
  Certainly! modifications to the reference affect the original variable.

This table offers a clear comparison of how each passing method is implemented
in terms of the function signature, calling convention, and declaration.

---

## Return with methods/functions

In C++, functions can return values in three primary ways: by value, by
pointer, and by reference. Let's look at each with examples and their
associated rules or restrictions.

### 1. Returning by Value

When a function returns by value, it returns a copy of the data. This is the
simplest and safest way to return data from a function.

```cpp
int add(int a, int b) {
    return a + b;
}
```

**Restrictions:**

- No major restrictions. However, returning large structures or classes by
  value can be inefficient due to the copying involved.

### 2. Returning by Pointer

A function can return a pointer to a data type. This is often used when dealing
with arrays or dynamically allocated memory.

```cpp
int* createArray(int size) {
    int* arr = new int[size];  // Dynamically allocated memory
    // Initialize array...
    return arr;
}
```

**Restrictions:**

- **Do not return pointers to local variables:** Local variables are destroyed
  once the function scope ends.
- **Memory Management:** If you return a pointer to dynamically allocated
  memory, you must ensure that this memory is properly managed (i.e., eventually
  freed) to avoid memory leaks.

### 3. Returning by Reference

Returning by reference allows a function to provide a reference to an existing
variable. This avoids copying, but you have to be careful about what you're
referencing.

```cpp
int& getElement(std::vector<int>& vec, int index) {
    return vec[index];
}
```

**Restrictions:**

- **Do not return a reference to a local variable:** Since local variables are
  destroyed when the function exits, this would lead to undefined behavior.
- **Be cautious with object lifetimes:** Ensure that the object you're
  returning a reference to will outlive the reference. For instance, don't return
  a reference to a temporary object.

### General Guidelines

- **Understand Object Lifetimes:** Whether returning by pointer or by
  reference, make sure the data lives long enough for the caller to use it.
- **Prefer Smart Pointers for Ownership Transfer:** If a function allocates
  memory and you want to transfer ownership, consider using smart pointers
  (`std::unique_ptr` or `std::shared_ptr`) instead of raw pointers.
- **Efficiency vs Safety:** Returning by value is safest but can be inefficient
  for large objects. Returning by reference is efficient but can be risky if not
  managed properly. Pointers offer flexibility but require careful memory
  management.
- **Const Correctness:** If you are returning a reference or pointer to an
  object that should not be modified, return a const reference or a pointer to
  const.

By following these guidelines and understanding the implications of each
method, you can make informed decisions on how to return data from functions in
C++.

## Return with string in functions/methods

- Let's explore how a function in C++ can return a string in the three ways you
  mentioned: by value, by pointer, and by reference. I'll provide examples for
  each and discuss the considerations or restrictions.

### 1. Returning by Value

Returning a string by value means returning a copy of the string. This is
straightforward and safe.

```cpp
std::string getMessageByValue() {
    std::string message = "Hello, World!";
    return message; // Returns a copy of the string
}
```

**Considerations:**

- **Safe and Simple:** The returned string is a copy, so the caller doesn't
  need to worry about its lifetime.
- **Potential Overhead:** For large strings, this could be less efficient due
  to the copying involved. However, modern C++ compilers often optimize this
  using Return Value Optimization (RVO).

### 2. Returning by Pointer

Returning a pointer to a string is less common but can be used, especially when
dealing with dynamic memory allocation.

```cpp
std::string* getMessageByPointer() {
    std::string* message = new std::string("Hello, World!");
    return message; // Returns a pointer to the string
}
```

**Considerations:**

- **Dynamic Memory Management:** The caller is responsible for deleting the
  returned string to avoid memory leaks.
- **Not Typically Recommended:** In modern C++, smart pointers
  (`std::unique_ptr`, `std::shared_ptr`) are preferred for managing dynamic
  memory.

### 3. Returning by Reference

Returning a reference to a string can be efficient, but you need to ensure the
string's lifetime is managed correctly.

```cpp
std::string globalMessage = "Hello, World!";

std::string& getMessageByReference() {
    return globalMessage; // Returns a reference to the global string
}
```

**Considerations:**

- **Lifetime Management:** The string being referenced must outlive the
  reference. In this case, a global or static string is used.
- **Avoid Local Variables:** Never return a reference to a local variable.

### Summary and Best Practices

- **By Value:** Safe and recommended for most cases. Modern C++ handles
  efficiency well with move semantics and RVO.
- **By Pointer:** Less common for strings. If needed, prefer smart pointers for
  safety.
- **By Reference:** Efficient but requires careful management of the referenced
  string's lifetime. Suitable for class members or global/static strings.

Remember that strings in C++ are already efficient due to small string
optimizations and move semantics, so returning by value is often the best
choice for simplicity and safety.

## Return for common scenarios - strings vs array

Let's explore examples for each scenario you've described.

### 1. Function Returning a `char` Pointer

A function returning a `char` pointer typically involves dynamic memory
allocation.

**Function Definition:**

```cpp
char* createGreeting() {
    char* greeting = new char[14];
    strcpy(greeting, "Hello, World!");
    return greeting;
}
```

**Usage:**

```cpp
char* message = createGreeting();
// ... use the message ...
delete[] message; // Important to avoid memory leak
```

**Considerations:**

- The caller must remember to `delete[]` the memory to avoid leaks.
- Use smart pointers in modern C++ to manage the memory automatically.

### 2. Function Returning a `char` Array

Returning a local `char` array directly is not possible because it will be
destroyed after the function exits. However, you can return it by encapsulating
it in a struct or class.

**Function Definition:**

```cpp
struct CharArray {
    char arr[14];
};

CharArray createGreetingArray() {
    CharArray c;
    strcpy(c.arr, "Hello, World!");
    return c;
}
```

**Usage:**

```cpp
CharArray arr = createGreetingArray();
// ... use arr.arr ...
```

**Considerations:**

- This returns by value, copying the entire array, which is safe but might be
  inefficient for large arrays.

### 3. Function Returning an Array of Integers

Returning a reference to an array of integers requires the array to be either
global, static, or part of an object's state.

**Function Definition:**

```cpp
int* createIntArray() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr; // Returning a pointer to a static array
}
```

**Usage:**

```cpp
int* myArray = createIntArray();
// ... use myArray ...
```

**Considerations:**

- The array is `static`, so it persists after the function call.
- No need to delete, but the array is shared across all function calls.

### Summary

- When returning a `char` pointer or an array, careful memory management is
  necessary.
- Returning local arrays directly is not possible, but wrapping them in a
  struct or class can work.
- For a static or global array, returning a pointer is safe but shared across
  calls.
- In modern C++, consider using `std::vector`, `std::array`, or `std::string`
  for more safety and convenience.
