//  @ Project : alisp
//  @ File Name : input.h
//  @ Date : 2014-08-24
//  @ Author : Stefanos Carlström
//
//
#ifndef INPUT_H

#define INPUT_H

int check_parens(const char* input);
char* input_error(char* input, const char* message);
char* get_input();
char* read_file(const char* filename);

#endif //INPUT_H
