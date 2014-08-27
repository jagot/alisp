#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

// Checks the amount of opening and closing parentheses in the input
// string.
int check_parens(const char* input)
{
  int o = 0;
  char* sp = (char*)input;
  char v;
  while((v = *sp++)){
    if(v == '(') o++;
    else if(v == ')') o--;
    // A closing parenthesis must always be preceded by an opening ditto.
    if(o < 0) return -1;
  }
  return o;
}

// Prints an error message and returns an empty string, that will
// evaluate to nothing.
char* input_error(char* input, const char* message)
{
  *input = 0;
  printf("%s\n", message);
  return input;
}

// Joins the strings a, b and c. The result is saved in a.
void cat_strings(char* a, const char* b, const char* c)
{
  size_t la = strlen(a),
    lb = strlen(b),
    lc = strlen(c);
  size_t s = la+lb+lc;

  a = realloc(a, s+1);
  a[s] = 0;
  strcpy(&a[la], b);
  strcpy(&a[la+lb], c);
}

// Read an input statement by joining consecutive input lines until
// the parentheses match up.
char* get_input()
{
  char* input;
  input = readline("al . ");
  if(!input) return NULL;
  
  int np;
  // If the parentheses do not match up, keep on reading input lines
  // until they do.
  while((np = check_parens(input))){
    if(np < 0) return input_error(input, "Unexpected ')'"); // E.g. ')('
    
    char* line = readline(" ... ");
    if(!line){
      free(line);
      return input_error(input, "\nUnexpected end-of-file!");
    }

    cat_strings(input, " ", line);
  }

  return input;
}

// Read the entire contents of a file into a string.
char* read_file(const char* filename)
{
  FILE *fp = fopen(filename, "r");
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  
  char* input = malloc(fsize+1);
  fread(input, fsize, 1, fp);
  input[fsize] = 0;
  
  fclose(fp);

  if(check_parens(input))
    return input_error(input, "Parenthesis mismatch");

  return input;
}
