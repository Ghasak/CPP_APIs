#include "Employee.hpp"

Employee::Employee() : name(""), id(0), salary(0.0) {}
Employee::Employee(const std::string &n, int i, double s)
    : name(n), id(i), salary(s) {}
std::string Employee::getName() const { return name; }
int Employee::getId() const { return id; }
double Employee::getSalary() const { return salary; }
void Employee::setName(const std::string &n) { name = n; }
void Employee::setId(int i) { id = i; }
void Employee::setSalary(double s) { salary = s; }

void Employee::display() const {
  std::cout << "Name: "
            << "\t" << name << "\t"
            << " ID: "
            << "\t" << id << "\t"
            << " Salary: $" << salary << "\n";
}

/* Create an obj destructor */
Employee::~Employee() {
  std::cout << std::string("The Employee[") << name
            << std::string("]Got destroyed") << std::endl;
}
