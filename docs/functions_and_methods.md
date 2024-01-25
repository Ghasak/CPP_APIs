# Functions and Methods

- Input variables will be consumed inside the function/method if they are
  passed as they are, instead we can pass them as a pointer or reference.
- Any local variable inside the function will also die once we exit the
  function body (function scope).
- To keep the variable from not dying if its inputted to our `function/method`
  is by passing it as a pointer or reference.
-

```sh

[outside the function]  --> +--+                                                                    +--+
                        --> |  |                    +-------------------+                           |  |
int var_x = 10;         --> |  |  o---- INPUT --->  |  Function/method  |    o---- OUTPUT --->      |  |
                        --> |  |                    +-------------------+                           |  |
                        --> |  |     [signature]   local defintion variables  [return]              |  |
                        --> +--+ <----------------------  Scope  -------------------------------->  +--+
                                                      int var_y = 10;                                var_x still alive
                                                                                                     var_y died at exit of the scope of the function/method
```
