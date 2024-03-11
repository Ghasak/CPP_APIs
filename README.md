# CPP Learning

The following repository is used mainly for developing and experimneting with
the latest `cpp` apis and the concepts behind the main issues.

## Agenda

- [x] Poiners and References

  - [x] double poiner
  - [x] poiners with array and char array

- [x] Chars and Strings
  - [x] Char and Strings as C-Style
  - [x] Array of Chars
  - [x] std::string
- [x] Arrays and Lists

  - [x] Arrays as a C-Style
  - [x] two dimensional array
  - [x] std::vector

- [x] Function/methods declaration, defitions and calling
- [x] OOP - Classes and Strings

  - [x] Pointers in Classes
  - [x] Member Initzliation
  - [x] Return types in class methods
  - [x] Static in methods
  - [x] Creating objects stack vs heap
  - [x] (\*this ) pointer
  - [x] Copy Constructors
  - [x] Operators with Classes
  - [x] Templates with Classes
  - [x] Virtual Methods
  - [x] Friend Methods

- [x] Modules and Project Structure
  - [x] CMake Buidling with Clang and Clangd-lsp
  - [x] Installing 3rd libraries Using:
    - [x] manually with CMake
    - [x] vcpkg
    - [x] as a git module
    - [x] CMake downloading directly
    - [x] Using pkg-config

### OOP with CPP

The concepts of object-oriented programming (OOP) are thoroughly analyzed and
implemented in the following programs, which facilitate advanced formulating.
These concepts include:

1. Abstraction - selecting and representing essential features or aspects of an
   object or system while hiding unnecessary details
2. Encapsulation - concealing certain information or functionality from
   unauthorized users or components, promoting data integrity and security
3. Inheritance - inheriting properties and methods from a parent class to a
   child class, facilitating code reusability and reducing duplication of effort
4. Polymorphism - utilizing the same method or function in different ways based
   on the context or type of input, enabling adaptability and versatility in
   program design.

## Changing log

- `Fir. Jan. 26th`: Wroking with pointers and references concepts.
- `Mon. Oct. 23rd`: Added more experimentals.
- `Sun. Sep. 3rd.`: Finished the right,

## Details

- CPP learning is a special directory where I put all the necessary fundamentals
  of learning `C++` concepts and ideas.

## CLI Running

- Using the following command to allow the `clang` to run the current file
  system.

```sh
clang++ -std=c++17 -o ./build/debug/main src/main.cpp  && ./build/debug/main
```

## Running in progress

```sh
fswatch -o src/ | xargs -n1 -I{} make all
```

## Debugging using CPPTOOLS

```lisp
(dap-register-debug-template
 "cpptools::Run Configuration-GHASAKII"
 (list :type "cppdbg"
       :request "launch"
       :name "cpptools::Run Configuration"
       :miDebuggerPath (expand-file-name ".local/share/nvim/mason/packages/cpptools/extension/debugAdapters/lldb-mi/bin/lldb-mi" "~")
       :MIMode "gdb"
       :program "${workspaceFolder}/build/debug/${fileBasenameNoExtension}"  ;; Refer to your binary here
       :cwd "${workspaceFolder}"))
```
