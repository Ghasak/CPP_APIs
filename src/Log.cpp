#include <iostream>
using namespace std;
void Log(const char* message)
{
    std::cout << "-------------------------------------------------------------- \n";
    std::cout << message << std::endl;
    std::cout << "-------------------------------------------------------------- \n";
}

void printing_message(const char* message)
{
    cout << "------------------------------------------- \n";
    cout << message << endl;
    cout << "------------------------------------------- \n";
}


int X(int a, int b)
{
    int result = a * b;
    return result;
}
