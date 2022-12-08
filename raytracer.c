// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vec.h"
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

    const int image_width = data.res[0];
    const int image_height = data.res[1];
    float view_height = abs(data.planes[3]) + abs(data.planes[4]);
    float view_width = abs(data.planes[1]) + abs(data.planes[2]);
    float near = data.planes[0];

    struct VecH eye = pointh_new(0.0, 0.0, 0.0);

    FILE *out_file;

    int i, j;

    printf("%sSaving image [%s]: %d x %d px\n", prefix_title, data.out_filename, image_width, image_height);

    char str[100];
    strcpy(str, "./results/");
    strcat(str, data.out_filename);

    out_file = fopen(str, "w"); // todo take out
    if (!out_file)
    {
        printf("%sProblem with file [%s], cannot be opened.\n", prefix_body, str);
        exit(1);
    }

    fprintf(out_file, "P3\n");
    fprintf(out_file, "%i %i\n", image_width, image_height);

    fprintf(out_file, "255\n");

    printf("%sRows generated: ", prefix_body);
    printf("[                    ] ");
    printf("%3i %c", 0, 37);

    for (i = image_height - 1; i >= 0; --i)
    {
        for (j = 0; j < image_width; ++j)
        {
            float u = -1.0 * (view_width / 2) + ((view_width / 2) * (2 * j) / image_width);
            float v = -1.0 * (view_height / 2) + ((view_height / 2) * (2 * i) / image_height);

            struct Ray ray;
            ray.point = eye;
            ray.vector = vech_new(u, v, -1.0 * near);

            struct Vec3 pixel_color = ray_color(ray, data.spheres, data.numSpheres, data.lights, data.numLights, data.ambient, data.background_color);
            fprintf(out_file, " %d %d %d\n", color_transform(pixel_color.x, 255), color_transform(pixel_color.y, 255), color_transform(pixel_color.z, 255));
        }
        fprintf(out_file, "\n");

        // Progress Bar
        printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        int completion = (((float)image_height - (float)i) / (float)image_height) * 100.0;
        printf("[%.*s", completion / 5, "####################");
        printf("%.*s] ", 20 - completion / 5, "                    ");
        printf("%3i %c", completion, 37);

        fflush(stdout);
    }
    fclose(out_file);

    printf("\n");
    printf("%sImage Saved [%s]:\n", prefix_title, data.out_filename);

    return 0;
}