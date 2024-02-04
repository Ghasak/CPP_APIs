#include "concepts/classes/Friends.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>
#include "concepts/classes/operators.hpp"

// Demonstrates the use of overloaded operators in the Vector2dA class.
void operators_and_operatos_overloading_concept() {
    LOG(INFO) << RED << "We are using now the operator module.." << RESET;

    // Demonstrates addition, multiplication, and comparison of Vector2dA objects.
    Vector2dA position(4.0f, 4.0f);
    Vector2dA speed = Vector2dA(3.45f, 4.04f);
    Vector2dA result1 = position.add(speed);
    Vector2dA result2 = position.muliply(speed);
    Vector2dA result3 = position.add(speed).muliply(position);

    LOG(INFO) << result1 << std::endl;
    LOG(INFO) << result2 << std::endl;
    LOG(INFO) << result3 << std::endl;
    // Operators Overloading
    // Demonstrates operator overloading for addition.
    Vector2dA result4 = position + speed;
    LOG(INFO) << result4 << std::endl;
    Vector2dA v1(10.0f, 10.0f);
    Vector2dA v2(10.0f, 10.0f);
    if (v1 == v2) {
        LOG(INFO) << BLUE << "v1 is equal to v2" << RESET;
    }
}

// Implementation of Vector2dA methods and friend functions follows...
Vector2dA::Vector2dA(float x, float y)
    : x{x},
      y{y} {}

Vector2dA Vector2dA::add(const Vector2dA& other) const {
    // return Vector2dA(this->x + other.x, this->y + other.y);
    // return *this + other; // Most common
    //  You can also write as
    return operator+(other);
}

Vector2dA Vector2dA::muliply(const Vector2dA& other) const {
    // return Vector2dA(this->x * other.x, this->y * other.y);
    //*this * other; // Most common
    return operator*(other);
}

std::ostream& operator<<(std::ostream& stream, const Vector2dA& other) {
    stream << "Vector: " << other.x << ", " << other.y;
    return stream;
}

Vector2dA Vector2dA::operator+(const Vector2dA& other) const {
    // We can do this:
    // return Vector2dA(this->x + other.x, this->y + other.y);
    // We can do this as well
    // return Vector2dA::add(other);
    // You can use
    return Vector2dA(
        x + other.x,
        y + other.y);  // <- If you select return *this + other; in add method
                       // Or you use return operator+(other); in the add function as well
}

Vector2dA Vector2dA::operator*(const Vector2dA& other) const {
    // We can do this:
    // return Vector2dA(this->x * other.x, this->y * other.y);
    // We can do this as well
    // return Vector2dA::add(other);
    // You can use
    return Vector2dA(
        x * other.x,
        y * other.y);  // <- If you select return *this * other; in add method
                       // Or you use return operator*(other); in the add function as well
}

bool Vector2dA::operator==(const Vector2dA& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

bool Vector2dA::operator!=(const Vector2dA& other) const {
    return (this->x == other.x) && (this->y == other.y);
    // return !(*this == other);  // We can do this as well
    // You can also do
    // return !(operator==(other));
}
