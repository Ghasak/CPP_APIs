# Strings in CPP

In C++, strings are simply arrays of characters used to store text. One can
think of an array as a collection of elements.

## My Understanding

### 1. C-Style String Understanding

#### 1.1 As a const pointer

Basically there are three ways to create a `C-style` string. These are:

```cpp
// Different syntaxes for declaring a C-style string as a pointer
const char* my_cstyle_string_as_a_ptr1 = "Hello World!";
static const char* my_cstyle_string_as_a_ptr2 = "Hello World!";
constexpr const char* my_cstyle_string_as_a_ptr3 = "Hello World!";
// Assuming 'getHelloWorld' returns a 'const char*' to "Hello World!"
const char* my_cstyle_string_as_a_ptr4 = getHelloWorld();
```

| No. | Syntax                                                                                |
| --- | ------------------------------------------------------------------------------------- |
| 1   | `const char* my_cstyle_string_as_a_ptr1 = "Hello World!";`                            |
| 2   | `static const char* my_cstyle_string_as_a_ptr2 = "Hello World!";`                     |
| 3   | `constexpr const char* my_cstyle_string_as_a_ptr3 = "Hello World!";`                  |
| 4   | `const char* my_cstyle_string_as_a_ptr4 = getHelloWorld();` // Assuming function call |

This table now only includes syntaxes that define a C-style string as a pointer
without using any array (`[]`) types. The function `getHelloWorld()` in the
last entry is hypothetical and is assumed to return a `const char*` pointing to
a C-style string.

1. Using char pointer (can be const)
   - Once declared, you cannot change it.
   - You perform pointer arithmetics on it but not to modifying it, only for read-only.
   - You can obtain the address of its first element by obtaining the pointer to it.
   - You can dereference the pointer to obtain its read-only contents.

| #   | Request/ Fact                                    | Syntax / Explanation                                                        | Description                                                                                                                                       |
| --- | ------------------------------------------------ | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Printing the string itself                       | `std::cout << my_cstyle_string_ptr << std::endl;`                           | Directly printing `my_cstyle_string_ptr` prints the entire string.                                                                                |
| 2   | Printing the memory address of the first element | `std::cout << static_cast<const void*>(my_cstyle_string_ptr) << std::endl;` | Gives the memory address of the first character in the string.                                                                                    |
| 3   | Dereferencing gives the first character          | `std::cout << *my_cstyle_string_ptr << std::endl;`                          | Dereferencing `my_cstyle_string_ptr` yields 'H', the first character.                                                                             |
| 4   | Can I modify the string?                         | No.                                                                         | Attempting to modify a string literal leads to undefined behavior as it is stored in read-only memory.                                            |
| 5   | Pointer arithmetic for read-only                 | `std::cout << (my_cstyle_string_ptr + n) << std::endl;`                     | Performing pointer arithmetic shifts the pointer and gives a substring starting at the `n`th character.                                           |
| 6   | Address of the pointer variable                  | `&my_cstyle_string_ptr`                                                     | Gives the memory address of the pointer variable itself, a pointer to a pointer.                                                                  |
| 7   | Null-termination included                        | `const char* my_cstyle_string_ptr = "Hello World!";`                        | The string is automatically null-terminated by the compiler.                                                                                      |
| 8   | Common usages for this string                    | N/A                                                                         | - Interfacing with C libraries<br>- Constant strings that don't need modification<br>- Performance-critical situations                            |
| 9   | Other considerations                             | N/A                                                                         | - String is read-only<br>- Be cautious of buffer overruns<br>- Manual memory management if dynamically allocated<br>- No built-in bounds checking |

##### 1.1.1. Accessing the pointer of the char pointer as a variable

In the C++ code snippet, the output of `std::cout << &my_cstyle_string_ptr` is
indeed a memory address, but with a specific meaning:

```cpp
std::cout << "[1] Obtaining the Pointer Itself: " << &my_cstyle_string_ptr << std::endl;
```

- This line prints the memory address of the variable `my_cstyle_string_ptr`
  itself, not the address of the string literal it points to. Here's what each
  component represents:

- `my_cstyle_string_ptr`: This is a pointer variable holding the address of the
  first character of the string literal `"Hello World!"`.
- `&my_cstyle_string_ptr`: This is the address of the pointer variable itself
  in memory.

