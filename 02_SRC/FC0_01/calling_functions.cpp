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
     printf("\nThe value of var2 = %d %c Which I assigned recently",var2,2);
     printf("\n--------------------------");
     // lets change the value there to 8
     *ptr6 = 8;
     printf("\nThe value of pointer now is = %d",var2);
     Log("\n===========================");






}


// Using printf in C++
void using_printf(const char* message)
{
    /**
     * Learn more about the place holder in: http://www.cplusplus.com/reference/cstdio/printf/
     * also you will need the header file #include <cstido>
     * specifier	Output	                                        Example
       d or i	Signed decimal integer	                            392
       u	     Unsigned decimal integer	                        7235
       o	     Unsigned octal	                                    610
       x	     Unsigned hexadecimal integer	                    7fa
       X	     Unsigned hexadecimal integer (uppercase)	        7FA
       f	     Decimal floating point, lowercase	                392.65
       F	     Decimal floating point, uppercase	                392.65
       e	     Scientific notation (mantissa/exponent), lowercase	3.9265e+2
       E	     Scientific notation (mantissa/exponent), uppercase	3.9265E+2
       g	     Use the shortest representation: %e or %f	        392.65
       G	     Use the shortest representation: %E or %F	        392.65
       a	     Hexadecimal floating point, lowercase	            -0xc.90fep-2
       A	     Hexadecimal floating point, uppercase	            -0XC.90FEP-2
       c	     Character	                                        a
       s	     String of characters	                            sample
       p	     Pointer address	                                b8000000
       n	     Nothing printed.
                 The corresponding argument must be a pointer to a signed int.
                 The number of characters written so far is stored in the pointed location.
       %	     A % followed by another % character will write a single % to the stream.	%
     *
     *
     *  */

    char ch = 'a';
    float a = 5.0, b = 3.0;
    int x = 10;
    printf("%.3f / %.3f = %.3f \n", a,b,a/b);
    printf("Setting width %*c \n",5,ch);
    printf("Octal equivalent of %d is %o \n",x,x);
    printf ("Characters: %c %c \n", 'a', 65);
    printf ("Decimals: %d %ld\n", 1977, 650000L);
    printf ("Preceding with blanks: %10d \n", 1977);
    printf ("Preceding with zeros: %010d \n", 1977);
    printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf ("Width trick: %*d \n", 5, 10);
    printf ("%s \n", "A string");
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
    /**
     * Notice that the result is equivalent to the one we have
     * in (INT_MAX) and the reason is: x is the maximum value of
     * a integer number can occupy the memory of (int) variable defined
     * such as: int---> is (4 bytes) and each (1 byte) is (8-bits)
     * which means (32-bits) for an (int). Then if we exclude the (sign)
     * such as (+/-) then we ended up with (31-bits). In the binary system
     * and as (1/0) we can represent any value we get (2^31).
     */
    printf("The maximum value of x as an integer value is = %.1f and signed integer is = %.1f\n", x, xnew);
    /**
     * Similary about double (or double-double in mac c++ compiler) we have
     * 16 bytes each byte is 8 bits and so we get (2^64) maximum double value
     * remove one bit for the sign we ended up with (2^63)
     */
    x = pow(2,63); // (8 bytes * 8 bits --> 64 ---> 64-1 = 63)
    xnew = x/2;
    Log("-------------------------------------------------------");
    printf("The maximum value of x as an double value is = %.1f and signed double is = %.1f\n", x, xnew);

    x = pow(2,16); //short
    xnew = x/2;
    Log("-------------------------------------------------------");
    printf("The maximum value of x as an short value is = %.1f and signed short is = %.1f\n", x, xnew);
    // Log("----------------------------------------------------");
    // Log("       Investgate the behavior of the mode          ");
    // Log("----------------------------------------------------");

    // int a, b;
    // cout << "Enter the first number --> " << endl;
    // cin >> a;
    // cout << "Enter the second number -> " << endl;
    // cin >> b;
    // cout << a << " % " << b << " = " << a%b << endl;

}

