# Constant Usage

## Introduction

- Syntax does not modify the variable as it is used for something that needs to
  be preserved, which is why it is not considered a variable.
  - Usage with pointers
  - Usage with classes

```cpp
const int version_number_majro {2};
const int version_number_minor{1};
```

## Explanation in Action

```sh
     int MAX_AGE = 90;

     +---------+ +---------+ +---------+ +---------+
     |    1    | |    2    | |    3    | |    4    |   <- 4-byte count
     +---------+ +---------+ +---------+ +---------+
     [ 0 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ] [ 0 ]   <- Hex representation
     [--------- The content of MAX_AGE ------------]   <- The content can reassigned or set to any value, (now it is `90`)

     ^
     |
    +--+  0x16d5d1e6c
    |0 |
    |x |   <- memeory address (pointer) refer to first byte of this `MAX_AGE` intger.(number here for demo only)
    |1 |
    |6 |
    |d |
    |5 |
    +--+

     ^
     |
     +-- The address `0x16d5d1e6c` can be assign to any other memory address.
     (Just an integer number in the memeory to refer to our current int `MAX_AGE`)

```

- From the diagram above, it shows that we can modify both the content and
  pointer of the `MAX_AGE`. However, using the `const` keyword prevents any
  changes and keeps their values constant during the runtime of our program.

- **RULE OF THUMB**:

  - const before (\*) will prevent from chaning this content of the `MAX_AGE`.
    - This form has two way to write it:
    ```cpp
       const int* ptr = &MAX_AGE;
       int const* ptr = &MAX_AGE;
    ```
  - const after (\*) will prevent from chaing the memeory address (pointer) and cannot assign it to another memeory address.
    - This form has only one way:
    ```cpp
        int* const ptr = &MAX_AGE;
    ```
  - blocking both the memeory addreess and the content form changing using:

  ```cpp
          int const* const ptr = &MAX_AGE;
          const int* const ptr = &MAX_AGE;
  ```

- Although this syntax might seem confusing, there is actually a simple rule: the const keyword applies
  to whatever is directly to its left. Consider this line again:

```cpp
int const* const ip { nullptr };
```

- From left to right, the first const is directly to the right of the word int.
  Thus, it applies to the int to which ip points.
- Therefore, it specifies that you cannot change the values to which ip points.
  The second const is directly to the right of the \*.
- Thus, it applies to the pointer to the int, which is the ip variable.
  Therefore, it specifies that you cannot change ip (the pointer) itself. The
  reason this rule becomes confusing is an exception. That is, the first const
  can go before the vari- able like this:

```cpp
const int* const ip { nullptr };
```

- This “exceptional” syntax is used much more commonly than the other syntax.
- You can extend this rule to any number of levels of indirection, as in this
  example:

```cpp
const int * const * const * const ip { nullptr };
```

- **NOTE** Here is another easy-to-remember rule to figure out complicated
  variable declarations: read from right to left. For example, int* const ip
  reads from right to left as “ip is a const pointer to an int.” Further, int
  const* ip reads as “ip is a pointer to a const int,” and const int\* ip reads as
  “ip is a pointer to an int constant.”

## Usage of const

Creating a table for the variations of `const` in C++ with pointers can be very
helpful for understanding how `const` modifies pointer behavior. Below is a
table that covers the common variations, along with their descriptions,
examples, usage, and benefits:

