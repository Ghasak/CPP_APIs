#ifndef CLASSES_HPP
#define CLASSES_HPP
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

// -------------------------------------
//         Classes Inheritance
// -------------------------------------

// Base class for Player
class PlayerParent {
public:
    float X, Y;  // Coordinates of the player

    // Default constructor
    PlayerParent();

    // Parameterized constructor to set initial position
    PlayerParent(float x, float y);

    // Moves the player to a new position
    void Move(float deltaX, float deltaY);
};

// Derived class from PlayerParent
class PlayerChild : public PlayerParent {
public:
    const char* Name;  // Name of the player
    PlayerChild(const char*);

    // Prints the player's name to the console
    void PrintName();
};

// This is a class implementation caller for the class methods and fields above
void class_implementation();

#endif
