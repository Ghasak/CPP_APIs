# Casting in C++

## Introduction

Casting in C++ is a way to convert a variable from one data type to another.
There are several types of casting in C++, each serving different purposes. I'll
cover the four main types of casting: static_cast, dynamic_cast, const_cast, and
reinterpret_cast. I'll also provide examples for each type, including cases
involving primitive, derived, and user-defined types.

### 1. **static_cast**

**Purpose:** Used for all types of conversions that do not require a runtime
check. It can be used to convert numeric data types such as int to float, or
pointer types (e.g., converting base class pointers to derived class pointers).

**Example:**

```cpp
int i = 10;
float f = static_cast<float>(i); // converts integer to float
std::cout << "float value: " << f << std::endl;

// Example with user-defined types
class Base {};
class Derived : public Base {};
Base* basePtr = new Derived();
Derived* derivedPtr = static_cast<Derived*>(basePtr); // downcasting
```

### 2. **dynamic_cast**

**Purpose:** Primarily used for handling polymorphism. You use it when you need
to safely downcast from a base class pointer to a derived class pointer.

**Example:**

```cpp
class Base {
public:
    virtual void display() {}
};
class Derived : public Base {
public:
    void display() override {}
};

Base* basePtr = new Derived();
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

if (derivedPtr != nullptr) {
    derivedPtr->display(); // Safe downcasting
} else {
    // Handle the error
}
```

### 3. **const_cast**

**Purpose:** Used to add or remove the `const` qualifier from a variable.

**Example:**

```cpp
const int a = 10;
int* b = const_cast<int*>(&a);
*b = 20; // Now, "a" can be modified through "b", although this leads to undefined behavior if "a" is truly const
```

### 4. **reinterpret_cast**

**Purpose:** Used for conversions of pointer types to other pointer types, even
if they are not related, and for conversions between pointers and integral
types. It's the most dangerous cast and should be used sparingly.

**Example:**

```cpp
int* iptr = new int(10);
char* cptr = reinterpret_cast<char*>(iptr); // pointer type conversion
```

### Combining Types

- **Primitive to User-defined Type:** You usually don't convert directly between
  primitive and user-defined types using casting operators. Instead, you might
  design your user-defined types to accept primitive types in their constructors
  or conversion operators.

**Example:**

```cpp
class MyInt {
    int value;
public:
    MyInt(int v) : value(v) {}
    operator int() { return value; } // conversion operator
};

int main() {
    MyInt mi = 5; // implicit conversion from int to MyInt
    int iv = mi;  // implicit conversion from MyInt to int
}
```

- **Derived to Primitive Type:** Conversion from a derived type to a primitive
  type usually involves a member function or an operator in the class that
  returns a primitive type.

**Example:**

```cpp
class Fraction {
    int numerator, denominator;
public:
    Fraction(int num, int den) : numerator(num), denominator(den) {}
    operator float() const { return static_cast<float>(numerator) / denominator; }
};

int main() {
    Fraction frac(3, 4);
    float value = frac; // using conversion operator
}
```

These examples demonstrate the basic use of casting in C++ and how to convert
between different types, including primitive, derived, and user-defined types.
Always use the appropriate casting operator to ensure your code's type safety
and clarity.
