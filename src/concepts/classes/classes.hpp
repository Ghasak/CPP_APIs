#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
#include <string>

void classes_conccepts_hub();

class Employee {
public:
    explicit Employee(std::string first_name,
                      std::string middle_name,
                      std::string last_name,
                      int age,
                      double salary);

    explicit Employee(std::string first_name, std::string middle_name, std::string last_name);

    // copy constructor
    // When you pass an object to the construction it will be consumed and construct its fields from
    // the passing object.
    Employee(const Employee& other);
    // destructor
    ~Employee();
    // Assignment operator: When you assign like Employee emp2 = emp1;
    Employee& operator=(const Employee& other);
    // constat memeber function
    // std::string getName() const;
    // Virtual function
    // virtual void displayInfo() const;

    // Friend function
    // friend void resetSalary(Employee& emp);
    // displayInfo
    void update_salary();
    std::string displayInfo();

private:
    int emp_id;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    int age;
    double salary;
    static int emp_count;
};
// This is a class implementation caller for the class methods and fields above
void class_implementation();
#endif  // EMPLOYEE_HPP