- So, the output is the address in memory where the pointer variable
  `my_cstyle_string_ptr` is stored. This is different from the content of
  `my_cstyle_string_ptr`, which would be the address of the `"Hello World!"`
  string in memory.

- In summary, the output is the memory address (pointer) of the pointer
  variable `my_cstyle_string_ptr`.

- There are several scenarios where obtaining the address of a pointer variable
  itself (`&my_cstyle_string_ptr`) can be useful in C++ programming:

  1. **Passing Pointer to a Function for Modification**: If you want a function
     to modify the pointer (not just the object it points to), you pass the
     address of the pointer. This way, the function can change where the pointer
     is pointing.

     Example:

     ```cpp
     void modifyPointer(const char** ptr) {
         // Modify where ptr points to
     }

     const char* myString = "Hello";
     modifyPointer(&myString);
     ```

  2. **Debugging and Logging**: Printing the address of a pointer variable can
     be useful for debugging purposes, to track how variables are stored and
     how their addresses change.
  3. **Implementing Data Structures**: In complex data structures like linked
     lists or trees, pointers to pointers are often used. Understanding the
     address of a pointer is essential in these contexts.
  4. **Reference Simulation**: Before C++ introduced references, programmers
     sometimes simulated references using pointers to pointers.
  5. **Array of Pointers Management**: In scenarios where you have an array of
     pointers, getting the address of these pointers can be useful for
     reorganizing or managing the array.
  6. **Interfacing with Low-Level APIs**: Certain low-level APIs or system
     calls might require the address of a pointer variable.
  7. **Memory Management Tools**: When building custom memory allocators or
     garbage collectors, knowing the address of a pointer variable can be
     crucial.
  8. **Learning and Education**: Understanding the concept of
     pointer-to-pointer (or the address of a pointer) is fundamental in
     learning about pointers and memory management in C++.

In general, while this usage might not be common in everyday high-level
application development, it's very important in systems programming, low-level
data structure implementation, and scenarios where fine-grained memory control
is required.

- Let's create a simple but solid example where we use `&my_cstyle_string_ptr`.
  We'll define a function that modifies the original pointer to point to a
  different string. This is a classic use case for passing the address of a
  pointer to a function.

  - Example: Changing Pointer to Point to a Different String

    - We have a pointer to a C-style string, and we want to change what
      this pointer points to from within a function. To do this, we need to
      pass the address of the pointer to the function.

      ```cpp
       #include <iostream>

      // Function that modifies the pointer to point to a different string
      void changePointer(const char** ptr) {
          *ptr = "Goodbye World!";
      }

      int main() {
          const char* my_cstyle_string_ptr = "Hello World!";

          // Print original string
          std::cout << "Original String: " << my_cstyle_string_ptr << std::endl;

          // Pass address of the pointer to the function
          changePointer(&my_cstyle_string_ptr);

          // Print new string after modification
          std::cout << "Modified String: " << my_cstyle_string_ptr << std::endl;

          return 0;
      }
      ```

- Explanation

  - **`changePointer` function**: This function takes a `const char\*\* ptr`,
    which is a pointer to a pointer to a `const char`. Inside the function, we
    dereference `ptr` once (`\*ptr`) to access the original pointer
    (`my_cstyle_string_ptr`in`main`) and change what it points to.

  - **`changePointer(&my_cstyle_string_ptr)`call**: We pass the address
    of`my_cstyle_string_ptr`to the`changePointer`function. This allows
    the function to modify the original pointer in the`main` function.

- Output

The program will first print "Original String: Hello World!" and then "Modified
String: Goodbye World!", demonstrating that the original pointer in `main` has
been successfully modified to point to a different string literal.

#### 1.2. As an array

Here is a table summarizing the syntax for each of your queries about the
C-style string

```cpp
// Different ways to declare a C-style string
const char my_cstyle_string_array1[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
const char my_cstyle_string_array2[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0};
const char my_cstyle_string_array3[] = "Hello World!\0";
static const char my_cstyle_string_array4[] = "Hello World!\0";

```

