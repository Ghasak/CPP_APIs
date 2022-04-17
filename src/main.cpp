#include <iostream>
#include <string>
#include <vector>
#include "./colorize/color.hpp"
#include "./eigen/Eigen/Dense"
using namespace std;
using namespace Eigen;


//cd "/Users/gmbp/Desktop/devCode/cppDev/src/" && g++ main.cpp -o main && "/Users/gmbp/Desktop/devCode/cppDev/src/"main
//g++ -o example example.cpp -std=c++17
// define our first class in cpp
//https://github.com/fengwang/colorize

class GradeBook {
    public:

        // display a welcome message
        void displayMessage( string courseName ) {
            cout << "\n\n\nWelcome to the grade book for .\ue799. \n" << courseName << "!" << endl;
            //cout << "\033[0;33;42mI am a Banana!\033[0m";
            string message = "I am a Banana!";
            cout << color::rize( message, "Green", "" ) << endl;

        }
        // Another random function
        void randomMessage() {
            for (int i = 0; i <= 10; i++) {
                string message = " Welcome to the grade book for ... ";
                cout << color::rize("[\ue799 ] ", "Red", "") << color::rize(message, "Magenta", "")<<endl;

            }
        }

};


int main() {

    // create a GradeBook object and assign it to myGradeBook
    string nameOfCourse;
    GradeBook myGradeBook;

    // call the displayMessage method
    cout << "Input the name of the course you want to construct ... " << endl;
    getline(cin, nameOfCourse);
    myGradeBook.displayMessage(nameOfCourse);
    myGradeBook.randomMessage();
    cout << "I use g++ main.cpp -o main -std=c++17 to compile this program ... " << endl;
    cout << "End of program.\n";


    // Using Egin library for matrix operations
    // I can also use  Eigen::MatrixXd
      MatrixXd m(2,2);
          m(0,0) = 3;
          m(1,0) = 2.5;
          m(0,1) = -1;
          m(1,1) = m(1,0) + m(0,1);
      std::cout << m << std::endl;

    return 0;
}











