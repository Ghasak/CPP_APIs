#include <string>

#pragma once

void classes_size_concept();

// Class with primitive types
class Vec2d {
public:
    int x;
    int y;
    const char* c;

public:
    // constructor
    Vec2d(int, int, const char*);
    // destructor
    ~Vec2d();
};

// Class with STD c++ data structure

// Class with primitive types
class Vec2c {
public:
    int X;
    int Y;
    const std::string m_Name;

public:
    // constructor
    Vec2c(int, int, const std::string&);
    // destructor
    ~Vec2c();
};
