#include "concepts/classes/object_lifetime.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <iostream>
#include <string>

/**********************************************
 * Declares the functions and classes         *
 * related to object lifetime concepts.       *
 **********************************************/
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
    std::cout << RED << "Size of the heap pointer eobj_heap_ptr -> " << sizeof(EEntity) << RESET
              << std::endl;

    delete eobj_heap_ptr;     // Properly delete heap-allocated object.
    eobj_heap_ptr = nullptr;  // Avoid dangling pointer by setting to nullptr.
}

/**********************************************
 * Definition the functions and classes       *
 * related to object lifetime concepts.       *
 **********************************************/
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

/****************************************************
 * CONCEPT OF FREEING MEMEORY AUTOMATICALLY -       *
 *   Making similar to unique pointers from scratch *
 *   - Basics edition                               *
 ****************************************************/
void similar_to_unique_pointer_from_scratch_concept() {
    // Inner scope to determine whether the
    // CEntity object is freed when it exists outside of it.

    {
        // Define our object k on heap
        CEntity* k = new CEntity();
        // Manage the object to be freed automatically
        // once it gets out of the inner-scope
        // ScopedPtr1 e(new CEntity());
        ScopedPtr1 e(k);
    }

    {
        // Define another object
        CEntity* c = new CEntity();
        // Manage the object to be freed automatically
        // once it gets out of the inner-scope
        // ScopedPtr2 e2(new CEntity());
        ScopedPtr2 e2(c);
    }
}

/***************************************************
 * Our Class which we want:                        *
 * Allocate dynamically on heap                    *
 * to free upon existing a its scope               *
 ***************************************************/
CEntity::CEntity() { LOG(INFO) << BLUE << "CEntity Object is created ..." << RESET; }
CEntity::~CEntity() { LOG(INFO) << BLUE << "CEntity Object is destroyed ..." << RESET; }

/* Smart pointer similar
 * to unique_pointer class
 */

ScopedPtr1::ScopedPtr1(CEntity* ptr)
    : m_Ptr{ptr} {}

ScopedPtr1::~ScopedPtr1() {
    delete m_Ptr;
    m_Ptr = nullptr;
}

/****************************************************
 * CONCEPT OF FREEING MEMEORY AUTOMATICALLY -       *
 *   Making similar to unique pointers from scratch *
 *   - Enhanced edition                             *
 *   - Definition                                   *
 ****************************************************/

// Constructor takes ownership of the passed pointer
ScopedPtr2::ScopedPtr2(CEntity* ptr)
    : m_Ptr(ptr) {
    LOG(INFO) << BLUE << "CEntity Object is created Using   -> " << YELLOW
              << "ScopedPtr2 Enhanced Edition" << RESET;
}

// Destructor releases the owned resource
ScopedPtr2::~ScopedPtr2() {
    delete m_Ptr;
    LOG(INFO) << BLUE << "CEntity Object is destroyed Using -> " << YELLOW
              << "ScopedPtr2 Enhanced Edition" << RESET;
}

// Optionally implement move semantics to allow transfer of ownership
ScopedPtr2::ScopedPtr2(ScopedPtr2&& other) noexcept
    : m_Ptr(other.m_Ptr) {
    other.m_Ptr = nullptr;
}

// Move assignment operator
ScopedPtr2& ScopedPtr2::operator=(ScopedPtr2&& other) noexcept {
    if (this != &other) {
        delete m_Ptr;           // Safely delete the current resource
        m_Ptr = other.m_Ptr;    // Transfer ownership
        other.m_Ptr = nullptr;  // Nullify the source pointer
    }
    return *this;
}
