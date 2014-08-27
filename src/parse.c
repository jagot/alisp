#include "parse.h"
#include "output.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

// Tries to parse the token delimited by a and b, and if successful,
// appends it to the list.
ListElement** parse_numeric(char* a, char* b, ListElement** list)
{
  char *c = a;
  int is_real = 0;
  for(; c != b; c++)
    is_real |= *c == '.' || *c == 'e' || *c == 'p';
  if(is_real)
    *list = list_append(*list, atof(a));
  else
    *list = list_append(*list, atoi(a));
  // Some kind of validation is necessary here, and NULL should be
  // returned if validation failed.

  return &((*list)->next);
}

ListElement** parse_list(char** a, ListElement** list)
{
  ListElement* new_list = parse(a);
  if(!new_list) return NULL;
  *list = list_append(*list, new_list);
  return &((*list)->next);
}

ListElement** parse_atom(char* a, char* b, ListElement** list)
{
  char *c = a;
  const int len = b-a;
  char atom[len+1];
  atom[len] = 0;

  int is_valid = 1;
  for(int i = 0; i < len; i++,c++){
    atom[i] = *c;
    is_valid &= *c != '(' && *c != ')';
  }
  if(!is_valid){
    printf("Invalid characters found in atom `%s`\n", atom);
    return NULL;
  }

  *list = list_append_atom(*list, atom);

  return &((*list)->next);
}

void parse_error(const char* message, char* a, char* b)
{
  printf("%s: ", message);
  while(a != b)
    putchar(*a++);
  putchar('\n');
}

int is_digit(char c)
{
  return c >= '0' && c <= '9';
}

ListElement* parse(char** input)
{
  ListElement* list = NULL;
  ListElement** list_p = &list;

  char *s = *input, *e;
  int np = 0;
  while(e = get_token(&s), e != s && *s != ')'){
    if(is_digit(*s) ||
       (is_digit(*(s+1)) &&
        (*s == '+' || *s == '-'))){
      list_p = parse_numeric(s, e, list_p);
    }
    else if(*s == '('){
      np++;
      list_p = parse_list(&e, list_p);

      if(*e == ')'){
        e++;
        np--;
      }
      else{
        printf("Expected ')'\n");
        return NULL;
      }
    }
    else if(*s == ')'){
      np--;
      if(np<0){
        printf("Unexpected ')'\n");
        return NULL;
      }
    }
    else{
      list_p = parse_atom(s, e, list_p);
    }

    if(!list_p) return NULL;

    s = e;
  }

  if(np){
    printf("Parenthesis mismatch: %d\n", np);
    return NULL;
  }

  *input = s;

  return list;
}
