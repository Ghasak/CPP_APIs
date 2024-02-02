#include <string>
#pragma once

void virtual_function_concept();
// Parent Class
class EntityVirtualClass {
public:
    virtual std::string GetName();
    virtual ~EntityVirtualClass();
};

// Child Class
class PlayerVirtualClass : public EntityVirtualClass {
private:
    std::string m_Name;

public:
    // constructor
    PlayerVirtualClass(const std::string& name);
    // Method with same name for the parent class
    std::string GetName() override;
    ~PlayerVirtualClass();
};
