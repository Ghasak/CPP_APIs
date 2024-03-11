#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/classes/move_semantics.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

/**
 * Demonstrates the concept of move semantics in C++.
 *
 * Move semantics is a feature introduced in C++11 that allows resources
 * (such as memory, file handles, etc.) to be moved rather than copied
 * when an object is transferred from a temporary object to a permanent one.
 * This function showcases an example of move semantics in action, aiming to
 * provide a clear and practical understanding of how move semantics can be
 * utilized to optimize resource management and performance in C++ applications.
 *
 * This function outputs a basic message to standard output as a placeholder
 * for where the demonstration of move semantics would take place. It's
 * intended as a starting point for developers to explore the implementation
 * and benefits of move semantics in their C++ projects.
 *
 * Parameters: None.
 * Returns: Void.
 */
void MoveSemanticsConcept() {
    std::cout << "This is a moving semantic session for the latest and greatest development ..."
              << std::endl;

    EntityG e = EntityG("GAME ENGINE");
    e.Print();
}

//--------------------------------------------------------

StringG::StringG() noexcept
    : m_Data(nullptr),
      m_Size(0) {
    // Intentionally left blank.
}

StringG::StringG(const char* string) {
    printf("Object is Created!\n");
    m_Size = std::strlen(string);
    m_Data = new char[m_Size + 1];
    std::memcpy(m_Data, string, m_Size + 1);
}

StringG::StringG(const StringG& other) {
    printf("Object is Copied!\n");
    m_Size = other.m_Size;
    m_Data = new char[m_Size + 1];
    std::memcpy(m_Data, other.m_Data, m_Size + 1);
}

StringG::StringG(StringG&& other) noexcept
    : m_Data(other.m_Data),
      m_Size(other.m_Size) {
    printf("Object is Moved!\n");
    other.m_Data = nullptr;
    other.m_Size = 0;
}

StringG::~StringG() {
    printf("Destroying object with size %u\n", m_Size);
    delete[] m_Data;
}

void StringG::Print() {
    for (uint32_t i = 0; i < m_Size; i++) {
        printf("%c", m_Data[i]);
    }
    printf("\n");
}

EntityG::EntityG(const StringG& name)
    : m_Name{name} {
    // Copy initializes the m_Name member with the provided name.
}

EntityG::EntityG(StringG&& name)
    : m_Name{std::move(name)} {  // <- same -> (StringG&& name)
    // Move initializes the m_Name member with the provided name.
}

void EntityG::Print() { m_Name.Print(); }
