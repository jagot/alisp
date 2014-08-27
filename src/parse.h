//  @ Project : alisp
//  @ File Name : parse.h
//  @ Date : 2014-08-24
//  @ Author : Stefanos Carlström
//
//
#ifndef PARSE_H

#define PARSE_H

#include "list.h"

ListElement** parse_numeric(char* a, char* b, ListElement** list);
void parse_error(const char* message, char* a, char* b);
int is_digit(char c);
ListElement* parse(char** input);

#endif //PARSE_H
