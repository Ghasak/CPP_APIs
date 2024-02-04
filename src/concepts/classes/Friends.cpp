/**
 * @file Friends.cpp Implementation of the Box class and demonstration of friend
 * function usage. Contains the definition of the `printWidth` friend function
 * and an action function to create a Box object and print its width.
 *
 * The `printWidth` function is a friend of the Box class, allowing it to access
 * private members. This file demonstrates creating a Box object, initializing
 * it, and using a friend function to access its private data.
 */

#include "concepts/classes/Friends.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>

// Tracking number of objects of Vector2d
int Vector2d::object_count = 0;

/**
 * Demonstrates the use of the Box class and its friend function.
 * Creates a Box object and prints its width using the `printWidth` friend function.
 */

int friends_in_action() {
    // 1. calling outside function as a friend into a class
    Box boxa(100.123);  // Creating a Box object.
    printWidth(boxa);   // Calling the friend function to print the width of the box.

    // 2. Friend Class Example
    /**
     * demonstrating the use of BoxB and Printer classes. Creates a Box object
     * and a Printer object, then uses the Printer to print the width of the
     * Box. @return Exit status of the program.
     */
    BoxB boxb(20.11);
    Printer printer;
    printer.printWidth(boxb);

    // 3. Friend Methods of Another Class Example
    YourClass yc;
    MyClass mc;
    mc.showYourClass(yc);

    // 4. Using ostream friend method operator <<
    Person person("John Doe", 30);
    std::cout << person << std::endl;

    // 5. Example Using ostream&  operator << function

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    Vector2d my_vector;  // don't use Vector2d my-vector()

    // Prompts the user for the number of Vector2d objects to create.
    /* int number_of_vectors; */
    /* std::cout << "Input number of vectors: ";  // Prompt the user for input */
    /* std::cin >> number_of_vectors;             // Read the input value */
    /* if (!std::cin) {                           // Check if the input operation failed */
    /*     std::cerr */
    /*         << "Error: Invalid input for the number of vectors, must be an integer decimal value." */
    /*         << std::endl; */
    /*     return 1; */
    /* } */

    int number_of_vectors = 10;
    // In the first loop, updates a single Vector2d object with new random coordinates on each

    for (int i = 0; i < number_of_vectors; i++) {
        // Generate random values for Y and Y
        float randomX = generate_random_value();
        float randomY = generate_random_value();

        // Assign to our object
        my_vector.X = randomX;
        my_vector.Y = randomY;

        // Output the object
        std::cout << my_vector << std::endl;
    }

    // coordinates on each iteration and prints it.
    std::cout << "========================" << std::endl;

    // iteration and prints it. In the second loop, creates a new Vector2d object with random
    for (int i = 0; i < number_of_vectors; i++) {
        // Generate random values for Y and Y
        float randomX = generate_random_value();
        float randomY = generate_random_value();
        Vector2d my_vector = Vector2d(randomX, randomY);
        std::cout << my_vector << std::endl;
    }
    return 0;
}

// ##############################################################
//  1. Calling outside function as a friend into a class as
// ##############################################################

/**
 * Constructor for the Box class. Initializes the width of the box.
 * @param w The width of the box.
 */
Box::Box(double w)
    : width(w) {}

/**
 * Friend function to print the width of a Box object.
 * As a friend function, it can access the private members of Box.
 * @param b Box object whose width is to be printed.
 */
void printWidth(Box b) {
    std::cout << "Width of box: " << b.width << std::endl;  // Accessing private member width.
}

// ##############################################################
//  2. Friend Class Example
// ##############################################################

/**
 * Extension of the initial demonstration of friend classes with additional functionality.
 * This example introduces a variation of the Box class, named BoxB, and extends the Printer class
 * to use colored output when printing the width of a BoxB object.
 */

/**
 * Constructor for the BoxB class.
 * Initializes the BoxB object with a specific width.
 * @param w The width of the box.
 */
BoxB::BoxB(double w)
    : width{w} {}

