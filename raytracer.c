// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("%sPlease specify a single file, %s files given.\n", prefix_title, argc);
        exit(0);
    }
    else if (argc > 2)
    {
        printf("%sPlease specify a file to process.\n", prefix_title);
        exit(0);
    }
    printf("%sProcess File: [%s]\n", prefix_title, argv[1]);
    char *filename = argv[1];

    struct Data data;
    data = processFile(filename);

    // int width = data.res[0];  // nCols
    // int height = data.res[1]; // nRows

    // int numPixels = width * height * 3;
    int pixels[400 * 400 * 3] = {0};
    // memset(pixels, 0, width * height * 3 * sizeof(int));
    generate_background(pixels, 400, 400, 255, 0, 0);

    save_image(400, 400, "testoutput.ppm", pixels);

    return 0;
}