| idx | **Variation**           | **Description**                                                                             | **Example**                  | **Usage**                                                                                                         | **Benefit**                                                                                         |
| --- | ----------------------- | ------------------------------------------------------------------------------------------- | ---------------------------- | ----------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| 01  | `const int* ptr`        | Pointer to a constant integer. The integer pointed to cannot be changed.                    | `const int* ptr = &x;`       | Use when you want to point to an integer without modifying it.                                                    | Ensures the data pointed to remains unchanged, enhancing code safety and const-correctness.         |
| 02  | `int* const ptr`        | Constant pointer to an integer. The pointer itself cannot change.                           | `int* const ptr = &x;`       | Use when you want a pointer always to point to the same integer, but the integer itself can be modified.          | Guarantees that the pointer will always point to the same memory location.                          |
| 03  | `int const* ptr`        | Equivalent to `const int* ptr`. Pointer to a constant integer.                              | `int const* ptr = &x;`       | Same as `const int* ptr`. Used to point to an integer without modifying it.                                       | Same as `const int* ptr`. Ensures the data pointed to remains unchanged.                            |
| 04  | `const int* const ptr`  | Constant pointer to a constant integer. Neither the integer nor the pointer can be changed. | `const int* const ptr = &x;` | Use when you want a constant pointer to a constant integer. Both the pointer and the integer are immutable.       | Enhances safety by preventing modification of both the pointer and the data it points to.           |
| 05  | `int const* const ptr`  | Equivalent to `const int* const ptr`. Constant pointer to a constant integer.               | `int const* const ptr = &x;` | Same as `const int* const ptr`. Ensures immutability of both the pointer and the integer it points to.            | Same as `const int* const ptr`. Maximizes const-correctness and immutability.                       |
| 06  | `const int** ptr`       | Pointer to a pointer to a constant integer.                                                 | `const int** ptr;`           | Use when you have a pointer to a pointer, and you want to protect the integer data from modification.             | Protects the integer data pointed to by the inner pointer from being modified.                      |
| 07  | `int* const* ptr`       | Pointer to a constant pointer to an integer.                                                | `int* const* ptr;`           | Use when you have a pointer to a constant pointer, allowing modification of the integer data but not the pointer. | Ensures the pointer being pointed to remains constant, but allows modification of the integer data. |
| 08  | `int** const ptr`       | Constant pointer to a pointer to an integer.                                                | `int** const ptr = &p;`      | Use when the pointer to a pointer must remain constant, but the pointers it points to can change.                 | Ensures the pointer to a pointer remains constant, enhancing stability in nested pointer scenarios. |
| 09  | `const int* const* ptr` | Pointer to a constant pointer to a constant integer.                                        | `const int* const* ptr;`     | Use for a higher level of const correctness when dealing with pointer to pointer.                                 | Protects both the pointer and the integer data it points to from modification.                      |
| 10  | `int const** ptr`       | Equivalent to `const int** ptr`. Pointer to a pointer to a constant integer.                | `int const** ptr;`           | Same as `const int** ptr`. Used to prevent modification of the integer data pointed to by the inner pointer.      | Same as `const int** ptr`. Protects the integer data from modification.                             |
| 11  | `int* const* const ptr` | Constant pointer to a constant pointer to an integer.                                       | `int* const* const ptr;`     | Use when you want the structure of your pointers to be completely immutable.                                      | Provides the highest level of immutability in pointer-to-pointer scenarios.                         |

- These variations demonstrate how `const` can be used to control and safeguard
  the modification of data and pointers in different ways. Understanding these
  nuances can help you write more predictable and bug-resistant C++ code.

### With Pointers

- This is one of the way to see that we break the promise to not modify the
  `MAX_AGE` although it is a `const`. This is done by casting our `&MAX_AGE` to
  our `Pointer` `a`.

```cpp

void with_pointer_2() {
    int MAX_AGE = 10;
    /* MAX_AGE = 200;  // Allowed  */
    const int MAX_WEIGHT = 100;
    /* MAX_WEIGHT = 200; //not allowed  */

    LOG(INFO)
        << BLUE
        << "[CASE: (1)] Modifying the content is not allowed, but Modifying the pointer is allowed "
        << RESET;
    const int* ptr1 = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "const int* ptr1 = &MAX_AGE;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr1) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr1 = &MAX_WEIGHT; => [Allowed] -> the memeory address (ptr1/pointer) can "
                 "reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr1 << RESET;
    /*  */

    LOG(INFO)
        << BLUE
        << "[CASE: (2)] Modifying the content is not allowed, but Modifying the pointer is allowed "
        << RESET;
    const int* ptr2 = &MAX_WEIGHT;
    LOG(INFO) << RED << "FORM[2]:" << BLUE << "const int* ptr2 = &MAX_WEIGHT;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr2) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr2 = &MAX_WEIGHT; => [Allowed] -> the memory address (ptr2/pointer) can "
                 "reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr2 << RESET;

    LOG(INFO)
        << BLUE
        << "[CASE: (3)] Modifying the content is allowed, but Modifying the pointer is not allowed "
        << RESET;
    int* const ptr3 = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "int* const ptr3 = &MAX_AGE;" << RESET;
    LOG(INFO) << RED << "*(ptr3) = 300;      => [Allowed] -> variable is assignable" << RESET;
    LOG(INFO) << RED
              << "ptr3 = &MAX_WEIGHT; => [ERROR:: not allowed] -> the memory address "
                 "(ptr3/pointer) cannot reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr3 << RESET;

    LOG(INFO) << BLUE
              << "[CASE: (4)] Modifying the content is not allowed, Also, Modifying the pointer is "
                 "not allowed "
              << RESET;
    const int* const ptr = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "const int* const ptr = &MAX_AGE;" << RESET;
    LOG(INFO) << RED << "FORM[2]:" << BLUE << "int const* const ptr = &MAX_AGE;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr = &MAX_WEIGHT; => [ERROR:: not allowed] -> the memory address (ptr3/pointer) "
                 "cannot reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr << RESET;

    LOG(INFO) << BLUE << "CASE: (1) & (2) are having similar effect" << RESET;
}
```

