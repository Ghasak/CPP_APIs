# Constexpr in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Constexpr in C++](#constexpr-in-c)
  - [-](#-)
  - [Why Use `constexpr`?](#why-use-constexpr)
  - [Restrictions](#restrictions)
  - [More Examples](#more-examples)
    - [`constexpr` with Constructors](#constexpr-with-constructors)
    - [`constexpr` for Compile-time Assertions](#constexpr-for-compile-time-assertions)
    - [Conclusion](#conclusion)
    - [Example](#example)
    - [`static`](#static)
    - [`constexpr`](#constexpr)
    - [`float`](#float)
    - [`PI`](#pi)
    - [`= 3.141592653f;`](#-3141592653f)
    - [Summary](#summary)

<!-- markdown-toc end -->

`constexpr` is a keyword introduced in C++11 that allows the expression of
certain kinds of constant expressions in a clear, concise, and type-safe manner.
The primary purpose of `constexpr` is to declare that the value of a variable or
the result of a function can be evaluated at compile time. This means that the
compiler can compute the value before the program runs, which can lead to more
efficient code and the use of constants in places where only compile-time
constant expressions are allowed (e.g., array sizes, template arguments).

### Basic Usage

When you declare a variable with `constexpr`, you are telling the compiler that
this variable's value is a constant that can be determined during compilation.
For example:

```cpp
constexpr int square(int n) {
    return n * n;
}

constexpr int squaredValue = square(5);
```

In this code, `square(5)` is evaluated at compile time, and `squaredValue` will
be initialized with the result (`25`) before the program runs. The function
`square` is also marked as `constexpr`, indicating it can be used in constant
expressions.

### Why Use `constexpr`?

1. **Performance:** `constexpr` allows certain computations to be moved from
   runtime to compile time, potentially improving performance by reducing what
   needs to be computed while the program is running.
2. **Type Safety:** It enables the use of constant expressions while retaining
   type safety and clear syntax, as opposed to preprocessor macros which are
   type-agnostic and can lead to obscure errors.
3. **Compile-time Validation:** When you use `constexpr` for variables and
   functions, it ensures that these can be evaluated at compile time, adding an
   extra layer of compile-time validation to your code.

### Restrictions

Not everything can be `constexpr`. For a function to be `constexpr`, certain
conditions must be met:

- The function body must be sufficiently simple (e.g., it must not contain
  static or thread-local variables, dynamic memory allocation, or calls to
  non-`constexpr` functions).
- It should contain only a return statement in C++11 (this restriction has been
  relaxed in later standards, allowing if-statements, loops, and more, as long
  as they adhere to the constexpr evaluation rules).

### More Examples

Here are more examples to illustrate how `constexpr` can be used:

#### `constexpr` with Constructors

You can use `constexpr` with constructors to initialize objects at compile time:

```cpp
class Point {
public:
    constexpr Point(double x, double y) : x_(x), y_(y) {}

    constexpr double x() const { return x_; }
    constexpr double y() const { return y_; }

private:
    double x_, y_;
};

constexpr Point origin(0.0, 0.0);
```

Here, `origin` is a `constexpr` object of type `Point`, and its value is determined at compile time.

#### `constexpr` for Compile-time Assertions

`constexpr` can be used together with `static_assert` for compile-time assertions:

```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

static_assert(factorial(5) == 120, "Unexpected factorial value");
```

This `static_assert` checks the result of `factorial(5)` at compile time and
produces a compile-time error if the assertion fails.

### Conclusion

`constexpr` is a powerful feature in C++ that facilitates the definition of
constants and constant expressions. It enhances type safety, allows for
compile-time optimizations, and can be used in a variety of contexts, including
functions, objects, and template arguments, to produce cleaner, faster, and more
reliable code.

### Example

In C++, the line `static constexpr float PI = 3.141592653f;` combines several
keywords and concepts to define a constant. Let's break down each term:

### `static`

- **Usage Context:** This keyword has different meanings depending on its
  context. When used in a class, it means that the variable or method is
  associated with the class itself rather than any instance of the class. When
  used outside of a class, as in your example, it gives the variable internal
  linkage, meaning it is only accessible within the translation unit it is
  defined in (typically a single .cpp file and its included headers). This
  prevents conflicts with the same named variables in other translation units.
- **Purpose:** In your example, `static` ensures that `PI` is local to the file,
  preventing name clashes and redefinitions in other parts of the program.

### `constexpr`

- **Usage Context:** A `constexpr` specifier declares that it's possible to
  evaluate the value of a variable or the result of a function at compile time.
  This is used for constants, as well as for optimizing calculations and
  ensuring compile-time evaluations where possible.
- **Purpose:** By marking `PI` as `constexpr`, you're informing the compiler
  that `PI` is a compile-time constant, allowing for potential optimizations.
  This can be particularly useful for array sizes, template arguments, and other
  contexts where compile-time values are necessary.

### `float`

- **Usage Context:** This is a floating-point type that specifies the type of
  the variable. `float` is a single-precision floating-point data type used in
  C++ for storing decimal numbers.
- **Purpose:** Declaring `PI` as a `float` specifies that it is a floating-point
  number with single precision, suitable for calculations that require decimal
  precision but not the double precision of a `double` type.

### `PI`

- **Usage Context:** This is the name of the variable. In this case, it's a
  conventional name for the mathematical constant Pi (π).
- **Purpose:** Naming the variable `PI` makes it clear that it represents the
  constant Pi, which is commonly used in mathematical and geometric
  calculations.

### `= 3.141592653f;`

- **Usage Context:** This initializes `PI` with the value `3.141592653`, and the
  `f` suffix indicates that this literal is a `float`, ensuring that the
  compiler treats it as single precision.
- **Purpose:** This sets the initial value of `PI` to an approximation of Pi.
  The `f` suffix is crucial for matching the type (`float`) of the variable,
  ensuring that the literal is not implicitly treated as a `double`, which is
  the default for floating-point literals.

### Summary

Putting it all together, `static constexpr float PI = 3.141592653f;` declares
`PI` as a compile-time, file-local, single-precision floating-point constant
initialized to an approximation of Pi. This is useful for ensuring that `PI` can
be used for compile-time calculations where applicable, while also being
restricted to the file scope to avoid naming conflicts.
