#include "concepts/mylogging.hpp"
#include "concepts/variables.hpp"
#include "concepts/classes.hpp"
// #include <cstddef> // this for reading environment variables
#include <glog/logging.h>
#include <iostream>
#include <iterator>
#include <math.h>
#include <ostream>

int main(int argc, char* argv[]) {
    // Initialize logging
    init_logging(argv);
    std::cout << "(((((((( STARTING WITH VARIABLES TIPS AND HINTS  ))))))))" << std::endl;
    const char* my_char = "This is just a test";
    std::cout << my_char << std::endl;
    Employee emp1 = Employee("Jack_1", "G.", "Michael", 34, 112331.0);
    Employee emp2 = Employee("Jack_2", "G.", "Michael", 34, 112331.0);
    Employee emp3 = Employee("Jack_3", "G.", "Michael", 34, 112331.0);
    Employee emp4 = emp3;
    emp4.update_salary();
    LOG(INFO) << RED << emp1.displayInfo() << RESET;
    LOG(INFO) << BLUE << emp2.displayInfo() << RESET;
    LOG(INFO) << RED << emp3.displayInfo() << RESET;
    LOG(INFO) << BLUE << emp4.displayInfo() << RESET;

    for (int i = 0; i < 10000; i++) {
        Employee empx = Employee("Jack_1", "G.", "Michael", 34, 112331.0);
        empx.displayInfo();
    }
    std::cout << "######################################\n";
}