- When creating a pointer to an integer or any type of variable, it is crucial to
  also delete the pointer once you have finished using its contents. This is
  typically done by initializing a null pointer: `void* ptr = nullptr;`. This
  helps prevent dangling pointers that can lead to memory corruption errors.
  read about memeory leaking and how to avoid dangling pointer.

## Const with Classes

- We here using the `const` with class-method that give us a promise this
  method will not modify the internal fields of a class.

```cpp

void const_with_classes() {
    class Entity {
    private:
        int m_x, m_y;

    public:
        // for getting information, we ensure the `m_x` and `m_y` will not be changed inside these
        // const methods.
        int get_x() const {
            /* m_x = 10;  // [ERROR: not allowed]  -> Cannot assign to non-static data memember
             * within const member function`get_x` */
            return m_x;
        }
        int get_y() const { return m_y; }
        // As we want to change the value of m_x, then we should not use const method
        void set_x(int x) { m_x = x; }
    };
}
```

- If you want to add the concepts with pointers alongside with the classes, you can use the following
  - The following means:
    - first restruction : You cannot modify the variables of m_x, and m_y
    - second restruction: You cannot modify the pointers that point to these values
    - third restruction : The method is constant, gaurantee to also not modify the values of the `m_x` and `m_y`, simiarl the first restricutions.

```cpp

void const_with_classes() {
    class Entity {
    private:
        int* m_x
        int* m_y;

    public:
        // for getting information, we ensure the `m_x` and `m_y` will not be changed inside these
        // const methods.
        const int* const get_x() const {
            /* m_x = 10;  // [ERROR: not allowed]  -> Cannot assign to non-static data memember
             * within const member function`get_x` */
            return m_x;
        }
}
```

### Why we need the class method?

- Why we need the `const` with class methods? We got it kind of promises not to
  touch things in this method and maybe if someone will extend this method, they
  would say okay this is not meant to write to the class, however does this
  actually enforce something? the answer yes,

  - It uses for passing a `const reference` to a function that will use the object.
  - The `const` method has to be passed to every method that is located inside a
    class and does not modify its class attributes, such as `m_x` and `m_y`.
    Therefore, the following class methods of both the `get_x`, `get_y`, and
    `display_info` will not alter the class attributes.

```cpp

class Entity {
public:
    Entity(int x, int y)
        : m_x{x},
          m_y{y} {}

    // Getter methods
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }

    // Setter methods
    void set_x(int x) { m_x = x; }
    void set_y(int y) { m_y = y; }

    std::string display_info() const {
        std::string entity_info = "<" + std::to_string(m_x) + "," + std::to_string(m_y) + ">";
        return entity_info;
    }

private:
    int m_x, m_y;
};

void print_eneity(const Entity& e) {  // <- just to pass a constat reference so you will need the
                                      // const-methods in the Entity class
    LOG(INFO) << BLUE << "Getting m_x: " << RED << e.get_x() << RESET;
    LOG(INFO) << BLUE << e.display_info();
}

int main(int argc, char* argv[]) {
    // Initialize logging
    init_logging(argv);
    std::cout << "######################################\n";
    /* array_function_in_depth(); */
    /* class_implementation(); */
    /* data_type_table(); */
    /* pointers_concept(); */
    // const_in_action();

    const Entity e = Entity(10, 20);
    print_eneity(e);
}

```

- Thats why, you will see sometimes two methods one with const and one without,
  and the complier will know which one to use when you need to pass a
  `const-reference` argument to your function (function means it is not a
  class-method).

- You still can change some variables even if you mark the method as a const
  class method using the `mutuble` keyword as:

```cpp

class Entity {
private:
    int m_x,
    mutable int m_y;

public:
    Entity(int x, int y)
        : m_x{x},
          m_y{y} {}

    // Getter methods
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }

```
