#include <string>

#pragma once

void lvalues_and_rvalues_concepts();

/*
 * Here the PrintName parameter lvalue-reference accept
 * an lvalue only
 */
void PrintName(std::string& name);

/*
 * Here the PrintName parameter lvalue-reference accept
 * an lvalue and revalue
 */
void PrintName(const std::string& name);

/*
 * Here the PrintName parameter rvalue-reference accept
 * an lvalue and rvalue, but will be prioritized over the const method above
 * Remove it if you want the const to be taken, as this will be prioritized.
 */
void PrintName(std::string&& name);

/*
 * Now i will implement the same thing about but with function pointer
 * so I can switch between the concepts to show the priority of lvalue-reference that accept an
 * lvalue and rvalue and also a rvalue-reference which also accept both the lvalue and rvalue, this
 * will be always prioritized over the former.
 */

// Define all possible functions
void PrintNameLValue(std::string& name);
void PrintNameConstLValue(const std::string& name);
void PrintNameRValue(std::string&& name);

// Declare external function pointers
extern void (*PrintNameLValuePtr)(std::string&);
extern void (*PrintNameConstLValuePtr)(const std::string&);
extern void (*PrintNameRValuePtr)(std::string&&);
