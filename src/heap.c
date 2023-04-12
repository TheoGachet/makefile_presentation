#include "heap.h"

void create_void_heap(Heap *heap, int max_size)
{
	heap->tab = (Helement*) malloc(max_size* sizeof(Helement)); 
	heap->size = 0;
}

void create_heap(Heap *heap, Helement *tab, int real_size, int max_size)
{
	create_void_heap(heap, max_size);
	for (int i = 0; i < real_size; i++)
		insert_heap(heap, tab[i]);
}

int index_left_child(int icell)
{
	return 2 * icell + 1;
}

int index_right_child(int icell)
{
  return 2 * icell + 2;
}

int index_parent(int icell)
{
  return (icell - 1) / 2;
}

int nb_children(Heap *heap, int icell)
{
  int ndescends;
  if (index_left_child(icell) > heap->size - 1)
    ndescends = 0;
  else if (index_right_child(icell) > heap->size - 1)
    ndescends = 1;
  else
    ndescends = 2;
  return ndescends;
}

Helement left_child(Heap *heap, int icell)
{
	return heap->tab[index_left_child(icell)];
}

Helement right_child(Heap *heap, int icell)
{
  return heap->tab[index_right_child(icell)];
}

Helement parent(Heap *heap, int icell)
{
  return heap->tab[index_parent(icell)];
}

Helement content_cell(Heap *heap, int icell)
{
  return heap->tab[icell];
}

void print_heap(Heap *heap)
{
  int i, level = 0, ndescends;

  for (i = 0; i < heap->size; i++)
  {
	  printf("%d", content_cell(heap, i).id);

    ndescends = nb_children(heap, i);
    if (ndescends == 2)
		printf("(%d %d)", left_child(heap, i).id, right_child(heap, i).id);
    else if (ndescends == 1)
      printf("(%d)", left_child(heap, i).id);

    if (i == level * (level + 1)) 
    {
      printf("\n");
      level++;
    }
    else
      printf(" ");
  }
  printf("\n");
}

void insert_heap(Heap *heap, Helement helem)
{

  int ivalue;

  heap->tab[heap->size++] = helem;  // add at the end of array
  ivalue = heap->size - 1;
  heapify_up(heap, ivalue);
  
}

void heapify_up(Heap *heap, int ivalue) 
{
	bool right_placed = false;

	if (heap->size == 1) 
		right_placed = true;

	while (!right_placed)
	{
		if (parent(heap, ivalue).value <= heap->tab[ivalue].value)
			right_placed = true;
		else
		{
			exchange_with_parent(heap, ivalue);
			ivalue = index_parent(ivalue);
		}
	}
}

Helement extract_min(Heap *heap)
{
	Helement min_ent = heap->tab[0]; 

	heap->tab[0] = heap->tab[heap->size-1];
	heap->size --;
	
	heapify_down(heap, 0);
	
	return min_ent;
}

void heapify_down(Heap *heap, int ivalue) 
{
	int index_smallest = ivalue;

	if (index_left_child(ivalue) < heap->size && left_child(heap, ivalue).value < heap->tab[ivalue].value )
			index_smallest = index_left_child(ivalue);

	if (index_right_child(ivalue) < heap->size && right_child(heap, ivalue).value < heap->tab[index_smallest].value )
			index_smallest = index_right_child(ivalue);

	if (index_smallest != ivalue) 
	{
		exchange_with_parent(heap, index_smallest);
		heapify_down(heap, index_smallest);
	}	
}

void update_priority_heap(Heap *heap, Helement ent)
{
	int ivalue = get_index_in_heap(heap, ent);
	heap->tab[ivalue].value = ent.value;

	heapify_down(heap, ivalue); 
	heapify_up(heap, ivalue);
}

void exchange_with_parent(Heap *heap, int icell)
{
	Helement helem = content_cell(heap, icell);

	heap->tab[icell] = parent(heap, icell);
	heap->tab[index_parent(icell)] = helem;
}

int get_index_in_heap(Heap *heap, Helement helem)
{
	bool find_helem = false;
	int i = 0;
	while (find_helem == false && i < heap->size)
	{
		if (heap->tab[i].id == helem.id) 
			find_helem = true;
		else 
			i++;
	}
	return i;
}




