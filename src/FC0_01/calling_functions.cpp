#include <iostream>
#include <cstdio>
//#include <math.h> // This one for c and I didn't use it here
#include <cmath> // This one for c++ and I used it for pow() function
//#include <stdio.h>   // This is for C-language only
using namespace std;

int add(int x, int y)
{
    return x + y;
}

int counter = 0;

int USING_IF(int x)
{
   bool comparisonResult = x == 5;
   if(comparisonResult)
   {
       printf("\nThe value of x = 5 and input is = ");

   }
   else if (x == 7)  // There is no elif together in C++
   {
       printf("\nThe value of x = 7 and input is = ");
   }
   else{
       printf("\nThe value you input is = ");
   }
    printf("\n------- you have used the function ------ \n");
    counter = counter +1;
    cout << "You have called this function " << counter << " times \n";
    printf("------- -------------------------- ------ ");
    printf("\n------- The value you input is =  ------ \n");
 return x;

}
void Log(const char* message)
{

    std::cout << message << std::endl;

}

void using_loop(const char* message)
{
    for(int i = 0 ; i < 10; i ++){
        // Log(message);
        std::cout << message <<" "<<i<<std::endl;
    }
}

void using_loop2(const char* message)
{
    int i = 0;
    bool condition = true;
    for (;condition;)
    {
        Log(message);
        i ++;
        if ( !(i < 5))
        {
            condition = false;
        }
    }
}

// Using the while loop here

void using_while(const char* message)
{
    int i = 1;
    while (i < 10)
    {
        Log(message);
        i ++;
    }
}


// using the do-while loop

void using_do_while(const char* message)
{
    int i = 0;
    do
    {
        Log("at least this will be executed once");
        Log("iteration No");
        cout << i << endl;
        i ++;
    } while ( i < 10);

}


// control flow statement with loops usually
// continue, break, return

void control_flow(const char* message)
{
    for (int i = 0; i < 5; i ++)
    {
        if ( i % 2 == 0) // skip every second value of increment i
        {
            continue;
        }
        Log(message);
        cout << i << endl;
    }

    for (int i = 0; i < 5; i ++)
    {
        if ( (i+1) % 2 == 0) // skip every second value of increment i
        {
            break;  // if the condition above true then the loop will be terminated
        }
        Log("========================");
        cout << i << endl;
    }

}


// Pointers - memory management enhancement -this is not smart pointer
// pointer is an integer of the address of memory -

void learn_pointer(const char* message)
{
    // pointer has not type - just a memory address (integer)
    // but there is a social convention to define data type.

     void* ptr1 = 0; // we gave a memory address of (0) we can read or write from (0)
     void* ptr2 = NULL;
     void* ptr = nullptr; // introdcued in C++11
     cout << ptr << endl;
     Log("===========================");
     int var = 8; // where is the location in memory for a variable already declared
     void* ptr3 = &var; // go bring me the address of memory and put it in pointer ptr3.
     cout << "The pointer ptr3 is = "<< ptr3 << endl;
     Log("You can see that uppersend just has return the address of (var) then we stored it in a pointer called ptr3");
     Log("===========================");
     Log("========= Change the pointer value doesn't change anything ===========");
     int* ptr4 = &var;
     cout << "The pointer ptr4 is = "<< ptr4 << endl;
     Log("--------- Learn how to cast for different datatype ---------");
     double* ptr5 = (double*)&var; // casting to make it same as the container that you declared.
     cout << "The pointer ptr5 is = "<< ptr5 << endl;
     Log("The data type of pointer is used only for manpulate data as we say store a (4) bytes as int in memory and it will not affect the address of memory which is the function of the pointer itself");
     Log("===========================");
     Log("--------- Dereferencing our pointer very important !!!! ---------");
     Log("Simply we when we do dereferencing we will need to specify the memory length and thus we will need to us int, double ..etc instead of void ");
     int var2 = 10;
     int* ptr6 = &var2; // it was void before, and we told the compiler to specify this pointer as (int) so we can obtain the value we specified. it can be 32-bit, 64-bit ...etc
     cout << "\nI print here the current value of the pointer = "<< *ptr6 ;
     printf("\nThe value of var2 = %d%*c Which I assigned recently",var2,2);
     printf("\n--------------------------");
     // lets change the value there to 8
     *ptr6 = 8;
     printf("\nThe value of pointer now is = %d",var2);
     Log("\n===========================");
     Log("--------- New Topic goes here ---------\n");

}


// Using printf in C++
void using_printf(const char* message)
{
    char ch = 'a';
    float a = 5.0, b = 3.0;
    int x = 10;
    printf("%.3f / %.3f = %.3f \n", a,b,a/b);
    printf("Setting width %*c \n",5,ch);
    printf("Octal equivalent of %d is %o \n",x,x);
}



