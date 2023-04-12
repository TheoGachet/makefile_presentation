#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _element
{
    int		id;
    struct	_element *next;
} Element;

typedef struct
{
    Element *head;
} List;

void initialize(List *list);
void add_via_head(List *list, int id);
void print_list(List *list);
bool is_void(List *list);
void delete_element(List *list, int id);
int get_head_id(List *list);
void delete_head(List *list);
void free_list(List *list);

#endif 
