# References in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [References in C++](#references-in-c)
    - [Personal Notes](#personal-notes)
        - [Understanding C++ References](#understanding-c-references)
        - [Example: Modifying a Value](#example-modifying-a-value)
            - [Function Definitions](#function-definitions)
            - [Main Function](#main-function)
            - [Analysis](#analysis)
        - [When to Use References](#when-to-use-references)
    - [Return a reference for a local value](#return-a-reference-for-a-local-value)
        - [Correct Usage: Returning a Reference](#correct-usage-returning-a-reference)
            - [Global Array Declaration](#global-array-declaration)
            - [Function Returning a Reference](#function-returning-a-reference)
            - [Main Function](#main-function-1)
        - [Common Mistake: Returning a Reference to a Local Variable](#common-mistake-returning-a-reference-to-a-local-variable)
            - [Incorrect Function](#incorrect-function)
            - [Main Function](#main-function-2)
        - [Key Takeaways](#key-takeaways)
    - [Example 1- return a reference for C-Style array](#example-1--return-a-reference-for-c-style-array)
        - [Function Definition](#function-definition)
        - [Main Function](#main-function-3)
        - [Explanation](#explanation)
    - [Example 2- return a reference for C-Style array](#example-2--return-a-reference-for-c-style-array)
        - [Function Definition](#function-definition-1)
        - [Main Function](#main-function-4)
        - [Explanation](#explanation-1)
    - [Example 3- return a reference for C-Style array](#example-3--return-a-reference-for-c-style-array)
        - [Example: Function Returning a Reference to a C-Style Array](#example-function-returning-a-reference-to-a-c-style-array)
            - [Function Definition](#function-definition-2)
            - [Main Function](#main-function-5)
        - [Use Cases for Returning a Reference](#use-cases-for-returning-a-reference)
        - [Important Considerations](#important-considerations)
    - [Example 4- return a reference for C-Style array](#example-4--return-a-reference-for-c-style-array)
        - [Function Definition](#function-definition-3)
        - [Main Function](#main-function-6)
        - [Explanation and Use Cases](#explanation-and-use-cases)
        - [When to Use References](#when-to-use-references-1)
    - [Fluent Interfaces/Method Chaining](#fluent-interfacesmethod-chaining)
        - [Class Definition](#class-definition)
        - [Main Function](#main-function-7)
        - [Explanation](#explanation-2)
        - [Use Cases](#use-cases)
    - [Can I achieve the chaining without return a reference? for same example above?](#can-i-achieve-the-chaining-without-return-a-reference-for-same-example-above)
        - [Modified Class Definition](#modified-class-definition)
        - [Main Function](#main-function-8)
        - [Explanation](#explanation-3)
        - [Comparison with Reference Returning](#comparison-with-reference-returning)
            - [How this is helpful compare to return the object itself using for example (\*this) to return the object?](#how-this-is-helpful-compare-to-return-the-object-itself-using-for-example-this-to-return-the-object)
        - [Returning `*this` (Reference to the Same Object)](#returning-this-reference-to-the-same-object)
            - [Advantages:](#advantages)
            - [Example:](#example)
        - [Returning a New Object](#returning-a-new-object)
            - [Advantages:](#advantages-1)
            - [Example:](#example-1)
        - [When to Use Each Approach](#when-to-use-each-approach)

<!-- markdown-toc end -->

Understanding C++ references and knowing when to use them is a crucial skill in
C++ programming. References in C++ provide an alternative way to access an
existing variable, akin to aliases. Let's dive into the details and then
illustrate this with a comprehensive example.

## Personal Notes

1. References are actually aliases for variable_name.
2. You can do everything with references that you can also do with pointers,
   pointers are much powerful than references.
3. Whenever possible, try to use references as they provide clean code and a
   convenient way to manage object resource usage.
4. Passing an alias for a function in function/method calling is similar to
   passing the variable itself (this is different from Rust and I feel it lacks
   consistency).

### Understanding C++ References

1. **Definition**: A reference is essentially an alias for another object. It
   must be initialized when declared and cannot be made to refer to a different
   object later.

2. **Syntax**: A reference is declared using the `&` symbol. For example,
   `int& ref = var;` creates a reference `ref` to the variable `var`.

3. **Use Cases**:

   - **Function Arguments**: Passing variables by reference to functions. This
     avoids copying large objects and allows the function to modify the original
     object.
   - **Return Values**: Returning references from functions can be efficient
     but be cautious of returning references to local objects; they become
     dangling once the function returns.
   - **Alias Creation**: Creating an alias for a variable, which can improve
     readability and ease of use in certain contexts.

4. **Reference vs Pointer**: Unlike pointers, references are always
   dereferenced automatically and cannot be null or uninitialized. They offer a
   more straightforward syntax and safer access compared to pointers.

### Example: Modifying a Value

Let's consider a simple example where we want to modify the value of an integer
using different methods: direct passing, using pointers, and using references.

#### Function Definitions

1. **Direct Passing**:

   ```cpp
   void modifyDirect(int value) {
       value = 10;
   }
   ```

2. **Pointers**:

   ```cpp
   void modifyPointer(int* value) {
       *value = 10;
   }
   ```

3. **References**:
   ```cpp
   void modifyReference(int& value) {
       value = 10;
   }
   ```

#### Main Function

```cpp
int main() {
    int x = 5;

    // Direct passing
    modifyDirect(x);
    cout << "Direct passing: " << x << endl; // x is still 5

    // Pointers
    modifyPointer(&x);
    cout << "Pointer: " << x << endl; // x is now 10

    // References
    modifyReference(x);
    cout << "Reference: " << x << endl; // x remains 10

    return 0;
}
```

#### Analysis

- **Direct Passing**: The value of `x` is copied into the function, so the
  original `x` is not modified.
- **Pointers**: The address of `x` is passed, allowing the function to modify
  `x` directly.
- **References**: The function receives an alias to `x`, so any modifications
  are reflected in `x`.

### When to Use References

- **Large Data Structures**: When dealing with large data structures (like big
  classes or structs), passing them by reference avoids the overhead of copying.
- **Operator Overloading**: When overloading certain operators, like assignment
  (`=`), using references is standard practice.
- **Consistency**: If a function should not change the argument and it's not
  primitive data type, consider using `const` reference to avoid unnecessary
  copying.

In summary, references in C++ provide a more intuitive and safer alternative to
pointers in many scenarios. They are particularly useful when you want to avoid
the overhead of copying objects and when you need to modify the original data
passed to a function.

## Return a reference for a local value

Returning a reference from a function can be powerful, but it also comes with
certain risks, especially when returning references to local variables. Let's
illustrate this with two examples. The first example will demonstrate the
correct use of returning a reference, and the second will highlight a common
mistake.

### Correct Usage: Returning a Reference

In this correct example, we will have a function that returns a reference to an
element in a global array.

#### Global Array Declaration

```cpp
const int SIZE = 10;
int myArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
```

#### Function Returning a Reference

```cpp
int& getElement(int index) {
    return myArray[index]; // Return a reference to the array element
}
```

#### Main Function

```cpp
int main() {
    // Change the 4th element
    getElement(3) = 10;

    // Access the modified element
    cout << "Modified Element: " << myArray[3] << endl; // Outputs 10

    return 0;
}
```

In this example, `getElement` returns a reference to an element in `myArray`.
Since `myArray` is a global variable, it's not destroyed when `getElement`
returns. Therefore, the reference remains valid.

### Common Mistake: Returning a Reference to a Local Variable

Now, let's see an example of a common mistake when returning a reference.

#### Incorrect Function

```cpp
int& getNumber() {
    int localNumber = 5;
    return localNumber; // WRONG: Returning a reference to a local variable
}
```

#### Main Function

```cpp
int main() {
    int& numRef = getNumber();
    cout << "Number: " << numRef << endl; // Undefined behavior

    return 0;
}
```

In this incorrect example, `getNumber` returns a reference to `localNumber`, a
local variable. When the function returns, `localNumber` goes out of scope, and
the memory it occupied may be used for something else. As a result, the
reference `numRef` in `main` becomes a dangling reference, leading to undefined
behavior.

### Key Takeaways

- Returning a reference can be useful for providing access to internal data
  structures (like elements of an array or class members).
- **Never** return a reference to a local variable. Local variables are
  destroyed once the function returns, making any references to them invalid.
- If you need to return a local object, return it by value. Modern C++
  compilers will often optimize this to prevent performance hits due to copying.

## Example 1- return a reference for C-Style array

Certainly! In this example, we'll create a function that takes a C-style array
and initializes its elements to the value of 100. The function will then return
a reference to this array. This is a good example to demonstrate how you can
manipulate an array in a function and then access the updated array outside the
function.

### Function Definition

First, we define a function that takes an array as an argument and returns a
reference to an array of integers.

```cpp
int (&initializeArray(int arr[], size_t size))[3] {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = 100;  // Setting each element to 100
    }
    return arr; // Returning a reference to the array
}
```

### Main Function

Now, we'll use this function in `main` to initialize an array and then access it.

```cpp
#include <iostream>

using namespace std;

// Function prototype
int (&initializeArray(int arr[], size_t size))[3];

int main() {
    int my_array[3];

    // Initialize the array and get the reference
    int (&refArray)[3] = initializeArray(my_array, 3);

    // Now refArray refers to the initialized array
    cout << "Array elements: ";
    for (int i = 0; i < 3; ++i) {
        cout << refArray[i] << " "; // Should print 100 100 100
    }
    cout << endl;

    return 0;
}
```

### Explanation

- The function `initializeArray` takes a pointer to an array and its size as
  arguments. This function iterates over the array and sets each element to 100.
- The function's return type is a bit tricky: `int (&)[3]`. This syntax means
  the function returns a reference to an array of three integers.
- In the `main` function, the array `my_array` is passed to `initializeArray`,
  and the reference returned is stored in `refArray`.
- We then use `refArray` to access the initialized values of `my_array`.

This example demonstrates how you can modify a C-style array inside a function
and return a reference to this array for further use. This approach is
beneficial when working with legacy code or in situations where C-style arrays
are preferred or required.

## Example 2- return a reference for C-Style array

In this example, I will create a function that takes a C-style array by
reference and performs an arithmetic operation on each element of the array.
The function will return `void` since it modifies the array in-place without
needing to return it.

### Function Definition

The function, let's call it `applyArithmetic`, will take a reference to an
array and its size. It will then iterate over the array, applying an arithmetic
operation to each element. In this case, let's say we add 5 to each element.

```cpp
void applyArithmetic(int (&arr)[3]) {
    for (int& element : arr) {
        element += 5; // Adding 5 to each element
    }
}
```

### Main Function

Now, let's use this function in `main` to modify an array.

```cpp
#include <iostream>

using namespace std;

// Function prototype
void applyArithmetic(int (&arr)[3]);

int main() {
    int my_array[3] = {1, 2, 3};

    // Apply arithmetic operation
    applyArithmetic(my_array);

    // Output the modified array
    cout << "Modified Array: ";
    for (int element : my_array) {
        cout << element << " "; // Should print 6 7 8
    }
    cout << endl;

    return 0;
}
```

### Explanation

- The `applyArithmetic` function takes a reference to a 3-element integer
  array. It uses a range-based `for` loop to access and modify each element of
  the array.
- Since the array is passed by reference, all changes made within
  `applyArithmetic` are reflected in the original array `my_array` in the `main`
  function.
- After calling `applyArithmetic`, the `main` function prints the modified
  array. Each element has been incremented by 5.

This example demonstrates how a function can directly modify the elements of a
C-style array passed by reference. It's an efficient way to manipulate arrays
as it avoids copying the array elements.

## Example 3- return a reference for C-Style array

Returning a reference from a function, particularly for a C-style array, can be
a powerful feature in C++. It allows you to directly manipulate and access
array elements outside the function that processes the array. This approach is
often used for efficiency reasons, as it avoids copying large arrays.

### Example: Function Returning a Reference to a C-Style Array

Let's create an example where a function takes a reference to a C-style array,
performs some operations, and then returns a reference to the same array.

#### Function Definition

Suppose we have a function that scales each element of an array by a given factor.

```cpp
int (&scaleArray(int (&arr)[3], int factor))[3] {
    for (int& element : arr) {
        element *= factor;
    }
    return arr; // Returning a reference to the array
}
```

#### Main Function

Here's how you can use this function:

```cpp
#include <iostream>

using namespace std;

// Function prototype
int (&scaleArray(int (&arr)[3], int factor))[3];

int main() {
    int myArray[3] = {1, 2, 3};

    // Scale the array elements
    int (&refArray)[3] = scaleArray(myArray, 2);

    // Print the scaled array
    cout << "Scaled Array: ";
    for (int element : refArray) {
        cout << element << " "; // Should print 2 4 6
    }
    cout << endl;

    // Demonstrating that myArray is also modified
    cout << "Original Array: ";
    for (int element : myArray) {
        cout << element << " "; // Will also print 2 4 6
    }
    cout << endl;

    return 0;
}
```

### Use Cases for Returning a Reference

1. **Efficiency**: When dealing with large arrays or data structures, returning
   a reference avoids the cost of copying the entire array.
2. **Chaining Operations**: Returning a reference allows for chaining
   operations on the array. For example, you can call multiple functions in a
   row that each modify the array.
3. **Direct Manipulation**: It enables direct manipulation of the array
   contents in the calling scope, as any changes made to the reference are
   reflected in the original array.
4. **Dynamic Data Structures**: If the array is part of a dynamic data
   structure (like a class or struct), returning a reference can provide direct
   access to modify specific elements without exposing the entire structure.

### Important Considerations

- **Lifetime of the Array**: Ensure that the array's lifetime is managed
  correctly. Avoid returning references to local arrays declared inside the
  function, as they will be destroyed when the function returns.
- **Safety and Encapsulation**: Returning a reference can break encapsulation
  in object-oriented design. Be cautious and ensure it aligns with your design
  principles.
- **Const Correctness**: If you do not intend for the calling function to
  modify the array, return a `const` reference to enforce read-only access.

## Example 4- return a reference for C-Style array

We can certainly achieve similar functionality without returning a reference
from a function. Instead, you can create a function that takes a reference to
an array as a parameter and performs operations directly on it. This approach
is actually more common and straightforward, as it avoids the complexities and
potential risks associated with returning references.

- Let's modify the previous example to illustrate this. We'll create a function
  that takes a reference to a C-style array and scales its elements, without
  returning a reference.

### Function Definition

In this example, the function `scaleArray` will take a reference to an array
and an integer factor, and it will scale each element of the array by this
factor.

```cpp
void scaleArray(int (&arr)[3], int factor) {
    for (int& element : arr) {
        element *= factor; // Scale each element by the factor
    }
}
```

### Main Function

Now, let's use this function to modify an array in the `main` function.

```cpp
#include <iostream>

using namespace std;

// Function prototype
void scaleArray(int (&arr)[3], int factor);

int main() {
    int myArray[3] = {1, 2, 3};

    // Scale the array elements
    scaleArray(myArray, 2);

    // Print the scaled array
    cout << "Scaled Array: ";
    for (int element : myArray) {
        cout << element << " "; // Should print 2 4 6
    }
    cout << endl;

    return 0;
}
```

### Explanation and Use Cases

- **Direct Manipulation**: The `scaleArray` function directly manipulates the
  elements of the array passed to it. Since the array is passed by reference, all
  changes are reflected in the original array in `main`.
- **Simplicity and Clarity**: This approach is simpler and more intuitive, as
  it clearly modifies the array in place without the need to deal with returning
  and capturing references.
- **Safety**: By not returning a reference, you avoid potential issues like
  accidentally returning a reference to a local variable.

### When to Use References

Returning a reference from a function can be useful in specific scenarios, such as:

1. **Fluent Interfaces/Method Chaining**: When designing classes that use
   method chaining, where each method returns a reference to the object itself
   for consecutive calls.
2. **Accessing Class Members**: When providing controlled access to class
   members, especially in operator overloading or getter functions that allow
   modification of private members.
3. **Avoiding Copies in Read-Only Scenarios**: When returning a large object
   that shouldn't be modified, where a `const` reference can prevent copying
   and enforce read-only access.

In most other cases, especially with simple operations on arrays or basic data
types, directly modifying the passed reference (like in your modified example)
is more common and appropriate.

## Fluent Interfaces/Method Chaining

Fluent interfaces and method chaining are common in object-oriented
programming, particularly in C++. This design allows for the chaining of method
calls by returning a reference to the object itself (`*this`) from each method.
It's often used in builder patterns, settings configurations, and similar
scenarios where consecutive method calls are used to configure an object.

- Let's create an example of a simple `StringBuilder` class that demonstrates
  this fluent interface pattern. This class will allow you to append strings in a
  chain of method calls.

### Class Definition

```cpp
#include <iostream>
#include <string>

class StringBuilder {
private:
    std::string value;

public:
    // Constructor
    StringBuilder() {}

    // Method for appending text
    StringBuilder& append(const std::string& str) {
        value += str;
        return *this; // Returning a reference to the current object
    }

    // Method to get the final string
    std::string build() const {
        return value;
    }
};
```

### Main Function

Using the `StringBuilder` class with method chaining:

```cpp
int main() {
    StringBuilder builder;

    // Chaining method calls
    builder.append("Hello, ").append("world! ").append("This is a test.");

    std::cout << "Result: " << builder.build() << std::endl;

    return 0;
}
```

### Explanation

- In the `StringBuilder` class, the `append` method concatenates a string to
  the current value and then returns a reference to the current object (`*this`).
  This allows for another call to `append` (or any other method returning
  `StringBuilder&`) to be chained directly after it.
- In the `main` function, we create an instance of `StringBuilder` and then
  chain several calls to `append`. This sequence of method calls is made possible
  by each `append` returning a reference to the `StringBuilder` instance.
- Finally, `build` is called to get the concatenated string.

### Use Cases

Fluent interfaces are often used in:

1. **Builder Patterns**: To build complex objects step by step.
2. **Configuration Objects**: For configuring objects in a readable and concise
   manner.
3. **APIs that Encourage Step-by-Step Manipulation**: Such as query builders or
   test assertion libraries.

This pattern makes the code more readable and expressive, particularly when
configuring or building objects through a series of steps.

## Can I achieve the chaining without return a reference? for same example above?

Yes, you can achieve a form of chaining without returning a reference, but it
changes the nature of the chaining. Instead of chaining methods on the same
object instance, you'd be chaining on new copies of the object created at each
step. This approach is generally less efficient and can be less intuitive, but
it's technically possible.

- Let's modify the `StringBuilder` example to demonstrate this approach. In
  this version, each `append` method will return a new `StringBuilder` object
  instead of a reference to the current object.

### Modified Class Definition

```cpp
#include <iostream>
#include <string>

class StringBuilder {
private:
    std::string value;

public:
    // Constructor with value
    StringBuilder(const std::string& val = "") : value(val) {}

    // Method for appending text
    StringBuilder append(const std::string& str) const {
        return StringBuilder(value + str); // Returning a new object
    }

    // Method to get the final string
    std::string build() const {
        return value;
    }
};
```

### Main Function

Using the modified `StringBuilder` class:

```cpp
int main() {
    StringBuilder builder;

    // Chaining method calls creates new objects at each step
    StringBuilder newBuilder = builder.append("Hello, ").append("world! ").append("This is a test.");

    std::cout << "Result: " << newBuilder.build() << std::endl;

    return 0;
}
```

### Explanation

- In this modified `StringBuilder`, each call to `append` creates and returns a
  new `StringBuilder` object. This new object contains the concatenated string up
  to that point.
- The chaining works, but it's important to note that each `append` creates a
  new object. This means that the original `builder` object remains unchanged,
  and `newBuilder` is a separate object containing the final string.
- This method is less efficient due to the repeated creation of new objects and
  might be less intuitive for a builder pattern.

### Comparison with Reference Returning

- **Efficiency**: Returning new objects is less efficient than returning a
  reference to the same object, especially for large or complex objects.
- **Mutability**: In the reference-returning approach, the original object is
  modified. In the new-object approach, the original object remains unchanged.
- **Use Cases**: Returning new objects can be appropriate in functional
  programming paradigms where immutability is a key principle.

In summary, while you can implement chaining by returning new objects, it's
generally more efficient and idiomatic in C++ to use method chaining with
references, especially for builder patterns and similar constructs.

#### How this is helpful compare to return the object itself using for example (\*this) to return the object?

Returning a reference to the object itself using `*this` in method chaining is
different from returning a new object, and each approach has its specific use
cases and advantages. Let's compare these two approaches using the
`StringBuilder` example for clarity.

### Returning `*this` (Reference to the Same Object)

#### Advantages:

1. **Efficiency**: This is more memory-efficient as it avoids creating new
   objects. It's especially beneficial for large objects or when methods are
   called many times in a chain.
2. **Mutability**: It allows methods to modify the state of the same object.
   This is typically what you want in a builder pattern, where each method call
   modifies the object's state and prepares it for the next operation.
3. **Idiomatic**: This approach is more common and idiomatic in C++ for builder
   patterns and fluent interfaces. It aligns with the C++ principle of explicit
   control over object lifetimes and memory management.

#### Example:

```cpp
StringBuilder& append(const std::string& str) {
    value += str;
    return *this; // Returning a reference to the current object
}
```

### Returning a New Object

#### Advantages:

1. **Immutability**: This approach is useful when you want to maintain the
   immutability of objects. Each method call returns a new object, leaving the
   original unchanged. This is a key principle in functional programming.
2. **State Preservation**: It allows preserving the state of the original
   object, which might be useful in certain scenarios where you need to keep
   the original state intact for later use.
3. **Thread Safety**: Immutable objects are inherently thread-safe, as their
   state cannot be modified once created. This can simplify concurrent
   programming.

#### Example:

```cpp
StringBuilder append(const std::string& str) const {
    return StringBuilder(value + str); // Returning a new object
}
```

### When to Use Each Approach

- Use **returning `*this`** for scenarios where you need to modify the state of
  the object across a chain of method calls. This is typical in builder patterns,
  object configurations, and stateful fluent interfaces.
- Use **returning a new object** in situations where immutability is desired,
  such as in functional programming patterns, thread-safe operations, or when you
  need to preserve the original object's state.

In summary, the choice between these two approaches depends on the specific
requirements of your application and design principles you are following. In
C++, returning `*this` for method chaining is commonly used due to its
efficiency and alignment with the language's emphasis on control over object
state and memory.