| #   | Request/ Fact                                    | Syntax / Explanation                                                             | Description                                                                                                                 |
| --- | ------------------------------------------------ | -------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------- |
| 1   | Printing the string itself                       | `std::cout << my_cstyle_string_as_array << std::endl;`                           | Directly printing `my_cstyle_string_as_array` prints the entire string.                                                     |
| 2   | Printing the memory address of the first element | `std::cout << static_cast<const void*>(my_cstyle_string_as_array) << std::endl;` | Gives the memory address of the first character in the array.                                                               |
| 3   | Dereferencing gives the first character          | `std::cout << *my_cstyle_string_as_array << std::endl;`                          | Dereferencing `my_cstyle_string_as_array` yields 'H', the first character.                                                  |
| 4   | Can I modify the string?                         | No.                                                                              | Since it's declared as `const`, the array content is immutable and attempting to modify it leads to undefined behavior.     |
| 5   | Pointer arithmetic for read-only                 | `std::cout << (my_cstyle_string_as_array + n) << std::endl;`                     | Performing pointer arithmetic shifts the pointer and gives a substring starting at the `n`th character.                     |
| 6   | Address of the array variable                    | `&my_cstyle_string_as_array`                                                     | Gives the memory address of the array variable itself.                                                                      |
| 7   | Null-termination included                        | `const char my_cstyle_string_as_array[] = "Hello World!\0";`                     | The string is explicitly null-terminated with `\0`. This is redundant as the compiler adds a null terminator automatically. |
| 8   | Common usages for this string as an array        | N/A                                                                              | - Suitable for local, constant strings<br>- Used when size and content of the string are known at compile time              |
| 9   | Other considerations                             | N/A                                                                              | - The array is read-only due to `const`<br>- Size is fixed at compile time<br>- Safe from buffer overruns within its size   |

This table provides an overview of the operations and characteristics related
to C-style strings when declared as an array (`const char[]`) in C++. The
syntax and behavior are specific to this declaration style.

##### 1.2.1 C-Style String as Array - Pointer comparision to regular C-Style Array

Here, I will compare the C-style array to similar C-Style array but occuppied
with `int` rather `char`, to see the differences betweeen these two.

The difference in how `int my_array[]` and `char my_char_array[]` are
dereferenced and treated in C++ boils down to the nature of their respective
data types and how arrays decay into pointers.

1. `int my_array[] = {0, 1, 2, 3};`

   - `my_array` is an array of integers. Each element of the array is an `int`.
   - When you dereference `my_array`, like with `*my_array`, you're accessing the
     first element of the array, which is an integer. In this case, `*my_array` will
     give you `0`, the first integer in the array.

2. `char my_char_array[] = "hello world";`

   - `my_char_array` is an array of characters. It's also a C-style string.
   - In C and C++, a string is essentially an array of characters terminated by
     a null character `'\0'`.
   - When you dereference `my_char_array`, like with `*my_char_array`, you're
     accessing the first element of the array, which is a `char`. In this case,
     `*my_char_array` will give you `'h'`, the first character in the string.

- Key Differences

  - **Data Type**: The main difference comes from the type of the array elements.
    `int` for `my_array` and `char` for `my_char_array`.
  - **Representation**: The integer array doesn't have a special textual
    representation. Each element is just an `int`. In contrast, the character
    array, when treated as a C-style string, represents a sequence of characters,
    which can be printed as a readable string.
  - **Dereferencing Behavior**: Dereferencing an `int` array gives you an `int`
    value. Dereferencing a `char` array gives you a single `char`. However, many
    C++ functions (like `std::cout`) treat `char*` (or decayed `char[]`) as a
    C-style string and will print the whole string starting from the pointed-to
    character.

- Why They Seem Similar

  - Both arrays decay to pointers when passed to a function or in certain
    expressions. `my_array` decays to `int*`, while `my_char_array` decays to
    `char*`. However, the types they point to (`int` vs. `char`) and how those
    types are treated (especially in the context of C-style strings for `char*`)
    account for the differences in behavior.

##### 1.2.2 C-Style String as Array - Allocation on Heap

Allocation on Heap for the C-Style as a const pointer is not possible, as the
`const pointer` refer to a read-only memeory location. Instead we create the
`C-Style` string in a form of an array which is the base and used later to
create it on the heap using:

- When you allocate a C-style string on the heap, it indeed involves creating
  an array of characters and then pointing to it. This differs from the original
  `const char* my_cstyle_string_ptr = "Hello World!";` in two key ways:

  1. **Memory Location and Mutability**: The string literal `"Hello World!"` in
     `const char* my_cstyle_string_ptr = "Hello World!";` is stored in a
     read-only section of memory (like the data segment), and you cannot modify the
     contents of this string. In contrast, when you allocate memory on the heap for
     a C-style string, the memory is writable. You can modify the characters in this
     array.
  2. **Dynamic Allocation and Arrays**: When you allocate memory on the heap for
     a C-style string, you're essentially creating an array of characters
     dynamically. For example:

  ```cpp
  char* my_cstyle_string_heap = new char[12];
  strcpy(my_cstyle_string_heap, "Hello World!");
  ```

- Here, `my_cstyle_string_heap` is a pointer to the first character of an array
  of characters on the heap. This array is mutable, meaning you can change the
  characters as needed. Also, unlike the string literal, you are responsible
  for managing this memory (allocating and freeing it).

- In summary, heap allocation for C-style strings is more flexible in terms of
  mutability and size adjustments, but it requires manual memory management. It's
  different from using string literals, which are immutable and managed by the
  compiler.

- The `strcpy` function in C and C++ automatically adds a null terminator
  ('\0') to the destination string. When you use `strcpy` to copy a string, it
  copies all characters from the source string up to and including the null
  terminator.

For example:

```cpp
char* my_cstyle_string_heap = new char[12];
strcpy(my_cstyle_string_heap, "Hello World!");
```

In this code:

- `"Hello World!"` is 11 characters long.
- `strcpy` will copy these 11 characters and the null terminator `\0` to
  `my_cstyle_string_heap`.
- The total length of the string in `my_cstyle_string_heap` becomes 12
  characters, including the null terminator.

Always ensure that the destination buffer is large enough to hold the entire
source string plus the null terminator to avoid buffer overruns. In this case,
`my_cstyle_string_heap` is correctly sized to 12 characters to accommodate
"Hello World!" and its null terminator.

- Allocating a C-style string on the heap in C++ involves using dynamic memory
  allocation. This is typically done using `new` and `delete`. Let's go through
  different ways to construct such strings and how to perform operations like
  dereferencing and pointer arithmetic.

- **More Information**: Constructing Heap-Allocated C-Style Strings

  1. **Allocating and Initializing with a String Literal**

     ```cpp
     char* str = new char[strlen("Hello") + 1]; // +1 for null terminator
     strcpy(str, "Hello");
     ```

  2. **Allocating with a Specific Size**

     ```cpp
     char* str = new char[10]; // Allocate space for 9 characters + null terminator
     ```

     After allocation, you can initialize it using functions like `strcpy`, or by setting individual characters.

  3. **Using `std::string` to Initialize**

     If you have a `std::string`, you can allocate a C-style string and copy the content:

     ```cpp
     std::string stdStr = "Hello";
     char* str = new char[stdStr.size() + 1];
     strcpy(str, stdStr.c_str());
     ```

- Dereferencing and Pointer Arithmetic

Once you have a heap-allocated string, you can manipulate it using pointer arithmetic and dereferencing:

- **Dereferencing**

  ```cpp
  std::cout << *str; // Outputs the first character of the string
  ```

- **Pointer Arithmetic**

  - Accessing specific characters:
    ```cpp
    std::cout << str[2]; // Accesses the 3rd character ('l' in "Hello")
    ```
  - Incrementing pointers:
    ```cpp
    char* ptr = str;
    ptr += 2; // Now ptr points to the 3rd character
    std::cout << *ptr; // Outputs 'l'
    ```

- Important Considerations:

  1. **Memory Management**: Always remember to free
     the allocated memory to avoid memory leaks.

  ```cpp
  delete[] str;
  ```

  2. **Bounds Checking**: Be careful with pointer arithmetic to avoid
     accessing memory outside the allocated range, which can lead to undefined
     behavior.
  3. **Initialization**: If you allocate with a specific size and don't
     immediately initialize (as in the second method), be aware that the memory
     is uninitialized. You should initialize it before using it to avoid
     undefined behavior.
  4. **Use of `std::string`**: In modern C++, it's recommended to use
     `std::string` for string handling because it manages memory automatically
     and is safer and more convenient. The above methods are more C-style and
     should be used with caution.