/**
 * Enhanced printWidth method of the Printer class to include colored output.
 * Prints the width of a BoxB object in color, demonstrating the extended capabilities
 * of a friend class when accessing private members of another class.
 * @param b A reference to the BoxB object whose width is to be printed in color.
 */
void Printer::printWidth(BoxB& b) {
    std::cout << BLUE << "Width of box: " << RED << b.width << std::endl;
}

// ##############################################################
//  3. Friend Methods of Another Class Example
// ##############################################################
/**
 * @file Friends.cpp
 * Implements the functionality declared in the corresponding header file.
 * Specifically, it provides the implementation for MyClass's showYourClass method,
 * which accesses private data within an instance of YourClass.
 */

/**
 * Implementation of MyClass::showYourClass, which has been granted friend access to YourClass's
 * private members. This method prints the value of the private member `secret` of a YourClass
 * instance, demonstrating how friend functions can bypass the usual encapsulation mechanisms in
 * C++.
 *
 * The output is color-coded for emphasis, using terminal color codes for RED and BLUE, and RESET to
 * return to default.
 *
 * @param y A reference to the YourClass instance whose secret will be revealed.
 */
void MyClass::showYourClass(YourClass& y) {
    std::cout << RED << "YourClass secret: " << BLUE << y.secret << RESET << std::endl;
}

// ##############################################################
//  4. Using ostream friend method operator <<
// ##############################################################
/**
 * @file Person.cpp
 * Implements the Person class, including its constructor and the friend function
 * to overload the << operator for streaming Person instances to output streams.
 */

/**
 * Constructor for the Person class. Initializes a Person object with a name and age.
 * @param n Name of the person.
 * @param a Age of the person.
 */
Person::Person(std::string n, int a)
    : name{n},
      age{a} {};
/**
 * Overloads the << operator for the Person class, allowing Person instances
 * to be output to ostream objects directly. This function is declared as a friend
 * within the Person class to enable access to its private members.
 *
 * The output includes color-coded information, assuming that RED, BLUE, and RESET
 * are defined macros/constants for terminal color codes.
 *
 * @param stream The output stream to which the Person information will be sent.
 * @param p The Person object to output.
 * @return Reference to the ostream object to enable chaining of << operator calls.
 */

std::ostream& operator<<(std::ostream& stream, const Person& p) {
    stream << "Person(Name: " << RED << p.name << RESET << ", Age: " << BLUE << p.age << RESET
           << ")";
    return stream;
}

// ##############################################################
//  5. Example Using ostream&  operator << function
// ##############################################################
/**
 * @file Friends.cpp
 * @brief Implementation of the Vector2d class and auxiliary functions.
 *
 * Implements the constructor for Vector2d, a custom output stream operator,
 * and a function to generate random float values.
 */

/**
 * @brief Construct a new Vector2d object and assigns a unique ID.
 *
 * @param xi Initial X coordinate.
 * @param yi Initial Y coordinate.
 */
Vector2d::Vector2d(float xi, float yi)
    : X{xi},
      Y{yi} {
    object_id = ++object_count;
}

/**
 * @brief Custom output stream operator for Vector2d objects.
 *
 * Formats and outputs the details of a Vector2d object, including its unique ID and coordinates, to
 * an output stream.
 * @param stream Reference to the output stream.
 * @param other The Vector2d object to be output.
 * @return std::ostream& Reference to the output stream for chaining.
 */
std::ostream& operator<<(std::ostream& stream, const Vector2d& other) {
    stream << RED << "Vector2d "
           << "[" << BLUE << other.object_id << RESET << "]"
           << " at:: " << BLUE << " < " << YELLOW << other.X << RED << " , " << YELLOW << other.Y
           << BLUE << " > " << RESET;
    return stream;
}

/**
 * @brief Generates a random float value scaled up to 100.
 *
 * Utilizes the rand() function to generate a random float value, scaled to be between 0 and 100.
 * @return float A random float value.
 */
float generate_random_value() {
    float random_variable = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 100);
    random_variable *= 100;
    return random_variable;
}
