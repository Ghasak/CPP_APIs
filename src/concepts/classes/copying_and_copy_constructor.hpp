#pragma once
#include <string>

/*
 * Concept:Copying and copy constructor concept in C++
 * Showing the supported copying and copy constructor
 * and why we need them in
 * C++. Mainly the optimization and having
 * a full-control over all the objects in
 *
 */

void copying_and_copy_constructor_concept();
/*
 * Class String bare minimum to our std::string class template
 * It allow to
 */
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

/*
 * Function accepting our String class-obj
 * Passing the obj by value which will create a copy
 */
void PrintString_ByValue_will_Copy(const String);

/*
 * Function accepting our String class-obj
 * Passing the obj by reference which will not copy the obj,
 * rather changing the original variable
 * outside of the function that we passed to it.
 */
void PrintString_ByRef_will_Not_Copy(const String&);

/*
 * Copy constructor for C++ testing
 */

class StringG {
public:
    StringG() = default;
    StringG(const char* message);
    StringG(const StringG& other);
    ~StringG();
    void Print();

private:
    char* m_buffer_ptr = nullptr;
    int m_size = 0;
};

void copy_construcotr_demo();
