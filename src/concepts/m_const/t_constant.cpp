#include <glog/logging.h>
#include <iostream>
#include <ostream>
#include "concepts/mylogging.hpp"
#include "t_constant.hpp"

void const_in_action() {
    /* const int version_number_major{2}; */
    /* const int version_number_minor{2}; */
    /* const std::string product_name{"Super Hyper Net Modulator"}; */
    /* const double PI{3.141592653589793238462}; */

    // LOG(INFO) << RED << "PI Value: " << BLUE << PI << RESET;
    //  usage of const
    //
    // -------------------
    // [1] with pointer
    // -------------------
    //  with_pointer_1();
    //  with_pointer_2();
    // -------------------
    // [1] with classes
    // -------------------
    //const_with_classes();
    const Entity e = Entity(10, 20);
    e.display_info();
    print_eneity(e);

}

void with_pointer_1() {
    const int MAX_AGE = 90;
    int* a = new int;  // allocate on the heap
    *a = 2;
    LOG(INFO) << BLUE << "Dereferencing *a as -> " << RED << *a << RESET;

    delete a;  // free the allocated memory
    int* ptrx = nullptr;
    LOG(INFO) << BLUE << "a become a null pointer -> " << BLUE << a << RESET;
    LOG(INFO) << BLUE << "ptrx is a null pointer -> " << BLUE << ptrx << RESET;

    a = (int*)&MAX_AGE;  // reassign a to point to MAX_AGE
    LOG(INFO) << BLUE << "Memory Address (pointer) of a is -> " << RED << a << RESET;
}

void with_pointer_2() {
    int MAX_AGE = 10;
    /* MAX_AGE = 200;  // Allowed  */
    const int MAX_WEIGHT = 100;
    /* MAX_WEIGHT = 200; //not allowed  */

    LOG(INFO)
        << BLUE
        << "[CASE: (1)] Modifying the content is not allowed, but Modifying the pointer is allowed "
        << RESET;
    const int* ptr1 = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "const int* ptr1 = &MAX_AGE;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr1) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr1 = &MAX_WEIGHT; => [Allowed] -> the memeory address (ptr1/pointer) can "
                 "reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr1 << RESET;
    /*  */

    LOG(INFO)
        << BLUE
        << "[CASE: (2)] Modifying the content is not allowed, but Modifying the pointer is allowed "
        << RESET;
    const int* ptr2 = &MAX_WEIGHT;
    LOG(INFO) << RED << "FORM[2]:" << BLUE << "const int* ptr2 = &MAX_WEIGHT;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr2) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr2 = &MAX_WEIGHT; => [Allowed] -> the memory address (ptr2/pointer) can "
                 "reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr2 << RESET;

    LOG(INFO)
        << BLUE
        << "[CASE: (3)] Modifying the content is allowed, but Modifying the pointer is not allowed "
        << RESET;
    int* const ptr3 = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "int* const ptr3 = &MAX_AGE;" << RESET;
    LOG(INFO) << RED << "*(ptr3) = 300;      => [Allowed] -> variable is assignable" << RESET;
    LOG(INFO) << RED
              << "ptr3 = &MAX_WEIGHT; => [ERROR:: not allowed] -> the memory address "
                 "(ptr3/pointer) cannot reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr3 << RESET;

    LOG(INFO) << BLUE
              << "[CASE: (4)] Modifying the content is not allowed, Also, Modifying the pointer is "
                 "not allowed "
              << RESET;
    const int* const ptr = &MAX_AGE;
    LOG(INFO) << RED << "FORM[1]:" << BLUE << "const int* const ptr = &MAX_AGE;" << RESET;
    LOG(INFO) << RED << "FORM[2]:" << BLUE << "int const* const ptr = &MAX_AGE;" << RESET;
    LOG(INFO)
        << RED
        << "*(ptr) = 300;      => [ERROR:: not allowed ] -> Read-only variable is not assignable"
        << RESET;
    LOG(INFO) << RED
              << "ptr = &MAX_WEIGHT; => [ERROR:: not allowed] -> the memory address (ptr3/pointer) "
                 "cannot reassigned to another address."
              << RESET;
    LOG(INFO) << RED << ptr << RESET;

    LOG(INFO) << BLUE << "CASE: (1) & (2) are having similar effect" << RESET;
}

void const_with_classes() {
    class EntityX {
    private:
        int m_x, m_y;

    public:
        // for getting information, we ensure the `m_x` and `m_y` will not be changed inside these
        // const methods.
        int get_x() const {
            // m_x = 10;  // [ERROR: not allowed]  -> Cannot assign to non-static data memember
            // within const member function`get_x`
            return m_x;
        }
        int get_y() const { return m_y; }
        // As we want to change the value of m_x, then we should not use const method
        void set_x(int x) { m_x = x; }
    };
}


// Constructor definition
Entity::Entity(int x, int y)
    : m_x{x}, m_y{y} {}

// Getter methods
int Entity::get_x() const { return m_x; }
int Entity::get_y() const { return m_y; }

// Setter methods
void Entity::set_x(int x) { m_x = x; }
void Entity::set_y(int y) { m_y = y; }

// Method to display information
std::string Entity::display_info() const {
    std::string entity_info = "<" + std::to_string(m_x) + "," + std::to_string(m_y) + ">";
    return entity_info;
}


void print_eneity(const Entity& e) {  // <- just to pass a constat reference so you will need the
                                      // const-methods in the Entity class
    LOG(INFO) << BLUE << "Getting m_x: " << RED << e.get_x() << RESET;
    LOG(INFO) << BLUE << e.display_info();
}
