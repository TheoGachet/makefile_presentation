
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
  int	id;
  float value;
} Helement;

typedef struct
{
	Helement* tab;
	int size;
} Heap;

void create_void_heap(Heap *heap, int max_size);
void create_heap(Heap *heap, Helement *tab, int real_size, int max_size);
Helement extract_min(Heap *heap);
void print_heap(Heap *heap);
void insert_heap(Heap *heap, Helement ent);
void update_priority_heap(Heap *heap, Helement ent);

int index_left_child(int icell);
int index_right_child(int icell);
int index_parent(int icell);
int nb_children(Heap *heap, int icell);

Helement left_child(Heap *heap, int icell);
Helement right_child(Heap *heap, int icell);
Helement parent(Heap *heap, int icell);
Helement content_cell(Heap *heap, int icell);

void heapify_down(Heap *heap, int ivalue);
void heapify_up(Heap *heap, int ivalue);
void exchange_with_parent(Heap *heap, int icell);

int get_index_in_heap(Heap *heap, Helement helem);

#endif
