# General concepts in CPP

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->

**Table of Contents**

- [General concepts in CPP](#general-concepts-in-cpp)
  - [Difference between parameters and arguments](#difference-between-parameters-and-arguments)
  - [Difference between Fields and Attributes in OOP](#difference-between-fields-and-attributes-in-oop)
  - [OOP Terms](#oop-terms)
  - [Assoicatd graphics accelerators](#assoicatd-graphics-accelerators)

<!-- markdown-toc end -->

There are several programming paradigms beyond procedural, imperative, and
expression-oriented programming. I'll expand the table to include a broader
range of these paradigms, along with examples of programming languages that
exemplify each:

| Programming Paradigm          | Description                                                                | Examples of Languages           |
| ----------------------------- | -------------------------------------------------------------------------- | ------------------------------- |
| Procedural                    | Focuses on procedure calls; structured into functions or routines.         | C, Pascal, Fortran              |
| Imperative                    | Centers on changing program state through statements.                      | Java, Python, C++               |
| Object-Oriented               | Based on the concept of "objects" which are data structures.               | Java, C++, Python               |
| Functional                    | Emphasizes the application of functions.                                   | Haskell, Lisp, Erlang           |
| Logic                         | Based on formal logic, primarily used for problem solving.                 | Prolog, Datalog                 |
| Declarative                   | Expresses the logic without describing its control flow.                   | SQL, HTML, Prolog               |
| Event-Driven                  | Focuses on the flow of the program driven by events like user actions.     | JavaScript, C#                  |
| Concurrent                    | Allows multiple computations to run simultaneously.                        | Go, Erlang, Java                |
| Distributed                   | Runs across multiple computer systems and communicates through network.    | Elixir, Scala, Akka             |
| Aspect-Oriented               | Focuses on separating cross-cutting concerns from the main program logic.  | AspectJ, Spring AOP             |
| Reflective                    | Ability of a program to manipulate the structure and behavior of the code. | Java, Python, Ruby              |
| Constraint-Based/Logic        | Solves problems by setting constraints and solving them.                   | Prolog, MiniZinc                |
| Parallel                      | Parallel execution of computations, often for performance in high load.    | CUDA, OpenMP, MPI               |
| Expression-Oriented           | Emphasizes expressions that return values over statements.                 | OCaml, Lisp, Haskell            |
| Query-Driven/Database-Centric | Paradigm revolving around database queries.                                | SQL, LINQ                       |
| Symbolic                      | Focuses on the manipulation of symbols and symbolic expressions.           | Lisp, Mathematica               |
| Meta Programming              | Writing programs that write or manipulate other programs.                  | Template Metaprogramming in C++ |

Please note that this categorization is not strict; many programming languages
support multiple paradigms, allowing developers to choose the best paradigm for
their specific task.

## Difference between parameters and arguments

In programming, particularly in the context of functions, the terms
"parameters" and "arguments" are often used and can sometimes be confusing as
they are closely related but have distinct meanings:

1. **Parameters**:

   - Parameters are the variables listed as part of a function's declaration or
     definition.
   - They are placeholders within the function that represent the values that
     the function expects to receive when it is called.
   - Parameters define what type of data the function expects.
   - Think of parameters as the "slots" in a function's signature where you
     specify the type and, optionally, a name for the data the function will
     operate on.

   Example in a function definition:

   ```cpp
   void printMessage(std::string message) {
       // 'message' is a parameter
   }
   ```

2. **Arguments**:

   - Arguments, on the other hand, are the actual values or expressions passed
     to the function when it is called.
   - They are the real pieces of data provided to the function to operate on.
   - Arguments are used to fill in the "slots" of the parameters when a function
     is invoked.

   Example in a function call:

   ```cpp
   int my_var = 10;
   printMessage("Hello, world!", my_var);
   // "Hello, world!" is an argument, which is a string literal passed to the function
   // my_var, also an argument.
   ```

In summary, when you define a function, you specify parameters. When you call a
function, you provide arguments. Parameters are in the context of function
definitions and declarations, whereas arguments are in the context of function
calls.

## Difference between Fields and Attributes in OOP

In the context of Object-Oriented Programming (OOP), the terms "field" and
"attribute" are often used interchangeably, but there can be subtle differences
in how they are perceived, depending on the programming language or the
programmer's perspective. Let's break it down:

1. **Field**: A field is typically considered a variable that belongs to an
   object or a class. In OOP, fields represent the state of an object and are
   used to store data. For example, in a `Car` class, fields might include
   `color`, `brand`, and `engineType`.
2. **Attribute**: The term attribute can also refer to a variable that belongs
   to an object or class. However, in some contexts, "attribute" might convey a
   broader meaning, encompassing not just the data (like fields) but also other
   characteristics or properties of an object. For instance, in some languages
   or frameworks, attributes can also refer to additional metadata or
   annotations that provide more information about the property (like
   constraints or serialization properties).

- In most practical scenarios in C++ and many other OOP languages, you can use
  "field" and "attribute" interchangeably when referring to the data part of a
  class. Both terms are used to describe the variables contained within a class
  that hold the state of an object.
- It's worth noting that different programming communities might have slight
  variations in how they use these terms. For example, in database-oriented
  contexts, "attribute" might more specifically refer to the columns of a table,
  while in web development, "attribute" often refers to properties of HTML
  elements.
- In summary, while there can be nuanced differences in meaning, in the
  day-to-day use of OOP in C++, "field" and "attribute" are generally considered
  synonymous and are used to refer to the data members of a class.

## OOP Terms

Certainly! In Object-Oriented Programming (OOP) with C++, various terms are used
to describe different concepts. Below is a table that maps these OOP terms to
their equivalent or related terms in procedural or general programming:

| OOP Term        | General Programming Term | Description                                                                                           |
| --------------- | ------------------------ | ----------------------------------------------------------------------------------------------------- |
| Class           | -                        | A blueprint for creating objects (instances). Defines attributes and methods.                         |
| Object          | -                        | An instance of a class. Contains data and behavior as defined in the class.                           |
| Instance        | -                        | Similar to object; an individual realization of any class.                                            |
| Method          | Function                 | A function defined within a class. Operates on data that is contained within the class.               |
| Constructor     | -                        | A special type of method used to initialize objects of a class.                                       |
| Destructor      | -                        | A special method called when an object is destroyed. Used to release resources.                       |
| Field           | Variable                 | Variables that belong to an object or class. Used to store data.                                      |
| Attribute       | Variable                 | Often used interchangeably with 'field'. Also refers to variables that define properties of a class.  |
| Member          | -                        | Refers to both methods and fields/attributes within a class.                                          |
| Parameter       | Parameter                | Variables listed as part of a method/function definition. Used to pass values into methods.           |
| Argument        | Argument                 | Actual values passed to a method/function when it is called.                                          |
| Encapsulation   | -                        | OOP concept of bundling data (fields) and methods that operate on the data into a single unit.        |
| Inheritance     | -                        | OOP concept where a class derives (or inherits) properties and behavior from another class.           |
| Polymorphism    | -                        | OOP concept that allows objects of different classes to be treated as objects of a common superclass. |
| Overloading     | -                        | Defining multiple methods with the same name but different parameters.                                |
| Overriding      | -                        | Redefining a method in a subclass that was already defined in a superclass.                           |
| Access Modifier | -                        | Keywords like `public`, `private`, and `protected` that define the access level of class members.     |
| Interface       | -                        | An abstract type that contains no data but defines behaviors as method signatures.                    |
| Abstract Class  | -                        | A class that cannot be instantiated and may contain abstract methods. Used as a base class.           |

Note that some of these terms do not have direct equivalents in procedural or
general programming, as they are specific to the OOP paradigm. The table above
provides a basic reference for understanding these terms in the context of C++
OOP.

## Assoicatd graphics accelerators

Creating a comprehensive and up-to-date table of all GeForce models currently
available in the market is quite extensive due to the large variety of models
and frequent updates. However, I can provide a generalized overview of some of
the key series and models within NVIDIA's GeForce lineup, including some of the
most popular and recent releases. For the most current and detailed
information, it's best to consult NVIDIA's website or a reliable tech news
outlet.

Here's a simplified overview:

| Series                                 | Models                                                                                          |
| -------------------------------------- | ----------------------------------------------------------------------------------------------- |
| GeForce 700 Series                     | 750, 750 Ti, 760, 770, 780, 780 Ti, etc.                                                        |
| GeForce 900 Series                     | 950, 960, 970, 980, 980 Ti, etc.                                                                |
| GeForce 1000 Series                    | 1050, 1050 Ti, 1060, 1070, 1070 Ti, 1080, 1080 Ti, etc.                                         |
| GeForce 1600 Series                    | 1650, 1650 Super, 1660, 1660 Super, 1660 Ti, etc.                                               |
| GeForce RTX 2000 Series                | RTX 2060, RTX 2060 Super, RTX 2070, RTX 2070 Super, RTX 2080, RTX 2080 Super, RTX 2080 Ti, etc. |
| GeForce RTX 3000 Series                | RTX 3060, RTX 3060 Ti, RTX 3070, RTX 3070 Ti, RTX 3080, RTX 3080 Ti, RTX 3090, etc.             |
| GeForce RTX 4000 Series (if available) | _Dependent on release and availability_                                                         |

Please note that this table is not exhaustive and does not include every single
model, especially the numerous custom variants offered by different
manufacturers. Also, the availability of these models can vary based on the
region and the current market situation. For the latest models and specific
details, checking the official NVIDIA website or a reputable computer hardware
retailer is recommended.
