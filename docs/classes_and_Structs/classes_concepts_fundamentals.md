# Classes In Action

The classes in C++ encompass the following concepts:
Sure, here's a list of fundamental concepts related to classes in C++:

1. **Class Definition:** The blueprint for creating objects. It defines a new
   data type which includes data members (attributes) and member functions
   (methods).
2. **Object:** An instance of a class. Each object has its own identity and
   attributes.
3. **Access Specifiers:** Define the access level of class members. The primary
   ones are `public`, `private`, and `protected`.
4. **Constructor:** A special member function that is automatically called when
   an object is created. It initializes the object's attributes.
5. **Destructor:** A special member function that is automatically called when
   an object is destroyed. It's used to clean up resources.
6. **Copy Constructor:** A constructor used to create a new object as a copy of
   an existing object.
7. **Assignment Operator:** Used to copy the values from one object to another
   existing object.
8. **this Pointer:** A pointer that refers to the object which invoked the
   member function.
9. **Inline Functions:** Functions defined inside the class declaration. They
   can speed up execution for small, frequently called functions.
10. **Friend Functions:** Functions that are not members of a class but can
    access the class's private and protected members.
11. **Static Members:** Class members that are shared by all objects of the
    class. There's only one copy of a static member for the entire class.
12. **Member Functions:** Functions that are declared and defined within a
    class.
13. **Inheritance:** A way to form new classes using classes that have already
    been defined.
14. **Polymorphism:** The ability of different classes to be treated as
    instances of the same class through inheritance.
15. **Virtual Functions:** Member functions which are expected to be redefined
    in derived classes. They enable runtime polymorphism.
16. **Abstract Classes and Pure Virtual Functions:** Classes that can't be
    instantiated. They are used to define interfaces.
17. **Operator Overloading:** The ability to redefine the meaning of an operator
    (like +, -, etc.) for user-defined types.
18. **Friend Classes:** A class that is declared as a friend of another class is
    able to access private and protected members of the other class.
19. **Encapsulation:** The bundling of data with the methods that operate on
    that data, and restricting direct access to some of an object's components.
20. **Inheritance Hierarchy:** The structure formed by classes inheriting from
    other classes.

These concepts form the basis of object-oriented programming in C++ and are
essential for effective use of the language.

## Classes Templates

Class templates in C++ are a powerful feature used for creating generic or
parameterized classes. Here are the key concepts associated with class
templates, presented as bullet points:

1. **Template Definition:** A way to define a class with a placeholder for data
   types. It allows the class to handle data of any type.
2. **Template Parameters:** These are placeholders for data types or values.
   They are specified within angle brackets (`< >`) after the `template`
   keyword.
3. **Instantiation of Template Classes:** Creating objects of a template class.
   The compiler generates a new class for each set of template arguments
   provided.
4. **Member Functions of Template Classes:** Just like regular classes, template
   classes can have member functions, which can also be templates.
5. **Default Template Arguments:** Similar to function templates, class
   templates can have default arguments, allowing some parameters to be
   optional.
6. **Template Specialization:** Creating a specific implementation of a template
   for a particular data type. This is useful when a generic implementation is
   not suitable.
7. **Partial Template Specialization:** Specializing only some parameters of a
   template class, while keeping others generic.
8. **Nested Template Classes:** Templates can be nested within other templates,
   allowing for complex data structures.
9. **Non-type Template Parameters:** Apart from types, template parameters can
   also be values like integers. This allows for more flexible and powerful
   templating.
10. **Template Template Parameters:** A template parameter can itself be a
    template, allowing for even more abstraction and flexibility.
11. **Template Metaprogramming:** An advanced use of templates to perform
    computations at compile-time, resulting in highly efficient runtime code.
12. **Type Traits and Type Manipulation:** Using templates to gather information
    about types or to manipulate types, often used in template metaprogramming.
13. **SFINAE (Substitution Failure Is Not An Error):** A principle in template
    metaprogramming where the failure of template argument substitution is not
    treated as an error but causes the template instantiation to be discarded in
    certain contexts.

Class templates are a fundamental tool in C++ for creating flexible and reusable
code. They are widely used in the Standard Template Library (STL), which is part
of the C++ standard library.
