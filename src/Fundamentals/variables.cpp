#include <iostream>
#include <cmath>

/*
 * === FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
    As we already know that the int is 4 bytes long, each byte is 8 bits. we save one bit for the sign.
    So, the maximum value that can be stored in an int is 2^31 =  2147483647.
    The minimum value that can be stored in an int is -2147483648.
    The maximum value that can be stored in a long is 2^63 = 9223372036854775807.
    The minimum value that can be stored in a long is -9223372036854775808.
    The maximum value that can be stored in a long long is 2^63 = 9223372036854775807.
    The minimum value that can be stored in a long long is -9223372036854775808.
    int is 32 bits long.
    long is 64 bits long.
    long long is 64 bits long.
    float is 32 bits long.
    double is 64 bits long.
    long double is 128 bits long.
    float is a single precision floating point number.
    double is a double precision floating point number.
    long double is a long double precision floating point number.

    Note: we store the number in binary format. which means either 0 or 1.
    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] [16] [17] [18] [19] [20] [21] [22] [23] [24] [25] [26] [27] [28] [29] [30] [31]

    Usually we have the the following five types of primitve data types for storing integer numbers:
    - char (8 bits) or  (1 byte)
    - short (16 bits) or  (2 bytes)
    - int (32 bits) or  (4 bytes)
    - long (64 bits) or  (8 bytes) or 4 bytes depends on the complier.
    - long long (64 bits) or  (8 bytes)
    - You also have unsigned types. which is the same as the signed types excpet that the sign bit is not used.
    - Char can also store a letter, a number, or a symbol.

    - We have for decimal numbers:
    - float (32 bits) or  (4 bytes), decimal numbers are stored in binary format.
    - double (64 bits) or  (8 bytes), decimal numbers are stored in binary format.
    - long double (128 bits) or  (16 bytes)

    - For boolean values:
    - bool (1 bit) or  (1 byte)
    - bool is a primitive data type that can only store two values: true or false.
    - Since we cannot access and address in memory a 1 bit to represent a
        boolean value, we use a byte (8 bits) to represent a boolean value.
        Although we need only one bit, we use 8 bits to represent a boolean value.

    - With these primitive types we also have the ability to use pointer or references to store
        a value.
    - Pointer is a variable that stores the address of another variable.
        - A pointer is declared using the * operator.
        - bool* var = false;
        - int* var = 0;
    - Reference is a variable that stores the value of another variable.
        - A reference is declared using the & operator.
        - bool& var = false;
        - int& var = 0;

 * =====================================================================================
 */

int main(){
    // g++ variables.cpp -o variables -std=c++20 && ./variables
    char c = 'A';
    int i = c;
    int variable = 8;
    bool decision = true;
    int variable_size = std::pow(2, 31);
    std:: cout << "the value of variable is: " << variable << std::endl;
    std:: cout << "the size of variable is: " << sizeof(variable) << std::endl;
    std:: cout << "the value of variable_size is: " << variable_size << std::endl;
    std:: cout << "We have char, int, long, long long, float, double, long double" << std::endl;
    std:: cout << "char is 1 byte long" << std::endl;
    std:: cout << "int is 4 bytes long" << std::endl;
    std:: cout << "long is 8 bytes long" << std::endl;
    std:: cout << "long long is 8 bytes long" << std::endl;
    std:: cout << "------------------------" << std::endl;
    std:: cout << "float is 4 bytes long" << std::endl;
    std:: cout << "double is 8 bytes long" << std::endl;
    std:: cout << "long double is 16 bytes long" << std::endl;
    std:: cout << c << std::endl;
    std:: cout << i << std::endl;
    std:: cout << "------------------------" << std::endl;
    std:: cout << "We have for decimal numbers: " << std::endl;
    std:: cout << "float is 4 bytes long" << std::endl;
    std:: cout << "double is 8 bytes long" << std::endl;
    std:: cout << "long double is 16 bytes long" << std::endl;
    std:: cout << "------------------------" << std::endl;
    std:: cout << "We have for boolean values: " << std::endl;
    std:: cout << "bool is 1 byte long" << std::endl;
    std:: cout << "------------------------" << std::endl;
    std:: cout << sizeof(decision) << std::endl;


    std::cin.get();
}


