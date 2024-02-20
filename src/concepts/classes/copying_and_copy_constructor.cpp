#include "concepts/classes/copying_and_copy_constructor.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <string>
#include <iostream>
#include <cstring>

void copying_and_copy_constructor_concept() {
    LOG(INFO) << YELLOW << "Starting with copying and cop constructor concept in C++" << RESET;

    String str1 = "Ghasak";
    String str2 = str1;  // [First-copy]
    str1[0] = 'K';
    // std::cout << str1 << std::endl;
    // std::cout << str2 << std::endl;  // <- Adding this, means deleting the str1dd

    PrintString_ByValue_will_Copy(str1);  // <-- [second-copy] Passing by value(means a new copy occur)
    PrintString_ByValue_will_Copy(str2);  // <-- [third-copy] Passing by value (means a new copy occur)
    std::cout << YELLOW << "(((( YOU WILL SEE ONLY ONE COPY HERE AFTER ))))" << RESET << std::endl;
    PrintString_ByRef_will_Not_Copy(str1);
    PrintString_ByRef_will_Not_Copy(str2);
    std::cout << MAGENTA << "(((( HERE WE CALLING THE COPY CONSTRUCTOR NOT THE DFFAULT CONSTURTOR ))))" << RESET << std::endl;
    copy_construcotr_demo();
}

// Adding our constructor
String::String(const char* string) {
    m_Size = strlen(string);
    m_Buffer = new char[m_Size + 1];   // strcpy() include the null-termination \0
    memcpy(m_Buffer, string, m_Size);  // We can add (+ 1) under
                                       // the assumption string is null-terminated,
    // Safe way to include the null termination, if the string is or not null-terminated.
    m_Buffer[m_Size] = 0;
}
// Copy-constructor shallow (by default)
// String(const String& other)
//     : m_Buffer{other.m_Buffer},
//       m_Size{other.m_Size} {};
// Copy-Constructor Deep (we create it)
String::String(const String& other)
    : m_Size{other.m_Size} {
    LOG(INFO) << RED << "Copy occur to " << YELLOW << other << RESET;
    m_Buffer = new char[m_Size + 1];
    memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
};

// Accessing characters in string using []
char& String::operator[](unsigned int index) { return m_Buffer[index]; }

String::~String() {
    LOG(INFO) << YELLOW << "Our string -> " << RED << this->m_Buffer << BLUE << " ::is deleted from the heap .." << RESET;
    delete[] m_Buffer;
}

std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_Buffer;
    return stream;
}

/*
 * Function accepting our String class-obj
 * Passing the obj by value which will create a copy
 */
void PrintString_ByValue_will_Copy(const String string) { std::cout << string << std::endl; }

/*
 * Function accepting our String class-obj
 * Passing the obj by reference which will not copy the obj,
 * rather changing the original variable
 * outside of the function that we passed to it.
 */
void PrintString_ByRef_will_Not_Copy(const String& string) { std::cout << string << std::endl; }

/* copy constructor class */

StringG::StringG(const char* message) {
    std::cout << "Message Object has been created"
              << "\n";
    m_size = strlen(message);
    m_buffer_ptr = new char[m_size + 1];
    memcpy(m_buffer_ptr, message, m_size + 1);
}
StringG::StringG(const StringG& other) {
    std::cout << "Object is copied "
              << "\n";
    m_size = other.m_size;
    m_buffer_ptr = new char[m_size + 1];
    memcpy(m_buffer_ptr, other.m_buffer_ptr, m_size + 1);
}
StringG::~StringG() {
    std::cout << "Object is destroyed .." << std ::endl;
    delete[] m_buffer_ptr;
}

void StringG::Print() { std::cout << RED << "Object is printed ..." << MAGENTA << this->m_buffer_ptr << "\n" << RESET; }

void copy_construcotr_demo() {
    LOG(INFO) << YELLOW << "We call the default construcotr here..."
              << "\n"
              << RESET;
    // StringG my_string_object("This is just a message");
    // my_string_object.Print();
    // StringG another_string; the default constructor is called not the copy constructor
    // another_string = my_string_object;
    // another_string.Print();

    LOG(INFO) << YELLOW << "We are calling the copy constructor here .. "
              << "\n"
              << RESET;
    StringG my_string_object("This is just a message");
    my_string_object.Print();
    StringG another_string = my_string_object;  // copy constructor is called not the default constructor
    another_string.Print();
}
