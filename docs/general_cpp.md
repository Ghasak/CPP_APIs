# General concepts in CPP

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [General concepts in CPP](#general-concepts-in-cpp)
    - [Difference between parameters and arguments](#difference-between-parameters-and-arguments)
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

   - Arguments, on the other hand, are the actual values or expressions passed to the function when it is called.
   - They are the real pieces of data provided to the function to operate on.
   - Arguments are used to fill in the "slots" of the parameters when a function is invoked.

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
