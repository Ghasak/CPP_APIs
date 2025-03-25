# Clangd update 

- Check your g++ version that you use 

```sh 
echo | g++ -v -x c++ -E -
```

- The output use `AI` to generate a `.clangd` file for you, based on the given version.



- You can see that I have used `C++ v11` before and now as I have updated and
  upgraded my current complier on `Ubuntu 24.04` I now use `C++ version 13`.

```sh 

# CompileFlags:
#   Add:
#     - -I/usr/include/c++/11
#     - -I/usr/include/x86_64-linux-gnu/c++/11
#     - -I/usr/include/c++/11/backward
#     - -I/usr/lib/gcc/x86_64-linux-gnu/11/include
#     - -I/usr/local/include
#     - -I/usr/include/x86_64-linux-gnu
#     - -I/usr/include
#
CompileFlags:
  Add:
    - -std=c++17
    - -I/usr/include/c++/13
    - -I/usr/include/x86_64-linux-gnu/c++/13
    - -I/usr/include/c++/13/backward
    - -I/usr/lib/gcc/x86_64-linux-gnu/13/include
    - -I/usr/local/include
    - -I/usr/include/x86_64-linux-gnu
    - -I/usr/include
```
