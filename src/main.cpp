/* #include "concepts/m_const/t_constant.hpp" */
/* #include "concepts_bundles.hpp" */
#include "concepts/mylogging.hpp"
/* #include "concepts_bundles.hpp" */
#include <glog/logging.h>
#include <iostream>
#include <ostream>
#include <string>

/*************************************
 * Class Entity
 * This is the parent class
 *************************************/
class Entity {
private:
    std::string m_Name;

public:
    virtual std::string GetName() { return std::string("Entity Object"); }
};

/*************************************
 * Class Player
 * This is the child class
 *************************************/
class Player : public Entity {
private:
    std::string m_ChildName;  // this is not need anymore

public:
    Player(const std::string& name)
        : m_ChildName{name} {};
    std::string GetName() override { return m_ChildName; }
};

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        // You run directly the ../build/debug/main arg1 arg2 arg3 ..etc.
        std::cout << "Argument No." << i << "which is -> " << argv[i] << std::endl;
    }

    // Initialize logging
    init_logging(argv);
    std::cout << "######################################\n";

    Entity e1;
    Player p1(std::string("Player Object"));
    std::cout << e1.GetName() << std::endl;
    std::cout << p1.GetName() << std::endl;

    // Create a pointer for an object on stack
    Entity* ptr1 = &e1;
    Player* ptr2 = &p1;

    std::cout << ptr1->GetName() << std::endl;
    std::cout << ptr2->GetName() << std::endl;

    // The problem occur when we do the following
    Entity* ptr3 = &p1;
    std::cout << ptr3->GetName() << std::endl;

    // ------------------------------
    // array_function_in_depth();
    // ------------------------------
    // class_implementation();
    // classes_concepts_hub();
    /* virtual_function_concept(); */
    // ------------------------------
    // data_type_table();
    // ------------------------------
    // pointers_concept();
    // ------------------------------
    // const_in_action();
    // ------------------------------
    // cstyle_string_as_apointer();
    // ------------------------------
    // c_style_string_in_action();
    // ------------------------------
    // double_pointers_in_action();
    // ------------------------------
    // enums_concept_hub();

    return 0;
}
