# Enums in C++

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Enums in C++](#enums-in-c)
    - [Notes to be taken](#notes-to-be-taken)
    - [Introduction](#introduction)
        - [Why We Need Enums](#why-we-need-enums)
        - [How to Use Enums](#how-to-use-enums)
            - [Basic Syntax](#basic-syntax)
            - [Example](#example)
        - [Things to Take Care When Dealing with Enums](#things-to-take-care-when-dealing-with-enums)
            - [Example of Scoped Enum (enum class)](#example-of-scoped-enum-enum-class)
        - [Things to Avoid](#things-to-avoid)
        - [Advanced Concepts](#advanced-concepts)
            - [Example of Enum Base](#example-of-enum-base)
            - [Summary Table](#summary-table)
        - [Examples](#examples)
            - [Basic Enum Example](#basic-enum-example)
            - [Enum Class Example](#enum-class-example)
            - [Using Enum with Switch Case](#using-enum-with-switch-case)
    - [Choose between Enum vs Struct?](#choose-between-enum-vs-struct)
        - [Enums](#enums)
        - [Structs](#structs)
        - [Practical Reason Not Using Struct Instead of Enum](#practical-reason-not-using-struct-instead-of-enum)

<!-- markdown-toc end -->

## Notes to be taken

- They represent only integer values bundled together
- We utilize them when we desire to extract merely one value from among them, in
  contrast to `struct` that serves as a means of building a novel type and
  requires all its variations.
- You cannot name same `fields` of an Enum even with two different names, for example this is not allowed:
  ```cpp
  +-------------------------------------+
  |            NOT-ALLOWED              |
  +-------------------------------------+
  |  // We use this                     |
  |  enum Choose { A, B, C };           |
  |  // You cannot name the `enum`      |
  |  // with same fields (choices)      |
  |  enum AnotherChoose {               |
  |      A = 0,                         |
  |      B = 2,                         |
  |      C = 100,                       |
  |  };                                 |
  +-------------------------------------+
  ```

## Introduction

C++ enums, short for enumerations, are a user-defined data type that allows you
to assign symbolic names to integral constants, making the code more readable
and maintainable. Enums can make your code more clearly defined and easier to
understand, as they replace numeric codes or flags with descriptive names.

### Why We Need Enums

Enums are used for representing a group of related constants in a programming
language. They are particularly useful when you have a variable that can only
take one out of a small set of possible values. Using enums can help you to:

- **Improve code readability:** By using meaningful names instead of numbers.
- **Reduce errors:** By limiting the values a variable can hold to those defined
  in the enum.
- **Facilitate documentation:** Making the code self-explanatory and easier to
  understand.

### How to Use Enums

#### Basic Syntax

```cpp
enum EnumName {
    Value1,
    Value2,
    Value3,
    // ...
};
```

- **EnumName:** The name of the enumeration.
- **Value1, Value2, Value3:** The enumerator names are constants of type
  `EnumName`.

#### Example

```cpp
enum Color {
    RED,
    GREEN,
    BLUE
};

Color favoriteColor = RED;
```

### Things to Take Care When Dealing with Enums

- **Underlying Type:** By default, the underlying type of the enum is `int`, but
  you can specify another integral type (like `short`, `unsigned int`, etc.).
- **Scope:** In C++11 and later, enum classes (scoped enums) are introduced to
  solve the scope and strong typing issues. With enum classes, the enum's names
  are local to the enum and you need to use the enum name to access the values.
- **Initialization:** Enumerators can be initialized with a specific integer
  value, but each enumerator must have a unique value.
- **Conversion:** Implicit conversion from enum to integer types is allowed, but
  converting from an integer to an enum type requires an explicit cast.

#### Example of Scoped Enum (enum class)

```cpp
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction movingDirection = Direction::UP;
```

### Things to Avoid

- **Avoid relying on the underlying integer values** of enums, unless you're
  interfacing with code that expects those specific values.
- **Avoid unnamed enums** if the enumeration is used in multiple places, to
  enhance readability and maintainability.

### Advanced Concepts

- **Enum base:** You can specify an underlying type for the enum to control the
  size and signedness of the enum type.
- **Forward declaration:** C++11 allows forward declarations of enums, which is
  useful for reducing compile-time dependencies.

#### Example of Enum Base

```cpp
enum Color : unsigned int {
    RED,
    GREEN,
    BLUE
};
```

#### Summary Table

| Concept         | Description                                                                          |
| --------------- | ------------------------------------------------------------------------------------ |
| Basic Usage     | Define a set of named integral constants.                                            |
| Enum Classes    | Scoped and strongly typed enums, preventing name clashes and implicit conversions.   |
| Underlying Type | Specify an underlying type to control size and type.                                 |
| Initialization  | Enumerators can be initialized with specific values.                                 |
| Scope Issues    | Use enum classes to avoid global namespace pollution.                                |
| Conversion      | Implicit conversion to integers is allowed; explicit conversion is needed otherwise. |

### Examples

#### Basic Enum Example

```cpp
enum Day { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };
Day today = Day::FRIDAY;
```

#### Enum Class Example

```cpp
enum class Month { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
Month birthMonth = Month::DECEMBER;
```

#### Using Enum with Switch Case

```cpp
enum class Season { SPRING, SUMMER, AUTUMN, WINTER };

Season currentSeason = Season::SUMMER;

switch (currentSeason) {
    case Season::SPRING:
        // Spring actions
        break;
    case Season::SUMMER:
        // Summer actions
        break;
    // Other cases
}
```

These examples and guidelines cover most aspects of using enums in C++. Enums
offer a powerful way to work with sets of constants, making your code more
readable and maintainable.

## Choose between Enum vs Struct?

Choosing between enums and structs in C++ depends on the specific use case
you're dealing with. While both are user-defined types, they serve different
purposes:

### Enums

- **Purpose:** Enums are used to define a set of named integral constants. They
  are ideal for variables that can only have one out of a limited set of
  possible values.
- **Use Case:** Enums are best used when you want to represent a variable that
  should only take on one of several predefined values, making your code more
  readable. For example, days of the week, states of a state machine, error
  codes, etc.

- Using `Enum` when you have a `pattern` that need variant, a selection of one
  option among many, that you access one at a time, which is a bit different
  from `strcut` which is used to store many options and use them all combined.

- **Advantages:**

  - Improve code readability and maintainability by replacing magic numbers with
    meaningful names.
  - Restrict the values a variable can take, reducing errors.

### Structs

- **Purpose:** Structs are used to group together variables (possibly of
  different types) into a single type, making it easier to manage related data.
- **Use Case:** Structs are best used when you need to represent a composite
  data type that encapsulates multiple pieces of data that are logically
  related. For example, a Point struct might contain x and y coordinates, or a
  Date struct might contain day, month, and year fields.
- **Advantages:**
  - Enable the grouping of different data types into a single logical unit.
  - Facilitate the passing of grouped data to functions or returning grouped data from functions.
  - Support data encapsulation and the principles of object-oriented programming.

### Practical Reason Not Using Struct Instead of Enum

A practical reason for choosing an enum over a struct is when your primary
concern is to define a variable that has a small, fixed set of possible values,
each of which is mutually exclusive and collectively exhaustive. Using an enum
makes it clear to anyone reading your code that the variable can only have one
of the limited set of values, and it helps the compiler enforce this rule.

- For example, consider you have a variable that represents the status of a
  network connection, which can be either `Connected`, `Disconnected`,
  `Connecting`, or `Disconnecting`. Using an enum for these states makes it
  immediately clear that these are the only possible states for your network
  connection variable, and it cannot hold any other value or combination of
  values. A struct, on the other hand, would allow for the possibility of
  holding multiple pieces of data, which is not what you want in this scenario.
  Additionally, using a struct would require more code to ensure that only valid
  state combinations are represented, which is automatically handled by using an
  enum.
- In summary, use enums when you need to represent a single value from a
  predefined set, and use structs when you need to encapsulate related but
  distinct pieces of data into a single type.
