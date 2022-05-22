# Tips and Tricks in CPP

## Introduction
It seems the library `colorize` and the library `egin` both need the modern
`cpp` compiler including 17, or 20. I found that including the library using the header file in the given
solution is the best way to include the necessary folders and files from the third party libraries.
You can download the libraries file using

- cout: support the ASCII icons and colors by default such as
```shell
cout << "\ue799 "
cout << "\033[0;33;42mI am a Banana!\033[0m";
```

```shell
-- For colorize the terminal
git clone https://github.com/fengwang/colorize.git
-- for matrix and linear algebra
git clone https://gitlab.com/libeigen/eigen.git

```
## Compile my Code using

```shell
g++ main.cpp -o main -std=c++20
# Or

g++ main.cpp -o main -std=c++17
# you can also use

g++ -o main main.cpp --std=c++17

# In Mac you can also use
c++ main.cpp -o main -std=c++20
```




## References
- [How to add color to the cout CPP](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)
- [C++ How to Program by Paul Deitel Harvey Deitel z-liborg](reading here)
- [Egin main page ... ](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [Egin How to install ... ](https://eigen.tuxfamily.org/dox/GettingStarted.html)
-- [Artificial Neural Network  C++ class](https://www.codeproject.com/Articles/5292985/Artificial-Neural-Network-Cplusplus-Class)
