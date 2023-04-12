/*********************************************************************************
Example of a C mini-project, which:

- From a given file, read and represent a graph G
- Find all shortest paths between a source node and all other nodes of G
*********************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main()
{
	const char* graphFileName = "RoadNetwork_Aix_Region.txt"; // RoadNetwork_Aix_Citycenter.txt, RoadNetwork_Aix_Region.txt
	Graph G;

	create_graph(&G, graphFileName);
	//printf("Graph G (Adjacency list): \n" );
	//print_graph(&G);

	int* dist_array = (int*) malloc(G.nb_nodes * sizeof(int));
	int source = 0;

	dijkstra_without_heap(&G, source, dist_array);
	//dijkstra_with_heap(&G, source, dist_array);
	//if(!bellman_ford(&G, source, dist_array)){
    //    printf("At least one negative cycle was found\n");
	//}

	printf("Distances corresponding to shortest paths from node %d to all graph nodes (%s): \n\n",
		source, graphFileName);

	for(int i = 0; i < G.nb_nodes; i++)
		printf(" %d ", dist_array[i]);
	printf("\n \n");

	/********************************************************************************************
	TODO (at home): Retrieve shortest paths

	Modify the following functions, in order to not only find the distance of shortest paths,
	but also to reconstruct the shortest paths from node source to all other nodes:

	- void dijkstra_without_heap(Graph* G, int source, int* dist_array);
	- void dijkstra_with_heap(Graph* G, int source,  int* dist_array);
	- bool bellman_ford(Graph* G, int source,  int* dist_array);
	********************************************************************************************/
	system("pause");
	return 0;
}
