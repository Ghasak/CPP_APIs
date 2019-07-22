# Running the C++ Code:
## C0_00- Basics:
We can debug our code in several ways in the Mac environment and here is the best way to do so


1. lets assume we have the following code in the directory (current)
```cpp
#include <iostream>
#include <string>

using namespace std;
int main(){
    std::cout << "------------------------------- \n";
    std::cout << "Processing Data Source in Order" << std::endl;
    std::cout << "-------------------------------";
    std::cin.get();

}
```

There are several ways to debug and run the code

### A-Method simplisit
Run the code using **Runner** in the vscode itself, or using **XCODE**.
### B-Method compiling using the terminal
simply run
```cpp
g++ C0_00.cpp // This will create a file called a.out, which can be run as:
./a.out
```
### C-The one I use
Either you use the full-directory like:

```cpp
cd "/Users/ghasak/Desktop/My_DATA_MP/Learning/11_CPP_APIs/src/" && g++ C0_00.cpp -o C0_00 && "/Users/ghasak/Desktop/My_DATA_MP/Learning/11_CPP_APIs/src/"C0_00
```
Or you use the following short version:
```cpp
cd "./." && g++ C0_00.cpp -o C0_00 && ./C0_00
```


# How the C++ Complier Works
Object file is the one we get from converting the txt file to a an object file. Changing the txt file to an object file (binary file).
**Translation unit**: if you want to put all your cpp files into one single cpp file.

