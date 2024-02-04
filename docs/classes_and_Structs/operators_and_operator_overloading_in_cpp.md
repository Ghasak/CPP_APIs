# Operators and Operators OverLoad

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Operators and Operators OverLoad](#operators-and-operators-overload)
  - [My Understanding](#my-understanding)
  - [Introduction to operators](#introduction-to-operators)
    - [What Are They?](#what-are-they)
    - [Why We Need Them](#why-we-need-them)
    - [How to Use Them](#how-to-use-them)
    - [Common Code Practices](#common-code-practices)
    - [Things to Be Considered](#things-to-be-considered)
    - [Examples](#examples)
    - [Conclusion](#conclusion)
  - [Operator Overloading](#operator-overloading)
    - [Class Definition with Operator Overloading](#class-definition-with-operator-overloading)
    - [Table of Operator Overloading in C++](#table-of-operator-overloading-in-c)
    - [Additional Common Operators](#additional-common-operators)
  - [References](#references)

<!-- markdown-toc end -->

Usually in `CPP` we can overload the operator. In other programming languages
like Java, it is not possible to perform operator overloading, whereas in C#,
there is some flexibility provided. However, only in C++ is it possible to have
complete control over the overloading of all operators.

## My Understanding

Operators are simply functions that enhance readability and comprehension in
expressions.

This class represents a bank account with a balance and provides methods for
depositing, withdrawing, and inquiring about its value. Instead of using a
function name like istead for depositing, we can use the addition operator (+)
to keep it simple and more readable by users. It's also recommended not to
override operators that cannot be easily understood by users.

## Introduction to operators

In C++, operators are symbols that perform operations on variables and values.
They are fundamental to programming in C++, as they allow you to manipulate
data, perform arithmetic, compare values, assign values, and more. Here's an
overview covering the essentials about operators in C++, including why we need
them, how to use them, common code practices, considerations, and examples.

### What Are They?

Operators in C++ can be categorized into several types based on the operations they perform:

1. **Arithmetic Operators**: Used for performing mathematical calculations like
   addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and
   modulus (`%`).
2. **Relational Operators**: Used to compare two values. Common relational
   operators include equals (`==`), not equals (`!=`), greater than (`>`), less
   than (`<`), greater than or equal to (`>=`), and less than or equal to
   (`<=`).
3. **Logical Operators**: Used to perform logical operations, primarily with
   boolean values (`true` or `false`). These include logical AND (`&&`), logical
   OR (`||`), and logical NOT (`!`).
4. **Assignment Operators**: Used to assign values to variables. The simple
   assignment operator is `=`. There are also compound assignment operators like
   `+=`, `-=`, `*=`, `/=`, and `%=` that perform an operation and assignment in
   one step.
5. **Bitwise Operators**: Perform operations on the binary representations of
   integers. They include AND (`&`), OR (`|`), XOR (`^`), NOT (`~`), left shift
   (`<<`), and right shift (`>>`).
6. **Increment and Decrement Operators**: `++` (increment) and `--` (decrement)
   operators increase or decrease the value of a variable by one, respectively.
7. **Special Operators**: Such as the ternary operator (`?:`), sizeof operator,
   and others.

### Why We Need Them

Operators are essential for performing operations on data, which is a
fundamental aspect of programming. They allow you to:

- Perform arithmetic calculations.
- Make decisions based on comparisons.
- Manipulate data at the bit level.
- Control the flow of the program through logical operations.
- Assign and manipulate the values of variables.

### How to Use Them

The usage depends on the operator type. Here are some examples:

- Arithmetic: `int result = 10 + 5;`
- Relational: `if (a == b)`
- Logical: `if (a > 10 && b < 5)`
- Assignment: `int a = 5; a += 10;`
- Bitwise: `int flags = a | b;`
- Increment/Decrement: `a++;` or `--b;`

### Common Code Practices

- **Use Parentheses for Clarity**: Especially in complex expressions involving
  multiple types of operators, to explicitly define operator precedence.
- **Avoid Side Effects in Expressions**: Incrementing or modifying variables
  within an expression can make your code harder to read and debug.
- **Prefer `+=` Over `=+`**: A common mistake is confusing `+=` with `=+`, the
  latter of which does not exist and will result in a syntax error.

### Things to Be Considered

- **Operator Precedence**: Some operators are evaluated before others. For
  example, multiplication is performed before addition unless parentheses are
  used to change the order of evaluation.
- **Type Conversions**: Be aware of implicit type conversions in expressions,
  especially in arithmetic and relational operations, to avoid unexpected
  results.
- **Overloading Operators**: C++ allows you to define or overload operators for
  your classes, enabling custom behavior when using operators with objects of
  those classes.

### Examples

```cpp
int a = 5, b = 10;
int sum = a + b; // Arithmetic

bool isEqual = (a == b); // Relational

bool isEitherPositive = (a > 0) || (b > 0); // Logical

a += 5; // Assignment

int bitwiseOr = a | b; // Bitwise

a++; // Increment
b--; // Decrement

// Ternary operator
int max = (a > b) ? a : b; // max will be equal to the greater of a and b
```

### Conclusion

Operators in C++ are the building blocks that allow you to perform various
operations on data. Understanding how and when to use them, along with common
practices and considerations, is essential for effective programming in C++.
Experimenting with the examples provided will help reinforce these concepts.

## Operator Overloading

Creating a typical class that overloads basic arithmetic operators (`+`, `-`,
`*`, `/`), the stream operator for `std::cin` and `std::cout`, the equality
operator (`==`), and other common operators in C++ involves defining how these
operators work with instances of the class. Let's start by defining a simple
class that represents a mathematical concept, such as a `Vector2D`, which
represents a two-dimensional vector. This example will help illustrate the
overloading of arithmetic, stream, and equality operators.

### Class Definition with Operator Overloading

```cpp
#include <iostream>

class Vector2D {
public:
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Overload the + operator.
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    // Overload the - operator.
    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    // Overload the * operator (scalar multiplication).
    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // Overload the / operator (scalar division).
    Vector2D operator/(float scalar) const {
        if (scalar != 0) {
            return Vector2D(x / scalar, y / scalar);
        } else {
            return Vector2D();
        }
    }

    // Overload the == operator.
    bool operator==(const Vector2D& v) const {
        return (x == v.x) && (y == v.y);
    }

    // Overload the stream insertion operator for std::cout.
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Overload the stream extraction operator for std::cin.
    friend std::istream& operator>>(std::istream& is, Vector2D& v) {
        is >> v.x >> v.y;
        return is;
    }
};
```

### Table of Operator Overloading in C++

| Operator | Signature Function                                                      | Example                   | Description                                   |
| -------- | ----------------------------------------------------------------------- | ------------------------- | --------------------------------------------- |
| `+`      | `Vector2D operator+(const Vector2D& v) const;`                          | `Vector2D v3 = v1 + v2;`  | Adds two `Vector2D` objects.                  |
| `-`      | `Vector2D operator-(const Vector2D& v) const;`                          | `Vector2D v3 = v1 - v2;`  | Subtracts one `Vector2D` object from another. |
| `*`      | `Vector2D operator*(float scalar) const;`                               | `Vector2D v2 = v1 * 2.0;` | Multiplies `Vector2D` object by a scalar.     |
| `/`      | `Vector2D operator/(float scalar) const;`                               | `Vector2D v2 = v1 / 2.0;` | Divides `Vector2D` object by a scalar.        |
| `==`     | `bool operator==(const Vector2D& v) const;`                             | `if (v1 == v2)`           | Checks if two `Vector2D` objects are equal.   |
| `<<`     | `friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);` | `std::cout << v1;`        | Inserts `Vector2D` object into the stream.    |
| `>>`     | `friend std::istream& operator>>(std::istream& is, Vector2D& v);`       | `std::cin >> v1;`         | Extracts `Vector2D` object from the stream.   |

### Additional Common Operators

Other common operators that might be overloaded depending on the class design
include:

- Copy assignment operator (`=`): Assigns the values from one object to another
  of the same class.
- The unary minus (`-`): Negates the value of an object.
- The increment (`++`) and decrement (`--`) operators: Increases or decreases
  the value of an object.

Overloading these operators makes your class more intuitive to use and
integrates more naturally with C++ language features, allowing objects of your
class to be used much like built-in types.

## References

- [Operators in C++ - cppreference.com](https://en.cppreference.com/w/cpp/language/operators)
