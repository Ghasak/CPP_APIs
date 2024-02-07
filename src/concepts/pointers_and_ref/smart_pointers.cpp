#include <glog/logging.h>
#include <memory>
#include "concepts/pointers_and_ref/smart_pointers.hpp"
#include "concepts/mylogging.hpp"
#include <iostream>

void smart_pointers_concept() {
    // Intro to smart pointers
    // introduction_to_smart_pointers();
    demonstrate_raw_pointer();
    demonstrate_smart_unique_pointer();
}

void introduction_to_smart_pointers() {
    /*************************************************
     * SMART-POINTERS:
     * TOPIC: Using std::unique_ptr
     * Calling and Demonstrating
     *************************************************/
    std::unique_ptr<Number> num1 = std::make_unique<Number>(10);
    std::unique_ptr<Number> num2 = std::make_unique<Number>(20);
    add(num1, num2);
    //---------------------------
    size_t size = 5;
    ArrayWrapper* wrapper = new ArrayWrapper(size);
    // Initialize the array elements (example initialization)
    for (size_t i = 0; i < size; i++) {
        wrapper->Array[i] = i * 2;
    }
    // Processing in the outer scope
    processArrayWrapper(wrapper);

    delete wrapper;
}

/*************************************************
 * SMART-POINTERS:
 * TOPIC: Using std::unique_ptr
 * Class Definition
 *************************************************/
// ---- 1.
Number::Number(int value)
    : Value{value} {}
int Number::getValue() const { return Value; }

// Function accepting a unique_ptr by reference
// Definition
void add(std::unique_ptr<Number>& a, std::unique_ptr<Number>& b) {
    std::cout << "Sum: " << a->getValue() + b->getValue() << std::endl;
}

// ---- 2.
ArrayWrapper::ArrayWrapper(size_t size)
    : Size{size},
      Array{new int[size]} {}

void processArrayWrapper(ArrayWrapper* wrapper) {
    std::cout << "Processing ArrayWrapper elements: ";
    for (size_t i = 0; i < wrapper->Size; ++i) {
        std::cout << BLUE << wrapper->Array[i] << " " << RESET;
    }
    std::cout << std::endl;
}

ArrayWrapper::~ArrayWrapper() {
    LOG(INFO) << YELLOW << "THE OBJECT FROM CLASS ArrayWrapper Status: " << BLUE << "Destroyed!"
              << RESET;
    delete[] Array;
}

// ---- 3.
/************************************************
 * Example of a raw pointer which later will
 * be compared to it using a smart pointer
 * Definition Part
 ************************************************/

void demonstrate_raw_pointer() {
    Vec2b* vec1 = nullptr;
    {
        Vec2b* vec2 = new Vec2b(10, 20);  // Allocation on the heap using new keyword
        vec2->Print();                    // Access and use
        vec1 = vec2;
    }
    LOG(INFO) << BLUE << vec1->X << YELLOW << ", " << vec1->Y << RESET;
    delete vec1;  // It's  crucial to manually delete to avoid memory leak
}

void demonstrate_smart_unique_pointer() {
    std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b1 = nullptr;

    {
        std::unique_ptr<Vec2b> smart_ptr_on_heap_object_Vec2b2 = std::make_unique<Vec2b>(200, 300);
        smart_ptr_on_heap_object_Vec2b2->Print();
        smart_ptr_on_heap_object_Vec2b1 = std::move(smart_ptr_on_heap_object_Vec2b2);
    }
    smart_ptr_on_heap_object_Vec2b1->Print();
}

Vec2b::Vec2b(int x, int y)
    : X{x},
      Y{y} {
    std::cout << RED << "Object of class Vec2b is created: " << BLUE "<" << YELLOW << this->X << RED
              << " , " << YELLOW << this->Y << BLUE ">" << RESET << std::endl;
}

void Vec2b::Print() const {
    std::cout << RED << "[INFO] " << MAGENTA << "Vec2b: " << BLUE "<" << YELLOW << this->X << RED
              << " , " << YELLOW << this->Y << BLUE ">" << RESET << std::endl;
}

Vec2b::~Vec2b() {
    std::cout << RED << "Object of class Vec2b is destroyed: " << BLUE "<" << YELLOW << this->X
              << RED << " , " << YELLOW << this->Y << BLUE ">" << RESET << std::endl;
}
