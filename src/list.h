//  @ Project : alisp
//  @ File Name : list.h
//  @ Date : 2014-08-24
//  @ Author : Stefanos Carlström
//
//
#ifndef LIST_H

#define LIST_H

typedef enum ListElementType { INTEGER,
                               REAL,
                               STRING,
                               ATOM,
                               LIST } ListElementType;
typedef struct ListElement
{
  ListElementType type;
  union {
    int intVal;
    double doubleVal;
    char* charVal;
    struct ListElement* listVal;
  } value;
  struct ListElement* next;
} ListElement;

ListElement* list_end(ListElement* list);

ListElement* list_append_int(ListElement* list, int v);
ListElement* list_append_double(ListElement* list, double v);
ListElement* list_append_string(ListElement* list, const char* v);
ListElement* list_append_atom(ListElement* list, const char* v);
ListElement* list_append_list(ListElement* list, ListElement* v);

#define list_append(list,v) _Generic((v),                               \
                                     int: list_append_int,              \
                                     double: list_append_double,        \
                                     char: list_append_string,          \
                                     ListElement*: list_append_list)(list,v)

ListElement* list_malloc(ListElement* list);
void list_free(ListElement* list);

void list_print(ListElement* list, int indent);

#endif //LIST_H
