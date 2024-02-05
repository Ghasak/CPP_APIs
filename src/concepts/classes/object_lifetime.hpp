#pragma once
#include <string>

/**********************************************
 * Declares the functions and classes         *
 * related to object lifetime concepts.       *
 **********************************************/
void object_life_time_concpet();
// Represents an entity with an integer and a name.
class EEntity {
public:
    int x;                 // The integer value of the entity.
    std::string eobjName;  // The name of the entity.

    // Constructs an EEntity with a specified integer and name.
    EEntity(int x, std::string name);

    // Default constructor.
    EEntity();

    // Destructor
    ~EEntity();
};
/****************************************************
 * CONCEPT OF FREEING MEMEORY AUTOMATICALLY -       *
 *   Making similar to unique pointers from scratch *
 *   - Basics edition                               *
 ****************************************************/
void similar_to_unique_pointer_from_scratch_concept();

// Our Class which we want:
// Allocate Dynamically on heap
// to free upon existing a its scope
class CEntity {
public:
    CEntity();
    ~CEntity();
};

// Smart pointer similar
// to unique_pointer class
class ScopedPtr1 {
private:
    CEntity* m_Ptr;

public:
    ScopedPtr1(CEntity*);
    ~ScopedPtr1();
};

/****************************************************
 * CONCEPT OF FREEING MEMEORY AUTOMATICALLY -       *
 *   Making similar to unique pointers from scratch *
 *   - Enhanced edition                             *
 *   - Declaration                                  *
 ****************************************************/

class ScopedPtr2 {
public:
    CEntity* m_Ptr;
    // Constructor takes ownership of the passed pointer
    explicit ScopedPtr2(CEntity*);

    // Destructor releases the owned resource
    ~ScopedPtr2();

    // Delete copy semantics to prevent multiple ownership issues
    ScopedPtr2(const ScopedPtr2&) = delete;
    ScopedPtr2& operator=(const ScopedPtr2&) = delete;

    // Optionally implement move semantics to allow transfer of ownership
    ScopedPtr2(ScopedPtr2&& other) noexcept;

    ScopedPtr2& operator=(ScopedPtr2&& other) noexcept;
};
