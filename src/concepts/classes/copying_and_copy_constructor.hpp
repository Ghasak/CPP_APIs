#include <string>

#pragma once

/*
 * Concept:Copying and copy constructor concept in C++
 * Showing the supported copying and copy constructor
 * and why we need them in
 * C++. Mainly the optimization and having
 * a full-control over all the objects in
 *
 */

void copying_and_copy_constructor_concept();

class String {
private:
    char* m_Buffer;
    unsigned int m_Size;

public:
    // Adding our constructor
    String(const char* string);
    String(const String& other);

    // Accessing characters in string using []
    char& operator[](unsigned int index);
    friend std::ostream& operator<<(std::ostream& stream, const String& other);
    ~String();
};

// Testing fucntion to pass as a reference
void PrintString_ByValue_will_Copy(const String);
void PrintString_ByRef_will_Not_Copy(const String&);
