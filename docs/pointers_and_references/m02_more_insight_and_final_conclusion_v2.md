# INSIGHT OVER POITNER

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [INSIGHT OVER POITNER](#insight-over-poitner)
  - [POINTER DIAGRAM](#pointer-diagram)
  - [Why Pointers are different in each run?](#why-pointers-are-different-in-each-run)
    - [Running the program - In Terminal](#running-the-program---in-terminal)
    - [Running the program - Inside lldb](#running-the-program---inside-lldb)

<!-- markdown-toc end -->

## POINTER DIAGRAM

```sh
# This is how the int of 4-bytes reprsented in hex numbers
┌────────────────────────┐
│[0][0][0][0][0][0][0][0]│ 8-bits in binary system representing 1-byte
└────────────────────────┘ 8-blocks occupied by 0/1
   ┌───────┘
   ▼
┌──────┐
│[0][0]│[0][0]-[0][0]-[0][0]||[0][0]-[0][0]-[0][0]-[0][0]
└──────┘
 |----|-|----|-|----|-|----||||----|-|----|-|----|-|----| 2-blocks (digit) in hex system representing 1-byte
    1      2     3      4        1      2      3      4   each block occupied from 0 to F
 |--------------------------||--------------------------|
          4-bytes                    4-bytes
           │
           ▼
           This is the defintion of
           an integer with value can occupy 4 bytes

              BEFORE MAPPING                              AFTER MAPPING
                                                ┌───────────────────────────────┐ ─┬─
        │[0][0]│──────▶ 0x16fdfbb00             │   │[0][0]│──────▶ 0x16fdfbb00 │  │  Integer Layout:
         [0][0] ──────▶ 0x16fdfbb04  ─────────▶ │    [0][0]                     │  │  - An integer of 4 bytes occupies 4 consecutive addresses in
         [0][0] ──────▶ 0x16fdfbb08             │    [0][0]                     │  │  memory, not 4 separate pointer addresses (e.g., 0x16fdfbb00, 0x16fdfbb04,etc.).
         [0][0] ──────▶ 0x16fdfbb0c             │    [0][0]                     │  │   The pointer points to the first byte only, and the rest of the bytes are
                                                └───────────────────────────────┘ ─┴─  accessed relative to the first address (e.g., ptr + 1, ptr + 2, etc.).
           ||              │                           ||                          │
        │[0][0]│           │                        │[0][0]│                       │
         [0][0]            │                         [0][0]                        └───▶ This width is specified when your declare a pointer by telling this pointer you will refer to
         [0][0]            │                         [0][0]                              to this block of memeory but your limit is up to 4 bytes. If you exceed this [memory access valiation]
         [0][0]            │                         [0][0]                              You will go beyond the limit of declaration of the integer and you get a memory leak.
           ||              │                           ||
        │[0][0]│           │                        │[0][0]│                                      0x16fdfbb04  ─┬─
         [0][0]            │                         [0][0]                                       0x16fdfbb08   │  These will be accessed only if you cast
         [0][0]            │                         [0][0]                                       0x16fdfbb0c  ─┴─  your pointer to move byte by byte (like cast to char)
         [0][0]            │                         [0][0]
           ||              │                           ||
        │[0][0]│           │                        │[0][0]│
         [0][0]            │                         [0][0]
         [0][0]            │                         [0][0]
         [0][0]            ▼                         [0][0]

# Integer (4 bytes) stored in memory

┌────────┬────────┬────────┬────────┐
│ Byte-1 │ Byte-2 │ Byte-3 │ Byte-4 │   <--- Integer value (4 bytes)
├────────┼────────┼────────┼────────┤
│0x1000  │0x1001  │0x1002  │0x1003  │   <--- Memory addresses of each byte
└────────┴────────┴────────┴────────┘

# Pointer to the Integer

┌───────────────┐
│ Pointer Value │   <-- The pointer stores the address of the first byte
├───────────────┤
│    0x1000     │   <-- Address of Byte-1
└───────────────┘

# Full Memory Layout (Pointer + Integer)

┌───────────────┐
│ Pointer (ptr) │   <-- Pointer stored at a separate memory address
├───────────────┤
│    0x1000     │   <-- Value of the pointer (points to Byte-1 of the integer)
└───────────────┘
      │
      ▼
┌────────┬────────┬────────┬────────┐
│ Byte-1 │ Byte-2 │ Byte-3 │ Byte-4 │   <-- Integer value (4 bytes)
├────────┼────────┼────────┼────────┤
│0x1000  │0x1001  │0x1002  │0x1003  │   <-- Memory addresses of each byte
└────────┴────────┴────────┴────────┘

Memory Viewer Note:
- The pointer (e.g., 0x16fdfbb00) refers to the first byte of the integer.
- The following bytes are accessed by offset (e.g., `ptr + 1`, `ptr + 2`, `ptr + 3`).

```

```cpp
    int x[3] = {1, 2, 3};
    for (size_t i = 0; i < std::size(x); i++) {
        LOG(INFO) << RED << "Value of x" << YELLOW << "  => " << BLUE << x[i] << RESET;
        ;
    }

    LOG(INFO) << BLUE << "I want to access the second element and get it back from x[3] = {1,2,3}" << RESET;
    LOG(INFO) << RED << "Address of second elment is given as (x+1), x is a pointer as we know: " << (x + 1) << RESET;
    LOG(INFO) << RED << "Dereference the Address of second elment is given as (x+1), x is a pointer as we know: " << *(x + 1) << RESET;
    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "Getting memory address of each byte of" << "[" << YELLOW << (x + i) << RESET << "]" << RESET;
    }

    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "The value of i -> " << *(x + i) << BLUE << RESET;
    }

    // Access by casting to a 1-byte
    for (size_t i = 0; i < sizeof(x) / sizeof(x[0]); i++) {
        LOG(INFO) << BLUE << "the value of x is -> " << YELLOW << (int*)((char*)x + 4 * i) << RESET;
    }

    if ((sizeof(x) / sizeof(x[0])) == (std::size(x))) {
        LOG(INFO) << YELLOW << "<YES>" << BLUE << " sizeof(x)/sizeof(x[0]) " << RED " IS EQUAL " << RESET << BLUE << " std::size(x)" RESET;
    }

```

- Expected output,

```cpp
 +++++++++++++++++++++++++++++++++++++++++++
I20241127 14:36:08.046536 15596391 main.cpp:165 Value of x  => 1
I20241127 14:36:08.046545 15596391 main.cpp:165 Value of x  => 2
I20241127 14:36:08.046551 15596391 main.cpp:165 Value of x  => 3
I20241127 14:36:08.046557 15596391 main.cpp:169 I want to access the second element and get it back from x[3] = {1,2,3}
I20241127 14:36:08.046563 15596391 main.cpp:170 Address of second elment is given as (x+1), x is a pointer as we know: 0x16f79a2cc
I20241127 14:36:08.046571 15596391 main.cpp:171 Dereference the Address of second elment is given as (x+1), x is a pointer as we know: 2
I20241127 14:36:08.046576 15596391 main.cpp:173 Getting memory address of each byte of[0x16f79a2c8]
I20241127 14:36:08.046582 15596391 main.cpp:173 Getting memory address of each byte of[0x16f79a2cc]
I20241127 14:36:08.046588 15596391 main.cpp:173 Getting memory address of each byte of[0x16f79a2d0]
I20241127 14:36:08.046594 15596391 main.cpp:177 The value of i -> 1
I20241127 14:36:08.046600 15596391 main.cpp:177 The value of i -> 2
I20241127 14:36:08.046605 15596391 main.cpp:177 The value of i -> 3
I20241127 14:36:08.046613 15596391 main.cpp:182 the value of x is -> 0x16f79a2c8
I20241127 14:36:08.046620 15596391 main.cpp:182 the value of x is -> 0x16f79a2cc
I20241127 14:36:08.046628 15596391 main.cpp:182 the value of x is -> 0x16f79a2d0
I20241127 14:36:08.046636 15596391 main.cpp:186 <YES> sizeof(x)/sizeof(x[0])  IS EQUAL  std::size(x)

```

---

## Why Pointers are different in each run?

### Running the program - In Terminal

Suppose we run the following code in the terminal with the extension

```cpp

int main(int argc , char** argv) {

    int x = 300;

    int* ptr = &x;  // Pointer to x

    // Print the address of x directly
    std::cout << "Address of x: " << std::hex << std::showbase << &x << std::endl;

    // Print the pointer value
    std::cout << "Pointer value: " << std::hex << std::showbase << ptr << std::endl;

    // Alternatively, use printf for consistent output
    printf("Address of x: %p\n", (void*)&x);
    printf("Pointer value: %p\n", (void*)ptr);

    std::cout << "Hex value of x => " << std::hex << x << std::endl;
    return 0;
}

```

The output will be:

```sh
+++++++++++++++++++++++++++++++++++++++++++
Address of x: 0x16d97fbac
Pointer value: 0x16d97fbac
Address of x: 0x16d97fbac
Pointer value: 0x16d97fbac
Hex value of x => 0x12c

```

### Running the program - Inside lldb

1. Before proceeding, you need to build the binary to its latest state and modification.
2. Next, we will navigate to `lldb`.

- Provide the binary name for your build.

```sh
(lldb) target create ./build/debug/main
```

3. You will use `run` to check the output of the binary similary to when we get
   it prrinting from terminal above.

```sh
+++++++++++++++++++++++++++++++++++++++++++
Address of x: 0x16fdfbafc
Pointer value: 0x16fdfbafc
Address of x: 0x16fdfbafc
Pointer value: 0x16fdfbafc
Hex value of x => 0x12c
Process 27980 exited with status = 0 (0x00000000)

```

- The first thing we observe is the disparity between the values of the pointer
  in the two runs due to the compiler mapping memory addresses to the running
  binary at each run. This process is analogous to renting or leasing the pointer
  (memory address) by the compiler during execution.

5. I will set a breakpoint to verify the program's functionality. In `lldb`,
   the `breakpoint` command only considers the file name and not the directory
   as each file is treated as a `translation unit` in C++. Notice this for every
   file.

```sh
(lldbinit) br s -f main.cpp -l 161
Breakpoint 1: where = main`TestingString(char const*) + 1064 at main.cpp:161:15, address = 0x000000010001c960
```

5. Now, we can make it work again with `run`
   we will obtain

```sh
------------------------------------------------------------------------------------------------------[regs]
   X0:  0x000000000000001B   X8:  0x0000000204CAF8EC  X16:  0x000000019FB5A7D0  X24:  0x000000019F812000
   X1:  0x0000000000000000   X9:  0x0000000204CB9F08  X17:  0x000000020CF0D740  X25:  0x0000000000000000
   X2:  0x00000000000120A8  X10:  0x0000000000000002  X18:  0x0000000000000000  X26:  0x0000000000000000
   X3:  0x000000013580881B  X11:  0x0000010000000000  X19:  0x0000000204A18050  X27:  0x0000000000000000
   X4:  0x000000019FAAA910  X12:  0x00000000FFFFFFFD  X20:  0x0000000204A180A0  X28:  0x0000000000000000
   X5:  0x000000016FDFBA30  X13:  0x0000000000000000  X21:  0x0000000204A18050   FP:  0x000000016FDFBBF0
   X6:  0x000000000000000A  X14:  0x0000000000000000  X22:  0x000000016FDFBE08   LR:  0x000000010001C95C
   X7:  0xFFFFFFFF00000200  X15:  0x0000000000000000  X23:  0x000000016FDFBE08   SP:  0x000000016FDFBA30
   PC:  0x000000010001C960  n z C v a i f
------------------------------------------------------------------------------------------------------[code]
TestingString(char const*) @ /Users/gmbp/Desktop/devCode/cppDev/CPP_APIs/build/debug/main:
->  0x10001c960 (0x10001c960): 60 02 00 90  adrp   x0, 76
    0x10001c964 (0x10001c964): 00 24 42 f9  ldr    x0, [x0, #0x448]
    0x10001c968 (0x10001c968): 21 02 00 f0  adrp   x1, 71
    0x10001c96c (0x10001c96c): 21 00 02 91  add    x1, x1, #0x80 ; "Hex value of x => "
    0x10001c970 (0x10001c970): f9 a3 ff 97  bl     0x100005954 ; std::__1::basic_ostream<char, std::__1::char_trait
    0x10001c974 (0x10001c974): e0 0f 00 f9  str    x0, [sp, #0x18]
    0x10001c978 (0x10001c978): 01 00 00 14  b      0x10001c97c ; <+1092> at main.cpp
    0x10001c97c (0x10001c97c): e0 0f 40 f9  ldr    x0, [sp, #0x18]
------------------------------------------------------------------------------------------------------------
Process 28418 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x000000010001c960 main`TestingString(str="Hello World!") at main.cpp:161:15
   158 	    printf("Address of x: %p\n", (void*)&x);
   159 	    printf("Pointer value: %p\n", (void*)ptr);
   160
-> 161 	    std::cout << "Hex value of x => " << std::hex << x << std::endl;
   162 	}
Target 0: (main) stopped.

```

6. This will give us the right way

```sh
(lldbinit) memory read ptr
0x16fdfbafc: 2c 01 00 00 55 22 06 00 01 00 00 00 49 22 06 00  ,...U"......I"..
0x16fdfbb0c: 01 00 00 00 80 bb df 6f 01 00 00 21 c4 bb df 6f  .......o...!...o

```

Also,

```sh
(lldbinit) print ptr
(int *) 0x000000016fdfbafc
```

Now, you notice that pointer is similar to the one we obtained by printing it
within the debugger during runtime. This is because pointers remain equivalent
in runtime until the subsequent run, during which the compiler remaps them to
different addresses (different locations in memory).
