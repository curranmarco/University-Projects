#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t1.h"

int printed = 0;

//Function to create a node for our graph with a given vertex 
Node* createNode (int vertex){
    //Allocate memory for the new node
    Node* newNode = (Node*) malloc(sizeof(Node));
    //Initialize the new node
    newNode->vertex = vertex;
    newNode->next = NULL;
    //Return the new node
    return newNode;
}

//Function to create a graph with a given number of nodes
Graph* create_graph (int num_nodes){
    //Allocate memory for the graph
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    //Initialize the graph variables
    graph->numberNodes = num_nodes;
    graph->adjList = (Node**) malloc(num_nodes * sizeof(Node*));
    graph->visited = (bool*) malloc(num_nodes * sizeof(bool));

    //Initialize the graph
    for (int i = 0; i < num_nodes; i++){
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }
    //Return the graph
    return graph;
}

void add_edge (Graph* g, int from, int to){
    //Create a new node with the vertex we want to add
    Node* newNode = createNode(to);
    //Add the new node to the adjacency list of the vertex we are adding the edge from
    newNode->next = g->adjList[from];
    g->adjList[from] = newNode;
}

void bfs(Graph* g, int origin){
    //Check if the graph is empty
    if (g == NULL || g->adjList == NULL){
        printf("Graph is empty\n");
        return;
    }

    //Allocate memory for the queue
    int* queue = (int*) malloc(g->numberNodes * sizeof(int));
    //Check if memory allocation failed
    if (queue == NULL){
        printf("Memory allocation failed\n");
        return;
    }

    //Initialize the front and rear of the queue
    int front = 0;
    int rear = 0;

    //Mark all nodes as not visited
    for (int i = 0; i < g-> numberNodes; i++){
        g->visited[i] = false;
    }

    //Enqueue the origin node
    queue[rear++] = origin;
    g->visited[origin] = true;

    //Here we start doing our BFS search 
    printf("BFS: ");
    //While the queue is not empty
    while (front < rear){
        //Dequeue the front node
        int current = queue[front++];
        //Print the current node we are visiting
        printf("%c", current + 'A');
        printf(" ");
        //Point to the adjacency list of the current node
        Node* temp = g->adjList[current];
        //For each node adjacent to the current node
        while (temp != NULL){
            //If the node has not been visited
            if (!g->visited[temp->vertex]){
                //Mark the node as visited and enqueue it
                queue[rear++] = temp->vertex;
                g->visited[temp->vertex] = true;
            }
            //Move to the next node in the adjacency list
            temp = temp->next;
        }
    }
    //Free the memory allocated for the queue 
    printf("\n");
    free(queue);
}


void dfs(Graph* g, int origin){
    //Mark the origin node as visited
    g->visited[origin] = true;
    //Print the origin node
    if (printed == 0){
        printf("DFS: ");
        printed = 1;
    }
    printf("%c ", origin + 'A');
    //For each node adjacent to the origin node
    Node* temp = g->adjList[origin];
    while (temp != NULL){
        //If the node has not been visited
        if (!g->visited[temp->vertex]){
            //Recursively call the dfs function on the node
            dfs(g, temp->vertex);
        }
        temp = temp->next;
    }
}

void delete_graph(Graph* g){
    //Free the memory allocated for the adjacency list of each node
    for (int i = 0; i < g->numberNodes; i++){
        Node* current = g->adjList[i];
        while (current != NULL){
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    //Free the memory allocated for the adjacency list and the visited array
    free(g->adjList);
    free(g->visited);
    free(g);
}

