# Compiler Configurations

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [Compiler Configurations](#compiler-configurations)
  - [Problem I faced](#problem-i-faced)
  - [Solution](#solution)

<!-- markdown-toc end -->

## Problem I faced

The problem that i faced when I tried to develop same project on my `Linux`
server using the `Ubuntu`, I found our the following facts;

1. You have two options:

- when you build your project either you select the GNU project tools for
  building these are related to the `GNU-GCC` project and the complier is `g++`
  located in the `/usr/bin/` which I believe comes by default installed with the
  Ubuntu-desktop.
- Using `Clang++` which is part of the project `LLVM` which is the same complier
  for using C++ on macOS.
2. The problem is now how to match your build with the compiler is no problem at
   first until you face to fetch a 3rd-party library (I for example used glog
   from goolge). They have used some specific flags which works only on
   GNU-projet as I donwload the depenendencies automatically using the `VCPKG`
   which will fetch the dependencies that fits to your system.
3. Thats lead me to find the following,When using clang++, you can specify the
   C++ standard library with the -stdlib= flag. For clang++, the two primary
   options for this flag are:

- `-stdlib=libc++` to use LLVM's implementation of the C++ standard library.
- `-stdlib=libstdc++` to use the GNU implementation of the C++ standard library,
  which is the default on most Linux distributions where GCC is the default
  compiler. Example usage with clang++:

```sh
clang++ -stdlib=libc++ my_program.cpp
```

- For g++ (GCC), there is no direct equivalent flag to choose the standard
  library because g++ is designed to work with libstdc++, which is GCC's own
  implementation of the C++ standard library. Therefore, you generally do not
  need to specify a standard library when using g++, as it will automatically
  use libstdc++.

- If you're compiling with clang++ on a system where g++ is also installed, you
  might need to specify -stdlib=libstdc++ if you want to use GCC's standard
  library with Clang. Otherwise, you might use -stdlib=libc++ to use LLVM's
  library, especially if you're targeting cross-platform consistency or want to
  leverage features specific to libc++.

- It's important to ensure that the chosen standard library is installed on your
  system. For example, on some Linux distributions, you might need to install
  libc++ and its development packages manually if you decide to use it with
  Clang.

## Solution

4. On my Ubuntu I have decided to use the language server for C++ which belong
   to the clang namely `clangd` and this lsp needs to know the files location
   which it will use to help you to use all the features of the lsp (such as
   jump to definition, hovering, linting, ..etc.), It works fine in the `macOS`
   as it knows the location of the installed `standard library of the C++`, but
   it dosn't know the standard library location of the linux of the GCC form GNU
   Project. so, to make the clangd complete and works for any file in your
   project or the standard library you will need two things:

- In Linux Systems (e.g., Ubuntu) you will tell the clangd to look into these headers

  - The standard library location

  ```clangd
  Add:
    - -I/usr/include/c++/11
    - -I/usr/include/x86_64-linux-gnu/c++/11
    - -I/usr/include/c++/11/backward
    - -I/usr/lib/gcc/x86_64-linux-gnu/11/include
    - -I/usr/local/include
    - -I/usr/include/x86_64-linux-gnu
    - -I/usr/include
  ```

  - You also have added the support by CMAKE for the clangd namely

  ```cmake
  # Setting my compiling command for clangd language server
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  ```

  - Then you need to link the out put to the root of your directory, the
    generated file called `compile_commands.json`.
