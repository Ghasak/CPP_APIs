#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/classes/std_move_and_move_assignment_operator.hpp"
#include <iostream>
#include <string>
#include <cstring>

void StdMoveAndMoveAssignmentOperatorConcept() {
    std::cout << RED << "(((((((((( " << BLUE << "WELCOME TO STD MOVE AND MOVE ASSIGNMENT OPERATOR"
              << RED << " ))))))))))" << RESET << std::endl;

    MoveAssignemntConcept::String string = "Hello";
    MoveAssignemntConcept::String destx = std::move(string);
    string = std::move(destx);

    MoveAssignemntConcept::String apple = "Apple";
    MoveAssignemntConcept::String dest;

    std::cout << "Apple: ";
    apple.Print();
    std::cout << "Dest: ";
    dest.Print();

    dest = std::move(apple);  // we are calling the move equal operator

    std::cout << "Apple: ";
    apple.Print();
    std::cout << "Dest: ";
    dest.Print();
}

namespace MoveAssignemntConcept {

// Default constructor.
// Initializes an empty `String` object. This constructor is noexcept as it does not throw any
// exceptions.
String::String() noexcept = default;

// Parameterized constructor.
// Creates a `String` object with a copy of the provided C-style string.
// @param string A null-terminated C-style string used to initialize the `String` object.
// Utilizes std::strlen to calculate the length of `string` and allocates memory accordingly.
// It also ensures the string is null-terminated by copying an extra character for the null
// terminator.
String::String(const char* string)
    : m_Data(new char[std::strlen(string) + 1]),
      m_Size(std::strlen(string)) {
    std::memcpy(m_Data, string, m_Size + 1);
}

// Copy constructor.
// Creates a `String` object as a copy of another `String` object.
// @param other The `String` object to be copied.
// This constructor performs deep copy by allocating its own memory and copying the data from
// `other`.
String::String(const String& other)
    : m_Data(new char[other.m_Size]),
      m_Size(other.m_Size) {
    std::memcpy(m_Data, other.m_Data, m_Size);
}

// Move constructor.
// Transfers the ownership of the resources from another `String` object to this object.
// @param other The `String` object whose resources are to be taken over.
// After transferring the resources, `other` is left in an empty state to ensure it's safely
// destructible.
String::String(String&& other) noexcept
    : m_Data(other.m_Data),
      m_Size(other.m_Size) {
    other.m_Size = 0;
    other.m_Data = nullptr;
}

// Move assignment operator.
// Allows the current object to take over the resources of another `String` object.
// @param other The `String` object to assign from.
// This operator checks for self-assignment, releases any existing resources,
// then adopts `other`'s resources. `other` is left in an empty, valid state.
// @return A reference to *this, enabling chaining of assignments.
String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    std::cout << "Move Assignment operator is called " << std::endl;
    return *this;
}

// Destructor.
// Releases the dynamically allocated memory to prevent memory leaks.
String::~String() { delete[] m_Data; }

// Print function.
// Outputs the string to the standard output.
// Iterates through the characters of the string and prints each character.
void String::Print() {
    for (size_t i = 0; i < m_Size; i++) {
        std::cout << m_Data[i];
    }
    std::cout << std::endl;
}

}  // namespace MoveAssignemntConcept
