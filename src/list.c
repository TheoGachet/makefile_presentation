#include "list.h"

void initialize(List *list)
{
	list->head = NULL;
}

void add_via_head(List *list, int id)
{
    Element *new_elem = (Element *)malloc(sizeof(Element));
    new_elem->id = id;

    new_elem->next = list->head;
    list->head = new_elem;
}

void print_list(List *list)
{
    Element *Element = list->head;

    printf("List : ");

    while (Element != NULL)
    {
        printf("%d ", Element->id);
        Element = Element->next;
    }

    printf("\n");
}

bool is_void(List *list)
{
    return list->head == NULL;
}

int get_head_id(List *list)
{
    if (list->head == NULL)
        return 0;
    else
        return list->head->id;
}

void delete_head(List *list)
{
    if (list->head != NULL)
    {
        Element *old_head = list->head;
        list->head = list->head->next;
        free(old_head);
    }
}

void delete_element(List *list, int id_elem)
{
    if (list->head != NULL)
    {
        Element *current, *previous;
		previous = NULL;
		current = list->head;

		while (current->id != id_elem && current != NULL)
		{
			previous	= current;
			current		= current->next;
		}
		if (previous != NULL && current != NULL) 
			previous->next = current->next;
		else 
			list->head = current->next;
		free(current);
    }
}

void free_list(List *list)
{
    while (list->head != NULL)
        delete_head(list);
}