# CMake easy example

We are trying to compile a `c++` file using a CMake and Make.
`CMake` is used to generate system files.

## Steps

1. We are trying to compile a script using

```shell
g++ main.cpp -o main -std=c++20 && ./main

```

But imagine in real world scenario we have hundreds or thousands of `*.cpp`
files that we need to compile, therefore, we will need a `build systems` like
the one we will use here which is `CMake`. `CMake` will generate a script of
`Makefiles` that will help us to compile and organize all the `cpp` files that
we have in our project.


2. Adding the `CMakeList.txt`
This file will tell `CMake` How to add the features we need to our project, the
example that I use here is

```CMake
cmake_minimum_required(VERSION "3.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
project(myProject)
add_executable(myProject main.cpp)
```
- `cmake_minimum_required(VERSION "3.0")`,
    this will our program file which `CMake` file to run for the given version.
- `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")`
    Here we add the `std=c++20` by appending it to the string of all given flags
- `project(myProject)`
    We define the project name that we want to our current project.
- `add_executable(myProject main.cpp)`
    this will create an executable file to our `main.cpp` that we provided as a source.
    We can add as many as we want of `soruce files` like the one we used `main.cpp`.

To run the `CMake` simply use, run it where you have your `main.cpp` file
```shell
cmake .
```

3. Run your complied project
If you go to the `Makefile` you will find a flag called `myProject` that we
specified in the step - `2` - at the `add_exectutable`. We can run and compile
our project using:

```shell
make myProject
# or simply
make
```

## Summary
For our `CMake` as one of the `system builds` available:
- We can see that with `CMake` its much easy to run `cmake . then make
  <project_name>`, this will be super handy when we compile several `*.cpp`
  files, and also the `CMake` will help us in managing our dependencies.

## Bonus
How about use same above with `CMake-gui`
- Define the project directory
```shell
~/devCode/cppDev/CPP_APIs/CMAKE_FUNDAMENTALS/CMAKE_INDEPTH/Complite_CPP_Using_CMake_and_Make
```
- Define the build directory
```shell
~/devCode/cppDev/CPP_APIs/CMAKE_FUNDAMENTALS/CMAKE_INDEPTH/Complite_CPP_Using_CMake_and_Make/build
```
- Click the button `Configure`
    - Use the default setting such as `Unix Makefile`, you can also select others like `Make` such as `Ninja`
- Click the button `Generate`
- `cd` to the `build` directory and use `make` or `make <name_project>` to build your project.


## References

- [Top 7 open source C++ build systems](https://www.incredibuild.com/blog/top-7-open-source-c-build-systems)
- [Compiling C++ using CMake and Make](https://www.youtube.com/watch?v=elycr5wi9_g&t=104s)
- [Cmake tips and trick](https://www.youtube.com/watch?v=ffwB60oKr-w&list=PL8i3OhJb4FNV10aIZ8oF0AA46HgA2ed8g)
