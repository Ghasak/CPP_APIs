//
//  myFunctions.hpp
//  TestingGh
//
//  Created by Ghasak Mothafer on 2019/09/24.
//  Copyright © 2019 Ghasak Mothafer. All rights reserved.
//

#ifndef myFunctions_hpp
#define myFunctions_hpp
#include <string>
#include <iostream>
#include <stdio.h>

int Gfunc(int a, int b);
double GAverage(double a , double b, double c);
void Brain();
double Guessing();
int guessingInt();
// GradeBook class definition

class GradeBook
{
public:
    // function that disply welcome to the GradeBook user
    void displyMessage(std::string courseName);
};

#endif /* myFunctions_hpp */
