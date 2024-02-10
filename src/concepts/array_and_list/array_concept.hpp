#pragma once
#include <array>  // For the std::array
void array_function_in_depth();
void standard_array_cpp();
void vector_allocated_on_heap();
void what_is_vecotor_on_heap();
void c_style_array();
void standard_array_cpp();
void pointer_with_array_arithmatic();
// The size of the std::array must known at complied time
// can be moved to a file for collecting all constant values - in real projects
// const int ARRAY_CONST_SIZE = 5;
/* incorrect Usage of std::array with Non-constexpr Size: You are trying to use
 * ARRAY_CONST_SIZE as the size of std::array, which is correct in intent.
 * However, the size of std::array must be known at compile time as a constexpr,
 * but const does not guarantee that the value will be a compile-time constant in
 * all contexts. This might not directly cause a compilation issue in all
 * compilers or settings, but it is a misuse of std::array semantics.
 */

constexpr int ARRAY_CONST_SIZE = 5;
void print_std_array(std::array<int, ARRAY_CONST_SIZE>);
