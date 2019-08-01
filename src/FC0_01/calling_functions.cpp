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

void using_loop(const char* message2)
{
    for(int i = 0 ; i < 10; i ++){
        // Log(message2);
        std::cout << message2 <<" "<<i<<std::endl;
    }
}
