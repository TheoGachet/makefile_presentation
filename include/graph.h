/*********************************************************************************
A graph is defined by:
- Number of nodes
- Array of pointers, containing the addresses of the successor lists of graph nodes
*********************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H
#define INFINITY 1000000  // or set e.g. INFINITY = INT_MAX - max_weight_graph(G);

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "heap.h"

typedef struct _node
{
	int		id;
	int		weight;
	struct	_node* successor;
} Node;

typedef struct
{
	int	nb_nodes;
	Node** list_successors;
} Graph;

/******************************************************************************
Read a graph G from file, and represent graph G in the form of an adjacency list
******************************************************************************/

void create_graph(Graph* G, const char* grapheFileName);
void print_graph(Graph* G);
int	 max_weight_graph(Graph* G);

/******************************************************************************
Find all shortest paths between node <source> and all other nodes:
Dijkstra's algorithm: Implementation without heap
******************************************************************************/

void dijkstra_without_heap(Graph* G, int source, int* dist_array);
void dijkstra_initialize(Graph* G, int* dist_array, bool* states_array, int source);
int get_argmin_in_list (int* distance, List *list);

/******************************************************************************
Find all shortest paths between node <source>  and all other nodes:
Dijkstra's algorithm: Implementation with heap (also called priority queue)
******************************************************************************/

void dijkstra_with_heap(Graph* G, int source,  int* dist_array);

/******************************************************************************
Find all shortest paths between node <source> and all other nodes:
Bellman-Ford's algorithm: Return false, if there are negative cycles
******************************************************************************/

bool bellman_ford(Graph* G, int source,  int* dist_array);

#endif

