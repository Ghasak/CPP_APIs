#include <iostream>
#include <stdio.h>

using namespace std;


int add(int x, int y)
{
    return x + y;
}

int USING_IF(int x)
{

   bool comparisonResult = x == 5;
   if(comparisonResult)
   {
       printf("\nThe value of x = ", x);
       printf("the bool value is = ",comparisonResult);


   }
 return x;

}


