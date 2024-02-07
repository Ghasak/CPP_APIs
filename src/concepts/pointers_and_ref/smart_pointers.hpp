#pragma once
#include <memory>
void smart_pointers_concept();
void introduction_to_smart_pointers();
/*************************************************
 * SMART-POINTERS:
 * TOPIC: Using std::unique_PR
 * Class Declaration
 *************************************************/
// ---- 1.
class Number {
public:
    int Value;
    // Constructor
    Number(int);
    int getValue() const;
};

// Function accepting a unique_ptr by reference
// Declaration
void add(std::unique_ptr<Number>&, std::unique_ptr<Number>&);

// ---- 2.
class ArrayWrapper {
public:
    size_t Size;
    int* Array;

    // Constructor
    ArrayWrapper(size_t);

    ~ArrayWrapper();
};

void processArrayWrapper(ArrayWrapper*);

// ---- 3.
/************************************************
 * Example of a raw pointer which later will
 * be compared to it using a smart pointer
 * Declaration Part
 ************************************************/

void demonstrate_raw_pointer();
void demonstrate_smart_unique_pointer();
class Vec2b {
public:
    int X, Y;
    Vec2b(int, int);
    void Print() const;
    ~Vec2b();
};
