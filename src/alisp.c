#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "input.h"
#include "list.h"
#include "parse.h"

int eval(char* input)
{
  char* stream = input;
  ListElement* list = parse(&stream);
  free(input);

  if(!list) return 1;

  list_print(list, 0);
  list_free(list);

  return 0;
}

int repl()
{
  char *input;
  for(;;){
    input = get_input();
    if(!input)
      break;
    add_history(input);

    if(eval(input)) return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc == 1) return repl();
  else
    if(eval(read_file(argv[1]))) return 1;
  return 0;
}
