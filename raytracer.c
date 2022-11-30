// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"



// Driver code
int main( int argc, char *argv[] ) {
    if( argc > 2 ) {
        printf("%sPlease specify a single file, %s files given.\n", prefix_title, argc);
        exit(0);
    }
    else if (argc > 2) {
        printf("%sPlease specify a file to process.\n", prefix_title);
        exit(0);
    }
    printf("%sProcess File: [%s]\n", prefix_title, argv[1]);
    char *filename = argv[1];

    // File Processing


    processFile(filename);

    

    return 0;
}