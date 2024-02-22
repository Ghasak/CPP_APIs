#include <string>

#pragma once
void c_style_string_in_action();
void cstyle_string_as_apointer();
void cstyle_string_allocated_on_heap();

/* This function support const input  */
char* find_my_string(const char*, char);

/* This function support const input  */
char* find_my_string(char*, char);
// char* find_my_string(char cstyle_string_input[], char search_word);

void cstyle_string_return_a_poniter_as_const();
void cstyle_string_return_a_poniter();
