#include "classes.hpp"
#include <iostream>
#include <string>

// Constructors
Employee::Employee(
    std::string first_name, std::string middle_name, std::string last_name, int age, double salary)
    : first_name{first_name},
      middle_name{middle_name},
      last_name{last_name},
      age{21},
      salary{0} {

      };
// Another form or constructor - accepting only names
Employee::Employee(std::string first_name, std::string middle_name, std::string last_name)
    : first_name{first_name},
      middle_name{middle_name},
      last_name{last_name},
      age{21},
      salary{0} {
      };

// Copy constructor
Employee::Employee(const Employee& other)
    : first_name{other.first_name},
      middle_name{other.middle_name},
      last_name{other.last_name},
      age{21},
      salary{0} {};

// Destructor
Employee::~Employee(){};

std::string Employee::displayInfo() {
    std::string temp_value = "first_name: " + first_name;
    return temp_value;
    }

// void Employee::updateSalary(){};
