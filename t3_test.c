#include "t3.h"
#include <stdio.h>
#include <stdlib.h>	

int main ( int argc, char *argv[] ) {
    //printf("Debug: Entered main function\n"); // Debug print

    if ( argc < 3 ) {
        printf("usage: ./bus VERTICES EDGES\n");
        return EXIT_FAILURE;
    }

    //printf("Debug: Loading vertices from %s\n", argv[1]); // Debug print
    if ( load_vertices( argv[1] ) != 0 ) {
        printf("Failed to load vertices\n");
        return EXIT_FAILURE;
    }

    //printf("Debug: Loading edges from %s\n", argv[2]); // Debug print
    if ( load_edges( argv[2] ) != 0 ) {
        printf("Failed to load edges\n");        
        return EXIT_FAILURE;
    }

    // get the start and end point
    printf("Please enter starting bus stop > ");
    int startingNode;
    if (scanf("%d", &startingNode) != 1) {
        printf("Error reading starting bus stop\n");
        return EXIT_FAILURE;
    }
    //printf("Debug: Starting bus stop: %d\n", startingNode); // Debug print

    printf("Please enter destination bus stop > ");
    int endingNode;
    if (scanf("%d", &endingNode) != 1) {
        printf("Error reading destination bus stop\n");
        return EXIT_FAILURE;
    }
    //printf("Debug: Destination bus stop: %d\n", endingNode); // Debug print

    //printf("Debug: Calculating shortest path\n"); // Debug print
    shortest_path(startingNode, endingNode);

    //printf("Debug: Freeing memory\n"); // Debug print
    free_memory();

    //printf("Debug: Exiting program\n"); // Debug print
    return EXIT_SUCCESS;
}
