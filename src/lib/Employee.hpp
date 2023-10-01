#pragma once
#include <iostream>
#include <string>

class Employee {
private:
  std::string name;
  int id;
  double salary;

public:
  Employee();
  explicit Employee(const std::string &n, int i, double s);
  std::string getName() const;
  int getId() const;
  double getSalary() const;
  void setName(const std::string &n);
  void setId(int i);
  void setSalary(double s);
  void display() const;
  ~Employee();
};
