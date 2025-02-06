#ifndef T1_H_
#define T1_H_

#include <stdbool.h>

//Node structure
typedef struct Node {
    //Vertex of the node
    int vertex;
    //Pointer to the next node
    struct Node* next;
} Node;

//Graph structure
typedef struct Graph{
    //Number of nodes in the graph
    int numberNodes;
    //Array of pointers to the adjacency list of each node
    Node** adjList;
    //Array of booleans to keep track of which nodes have been visited
    bool *visited;
} Graph;

Node* createNode (int vertex); // creates a node with a given vertex
Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph* g); //deletes the graph and frees the memory


#endif