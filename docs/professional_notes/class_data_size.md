# Class - Struct data size

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Class - Struct data size](#class---struct-data-size)
  - [Class/Struct of all fields on stack](#classstruct-of-all-fields-on-stack)
  - [Class/Struct of all fields on Heap](#classstruct-of-all-fields-on-heap)
    - [Member Variables](#member-variables)
    - [Calculating the Size](#calculating-the-size)
    - [Total Size](#total-size)
    - [Conclusion](#conclusion)

<!-- markdown-toc end -->

There is a way to make our understanding more robust about classes and structs
by measuring the size in bytes of the object (instance) that is derived from a
given class or struct. While we have discovered that these constructs serve as
ways to combine primitive data or other types and group them together, this
metric can provide us with additional insights into their memory consumption..

## Class/Struct of all fields on stack

Here we have primitive types of data.

```cpp
class Vec2d {
    int x;
    int y;
    const char* c;

public:
    Vec2d(int xi, int yi, const char* ci)
        : x{xi},
          y{yi},
          c{ci} {}
};

int main(int argc, char* argv[]){
    const char* my_name = "ABC";
    LOG(INFO) << RED "Size of this char* "
              <<"pointer data type -> "
              << BLUE << sizeof(my_name) << RESET;

    Vec2d v1 = Vec2d(10, 20, "ABC");
    LOG(INFO) << RED "Size of this Vec2d Class data type -> " << BLUE << sizeof(Vec2d) << RESET;

return 0;
}
// Output macOS x64
//I20240205 03:10:03.598434 14790394 main.cpp:48] Size of this char* pointer data type -> 8
//I20240205 03:10:03.600180 14790394 main.cpp:51] Size of this Vec2d Class data type   -> 16      //<-(MY NOTE: as expected no padding)


```

- The size w can expect from sizeof(my_name) does not depend on the content the
  pointer points to ("ABC" in this case) but rather on the architecture of the
  system on which the code is compiled and run. The size of a pointer is
  determined by the architecture's address space:

  - On a 32-bit system, pointers are generally 4 bytes in size.
  - On a 64-bit system, pointers are generally 8 bytes in size.

- The sizeof operator is returning the size of the pointer itself, not the length
  of the string it points to. The reason why sizeof is used on a pointer in this
  context is typically to understand or document the memory requirements or
  structure layouts in the program, rather than to get the length of the string.
  For string length, functions like strlen are used instead, which count the
  number of characters up to the first null terminator.

- Therefore, based on the architecture of the system you are using, you can expect:

  - 4 bytes for a 32-bit system.
  - 8 bytes for a 64-bit system.

- This information is useful for understanding memory allocation and pointer
  arithmetic in your program.

- To determine the size of the `Vec2d` class, you must consider the size of its
  member variables. The class has the following members:

  - `int x;` // size is typically 4 bytes on most systems
  - `int y;` // size is typically 4 bytes on most systems
  - `const char* c;` // size depends on the architecture, 4 bytes on 32-bit systems and 8 bytes on 64-bit systems

However, the actual size of an instance of `Vec2d` can be larger than the simple
sum of its members' sizes due to **padding** and **alignment** requirements
imposed by the compiler to optimize memory accesses. These requirements can vary
between compilers and target architectures.

Assuming no compiler optimizations such as padding for alignment:

- On a **32-bit** system, the size would likely be **4 (x) + 4 (y) + 4 (c) = 12 bytes**.
- On a **64-bit** system, the size would likely be **4 (x) + 4 (y) + 8 (c) = 16 bytes**.

- However, because of alignment requirements, the compiler might add padding to
  ensure that `c` is aligned on an 8-byte boundary in a 64-bit system (and
  potentially even on a 32-bit system, depending on the compiler's rules for
  alignment). This could alter the expected size.

- For example, if the compiler requires `c` to be aligned on an 8-byte boundary
  on a 64-bit system, it might insert 4 bytes of padding after `y` to ensure
  that `c` starts at an 8-byte boundary, making the size of the class 16 bytes
  on a 32-bit system and 24 bytes on a 64-bit system.

- To get an exact size, it's best to compile the code on the target system and
  use `sizeof(Vec2d)` to see the size determined by the specific compiler and
  architecture you are using. Padding and alignment can vary, so the real size
  can only be accurately determined through compilation.

## Class/Struct of all fields on Heap

```cpp
// Represents an entity with an integer and a name.
class EEntity {
public:
    int x; // The integer value of the entity.
    std::string eobjName; // The name of the entity.

    // Constructs an EEntity with a specified integer and name.
    EEntity(int x, std::string name);

    // Default constructor.
    EEntity();

    // Destructor.
    ~EEntity();
};
```

To understand why the size of the `EEntity` class might be 32 bytes, we need to
consider the size of its member variables and any padding/alignment requirements
imposed by the compiler. However, it's important to note that the exact size can
vary depending on the compiler, the architecture (32-bit vs. 64-bit), and the
implementation of the `std::string` class in the C++ Standard Library being
used. Here's a breakdown based on common implementations and a 64-bit
architecture:

### Member Variables

- **`int x;`**: The size of an `int` is typically 4 bytes on both 32-bit and
  64-bit systems.
- **`std::string eobjName;`**: In many implementations of the C++ Standard
  Library, such as the GNU Standard C++ Library (libstdc++) and LLVM's libc++, a
  `std::string` object usually contains:
  - A pointer to the dynamic character array (heap) (8 bytes on a 64-bit
    system).
  - A size member to track the number of characters in the string (8 bytes).
  - A capacity member indicating how much space has been allocated (8 bytes).

The above layout for `std::string` is just one possible implementation and can
differ; for example, the Small String Optimization (SSO) could change how small
strings are stored internally, but this doesn't typically affect the reported
size of the `std::string` object itself from `sizeof`.

### Calculating the Size

- **`int x;`**: 4 bytes
- **`std::string eobjName;`**: The size of `std::string` could be 24 bytes given
  the components listed above (for a typical implementation without considering
  SSO internals).

### Total Size

- Adding these together, we get 4 bytes (int) + 24 bytes (std::string) = 28
  bytes.
- However, the class's size is mentioned as 32 bytes, which can be accounted for
  by padding added for alignment purposes. The compiler often adds padding to
  ensure that objects are aligned in memory according to their alignment
  requirements, which can help with access speed and conform to hardware and
  architecture requirements.

In a 64-bit architecture, aligning to 8-byte boundaries is common. Since the
size of the `int` and `std::string` together is 28 bytes, an additional 4 bytes
of padding might be added after the `int` member to align the start of the
`std::string` on an 8-byte boundary, depending on the compiler's behavior and
the `std::string`'s actual implementation. However, the given size directly as
32 bytes suggests that the compiler has arranged or padded the class to fit this
size for alignment reasons.

### Conclusion

The stated size of 32 bytes for the `EEntity` class could be a result of the
combined sizes of its members and any compiler-imposed padding/alignment. The
exact reason can vary based on several factors, including the specific compiler
and its version, the C++ standard library implementation, and the target
architecture's alignment requirements.
