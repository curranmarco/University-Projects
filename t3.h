#ifndef T3_H_
#define T3_H_


typedef struct edge {
    // the destination of the edge
    int to;
    // weight of the edge
    int weight;
    // pointer to the next edge
    struct edge *next;
} edge;

typedef struct vertex {
    // the stopID of the vertex
    int stopID;
    // the name of the stop
    char stopName[100];
    // the latitude and longitude of the stop
    double latitude;
    double longitude;
    // pointer to the first edge
    struct edge *edges;
} vertex;

int count_lines ( char *fname ); // counts the number of lines in the file of name fname
void removeQuotes ( char *line ); // removes the quotes from the line
void add_edge (int from, int to, int weight); // adds an edge from vertex from to vertex to with weight weights
int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif