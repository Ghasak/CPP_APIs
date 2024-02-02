# CheatSheet C++ - General
<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [CheatSheet C++ - General](#cheatsheet-c---general)
    - [1. Strings](#1-strings)
        - [1.1 C-Style](#11-c-style)
            - [1.1.1 `const char* mystr1 = "Hello World";`](#111-const-char-mystr1--hello-world)
            - [1.1.2 `const char mystr2[] = "Hello World";`](#112-const-char-mystr2--hello-world)
            - [1.1.3 C-Style Array (Non-Const)](#113-c-style-array-non-const)
        - [1.2 std::string](#12-stdstring)
    - [2. Arrays and Lists](#2-arrays-and-lists)
        - [2.1 std::Vector](#21-stdvector)

<!-- markdown-toc end -->

## 1. Strings

### 1.1 C-Style

Comparing C-style arrays with `const char*` and `const char[]` in terms of
syntax and characteristics:

#### 1.1.1 `const char* mystr1 = "Hello World";`

| Aspect                      | Details                                                                                     |
| --------------------------- | ------------------------------------------------------------------------------------------- |
| **Type**                    | Pointer to `const char`                                                                     |
| **Storage**                 | Points to a string literal in read-only memory.                                             |
| **Memory Location**         | Read-only section of memory (data segment).                                                 |
| **Modifiability**           | The string literal is not modifiable.                                                       |
| **Common Usage**            | Common for fixed strings that are not modified.                                             |
| **Syntax Example**          | `const char* mystr1 = "Hello World";`                                                       |
| **Heap Allocation Example** | `const char* mystr1 = new char[strlen("Hello World") + 1];\nstrcpy(mystr1, "Hello World");` |
| **Heap Deallocation**       | `delete[] mystr1;`                                                                          |
| **Null-Terminated**         | Yes                                                                                         |

#### 1.1.2 `const char mystr2[] = "Hello World";`

| Aspect                         | Details                                                                                                                                                                                                                                         |
| ------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Type**                       | Array of `const char`                                                                                                                                                                                                                           |
| **Storage**                    | Creates a copy of the string on the stack.                                                                                                                                                                                                      |
| **Memory Location**            | Stack (as part of local variables).                                                                                                                                                                                                             |
| **Modifiability**              | The string itself is not modifiable due to `const`.                                                                                                                                                                                             |
| **Common Usage**               | Less common, used for local, read-only copies.                                                                                                                                                                                                  |
| **Syntax Example**             | `const char mystr2[] = "Hello World";`                                                                                                                                                                                                          |
| **Heap Allocation Equivalent** | Not directly applicable as arrays have fixed size at compile time, but a similar effect can be achieved using dynamic allocation with a `char*`. Example: `char* mystr2 = new char[strlen("Hello World") + 1];\nstrcpy(mystr2, "Hello World");` |
| **Heap Deallocation**          | `delete[] mystr2;` (For the dynamically allocated array)                                                                                                                                                                                        |
| **Null-Terminated**            | Yes                                                                                                                                                                                                                                             |

#### 1.1.3 C-Style Array (Non-Const)

| Aspect                      | Details                                                                               |
| --------------------------- | ------------------------------------------------------------------------------------- |
| **Type**                    | Array of `char`                                                                       |
| **Storage**                 | Allocates and initializes an array on the stack.                                      |
| **Memory Location**         | Stack (as part of local variables).                                                   |
| **Modifiability**           | The contents of the array can be modified.                                            |
| **Common Usage**            | Common for modifiable strings or when a buffer is needed.                             |
| **Syntax Example**          | `char mystr3[] = "Hello World";`                                                      |
| **Heap Allocation Example** | `char* mystr3 = new char[strlen("Hello World") + 1];\nstrcpy(mystr3, "Hello World");` |
| **Heap Deallocation**       | `delete[] mystr3;` (For the dynamically allocated array)                              |
| **Null-Terminated**         | Yes                                                                                   |

In summary:

- `const char*` points to a constant string literal, usually in read-only memory.
- `const char[]` creates a local, read-only copy of the string on the stack.
- A non-const `char[]` array allows modification of its contents on the stack.
- For dynamic allocation, a `char*` is used, and `new[]`/`delete[]` manage memory on the heap.
- All these strings are null-terminated, which is crucial for using them with standard C string functions.

- a table summarizing some commonly used C-style string functions along with
  examples for each. These functions are part of the C standard library
  (`<cstring>` or `<string.h>` in C++) and are used for various operations on
  null-terminated strings:

| Function  | Purpose                                              | Example Usage                                        | Notes                                                                                             |
| --------- | ---------------------------------------------------- | ---------------------------------------------------- | ------------------------------------------------------------------------------------------------- |
| `strcpy`  | Copies a string to another                           | `char str[50]; strcpy(str, "Hello");`                | Destination array should be large enough to hold the source string including the null terminator. |
| `strncpy` | Copies a specified number of characters of a string  | `char str[50]; strncpy(str, "Hello", 2);`            | Safer than `strcpy`, as it limits the number of copied characters.                                |
| `strlen`  | Returns the length of a string                       | `size_t len = strlen("Hello");`                      | Length does not include the null terminator.                                                      |
| `strcmp`  | Compares two strings                                 | `if (strcmp(str, "Hello") == 0) { ... }`             | Returns 0 if strings are equal.                                                                   |
| `strncmp` | Compares a specified number of characters of strings | `if (strncmp(str, "Hello", 2) == 0) { ... }`         | Similar to `strcmp`, but compares only the first n characters.                                    |
| `strcat`  | Concatenates two strings                             | `char str[50] = "Hello"; strcat(str, " World");`     | Destination array should have enough space for the concatenated result.                           |
| `strncat` | Concatenates a specified number of characters        | `char str[50] = "Hello"; strncat(str, " World", 2);` | Similar to `strcat`, but appends only the first n characters of the second string.                |
| `strchr`  | Locates a character in a string                      | `char *ptr = strchr(str, 'e');`                      | Returns a pointer to the first occurrence of the character.                                       |
| `strrchr` | Locates the last occurrence of a character           | `char *ptr = strrchr(str, 'l');`                     | Returns a pointer to the last occurrence of the character.                                        |
| `strstr`  | Locates a substring                                  | `char *ptr = strstr(str, "lo");`                     | Returns a pointer to the first occurrence of the substring.                                       |
| `strtok`  | Splits a string into tokens                          | `char *token = strtok(str, " ");`                    | Returns a pointer to the first token found in the string.                                         |

These functions form the core of C-style string manipulation. Remember, since
C-style strings are arrays of characters ending with a null character (`'\0'`),
it's important to always ensure that the strings you work with are properly
null-terminated and that there's enough space in your arrays to handle the
operations you're performing to avoid buffer overflows and other undefined
behaviors.

### 1.2 std::string

Here is an updated table including `std::string::npos` and another similar member:

| Method              | Purpose                                                    | Example Usage                                         |
| ------------------- | ---------------------------------------------------------- | ----------------------------------------------------- |
| `length()`/`size()` | Returns the number of characters in the string.            | `std::string str = "Hello"; auto len = str.length();` |
| `empty()`           | Checks if the string is empty.                             | `if (str.empty()) {...}`                              |
| `append()`          | Appends specified content to the string.                   | `str.append(" World");`                               |
| `push_back()`       | Appends a character to the end of the string.              | `str.push_back('!');`                                 |
| `at()`              | Accesses the character at the specified position.          | `char ch = str.at(1);`                                |
| `operator[]`        | Accesses the character at the specified position.          | `char ch = str[1];`                                   |
| `front()`           | Accesses the first character.                              | `char first = str.front();`                           |
| `back()`            | Accesses the last character.                               | `char last = str.back();`                             |
| `substr()`          | Returns a substring.                                       | `std::string sub = str.substr(1, 2);`                 |
| `find()`            | Finds the position of the first occurrence of a substring. | `size_t pos = str.find("lo");`                        |
| `rfind()`           | Finds the position of the last occurrence of a substring.  | `size_t pos = str.rfind('l');`                        |
| `replace()`         | Replaces part of the string.                               | `str.replace(0, 5, "Hi");`                            |
| `erase()`           | Erases part of the string.                                 | `str.erase(1, 3);`                                    |
| `clear()`           | Clears the contents.                                       | `str.clear();`                                        |
| `c_str()`           | Returns a C-style string (const char\*).                   | `const char* cstr = str.c_str();`                     |
| `data()`            | Returns a pointer to the internal array.                   | `const char* data = str.data();`                      |
| `swap()`            | Swaps the contents with another string.                    | `std::string str2 = "World"; str.swap(str2);`         |
| `resize()`          | Resizes the string to a specified length.                  | `str.resize(10, 'x');`                                |
| `insert()`          | Inserts characters at the specified location.              | `str.insert(1, "ey");`                                |
| `compare()`         | Compares the string with another string.                   | `if (str.compare("Hello") == 0) {...}`                |
| `npos`              | Represents the maximum value for `size_t`.                 | `if (str.find("World") == std::string::npos) {...}`   |

- `std::string::npos` is a static member constant value with the greatest possible
  value for an element of type `size_t`. This constant is used to indicate that no
  matches were found by methods like `find()` and `rfind()` in the `std::string`
  class.

- `std::string::npos` is particularly useful when you need to check if a method
  like `find()` did not find the specified substring or character, as these
  methods return `std::string::npos` when the search is unsuccessful. It's a way
  of indicating an invalid position or a "not found" scenario in string
  operations.

## 2. Arrays and Lists
### 2.1 std::Vector

Here's a table summarizing some of the common methods of `std::vector` in C++,
along with example usages:

| Method              | Purpose                                                         | Example Usage                                               |
| ------------------- | --------------------------------------------------------------- | ----------------------------------------------------------- |
| `push_back()`       | Adds an element to the end of the vector.                       | `std::vector<int> v; v.push_back(10);`                      |
| `pop_back()`        | Removes the last element of the vector.                         | `v.pop_back();`                                             |
| `size()`            | Returns the number of elements in the vector.                   | `auto n = v.size();`                                        |
| `empty()`           | Checks if the vector is empty.                                  | `if (v.empty()) {...}`                                      |
| `at()`              | Accesses the element at the specified position.                 | `int x = v.at(1);`                                          |
| `operator[]`        | Accesses the element at the specified position.                 | `int x = v[1];`                                             |
| `front()`           | Accesses the first element.                                     | `int first = v.front();`                                    |
| `back()`            | Accesses the last element.                                      | `int last = v.back();`                                      |
| `clear()`           | Removes all elements from the vector.                           | `v.clear();`                                                |
| `insert()`          | Inserts elements at the specified location.                     | `v.insert(v.begin() + 1, 20);`                              |
| `erase()`           | Erases elements at the specified location.                      | `v.erase(v.begin());`                                       |
| `reserve()`         | Requests a change in capacity.                                  | `v.reserve(100);`                                           |
| `resize()`          | Resizes the container to contain a specific number of elements. | `v.resize(5);`                                              |
| `capacity()`        | Returns the size of the allocated storage.                      | `auto cap = v.capacity();`                                  |
| `swap()`            | Swaps the contents with another vector.                         | `std::vector<int> v2; v.swap(v2);`                          |
| `emplace_back()`    | Constructs an element in-place at the end.                      | `v.emplace_back(30);`                                       |
| `data()`            | Provides direct access to the underlying array.                 | `int* ptr = v.data();`                                      |
| `begin()`/`end()`   | Returns iterators to the beginning/end of the vector.           | `for (auto it = v.begin(); it != v.end(); ++it) {...}`      |
| `rbegin()`/`rend()` | Returns reverse iterators to the vector.                        | `for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {...}` |

`std::vector` is a sequence container that encapsulates dynamic size arrays.
These methods provide various ways to manipulate the vector, including adding
and removing elements, accessing elements, and querying its properties. It's one
of the most widely used containers in the C++ Standard Library due to its
flexibility and ease of use.