void practice_pointers_data_type(const char* message)
{
    Log("====================================================");
    Log("               Practice the datatypes               ");
    Log("====================================================");
     // Decimal numbers
     int       x1     = 100;
     short     x1_1   = 100;
     long      x1_2   = 100;
     long long x1_3   = 100;
    // Character and logical
     char        A    = 'a';
     bool        B    = true;
    // floating numbers
     double      x2   = 100.10;
     float       x3   = 200.10;
     long double x2_1 = 100.10;
    Log("----------------------------------------------------");
    printf("The integers values types we have are x = %d, x1_1 = %d, x1_2 = %ld and x1_3 = %lld\n",x1,x1_1,x1_2,x1_3);
    printf("While the sizes are given for each are int       x1   = %lu\n",sizeof(x1));
    printf("While the sizes are given for each are short     x1_1 = %lu\n",sizeof(x1_1));
    printf("While the sizes are given for each are long      x1_2 = %lu\n",sizeof(x1_2));
    printf("While the sizes are given for each are long long x1_3 = %lu\n",sizeof(x1_3));
    Log("----------------------------------------------------");
    printf("The boolian character are represented by char A = %c and B = %d\n",A,B);
    printf("While the sizes are given for each are char       A   = %lu\n",sizeof(A));
    printf("While the sizes are given for each are bool       B   = %lu\n",sizeof(B));
    Log("----------------------------------------------------");
    printf("The floating numbers represented by double are x2 = %.2f and float x3 = %.2f\n and long double x2_1 = %.2Lf \n",x2,x3,x2_1);
    printf("While the sizes are given for each are double       x2     = %lu\n",sizeof(x2));
    printf("While the sizes are given for each are float        x3     = %lu\n",sizeof(x3));
    printf("While the sizes are given for each are long double  x2_1   = %lu\n",sizeof(x2_1));
    Log("----------------------------------------------------");
    int* intptr = &x1;
    printf("The address to refere to x1 in memory is       = %p\n",intptr);
    printf("Dereferencing to obtain back the value of x1   = %d\n", *intptr);
    printf("The value of x1 before changing is = %d\n", x1);
    *intptr = 500;
    printf("The value of x1 after changing is  = %d\n", x1);
    printf("Can we chagne to other types .....\n");
    double s = (1.000 * x1); //(double)x1;   // or you can cast by using 1.000 * x1
    double* doubleptr = &s;   // you can't use &(double)x1;
    *doubleptr = 500.5;
    printf("The value of s after changing from int to double is  = %.3f\n",s);
    printf("---------------------------------------------------\n");
    short* shortptr = &x1_1;
    printf("The address to refere to x1_1 in memory is     = %p\n",  shortptr);
    printf("Dereferencing to obtain back the value of x1_1 = %d\n", *shortptr);
    printf("The value of x1_1 before changing is = %d\n", x1_1);
    *shortptr = 1000;
    printf("The value of x1_1 after changing is  = %d\n", x1_1);
    printf("---------------------------------------------------\n");


}

// Cating types in C++
void Type_Casting_Operators(const char* message)
{
    /**
     *          Static_cat in C++: Type Casting Operators
     * A cast is an unary operator which forces one data type to be converted
     * into another data type C++ supports four types of casting:
     *          - Static      cast
     *          - Dynamic     cast
     *          - Const       cast
     *          - Reinterpret cast
     */

    float f = 3.5;
    int a = f; // this is how you do in C
    int b = static_cast<int>(f);
    cout << b << endl;
    cout << a << endl;

    int x1 = 100;
    double x2 = static_cast<double>(x1);
    double* doubleptr = &x2;
    cout << doubleptr << endl;
    cout << *doubleptr << endl;

    double* q = static_cast<double*>(&x2);
    cout << q  << endl;
    cout << *q << endl;


}

