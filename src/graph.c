#include "graph.h"

void create_graph(Graph* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL) 
	{
		int nb_nodes, nb_arcs, u, v, w;
		fscanf(fp, "%d %d", &nb_nodes, &nb_arcs);	
		G->nb_nodes 		= nb_nodes;
		G->list_successors	= (Node**) malloc(nb_nodes * sizeof(Node*));

		for (int i = 0; i < nb_nodes; i++) 
			G->list_successors[i]	= NULL;

		for (int i = 0; i < nb_arcs; i++) 
		{
			fscanf(fp, "%d %d %d", &u, &v, &w);
			Node* s					= (Node*) malloc(sizeof(Node)); 
			s->id					= v;
			s->weight				= w;
			s->successor			= G->list_successors[u];
			G->list_successors[u]	= s;
		}
	}
	else printf("File not found.");
	fclose(fp);
}

void dijkstra_without_heap(Graph* G, int source, int* dist_array) 
{
	bool *states_array	= (bool*) malloc(G->nb_nodes*sizeof(bool));
	dijkstra_initialize(G, dist_array, states_array, source);

	List processing_list;
	initialize(&processing_list);
	add_via_head(&processing_list, source);

	while(!is_void(&processing_list)) 
	{
		int	 u	= get_argmin_in_list (dist_array, &processing_list);
		delete_element(&processing_list, u);
		
		Node* outgoing_arc = G->list_successors[u];
		while(outgoing_arc != NULL)
		{
			int v = outgoing_arc->id;
			if(dist_array[u] + outgoing_arc->weight < dist_array[v])
			{
				dist_array[v] = dist_array[u] + outgoing_arc->weight;
				if (states_array[v] == false)
				{
					add_via_head(&processing_list, v);
					states_array[v] = true;
				}
			}
			outgoing_arc =  outgoing_arc->successor;
		} 
	}
}

void dijkstra_with_heap(Graph* G, int source, int* dist_array) 
{
	bool *states_array	= (bool*) malloc(G->nb_nodes*sizeof(bool));
	dijkstra_initialize(G, dist_array, states_array, source);

	Heap processing_heap;
	create_void_heap(&processing_heap, G->nb_nodes);

	Helement hsource = {source, dist_array[source]};
	insert_heap(&processing_heap, hsource);

	while(processing_heap.size > 0) 
	{
		int u = extract_min(&processing_heap).id;
		
		Node* outgoing_arc = G->list_successors[u];
		while(outgoing_arc != NULL)
		{
			int v = outgoing_arc->id;
			if(dist_array[u] + outgoing_arc->weight < dist_array[v])
			{
				dist_array[v] = dist_array[u] + outgoing_arc->weight;
				Helement hnode = {v, dist_array[v]};
				if (states_array[v] == false)
				{
					insert_heap(&processing_heap, hnode);
					states_array[outgoing_arc->id] = true;
				}
				else
					update_priority_heap(&processing_heap, hnode);
			}
			outgoing_arc =  outgoing_arc->successor;
		} 
	}
}

bool bellman_ford(Graph* G, int source, int* dist_array) 
{
	for (int i = 0; i < G->nb_nodes; i++)
		dist_array[i]  = INFINITY;
	dist_array[source] = 0;

	for (int i = 0; i < G->nb_nodes - 1; i++)
		for (int u = 0; u < G->nb_nodes; u++)
			{
				Node* outgoing_arc = G->list_successors[u];
				while(outgoing_arc != NULL)
				{
					int v = outgoing_arc->id;
					if(dist_array[u] + outgoing_arc->weight < dist_array[v])
						dist_array[v] = dist_array[u] + outgoing_arc->weight;
					
					outgoing_arc =  outgoing_arc->successor;
				}
			}

	for (int i = 0; i < G->nb_nodes; i++)
	{
		Node* outgoing_arc = G->list_successors[i];
		while(outgoing_arc != NULL)
		{
			if(dist_array[i] + outgoing_arc->weight < dist_array[outgoing_arc->id])
				return false;
			outgoing_arc =  outgoing_arc->successor;
		}
	}
	return true;
}

void print_graph(Graph* G) 
{
	for(int i = 0; i < G->nb_nodes; i++) 
	{
		printf("Node %d : ", i+1);
		Node* current = G->list_successors[i];
		while(current != NULL)
		{
			printf("%d, ", current->id);
			current =  current->successor;
		} 
		printf("\n\n");
	}
}

int max_weight_graph(Graph* G)
{
	int max_weight = 0;

	for(int i = 0; i < G->nb_nodes; i++) 
	{
		Node *current = G->list_successors[i];
		while(current != NULL)
		{
			if (max_weight < current->weight)
				max_weight = current->weight;
			current =  current->successor;
		} 
	}
	return max_weight;
}

int get_argmin_in_list (int* distance, List *list)
{	
	int min		= distance[(*list->head).id]; 
	int argmin	= (*list->head).id;
	
	Element *current = list->head->next;

	while(current != NULL)
	{	
		if (min > distance[(*current).id])
		{
			min		= distance[(*current).id];
			argmin	= (*current).id;
		}
		current = current->next;
	}
	return argmin;
}

void dijkstra_initialize(Graph* G, int* dist_array, bool* states_array,  int source)
{
	for (int i = 0; i < G->nb_nodes; i++)
	{
		dist_array[i]  = INFINITY; 
		states_array[i] = false;
	}
	dist_array[source]	= 0;
	states_array[0]		= true;
}
