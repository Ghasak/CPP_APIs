#pragma once
#include <ostream>

// Declares a concept demonstration function for operators and operator overloading.
void operators_and_operatos_overloading_concept();

// Represents a 2-dimensional vector with arithmetic and comparison operators overloaded.
class Vector2dA {
    float x, y;  // Coordinates of the vector

public:
    // Constructs a Vector2dA with specified x and y components.
    Vector2dA(float, float);

    // Adds two Vector2dA objects and returns the result.
    Vector2dA add(const Vector2dA& other) const;

    // Multiplies two Vector2dA objects and returns the result.
    Vector2dA muliply(const Vector2dA& other) const;

    // Overloads the + operator to add two Vector2dA objects.
    Vector2dA operator+(const Vector2dA& other) const;

    // Overloads the * operator to multiply two Vector2dA objects.
    Vector2dA operator*(const Vector2dA& other) const;

    // Overloads the == operator to compare two Vector2dA objects for equality.
    bool operator==(const Vector2dA& other) const;

    // Overloads the != operator to compare two Vector2dA objects for inequality.
    bool operator!=(const Vector2dA& other) const;

    // Overloads the << operator to insert a Vector2dA object into an output stream.
    friend std::ostream& operator<<(std::ostream& stream, const Vector2dA& other);
};
