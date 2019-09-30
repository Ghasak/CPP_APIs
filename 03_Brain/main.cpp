//
//  main.cpp
//  TestingGh
//
//  Created by Ghasak Mothafer on 2019/09/24.
//  Copyright © 2019 Ghasak Mothafer. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>

#include "myFunctions.hpp"
using namespace std;



int main(int argc, const char * argv[]) {
    
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << "This is the first program that I did" << std::endl;
    printf("The value you are looking for is %d \n", Gfunc(4, 5));
    printf("While the average of all values is = %f \n",GAverage(100, 232, 23323));
    
    double a = 0;
    double b = 0;
    double c = 0 * 100;
    
    for (int i = 0; i <100; i++){
        printf("the value of iteration i=%d is equal to = %f \n",i, GAverage(a, b, c));
        
        a= a+1;
        b= b+1;
        c= c+1;
        
    }
    Brain();
    
    for (int i =0; i < 10; i++){
            printf("The value of guessing is = %f and guessing int = %d\n", Guessing(),guessingInt());
    }
    
    
    // How to implement a Class in CPP - Header file has the class and fields and functions goest to cpp file.
    string nameOfCourse;                        // string of characters to store the course name
    nameOfCourse = "Mathematics";
    GradeBook myGradeBook;                    // create a GradeBook object named myGradeBook
    myGradeBook.displyMessage(nameOfCourse); // create a GradeBook object named myGradeBook
    
    
    return 0;
}
