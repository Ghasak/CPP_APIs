# Strings literals

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Strings literals](#strings-literals)
    - [My Understanding](#my-understanding)
        - [1. `"Hello World1"`](#1-hello-world1)
        - [2. `const char* my_cstyle_string_ptr = "Hello World2";`](#2-const-char-my_cstyle_string_ptr--hello-world2)
        - [3. `const char my_cstyle_string_array[] = "Hello World3";`](#3-const-char-my_cstyle_string_array--hello-world3)
        - [Summary](#summary)
    - [Understanding String Literals in C++](#understanding-string-literals-in-c)
        - [Type of String Literals](#type-of-string-literals)
        - [Storage of String Literals](#storage-of-string-literals)
        - [Relation to `const char*` and `const char[]`](#relation-to-const-char-and-const-char)
        - [Termination Point `\0`](#termination-point-0)
        - [Syntax for Creating String Literals](#syntax-for-creating-string-literals)
        - [Using String Literals in Functions](#using-string-literals-in-functions)
        - [Examples](#examples)

<!-- markdown-toc end -->



String literals in C++ are a fundamental concept and are quite interesting.
Let's break down your questions one by one.

## My Understanding

In C++, the way string literals are stored can vary based on how they are
declared.
```cpp

"Hello World!"  <- this will be stored in `read-only` memeory and you cannot modify
^                   it and it is a `const char[]` that you cannot access it directly,
|                   you cannot change the size during the run-time.
|                   This section of memeory is a const means you cannot change
+------------+      this string size or modification. and it will lives along the program life.
             |
const char* my_cstyle_string_ptr = "Hello World!";
            ^
            |
            If you want to assign a pointer to track this,
            you have an option of `const char* my_cstyle_string_ptr`.
            Usually the pointer is stored with a specific life-time either
            global as `static` or `local` within the function/method scope.

const char my_cstyle_string_array[] = "Hello World!";
           ^
           |
           |
           +------ If you want to change the string literal (modifying some characters not chaning the size)
                   Then we create the string literal on a stack as an array of characters and it will be
                   a null-terminated with `\0`. Now, this can be modified and also the `my_cstyle_string_array`
                   can decay to a pointer to first element (check more about string cstyle as an array).


char* my_cstyle_string_array_on_heap[] = new char*[]{"Hello World!"};
            ^
            |
            |
            +---- Now, we allocate on heap for growing string type as we want to
                  increase the size or modify in run-time, also for lifetime contorl for this string literal.
                  **notice** that I didn't add the `const` as this string we want it to grow in size as we allocated on the heap.
                  but, if you want to just keep it to live beyond the scope that it declared,
                  and you don't want to modify the size, then it is ok to use `const`.

```
Let's examine each of your examples:

```cpp
std::cout << "Hello World1" << std::endl;
const char* my_cstyle_string_ptr = "Hello World2";
const char my_cstyle_string_array[] = "Hello World3";
```

### 1. `"Hello World1"`
This is a string literal. In C++, string literals are stored in a read-only
section of memory (often the data segment). They have static storage duration,
which means they exist for the entire duration of the program.

- **Type:** `const char[12]`
- **Storage:** Read-only, static storage duration.

### 2. `const char* my_cstyle_string_ptr = "Hello World2";`
Here, `my_cstyle_string_ptr` is a pointer to a string literal. The string
literal `"Hello World2"` itself is stored in a read-only memory segment, just
like the first case. The pointer `my_cstyle_string_ptr` points to the first
character of this string.

- **Literal Type:** `const char[12]`
- **Pointer Type:** `const char*`
- **Storage of Literal:** Read-only, static storage duration.
- **Storage of Pointer:** Depends on where `my_cstyle_string_ptr` is declared.
  If it's a global variable, it has static storage duration. If it's a local
  variable, it has automatic storage duration.

### 3. `const char my_cstyle_string_array[] = "Hello World3";`
In this case, `my_cstyle_string_array` is an array that is initialized with the
string literal `"Hello World3"`. Unlike the pointer in the previous example, the
array here will copy the contents of the string literal into its own memory
space.

- **Type:** `const char[13]`
- **Storage:** The array `my_cstyle_string_array` has its own storage. If it's a
  global variable, it has static storage duration. If it's a local variable, it
  has automatic storage duration.

### Summary

- String literals themselves are stored in read-only memory with static storage
  duration.
- Pointers to string literals (like `my_cstyle_string_ptr`) point to this
  read-only memory.
- Arrays initialized with string literals (like `my_cstyle_string_array`) copy
  the literal into their own memory space. The storage duration of this memory
  depends on where the array is declared (global or local scope).

----

## Understanding String Literals in C++

A string literal in C++ is a sequence of characters surrounded by double quotes.
For example, `"Hello, World!"` is a string literal. It's a way to represent text
within the code.

### Type of String Literals

In C++, string literals are of type `const char[]`. This means they are arrays
of constant characters. When you use a string literal in your code, it is
actually an array of characters.

### Storage of String Literals

String literals are typically stored in a special section of the program's
memory, often referred to as the "read-only data" section or "text segment."
This is neither the stack nor the heap but a separate area where constants are
stored. This area is read-only, meaning you cannot modify the contents of string
literals.

### Relation to `const char*` and `const char[]`

- `const char* my_cstyle_string_as_ptr`: When you assign a string literal to a
  `const char*`, the pointer points to the first character of the string literal
  in the read-only memory section.
- `const char my_cstyle_string_as_array[]`: This is an array of characters. If
  you initialize an array with a string literal, the characters of the literal
  are copied into the array, which resides in the stack (if it's a local array)
  or the heap (if dynamically allocated).

### Termination Point `\0`

In C++, string literals are automatically null-terminated. This means a `\0`
(null character) is automatically added at the end of the string literal. This
null character is important for functions in the C Standard Library to determine
where the string ends.

### Syntax for Creating String Literals

In C++, you can create string literals using double quotes, like `"Hello"`.
Additionally, C++11 introduced raw string literals, which allow for multiline
and unescaped sequences, using the syntax `R"(sequence)"`. For example:

```cpp
R"(This is a
raw string literal "with quotes" and \n no escape characters.)"
```

### Using String Literals in Functions

- **As Input Parameters**: You can pass string literals as `const char*` or
  `const std::string&` to functions. For example, `void myFunction(const char* str)` or `void myFunction(const std::string& str)`.
- **As Return Values**: You can return a string literal from a function as
  `const char*`. However, returning it as a `std::string` is more common in C++
  as it is safer and more flexible.
- **Getting a Reference**: You generally don't get a reference to a string
  literal directly. Instead, you might refer to it through a pointer or by
  copying it into a `std::string` object.

### Examples

Here are some examples to illustrate these concepts:

1. **Basic String Literal**:

   ```cpp
   const char* hello = "Hello, World!";
   ```

2. **Function Using String Literal**:

   ```cpp
   void printMessage(const char* message) {
       std::cout << message << std::endl;
   }

   // Usage
   printMessage("Hello, World!");
   ```

3. **Returning String Literal from Function**:

   ```cpp
   const char* getGreeting() {
       return "Hello, World!";
   }
   ```

4. **Raw String Literal**:
   ```cpp
   auto rawStr = R"(This is a "raw" string literal \n with no escape.)";
   ```

Remember that while you can modify characters in a `char[]` array, you should
never modify a string literal directly as it is stored in read-only memory and
doing so can lead to undefined behavior.
