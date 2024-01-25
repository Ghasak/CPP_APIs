# Tips and Tricks in C++

The following tips and tricks are generally common for professional C++ code writing.



## Rules of OPP

1. Always pass your object as `const type&` , for example

```cpp
// Assume you have an object called e extensionated from a class called Entity.
void my_function_caller(const &Entity e){}
```



