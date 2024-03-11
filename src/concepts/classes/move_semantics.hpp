#pragma once
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include <cstdint>
#include <string>

void MoveSemanticsConcept();

class StringG {
public:
    /**
     * Default constructor.
     * Constructs an empty StringG object with no data and size zero.
     * This constructor is marked noexcept to indicate it throws no exceptions.
     */
    StringG() noexcept;

    /**
     * Parameterized constructor for creating a StringG object from a C-style string.
     * Allocates memory and copies the provided string into the newly allocated buffer.
     * @param string A null-terminated C-style string to initialize the StringG object with.
     */
    StringG(const char* string);

    /**
     * Copy constructor.
     * Creates a new StringG object as a deep copy of another StringG object.
     * @param other A reference to the StringG object to copy.
     */
    StringG(const StringG& other);

    /**
     * Move constructor.
     * Transfers the resources of another StringG object to this one.
     * After the operation, the other StringG object is left in a valid, but unspecified state.
     * @param other An r-value reference to a StringG object to move from.
     */
    StringG(StringG&& other) noexcept;

    /**
     * Destructor.
     * Cleans up the object's resources, deleting the dynamically allocated memory for the string
     * data.
     */
    ~StringG();

    /**
     * Prints the string to standard output.
     * Iterates over the internal character array and prints each character until the end of the
     * string.
     */
    void Print();

private:
    char* m_Data;     ///< Pointer to the dynamically allocated memory holding the string.
    uint32_t m_Size;  ///< Size of the string stored in m_Data.
};

class EntityG {
public:
    /**
     * Constructs an EntityG with a given name.
     * Initializes the entity with a name provided as a constant StringG reference.
     * @param name A constant reference to a StringG object to be used as the entity's name.
     */
    EntityG(const StringG& name);

    /**
     * Constructs an EntityG by moving a given name into it.
     * Initializes the entity with a name by moving a StringG object.
     * @param name An r-value reference to a StringG object to be moved as the entity's name.
     */
    EntityG(StringG&& name);

    /**
     * Prints the entity's name to standard output.
     * Delegates the printing to the Print method of the StringG member m_Name.
     */
    void Print();

private:
    StringG m_Name;  ///< The name of the entity stored as a StringG object.
};
