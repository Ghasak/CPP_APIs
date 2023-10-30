#include "./lib/Employee.hpp"
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// *************************************************
//             Declare the function
// *************************************************
int my_function(int, int); // this is also called the function signature.
int my_function_pointer(int *, int *);
int my_function_reference(int &, int &);
std::string my_function(std::string, std::string);
void my_string(std::string &);
void function_does_nothing(size_t n);
void add_fn(float &, float &);
char *testing_string();

// class Entity {
// public:
//   std::string object_name;
//   Entity(std::string object_name) : object_name(object_name) {

//     std::cout << "Created Entity:" << object_name << std::endl;
//   }
//   ~Entity() { std::cout << "Destroyed Entity:" << object_name << std::endl; }
// };

int main(int argc, char *argv[]) {

  {
    // create employee on stack
    Employee emp1 = Employee(std::string("Jack"), 102, 1121.33);
    // create employee on heap
    // Entity *e2 = new Entity(std::string("e2"));
    Employee *emp2 = new Employee(std::string("Michael"), 1022, 2112.33);
  }

  std::cin.get();

  /* for (int i = 0; i < argc; ++i) { */
  /*   std::cout << "arg: " << argv[i] << std::endl; */
  /* } */
  /* std::cout << "Hello World! Wow" << std::endl; */
  /* std::vector<std::string> names = {"Jack", "Michael", "Luke"}; */
  /* // Randomly selecting a value from the vector */
  /* std::random_device rd;  // Obtain a random number from hardware */
  /* std::mt19937 gen(rd()); // Seed the generator */
  /* std::string input_string = "Hello"; */
  /* my_string(input_string); */
  /*  */
  /* // Generate random ID between 1000 and 9999 */
  /* std::uniform_int_distribution<> idDistrib(1000, 9999); */
  /*  */
  /* // Generate random salary between 50000.00 and 150000.00 */
  /* // Here, we'll first generate between 5000000 and 15000000 (multiplied by
   * 100) */
  /* // and then divide by 100 to get two decimal places */
  /* std::uniform_int_distribution<> salaryDistrib(5000000, 15000000); */
  /* int n = 20; */
  /* function_does_nothing(n); */
  /* /* int a = 10; */
  /* /* int b = 20; */
  /* for (int i = 0; i < 10; i++) { */
  /*   // calling the function passing by value */
  /*   // std::cout << "value of i -> [" << my_function(a , i) << "]" <<
   * std::endl; */
  /*   // calling the function passing by pointer */
  /*   // std::cout << "value of i -> [" << my_function_pointer(&a , &i) << "]"
   * << */
  /*   // calling the funcntion passing by reference */
  /*   // std::cout << "value of i -> [" << my_function_reference(a, i) << "]"
   * << */
  /*   // std::endl; */
  /*   std::uniform_int_distribution<> distrib( */
  /*       0, names.size() - 1); // Define the distribution */
  /*  */
  /*   int randomIndex = distrib(gen); // Generate random index */
  /*   std::string randomName = */
  /*       names[randomIndex]; // Get the randomly selected name */
  /*   int randomId = idDistrib(gen); */
  /*   double randomSalary = salaryDistrib(gen) / 100.0; */
  /*   Employee emp1(randomName, randomId, randomSalary); */
  /*   emp1.display(); */
  /*   // std::string output = my_function(emp1.getName(), "Wow"); */
  /*   // std::cout << output << "\n"; */
  /* } */
  /* // testing a function */
  /* std::cout << "*****************\n"; */
  /* std::uniform_int_distribution<> rand_param(-1000, 1000); */
  /* for (size_t i = 0; i < 10; ++i) { */
  /*   double random_param_val = rand_param(gen); */
  /*   float param_1 = 14.0 - random_param_val; */
  /*   float param_2 = 15.0 + random_param_val; */
  /*   add_fn(param_1, param_2); */
  /* } */
  /* int my_function_definition(int32_t & param_a, int32_t & param_b); */
  /* const char* output_message = testing_string(); */
  /* std::cout << output_message << "\n"; */
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

void my_string(std::string &my_string) {
  if (my_string.empty()) {
    std::cout << "The string is empty ..." << std::endl;
  } else {
    int string_size = my_string.size();
    std::cout << "current input ->: \n"
              << my_string << "\nwith size:" << string_size << std::endl;
  }
}
void function_does_nothing(size_t n) {
  for (size_t i = 0; i < n; i++) {
    std::cout << "[INFO] The current string is given to => " << i << std::endl;
  }
}

void add_fn(float &param_a, float &param_b) {
  if (param_a > param_b) {
    std::cout << "your input param_a: " << param_a << " > " << param_b
              << " param_b " << std::endl;
  } else {
    std::cout << "your input param_a: " << param_a << " < " << param_b
              << " param_b " << std::endl;
  }
}

void my_string_fn(int param_a, int param_b) {
  if (param_a > param_b) {
    std::cout << "param_a: " << param_a << " > "
              << " param_b " << std::endl;
  }
}

char *testing_string() { return (char *)"Hello my Name is Michael"; }
