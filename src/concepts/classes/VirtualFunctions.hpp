#include <string>
#include "concepts/classes/classes.hpp"
#pragma once

void virtual_function_concept();
// Parent Class
class EntityVirtualClass {
public:
    std::string GetName();
    ~EntityVirtualClass();
};

// Child Class
class PlayerVirtualClass : public EntityVirtualClass {
private:
    std::string m_Name;

public:
    // constructor
    PlayerVirtualClass(const std::string& name);
    // Method with same name for the parent class
    std::string GetName();
    ~PlayerVirtualClass();
};
