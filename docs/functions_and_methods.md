# Functions and Methods

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Functions and Methods](#functions-and-methods)
  - [1. My Understanding](#1-my-understanding)
  - [2. Function/method syntax](#2-functionmethod-syntax)
    - [2.1. Common Coding Practices for Function Creation in C++](#21-common-coding-practices-for-function-creation-in-c)
    - [2.2. Example Function](#22-example-function)
  - [3. Return types of function signature](#3-return-types-of-function-signature)
    - [3.1. Points to Note:](#31-points-to-note)
  - [4. Passing arguments to parameters](#4-passing-arguments-to-parameters)

<!-- markdown-toc end -->

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

[outside the function]  --> +--+                                                                    +--+
                        --> |  |                    +-------------------+                           |  |
int var_x = 10;         --> |  |  o---- INPUT --->  |  Function/method  |    o---- OUTPUT --->      |  |
                        --> |  |                    +-------------------+                           |  |
                        --> |  |     [signature]   local defintion variables  [return]              |  |
                        --> +--+ <----------------------  Scope  -------------------------------->  +--+
                                                      int var_y = 10;                                var_x still alive
                                                                                                     var_y died at exit of the scope of the function/method
```

- In regards to references, always return a reference of an entity, such as a
  variable, object, or similar, that is created outside the function/method body
  to avoid creating a dangling reference.

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
