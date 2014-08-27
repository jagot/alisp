#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// # A linked list library
// This is a simple implementation of a generic linked list.

// Find last element in a linked list
ListElement* list_end(ListElement* list)
{
  while(list->next)
    list = list->next;
  return list;
}



// Create a new list element at the end of the linked list.
ListElement* list_new(ListElement* list, ListElementType type)
{
  list = list_malloc(list);
  list->type = type;
  return list;
}

// Append an integer at the end of the linked list.
ListElement* list_append_int(ListElement* list, int v)
{
  list = list_new(list, INTEGER);
  list->value.intVal = v;
  return list;
}

// Append a double at the end of the linked list.
ListElement* list_append_double(ListElement* list, double v)
{
  list = list_new(list, REAL);
  list->value.doubleVal = v;
  return list;
}

// Append a string at the end of the linked list.
ListElement* list_append_string(ListElement* list, const char* v)
{
  list = list_new(list, STRING);
  list->value.charVal = malloc(strlen(v)+1);
  strcpy(list->value.charVal, v);
  return list;
}

// Append a atom at the end of the linked list.
ListElement* list_append_atom(ListElement* list, const char* v)
{
  list = list_new(list, ATOM);
  list->value.charVal = malloc(strlen(v)+1);
  strcpy(list->value.charVal, v);
  return list;
}

// Append a linked list at the end of the linked list.
ListElement* list_append_list(ListElement* list, ListElement* v)
{
  list = list_new(list, LIST);
  list->value.listVal = v;
  return list;
}

ListElement* list_malloc(ListElement* list)
{
  if(list){
    list = list_end(list);
    list->next = malloc(sizeof(ListElement));
    list = list->next;
  }
  else{
    list = malloc(sizeof(ListElement));
  }
  list->next = NULL;
  return list;
}

// Free the entire linked list and it elements, recursively.
void list_free(ListElement* list)
{
  ListElement* prev = list;
  do {
    if(list->type == STRING || list->type == ATOM)
      free(list->value.charVal);
    if(list->type == LIST)
      list_free(list->value.listVal);
    prev = list;
    list = list->next;
    free(prev);
  } while(list);
}

void print_indent(int indent)
{
  for(int i = 0; i < indent; i++)
    putchar(' ');
}

void list_print(ListElement* list, int indent)
{
  while(list){
    print_indent(indent);
    if(list->type == INTEGER)
      printf("Integer: %i\n", list->value.intVal);
    if(list->type == REAL)
      printf("Real: %f\n", list->value.doubleVal);
    if(list->type == ATOM)
      printf("Atom: %s\n", list->value.charVal);
    if(list->type == STRING)
      printf("String: %s\n", list->value.charVal);
    if(list->type == LIST){
      printf("List:\n");
      list_print(list->value.listVal, indent+4);
    }

    list = list->next;
  }
}