Allocating and manipulating C-style strings on the heap provides flexibility
but requires careful handling of memory and bounds. Always prefer higher-level
abstractions like `std::string** unless you have a specific reason to manage
memory manually.

##### 1.2.3 C-Style String as Array - When we need Termianation Point

- **NOTE*: You will need it when you have access the charcters index.

You need to manually add a null terminator to a C-style string in C++ in the
following scenarios:

1. **When Initializing an Array with Individual Characters:**
   If you initialize a character array with individual characters (not using a
   string literal), you must manually add the null terminator.

   ```cpp
   char str[] = {'H', 'e', 'l', 'l', 'o', '\0'}; // Manually adding null terminator
   ```

   Without the `\0` at the end, it's just an array of characters and not a proper C-style string.

2. **When Building or Modifying a String in an Array:**
   If you're constructing a string character by character or modifying an
   existing string in an array, ensure it's null-terminated.

   ```cpp
   char str[6];
   str[0] = 'H';
   str[1] = 'i';
   // ... additional characters ...
   str[5] = '\0'; // Null terminator is required
   ```

3. **When Using Functions That Don't Automatically Null-Terminate:**
   Certain functions that manipulate C-style strings do not automatically add a
   null terminator. For example, functions like `strncpy` can leave the
   resulting string without a null terminator if the length argument is equal to
   the size of the destination array.

   ```cpp
   char src[] = "Hello";
   char dest[6];
   strncpy(dest, src, 6); // No null terminator added if src is exactly 6 characters or longer
   dest[5] = '\0'; // Manually ensuring null termination
   ```

4. **When Dynamically Allocating Memory for Strings:**
   When you allocate memory for a string using `new`, you should manually add a
   null terminator to mark the end of the string.

   ```cpp
   char* str = new char[10];
   // Populate str
   str[9] = '\0'; // Ensure the last character is a null terminator
   ```

- Key Points
  - **Always Null-Terminate:** In C++, a C-style string is expected to be
    null-terminated. Failing to add a null terminator can lead to undefined
    behavior when functions expecting a C-style string try to read past the end
    of the string.
  - **Automatic with String Literals:** When you use a string literal to
    initialize a char array, the null terminator is automatically included. You
    don’t need to add it manually in this case.
  - **Be Mindful with Memory:** Especially when dealing with dynamic memory
    allocation or manipulating strings in arrays, always ensure the string is
    properly null-terminated.

#### 1.3 Comparison between C-Style as a Pointer and as An Array

This table now includes a comparison of mutability in both scenarios: with and
without the `const` keyword, for both pointer and array declarations of C-style
strings.

| Feature                                 | Pointer Declaration (`const char*`)                                                | Array Declaration (`const char[]`)                                                 |
| --------------------------------------- | ---------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| **Storage Location**                    | Points to a string literal in read-only memory (text segment).                     | Stores a local copy of the string literal in the array (usually on the stack).     |
| **String Mutability (with `const`)**    | Immutable.                                                                         | Immutable.                                                                         |
| **String Mutability (without `const`)** | Immutable, but reassignable. Modifying string literal leads to undefined behavior. | Mutable (can modify characters, but not the size).                                 |
| **Reassignment**                        | The pointer can be reassigned to point to another string.                          | The array itself cannot be reassigned to another string.                           |
| **Memory Usage**                        | Occupies memory only for the pointer (size depends on architecture).               | Occupies memory equal to the length of the string (including the null terminator). |
| **String Literal Mutability**           | Immutable, attempting to modify it can lead to undefined behavior.                 | Immutable, attempting to modify it can lead to undefined behavior.                 |
| **String Length**                       | Length is determined by the string literal up to the null terminator.              | Explicitly defined length including the null terminator (if provided).             |
| **Use Case**                            | Suitable for pointing to fixed strings, especially in low-memory scenarios.        | Suitable for creating a local, immutable copy of the string.                       |

---

## C-Style Strings Types

Let's dive into `C-style` strings in C++. Below is a table summarizing the
different ways to declare a `C-style` string in C++. Each method has its
specific characteristics and use cases:

| Method of Declaration                            | Description                                                              | Mutable | Notes                                                                                 |
| ------------------------------------------------ | ------------------------------------------------------------------------ | ------- | ------------------------------------------------------------------------------------- |
| `char str[] = "Hello";`                          | String literal assigned to a character array.                            | Yes     | Array size is inferred. Mutable.                                                      |
| `char str[6] = "Hello";`                         | String literal assigned to a character array of specified size.          | Yes     | Size includes null terminator. Mutable.                                               |
| `char str[10] = "Hello";`                        | Larger array size than needed for the string.                            | Yes     | Extra space can be used later. Mutable.                                               |
| `char* str = "Hello";`                           | Pointer to string literal.                                               | No      | Points to read-only memory. Modifying through `str` is undefined behavior.            |
| `char str[] = {'H', 'e', 'l', 'l', 'o', '\0'};`  | Character array with explicit null terminator.                           | Yes     | Null terminator must be included manually. Mutable.                                   |
| `char str[6] = {'H', 'e', 'l', 'l', 'o'};`       | Character array with implicit null terminator due to size specification. | Yes     | Last character is implicitly a null terminator. Mutable.                              |
| `char* str = new char[6];`                       | Dynamically allocated array on the heap.                                 | Yes     | Requires manual management with `new` and `delete`. Mutable.                          |
| `const char* str = "Hello";`                     | Pointer to a constant string literal.                                    | No      | Points to read-only memory. Modifying through `str` is undefined behavior.            |
| `static char str[] = "Hello";`                   | Static storage duration character array.                                 | Yes     | Lifetime is the entire program execution. Mutable.                                    |
| `extern char str[];` (with definition elsewhere) | External linkage to a character array defined in another file.           | Yes/No  | Mutability depends on how it's defined elsewhere. Used for sharing data across files. |

Each method has its appropriate use depending on the specific requirements of
your application, such as whether the string needs to be mutable, whether it
should have static or automatic storage duration, or if it should be allocated
dynamically on the heap. Remember that handling strings in C-style requires
careful management, especially with pointers and dynamic allocation, to avoid
memory leaks and undefined behavior.

### 1. **Introduction to C-Style Strings**

In C++, a `C-style` string is a sequence of characters ending with a null
character (`\0`). This null character is essential as it marks the end of the
string. These strings are stored in arrays of type `char`.

#### **Syntax of Creating a C-Style String**

You can create a `C-style` string in several ways:

- **Using String Literals**

  ```cpp
  char str1[] = "Hello, World!";
  ```

  This automatically adds the null character at the end.

- **Character Array Initialization**

  ```cpp
  char str2[14] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};

  ```

  Here, you manually add the null character.

#### **Considerations for C-Style Strings**

- **Null Termination**: Always ensure the string is null-terminated (`\0`). If
  this is omitted, functions that operate on C-style strings may read past the
  end of the array, causing undefined behavior.
- **Buffer Size**: Allocate enough space for the characters and the null
  terminator. For example, "Hello" requires 6 characters, including `\0`.
- **Immutable String Literals**: When a string literal is used, it's typically
  stored in a read-only section of memory. Modifying it results in undefined
  behavior.

### 2. **Representing Strings Using `char`**

- **As an Array**

  ```cpp
  char myString[] = "Example";
  ```

  `myString` is an array of `char` capable of holding the string "Example" and the null terminator.

- **As a Pointer**
  ```cpp
  char* myString = "Example";
  ```
  Here, `myString` is a pointer to the first character of the string. It's
  important to note that the string literal is immutable.

#### **Is a Char String a Pointer?**

In some contexts, yes. When you define a string like `char* str = "Hello";`,
`str` is a pointer to the first character of the string. However, when you
define it as an array, like `char str[] = "Hello";`, it's not a pointer but can
decay to a pointer in certain contexts.

### 3. **Allocating Strings on the Heap**

To allocate a string on the heap:

```cpp
char *str = new char[size];
```

Remember to free the allocated memory:

```cpp
delete[] str;
```

### 4. **Passing and Returning Strings from Functions**

#### **Passing Strings**

- **As is (by pointer)**

  ```cpp
  void printString(const char *str) {
      // use str
  }
  ```

- **As an Array (decays to pointer)**
  ```cpp
  void printString(char str[]) {
      // use str
  }
  ```

#### **Returning Strings**

- **Returning by Pointer**

  ```cpp
  char* getString() {
      char *str = new char[size];
      // fill str
      return str; // Caller must delete[] this memory
  }
  ```

- **Returning as a Reference (not common for C-style strings)** Typically, you
  don't return C-style strings by reference due to the risk of dangling
  references. Instead, return by pointer or use `std::string` in modern C++.

- Remember, managing memory with raw pointers (like with C-style strings) can
  be error-prone, leading to leaks or undefined behavior. Modern C++ encourages
  the use of `std::string` and smart pointers for safer and more efficient string
  handling. We'll get to `std::string` later as you expand your question.


## References

- [Decimal to Hex Calcualtor](https://www.rapidtables.com/convert/number/decimal-to-hex.html)
- [ASCII Table](https://www.asciitable.com)
