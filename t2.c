#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <limits.h>
#include "t2.h"

// creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
Graph* create_graph(int num_nodes){
    //allocate memory for the graph
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    //check if the memory was allocated
    if (graph == NULL){
        return NULL;
    }

    //initialize the number of nodes
    graph -> numnodes = num_nodes;
    
    //check if the number of nodes is greater than the maximum number of vertices
    if (num_nodes > MAX_VERTICES){
        return NULL;
    }
    
    //initialize the adjacency matrix
    for (int i = 0; i < num_nodes; i++){
        for (int j = 0; j < num_nodes; j++){
            graph -> adj[i][j] = 0;
        }
    }

    return graph;
}

// adds an undirected weighted edge between from and to
void add_edge(Graph *g, int from, int to, int weight){
    //check if the nodes are valid and if the edge already exists
    if (from >= g->numnodes || to >= g->numnodes || g->adj[from][to] != 0){
        return;
    }
    //if valid, add the edge
    g->adj[from][to] = weight;
    g->adj[to][from] = weight;
}

// implements the dijkstra algorithm and prints the order in which the nodes are made permament, and the length of the shortest path between the origin node and all the other nodes
void dijkstra(Graph* g, int origin){
    //allocate memory for the distance and visited arrays
    int* distance = (int*)malloc(g->numnodes * sizeof(int));
    bool* visited = (bool*)malloc(g->numnodes * sizeof(bool));

    //initialize the distance and visited arrays
    for (int i = 0; i < g->numnodes; i++){
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    //initialize the distance of the origin node to 0
    distance[origin] = 0;

    //iterate through all the nodes
    for (int count = 0; count < g->numnodes; count++){
        //initialize the minimum distance and the minimum index
        int min = INT_MAX;
        int minIndex = 0;

        //find the minimum distance
        for (int i = 0; i < g->numnodes; i++){
            //if the node is not visited and the distance is less than the minimum distance
            if (visited[i] == false && distance[i] <=min){
                //update the minimum distance and the minimum index
                min = distance[i];
                minIndex = i;
            }
        }

        //mark the minimum index as visited
        visited[minIndex] = true;
        //update the distance array
        for (int j = 0; j < g->numnodes; j++){
            //if the node is not visited and there is an edge between the minimum index and the node and the distance of the minimum index is not INT_MAX and the sum of the distance of the minimum index and the edge is less than the distance of the node
            if(visited[j] == false && g->adj[minIndex][j] != 0 && distance[minIndex] != INT_MAX && distance[minIndex] + g ->adj[minIndex][j] < distance[j]){
                //update the distance of the node
                distance[j] = distance[minIndex] + g->adj[minIndex][j];
            }
        }
        printf("%c", minIndex + 'A');
        printf(" ");
       
    }
    printf("\n");

    //print the order in which the nodes are made permanent and the length of the shortest path between the origin node and all the other nodes
    for (int i = 0; i < g->numnodes; i++){
        printf("The length of the shortest path between A and %c is %d\n", i + 'A', distance[i]);
    }

    //free the memory allocated for the distance and visited arrays
    free(distance);
    free(visited);

}

void delete_graph(Graph* g){
    //free the memory allocated for the graph
    free(g);
}
