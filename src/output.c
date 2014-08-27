#include "output.h"
#include <stdio.h>

void putvec(char* a, char* b)
{
  while(a != b)
    putchar(*a++);
}
