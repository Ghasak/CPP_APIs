# CPP Core concepts:
Collecting my notes on the `C++` Core concepts.

## Common Practice for memory management

Seems that most developers in C++ are using some pre-defined tools and data
stature which allow them to control the objects and data creation in the
memory. As we know the heap is a part of memory fer dynamic memory allocation
while stack is on top of that that is used for static memory allocation.
That is why for a `list` built-in in `C++` (not the one from `STl: standard
template library`) must define the size statically, which means it cannot be
expanded in `Runtime`. That is for the `Heap` which is used to allocate
dynamically a list using the `heap` allocation which will be expanded
dynamically in `runtime`, and also we have `size()` method usually defined to
get us the size.

- Use `stack` allocation data types and data structure.
- Use smart pointers.
- Use the data structure `Vector` from `STL` and use the static ones, don't use
  the `heap` array with (`new`) keyword.

**Note**:
In python, it seems that the `variables` and some pre-defined size `list` such
as `numpy.array` are created on the `stack` while dictionary or any other data
structure that will expand in the `runtime` it will be created on the `heap`.
Creating anything on the `heap` is considered a bad practice as it's notoriously
slower than the `stack`.


## How to run
```cpp
c++ ./src/main.cpp -o ./build/main --std=c++20  && ./build/main
```

## Data Types and Data Structures and Fundamentals:

- [x] Data Primitive Types.
- [x] Array, list, vector - on stack and heap.
- [x] Pointer and reference with functions and implementations.
- [x] Data Map, Hash table (called dictionary in python).
- [x] OOP in C++
- [x] Templates.
- [x] Life of the objects in C++
- [x] Other concepts.

## Operators

### The (::) operator

This operator has several implementations in `CPP`:
- As a `namespace` to group files
- As a scope resolution operator
    - read more on page 92 `Antonio Mallia Francesco Zoffoli - C++
      Fundamentals_ Hit the ground running with C++ the language that supports
      tech giants globally-Packt Publishing 2019.pdf`
    - Also watch more details here [C++ object-oriented tutorials](https://www.youtube.com/watch?v=crtrkPFWq6o&list=PLfyXUgjpxUVFwHkJJ7O6tejR-IL13J2uL&index=8)

- As a `unary Scope Operator`,
  - check this out
  - [unary scope operator](https://www.youtube.com/watch?v=G4qXfcxMgMM&list=PLfyXUgjpxUVGsuprhbbniYm3VGuEaJN0s&index=25)

## Reference:
- [How to color the std::cout](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)
