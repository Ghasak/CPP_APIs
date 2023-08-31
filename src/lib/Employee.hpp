#pragma once
#include <string>
#include <iostream>

class Employee {
private:
    std::string name;
    int id;
    double salary;
public:
    Employee();
    Employee(const std::string &n, int i, double s);

    std::string getName() const;
    int getId() const;
    double getSalary() const;

    void setName(const std::string &n);
    void setId(int i);
    void setSalary(double s);

    void display() const;
};

