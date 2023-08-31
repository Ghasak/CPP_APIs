#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "./lib/Employee.hpp"

// *************************************************
//             Declare the function
// *************************************************
int my_function(int, int); // this is also called the function signature.
int my_function_pointer(int *, int *);
int my_function_reference(int &, int &);
std::string my_function(std::string, std::string);

int main(int argc, char *argv[]) {
  std::cout << "Hello World! Wow" << std::endl;
  std::vector<std::string> names = {"Jack", "Michael", "Luke"};
  // Randomly selecting a value from the vector
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator

  // Generate random ID between 1000 and 9999
  std::uniform_int_distribution<> idDistrib(1000, 9999);

  // Generate random salary between 50000.00 and 150000.00
  // Here, we'll first generate between 5000000 and 15000000 (multiplied by 100)
  // and then divide by 100 to get two decimal places
  std::uniform_int_distribution<> salaryDistrib(5000000, 15000000);

  /* int a = 10; */
  /* int b = 20; */
  for (int i = 0; i < 1000000; i++) {
    // calling the function passing by value
    // std::cout << "value of i -> [" << my_function(a , i) << "]" << std::endl;
    // calling the function passing by pointer
    // std::cout << "value of i -> [" << my_function_pointer(&a , &i) << "]" <<
    // calling the funcntion passing by reference
    // std::cout << "value of i -> [" << my_function_reference(a, i) << "]" <<
    // std::endl;
    std::uniform_int_distribution<> distrib(0, names.size() - 1); // Define the distribution

    int randomIndex = distrib(gen); // Generate random index
    std::string randomName = names[randomIndex]; // Get the randomly selected name
    int randomId = idDistrib(gen);
    double randomSalary = salaryDistrib(gen) / 100.0;
    Employee emp1(randomName, randomId, randomSalary);
    emp1.display();
    //std::string output = my_function(emp1.getName(), "Wow");
    //std::cout << output << "\n";
  }
  int my_function_definition(int32_t & param_a, int32_t & param_b);

  return 0;
}

// *************************************************
//          Definition of the function
// *************************************************
// here we define the body of the funciton
int my_function(int param_a, int param_b) { return param_a + param_b; }

// Passing by pointer
/**
 *  Passing by Pointers
 * Here we are passing pointers to the fucntion instead of
 * @param values Container whose values are summed.
 * @return sum of `values`, or 0.0 if `values` is empty.
 */
int my_function_pointer(int *param_a, int *param_b) {
  return 100 * (*(param_a) + *(param_b));
}

// passing by reference
int my_function_reference(int &param_a, int &param_b) {
  return 1000 * (param_a + param_b);
}

std::string my_function(std::string input_value, std::string value_extension) {
  std::string extension = " ==> ";
  return input_value + extension + value_extension;
}
