//
//  myFunctions.cpp
//  TestingGh
//
//  Created by Ghasak Mothafer on 2019/09/24.
//  Copyright © 2019 Ghasak Mothafer. All rights reserved.
//


#include "myFunctions.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>          // for rand()
#include <ctime>            // for srand(time)



// to return only the sum of two integers.
int Gfunc(int a, int b){
    return a+b;
}

// to return the average of three integers
double GAverage(double a , double b, double c){
    return (a+b+c)/3;
}


//declare your guessing int function here for using in the Brain
//int guessingInt();

void Brain() {
    bool logic = true;
    std::string message;
    printf("What is name ? ");
    getline(std::cin, message);
    std::cout << "Hello "<< message << " How have you been? " << std::endl;
    getline(std::cin, message);
    printf("Oh.. I see!!");
    printf("\nWhat is your work? ");
    getline(std::cin, message);
    std::cout << "Your work as "<< message << " sound interesting!!\n" << std::endl;

    while(logic){
        
            printf("Do you wish to continue (y/n)?... ");
            getline(std::cin,message);
            if (message == "n"){
                break;
            }else{
            std::cout << "Ask your question? ";
            getline(std::cin, message);
            
            int number =  guessingInt();
            
            switch (number) {
                    
                case (1):
                    printf("Ok! \n");
                    break;
                case (2):
                    printf("Very OK! \n");
                    break;
                case (3):
                    printf("This is Excellent!! \n");
                    break;
                case (4):
                    printf("This is Very Good!!\n");
                    break;
                case (5):
                    printf("This is Top level Good!!! \n");
                    break;
                case (6):
                    printf("Not Ok! \n");
                    break;
                case (7):
                    printf("Not good at all \n");
                    break;
                case (8):
                    printf("Maybe you should not consider!! \n");
                    break;
                case (9):
                    printf("Ok this is very very bad!! \n");
                    break;
                default:
                    break;
            
            }
        }
    }
}

double Guessing(){
    //std::srand((unsigned)time(0));
    double random_number = std::rand();
    random_number = (static_cast<int>(random_number) % 100 + 1)/100.0 ; //very important to create 100.0 rather than int 100
    //std::cout << random_number << std::endl;
    return random_number;
}

int guessingInt(){
    /**
        This is a function to guess a number between two int values max and min
              -->  int randNum = rand()%(max-min + 1) + min;
     */
    int randNum = std::rand()%(9-1 + 1) + 1;
    return randNum;
}

// implementation goes in the CPP file:
void GradeBook::displyMessage(std::string courseName){
    std::cout << "Welcome to the grade book for \n" << courseName << "!" << std::endl;
}
