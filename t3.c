#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "t3.h"

vertex *graph = NULL;
int numVertices = 4807;
int maxStop = 7667;
int numberEdges = 0;

//counts the number of lines in the file of name fname
int count_lines ( char *fname ){
    FILE *file = fopen(fname, "r");

    if (file == NULL){
        printf("Error opening file\n");
        return -1;
    }

    //variables to store the number of lines and the current line
    int count = 0;
    char line[256];

    // Skip the header line
    fgets(line, sizeof(line), file);

    //iterate over all the lines
    while (fgets(line, sizeof(line), file)){
        count++;
    }

    fclose(file);
    return count;
}

void removeQuotes(char *str){
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';  // Null-terminate the string
    //printf("Debug: After removing quotes: %s\n", str); // Debug print
}
//loads the vertices from the CSV file of name fname
int load_vertices ( char *fname ){
    FILE *file = fopen(fname, "r");

    if (file == NULL){
        printf("Error opening file\n");
        return -1;
    }
    //substract 1 from the number of vertices because of the header line
    numVertices = count_lines(fname) - 1; 
    printf("Number of vertices: %d\n", numVertices); // Debug print
    //check if the number of vertices is less than or equal to 0
    if(numVertices <= 0){
        printf("Error: Number of vertices is less than or equal to 0\n"); // Debug print
        fclose(file);
        return -1;
    }

    //allocate memory for the graph
    graph = malloc(numVertices * sizeof(vertex));
    if (graph == NULL){
        printf("Error allocating memory for graph\n");
        fclose(file);
        return -1;
    }

    //read the header line
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); 

    //read the vertices
    for (int i = 0; i < numVertices; i++){
        //stopName is a temporary variable to store the stopName
        char stopName[100];
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf("Error reading vertex data at line %d\n", i + 1);
            free(graph);
            fclose(file);
            return -1;  
        }

        // Remove quotes and parse the line
        removeQuotes(buffer);
        //printf("Debug: Line %d after removing quotes: %s\n", i + 1, buffer); // Debug print
        if (sscanf(buffer, "%d,%99[^,],%lf,%lf",
                   &graph[i].stopID, stopName, &graph[i].latitude, &graph[i].longitude) != 4) {
            printf("Error parsing vertex data at line %d: %s\n", i + 1, buffer);
            free(graph);
            fclose(file);
            return -1;  // Indicate error in parsing
        }

        //copy the stopName to the graph
        strncpy(graph[i].stopName, stopName, sizeof(graph[i].stopName));
        graph[i].edges = NULL;
    }

    fclose(file);
    //printf("Debug: Successfully loaded vertices\n"); // Debug print
    return 0;
}

void add_edge (int from, int to, int weight){
    //printf("Debug: Entering add_edge with from=%d, to=%d, weight=%d\n", from, to, weight); // Debug print

    if (from < 0 || from >= numVertices || to < 0 || to >= numVertices) {
        //printf("Error: Invalid vertex index from=%d, to=%d\n", from, to);
        return;
    }

    // Create a new edge and add it to the start of the list
    edge *newEdge = malloc(sizeof(edge));
    //check if the memory was allocated successfully
    if (newEdge == NULL){
        printf("Error allocating memory for edge\n");
        return;
    }

    //add the edge to the graph
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from].edges;
    graph[from].edges = newEdge;
    numberEdges++;

    //printf("Debug: Added edge from %d to %d with weight %d\n", from, to, weight); // Debug print
}

//loads the edges from the CSV file of name fname
int load_edges ( char *fname ){
    FILE *file = fopen(fname, "r");

    if (file == NULL){
        printf("Error opening file\n");
        return -1;
    }

    //variables to store the data of the edges
    int from, to, weight;

    //skip the header line
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    //read the edges
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        // Remove quotes and parse the line
        removeQuotes(buffer);
        //printf("Debug: Parsing edge data: %s\n", buffer); // Debug print
        if (sscanf(buffer, "%d,%d,%d", &from, &to, &weight) != 3) {
            printf("Error parsing edge data: %s\n", buffer);
            fclose(file);
            return -1;  // Indicate error in parsing
        }

        // Add both directions as it is an undirected graph 
        //printf("Debug: Adding edge from %d to %d with weight %d\n", from, to, weight); // Debug print
        add_edge(from, to, weight);
        add_edge(to, from, weight);
    }

    fclose(file);
    //printf("Debug: Successfully loaded edges\n"); // Debug print
    printf("Number of edges: %d\n", numberEdges);
    return 0;
}



// prints the shortest path between startNode and endNode, if there is any
void shortest_path(int startNode, int endNode){
    //variables to store the distance and the previous node
    int dist[4807];
    int prev[4807]; 
    bool *visited = malloc(numVertices * sizeof(bool));

    //check if the memory was allocated successfully
    if (!visited){
        printf("Error allocating memory for visited array\n");
        return;
    }

    //initialize the arrays
    for (int i = 0; i < numVertices; i++){
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    //initialize the start node
    dist[startNode] = 0;

    //iterate over all the vertices
    for (int i = 0; i < numVertices; i++){
        //find the closest node
        int closestNode = -1;
        int shortestDistance = INT_MAX;

        //iterate over all the vertices
        for (int j = 0; j < numVertices; j++){
            //if the node is not visited and the distance is smaller than the current shortest distance, we update the shortest distance
            if (!visited[j] && dist[j] < shortestDistance){
                closestNode = j;
                shortestDistance = dist[j];
            }
        }

        //if we didn't find any unvisited node with a distance smaller than INT_MAX, we break
        if (closestNode == -1){
            break;
        }

        //mark the closest node as visited
        visited[closestNode] = true;

        //iterate over all the edges of the closest node
        edge *edge = graph[closestNode].edges;

        while (edge){
            //if the node is not visited and the distance to the node is smaller than the current distance, we update the distance
            int v = edge->to;
            int weight = edge->weight;

            //if the node is not visited and the distance is smaller than the current distance, we update the distance
            if(!visited[v] && dist[closestNode] + weight < dist[v]){
                dist[v] = dist[closestNode] + weight;
                prev[v] = closestNode;
            }
            //move to the next edge
            edge = edge->next;
        }
    }

    //Print the path and the total distance 
    if (dist[endNode] == INT_MAX){
        printf("No path found\n");
        return;
    }

    //store the path in an array
    int path[4807];
    int pathLength = 0;

    //iterate over the previous nodes to store the path
   int currentNode = endNode;   
   while (currentNode != -1){
        path[pathLength++] = currentNode;
        currentNode = prev[currentNode];
    }

    printf("The shortest path from %d to %d is:\n", startNode, endNode);

    //print the path in reverse order
    for (int i = pathLength -1; i >= 0; i--){
        int stopID = path[i];
        printf("%d %s %.6f %.6f\n",
        graph[stopID].stopID, graph[stopID].stopName,
        graph[stopID].latitude, graph[stopID].longitude);
    }

    int totalDistance = dist[endNode];
    printf("\nTotal distance: %d\n", totalDistance);

    free(visited);

}

// frees any memory that was used
void free_memory ( void ){
    //iterate over all the vertices and free the edges
    for (int i = 0; i < numVertices; i++){
        //free the edges
        edge *current = graph[i].edges;
        while(current){
            edge *nextEdge = current->next;
            free(current);
            current = nextEdge; 
        }
    }

    //free the graph
    free(graph);

    printf("Memory freed\n");

}