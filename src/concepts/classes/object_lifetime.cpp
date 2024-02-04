#include "concepts/classes/object_lifetime.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <string>

// Demonstrates the concept of object lifetime, including stack and heap allocation.
void object_life_time_concpet() {
    EEntity* eobj_stack_ptr = nullptr;
    EEntity* eobj_heap_ptr = nullptr;

    // Hypothetical Inner Scope
    {
        // Allocate on stack
        EEntity ex = EEntity(1, "eobj_stack_ptr");
        eobj_stack_ptr = &ex;

        std::cout << "Stack Pointer eobj_stack_ptr -> " << BLUE << eobj_stack_ptr << RESET
                  << std::endl;
        ;
        // Allocate on heap
        eobj_heap_ptr = new EEntity(2, "eobj_heap_ptr");

        std::cout << "Arriving to the end of the hypothetical inner-scope." << std::endl;

        eobj_stack_ptr = nullptr;  // to avoid dangling pointer even if its on stack.
    }
    std::cout << "Exited the hypothetical inner-scope." << std::endl;
    std::cout << "Arriving to the end of the outer-scope." << std::endl;

    delete eobj_heap_ptr;     // Properly delete heap-allocated object.
    eobj_heap_ptr = nullptr;  // Avoid dangling pointer by setting to nullptr.
}

// Constructs an EEntity with a specified integer and name. Prints creation message.
EEntity::EEntity(int x, std::string name)
    : x{x},
      eobjName{name} {
    std::cout << RED << "Create an object "
              << "Object Name: " << YELLOW << this->eobjName << "of EEnity Class " << RESET
              << std::endl;
}
// Default constructor. Prints creation message.
EEntity::EEntity()
    : x{0} {
    std::cout << RED << "Create an object "
              << "Object Name: " << YELLOW << this->eobjName << "of EEnity Class " << RESET
              << std::endl;
}

// Destructor. Prints destruction message.
EEntity::~EEntity() {
    std::cout << RED << "Destroying an object "
              << "Object Name: " << YELLOW << this->eobjName << " of EEnity Class " << RESET
              << std::endl;
}
