# Installing SDL 2.0 for Mac

The following steps are based on the idea of installing `sdl2` binary/complied without a need to use the `xcode`.
The steps consist of two main things if we want to use only the binary.

![SDL2 Rendering]("./assets/sdl2_rendering_snippet.gif")

## Instructions
1. Install the binary of `sdl2` using

```shell
brew install sdl2
# It will be located at
cd /opt/homebrew/Cellar/sdl2/2.0.22
```
- It's a complied version of `SDL2`, so we don't need to build the project of `SDL2` from scratch.


2. Compile the project using

```shell
g++ main.cpp -I ./dependencies/SDL2.framework/Headers -o main  -std=c++20  && ./main
clang main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -target x86_64-apple-darwin20.3.0 -o test.o
g++ main.cpp -I ./dependencies/SDL2.framework/Headers -L ./dependencies/SDL2.framework/Resources -o main  -std=c++20  && ./main
```

All these I was not able to compile my project with `SDL` it seems my Mac ARM
not compatible even with Metal.


## Instructions -2-
1. Go to SDL official website and download the `SDL2-2.022.dmg` from [SDL
   official website](https://www.libsdl.org/download-2.0.php), under the
   section `Development Libraries:` get the latest version of your SDL2.
2. Now we have all the required both the library and the headers, we can map
   them to our project using: this will give us the `SDL.h` directed to our current directory.

```cpp
#include "./dependencies/SDL2.framework/Headers/SDL.h"
```

3. Later I found the following, that as I already used `brew` I direct both the headers and the lib to these directories `opt/homebrew/include` and `opt/homebrew/lib`
not to mention the flag `lSDL2` to make it work.
```shell
g++ main.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o main  && ./main

```
also, including in the header of your main file

```cpp
#include "./dependencies/SDL2.framework/Headers/SDL.h"
```

I got the same results if I use

```shell
g++ main.cpp -I./dependencies/SDL2.framework/Headers -L./dependencies/SDL2.framework/Resources -lSDL2 -o main  && ./main
# It supposed to be like:
g++ main.cpp -I./dependencies/SDL2.framework/Headers -L./dependencies/SDL2.framework/Resources -l./dependencies/SDL2.framework/SDL2 -o main  && ./main
```
but, this will work for my current dependencies file


## Instructions -3-

Steps that I created

1. Copy the contains of the `SDL2` library into your current project directory using

```shell
cp -r /opt/homebrew/Cellar/sdl2/2.0.22 ./dependencies/

```
2. Refer to it in your main.cpp using

```cpp
#include "./dependencies/include/SDL2/SDL.h"
```

3. Build your system using:
Once we directed the lib with the flag (-L) which is the absolute directory, we
can also add a relative directory (-l). Therefor the `-l SDL2` can refer also
to the directory of the form our already defined directory before.

```shell
g++ main.cpp -I./dependencies/include -L./dependencies/lib -lSDL2 -o main  && ./main
# Or as I don't like not adding spaces, like other developers do.
g++ main.cpp -I ./dependencies/include -L ./dependencies/lib -l SDL2 -o main  && ./main
# Or - This one I use -
g++ ./main.cpp -o main -I  dependencies/include -L dependencies/lib  -lSDL2 -std=c++17  && ./main
```

### Hint
- The `./dependencies/include/` has the header for all functions, attributes, classes, structs and methods declarations.
- The `./dependencies/lib/` has all the definitions.
- (-L) are the binary files to be linked to your final binary. Like `.so` or `.a files` in Linux for example
- (-I) is the directory that has the header files.
- We add (-lSDL2) to add the compiled static or shared library to your final executable


## References

- [Setup SDL2 on your Mac without Xcode](https://medium.com/@edkins.sarah/set-up-sdl2-on-your-mac-without-xcode-6b0c33b723f7)
- [SDL Wiki](https://wiki.libsdl.org/Installation)
- [CMake Super-builds and Git Sub-modules](https://www.kitware.com/cmake-superbuilds-git-submodules/?fbclid=IwAR2ANzGXdfT5Hs_LErPS-I8PIZEBoNZ6hmCmZTyLM5uiXmU7ZNIGhN6EZgA)

