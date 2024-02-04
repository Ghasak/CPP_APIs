#pragma once
#include <string>

// Declares the functions and classes related to object lifetime concepts.
void object_life_time_concpet();

// Represents an entity with an integer and a name.
class EEntity {
public:
    int x; // The integer value of the entity.
    std::string eobjName; // The name of the entity.

    // Constructs an EEntity with a specified integer and name.
    EEntity(int x, std::string name);

    // Default constructor.
    EEntity();

    // Destructor.
    ~EEntity();
};

