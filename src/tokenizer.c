#include "tokenizer.h"

int is_whitespace(char c)
{
  if(c == ' ' || c == '\t' || c == '\n') return 1;
  return 0;
}

char* get_token(char** a)
{
  while(is_whitespace(**a) && **a != 0)
    (*a)++;
  char* b = *a;

  switch(*b){
  case '(':
  case ')':
    b++;
    break;
  default: // Eat everything until whitespace, parenthesis or EOF
    while(!is_whitespace(*b) &&
          *b != '(' && *b != ')' &&
          *b != 0)
      b++;
  }

  return b;
}
