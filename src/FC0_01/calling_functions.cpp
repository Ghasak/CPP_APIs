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

}




