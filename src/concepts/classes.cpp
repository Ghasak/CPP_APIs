#include "classes.hpp"
#include "mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <string>

int Employee::emp_count = 0;

// Constructors
Employee::Employee(
    std::string first_name, std::string middle_name, std::string last_name, int age, double salary)
    : first_name{first_name},
      middle_name{middle_name},
      last_name{last_name},
      age{age},
      salary{salary} {
    emp_id = ++emp_count;
};
// Another form or constructor - accepting only names
Employee::Employee(std::string first_name, std::string middle_name, std::string last_name)
    : first_name{first_name},
      middle_name{middle_name},
      last_name{last_name},
      age{21},
      salary{0} {
    emp_id = ++emp_count;
};

// Copy constructor
Employee::Employee(const Employee& other)
    : first_name{other.first_name},
      middle_name{other.middle_name},
      last_name{other.last_name},
      age{other.age},
      salary{other.salary} {
    emp_id = ++emp_count;
};

// Destructor
Employee::~Employee() { LOG(INFO) << "REMOVE (freed from memory) object_id: " << RED << emp_id << RESET; };

std::string Employee::displayInfo() {
    std::string temp_value = "name: " + first_name + " " + middle_name + " " + last_name +
                             " with ID:[" + std::to_string(emp_id) + "]" +
                             "salary:" + std::to_string(salary);
    return temp_value;
}

// Assignment operator

// Assignment operator
Employee& Employee::operator=(const Employee& other) {
    if (this != &other) {
        first_name = other.first_name;
        middle_name = other.middle_name;
        last_name = other.last_name;
        age = other.age;
        salary = other.salary;
        emp_id = ++emp_count;
    }
    return *this;  // means dereferencing the object and return the value.
}

void Employee::update_salary() {
    salary = salary + 0.40 * salary;
};