void data_type(const char* message)
{
    /**
     * Report on the size of various c++ data types.
     * This program may give different results when run on different computers depending
     * on how how each of the fundamental data type is defined on those platflorms.
     */
    // Integer types:
    Log("============================================");
    Log("         Data types and their memory        ");
    Log("============================================");
    Log("--------------------------------------------");
    Log("---- The Integer types ------");
    Log("--------------------------------------------");
    cout << "The size of short is     = " << sizeof(short) << " bytes" << endl;
    cout << "The size of int   is     = " << sizeof(int)   << " bytes" << endl;
    cout << "The size of long  is     = " << sizeof(long)  << " bytes" << endl;
    // long long might not exist on all computers.
    Log("--------------------------------------------");
    Log("---- The long-long types ------");
    Log("--------------------------------------------");
    cout << "The size of long long is = " << sizeof(long long) << " bytes" << endl;
    // Character and boolean types:
    Log("--------------------------------------------");
    Log("---- The boolean types ------");
    Log("--------------------------------------------");
    cout << "The size of char   is    = " << sizeof(char)  << " bytes" << endl;
    cout << "The size of bool   is    = " << sizeof(bool)  << " bytes" << endl;
    // Floating point types:
    Log("--------------------------------------------");
    Log("---- The floating-point types ------");
    Log("--------------------------------------------");
    cout << "The size of float  is    = " << sizeof(float) << " bytes" << endl;
    cout << "The size of double is    = " << sizeof(double)<< " bytes" << endl;
    // long-double might not exist on all computers:
    Log("--------------------------------------------");
    Log("---- The long-double types ------");
    Log("--------------------------------------------");
    cout << "The size long-double is  = " << sizeof(long double) << " bytes" << endl;

    /**
     * Notice that an int is 4 bytes on both machines and so, in both cases, int variables can hold values from −2^31 to 2^31 − 1. Note also that double variables on both machines are 8 bytes, but this does not tell us the range of values that double values can take.
        For the float and double data types, there are three quantities of interest: the largest value, the smallest positive value, and the difference between 1 and the smallest value greater than 1. This latter value is known as the epsilon value of the data type. Knowing that a double is 8 bytes does not immediately reveal these three quantities.
        C++ provides header files with this information. The header file climits gives the minimum and maximum value of various integer types. It defines symbols such as INT_MIN and INT_MAX that are equal to the smallest and largest value an int may hold. Similarly, the header file cfloat gives the minimum positive, maximum, andepsilonvaluesforfloat,double,andlong double(if available)datatypes.
     */
    // #include <climits>  // max & min size of integer types
    // #include <cfloat>   // max & min size of real types
    // Integer types:
    Log("============================================");
    Log("         Data types and their memory        ");
    Log("============================================");
    // print out the extreme values of various integer types.
    Log("--------------------------------------------");
    Log("The maximum and minium of integer data types");
    Log("--------------------------------------------");
    cout << "The maximum size of an int  is              = " << INT_MAX  << endl;
    cout << "The minimum size of an int  is              = " << INT_MIN  << endl;
    cout << "The maximum size of a short is              = " << SHRT_MAX << endl;
    cout << "The minimum size of a short is              = " << SHRT_MIN << endl;
    cout << "The maximum size of a long  is              = " << LONG_MAX << endl;
    cout << "The minimum size of a long  is              = " << LONG_MIN << endl;
    Log("----------------------------------------------------");
    Log("long - long values might not exist on some computers");
    Log("----------------------------------------------------");
    cout << "The maximum size of a long long is          = " << LLONG_MAX << endl;
    cout << "The minimum size of a long long is          = " << LLONG_MIN << endl;
    Log("----------------------------------------------------");
    Log("               Float point                          ");
    Log("----------------------------------------------------");
    cout << "The minimum positive value of a float is    = "  << FLT_MIN     << endl;
    cout << "The minimum epsilon value of a float is     = "  << FLT_EPSILON << endl;
    cout << "The maximum value of a float is             = "  << FLT_MAX     << endl;

    cout << "The minimum positive value of a double is   = "  << DBL_MIN     << endl;
    cout << "The minimum epsilon value of a double is    = "  << DBL_EPSILON << endl;
    cout << "The maximum value of a double is            = "  << DBL_MAX     << endl;

    Log("----------------------------------------------------");
    Log("               Long-double                          ");
    Log("----------------------------------------------------");
    cout << "The minimum positive value of a long double is = "  << LDBL_MIN     << endl;
    cout << "The minimum epsilon value of a long double is  = "  << LDBL_EPSILON << endl;
    cout << "The maximum value of a long double is          = "  << LDBL_MAX     << endl;

    Log("----------------------------------------------------");
    Log("               Example on variables types           ");
    Log("----------------------------------------------------");
    double numerator = 13;
    double denominator = 5;
    double quotient;
    quotient = numerator / denominator;
    printf("the value of r is = %.5f and the value of s = %.5f and the value of denomiantor is = %.5f \n",quotient,numerator,denominator);
    Log("----------------------------------------------------");
    Log("               Using int value capacity             ");
    Log("----------------------------------------------------");
    double x = pow(2,31); // Using the math
    double xnew = x / 2;
    printf("The value of x is = %.1f and xnew is = %.1f", x, xnew);


}




