#include <string>
#pragma once

void StdMoveAndMoveAssignmentOperatorConcept();

// String.h
#pragma once

namespace MoveAssignemntConcept {

// A custom string class that demonstrates move semantics and resource management.
class String {
public:
    // Default constructor.
    // Constructs an empty String object. Marked noexcept as it guarantees not to throw any
    // exceptions.
    String() noexcept;

    // Parameterized constructor.
    // Constructs a String object with a copy of the provided C-style string.
    // @param string A null-terminated C-style string to initialize the String object.
    String(const char* string);

    // Copy constructor.
    // Constructs a String object as a deep copy of another String object.
    // @param other The String object to be copied.
    String(const String& other);

    // Move constructor.
    // Constructs a String object by taking over the resources of another String object.
    // @param other The String object whose resources are to be moved.
    // Marked noexcept as it guarantees not to throw any exceptions.
    String(String&& other) noexcept;

    // Move assignment operator.
    // Allows the current object to take over the resources of another String object.
    // @param other The String object to assign from.
    // Checks for self-assignment and releases any existing resources before moving.
    // @return A reference to the current object, enabling assignment chaining.
    String& operator=(String&& other) noexcept;

    // Destructor.
    // Cleans up by releasing any dynamically allocated memory.
    ~String();

    // Prints the string to the standard output.
    // Iterates through each character of the string and outputs it.
    void Print();

private:
    char* m_Data =
        nullptr;  // Pointer to the dynamically allocated memory for storing the string characters.
    uint32_t m_Size =
        0;  // The size of the string (number of characters), not including the null terminator.
};

}  // namespace MoveAssignemntConcept
