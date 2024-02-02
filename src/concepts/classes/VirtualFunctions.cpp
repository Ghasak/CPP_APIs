#include "concepts/classes/VirtualFunctions.hpp"
#include <glog/logging.h>
#include <string>
#include <iostream>

void virtual_function_concept() {
    EntityVirtualClass e1;
    PlayerVirtualClass p1 = PlayerVirtualClass("PlayerVirtualClass");

    // on stack - no pointer
    std::cout << e1.GetName() << std::endl;
    std::cout << p1.GetName() << std::endl;

    // Allocating on heap - with pointer
    EntityVirtualClass* e2 = new EntityVirtualClass();
    PlayerVirtualClass* p2 = new PlayerVirtualClass("PlayerVirtualClass");

    std::cout << e2->GetName() << std::endl;
    std::cout << p2->GetName() << std::endl;

    // Now see that why we need virtual functions
    EntityVirtualClass* p3 = p2;
    std::cout << p3->GetName() << std::endl;  // This suppose to print ``

    delete e2;
    delete p2;
    e2 = nullptr;
    p2 = nullptr;
};
// Parent Class
std::string EntityVirtualClass::GetName() { return std::string("EntityVirtualClass"); }
// destructor for Entity
EntityVirtualClass::~EntityVirtualClass() {
    std::cout << "Entity Object got destroyed" << std::endl;
}

// Child Class
// constructor
PlayerVirtualClass::PlayerVirtualClass(const std::string& name)
    : m_Name{name} {}

// method definition of a sub-class same name to parent class
std::string PlayerVirtualClass::GetName() { return m_Name; }

// Destructor
PlayerVirtualClass::~PlayerVirtualClass() {
    std::cout << "Player Object got destroyed" << std::endl;
}
