#pragma once
#include <iostream>
void const_in_action();


#pragma once
#include <string>

class Entity {
public:
    // Constructor declaration
    Entity(int x, int y);
    // Getter methods
    int get_x() const;
    int get_y() const;

    // Setter methods
    void set_x(int x);
    void set_y(int y);

    // Method to display information
    std::string display_info() const;

private:
    int m_x, m_y;
};

void print_eneity(const Entity& e);
