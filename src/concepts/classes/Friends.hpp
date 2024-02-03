#pragma once
#include <string>
/**********************************************
 * Main Function for showing the friend concept
 **********************************************/
int friends_in_action();

// ##############################################################
//  1. Calling outside function as a friend into a class as
// ##############################################################

/**********************************************
 *               BOX CLASS
 **********************************************/
/**
 * @file Friends.hpp
 * Demonstrates the use of friend functions in C++. A friend function is
 * declared within the class `Box` to illustrate how it can access private
 * members of the class. Note that there's no need to declare the `printWidth`
 * function in the header file outside of the class declaration, as its friend
 * declaration inside the class is sufficient for enabling external access to
 * private class members.
 */

class Box {
    double width;  // Private member variable holding the width of the box.

public:
    /**
     * Constructor for the Box class.
     * @param w The width of the box.
     */
    Box(double w);

    /**
     * Friend function declaration.
     * Allows `printWidth` function to access the private members of Box.
     * @param b Box object whose width is to be printed.
     */
    friend void printWidth(Box b);
};

// void printWidth(Box b); // <- Not needed

// ##############################################################
//  2. Friend Class Example
// ##############################################################
/**
 * @file main.cpp
 * Demonstrates the use of friend classes in C++ through a simple example
 * involving two classes, BoxB and Printer. The BoxB class defines a single
 * private member variable and grants access to the Printer class, allowing it
 * to directly access Box's private members. This example illustrates how friend
 * classes can be used to enable tight coupling between classes when necessary.
 */

/**
 * A simple class representing a boxb with a width.
 * It declares the Printer class as a friend, allowing Printer to access its private members.
 */
class BoxB {
    double width;  // Private member variable holding the width of the box.

public:
    /**
     * Constructor that initializes a Box object with a given width.
     * @param w The width of the box.
     */
    BoxB(double);
    // Friend class declaration.
    friend class Printer;
};

/**
 * A class capable of printing properties of a BoxB object.
 * As a friend of BoxB, it has access to BoxB's private members.
 */
class Printer {
public:
    void printWidth(BoxB&);
};

// ##############################################################
//  3. Friend Methods of Another Class Example
// ##############################################################
/**
 * @file YourHeader.hpp
 * Demonstrates the use of forward declaration and friend functions within class definitions in C++.
 * This header file contains two class declarations, MyClass and YourClass, where MyClass has a
 * method that is made a friend of YourClass, allowing it direct access to YourClass's private
 * members.
 */

/**
 * Forward declaration of YourClass.
 * Allows MyClass to reference YourClass before its definition.
 */
class YourClass;
/**
 * MyClass is designed to interact with instances of YourClass.
 */
class MyClass {
public:
    /**
     * showYourClass is a method that can access the private members of YourClass.
     * This method is declared as a friend within YourClass, enabling such access.
     * @param y A reference to an instance of YourClass, whose private data will be accessed.
     */
    void showYourClass(YourClass& y);
};

/**
 * YourClass holds private data but allows MyClass's showYourClass method
 * direct access to its internals through the friend declaration.
 */
class YourClass {
    int secret = 112000023;

public:
    /**
     * Friend declaration for MyClass::showYourClass, granting it access to private members of
     * YourClass.
     */
    friend void MyClass::showYourClass(YourClass&);
};

// ##############################################################
//  4. Using ostream friend method operator <<
// ##############################################################

// The previous example of using `operator<<` for the `Person` class involves a **friend function**.
// It's not a method of a class or a friend class. In C++, a friend function is a function that is
// not a member of a class but has access to its private and protected members. This access is
// granted by the class itself via the `friend` keyword.

// ### Friend Function Explanation

// In the context of overloading the `operator<<`, the function is defined outside of any class but
// is declared as a friend inside the class it needs to access. This setup allows the function to
// stream private data from the class directly to an output stream (like `std::cout`), which
// wouldn't be possible if it were a regular function without access to the class's private or
// protected members.

// ### Signature of `operator<<`

// The signature of the `operator<<` in the previous example is as follows:

//```cpp
// std::ostream& operator<<(std::ostream& stream, const Person& p);
//```
//
//- **Arguments/Parameters:**
//  - `std::ostream& stream`: The first parameter is a reference to an instance of `std::ostream`.
//  This is the stream to which the data will be output. It's passed by reference to avoid copying
//  the stream object, which is not only inefficient but also semantically incorrect since stream
//  objects represent unique resources like files or console output.
//  - `const Person& p`: The second parameter is a constant reference to the `Person` object that we
//  want to output to the stream. It's constant because we don't want to modify the `Person` object
//  during the operation, and it's a reference to avoid unnecessary copying.
//
//- **Return Type:**
//  - `std::ostream&`: The function returns a reference to the same `std::ostream` instance passed
//  to it. This design allows chaining of `<<` operator calls. For example, you can do something
//  like `std::cout << person1 << person2;`, where each `operator<<` call returns the stream itself,
//  allowing the next item to be output seamlessly.
//
// ### Summary
//
// The `operator<<` in this context is a **friend function** of the `Person` class, which allows it
// to access the class's private data for output purposes. The function takes a reference to an
// `std::ostream` object and a constant reference to a `Person` object as parameters, and returns a
// reference to an `std::ostream` object to enable the chaining of output operations.
/**
 * @file Person.hpp
 * Demonstrates the use of an ostream friend method to enable the << operator to work
 * with custom types, specifically the Person class in this example.
 * This allows instances of Person to be directly streamed to output streams (like std::cout)
 * in a human-readable format.
 */
class Person {
    std::string name;  // Name of the person
    int age;           // Age of the person
public:
    /**
     * Constructs a new Person object with a name and age.
     * @param n Name of the person.
     * @param a Age of the person.
     */
    Person(std::string n, int a);
    /**
     * Friend function to overload the << operator for the Person class.
     * Allows Person instances to be output directly to ostream objects.
     * @param stream The output stream object (e.g., std::cout).
     * @param p The Person instance to output.
     * @return Reference to the modified ostream object, enabling chaining of << operator calls.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Person& p);
};

// ##############################################################
//  5. Example Using ostream&  operator << function
// ##############################################################
/**
 * @file Friends.hpp
 * @brief Declaration of the Vector2d class and auxiliary functions.
 *
 * Defines the Vector2d class, which represents a 2D vector with float coordinates X and Y.
 * Includes declarations for a custom output stream operator and a function to generate random float
 * values.
 */

class Vector2d {
public:
    float X, Y;  ///< Public float members representing the coordinates of the vector.
    static int
        object_count;  ///< Static member to track the total number of Vector2d objects created.
    int object_id;     ///< Unique identifier for each Vector2d object instance.

public:
    /**
     * @brief Construct a new Vector2d object.
     *
     * Initializes a Vector2d object with coordinates (xi, yi) and assigns a unique object ID.
     * @param xi Initial X coordinate.
     * @param yi Initial Y coordinate.
     */
    Vector2d(float xi = 0, float yi = 0);
    /**
     * @brief Overloads the << operator for Vector2d objects.
     *
     * Enables direct output of Vector2d objects' details to standard output streams.
     * @param stream Reference to the output stream (e.g., std::cout).
     * @param other The Vector2d object to output.
     * @return std::ostream& Reference to the output stream for chaining.
     */
    friend std::ostream& operator<<(std::ostream&, const Vector2d& other);
};

/**
 * @brief Generates a random float value.
 *
 * Generates a random float value within a specified range, using a simple scaling.
 * @return float A random float value.
 */
float generate_random_value();
