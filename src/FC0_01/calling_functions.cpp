#include <iostream>
#include <stdio.h>
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
     int* ptr6 = &var2; // it was void before, and we told the compiler to specify this pointer as (int) so we can obtain the value we specified.
     cout << *ptr6 ;



}







