#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global constants
const char *prefix_title = ":RT:--    ";
const char *prefix_body = ":-----       ";
const char *plane_key[6] = {"NEAR", "LEFT", "RIGHT", "BOTTOM", "TOP"};
const char *res_key = "RES";
const char *sphere_key = "SPHERE";
const char *light_key = "LIGHT";
const char *background_key = "BACK";
const char *ambient_key = "AMBIENT";
const char *output_key = "OUTPUT";

// structs

struct Vec3
{
    float x;
    float y;
    float z;
};

struct Ray
{
    struct Vec3 point;
    struct Vec3 direction;
};

void druck(char *string)
{
    char *prefix_title = ":RT:--    ";
    printf("%s%s\n", prefix_title, string);
}

struct Data processFile(char *filename)
{
    FILE *file;
    int i;

    file = fopen(filename, "r");

    if (!file)
    {
        printf("%sProblem with file [%s], cannot be opened.\n", prefix_title, filename);
        exit(0);
    }

    printf("%sFile Contents:\n", prefix_title);

    char *line = NULL;
    size_t len = 0;

    char *token;
    const char space[2] = " ";
    const char newline[2] = "\n";

    struct Data data;

    int numSpheres = 0;
    int numLights = 0;
    int key_found;

    while (getline(&line, &len, file) != -1)
    {
        key_found = 0;

        token = strtok(line, space);

        for (i = 0; i < 5; i++)
        {
            if (!key_found && !strcmp(token, plane_key[i]))
            {
                data.planes[i] = atof(strtok(NULL, newline));
                key_found = 1;
            }
        }
        if (!key_found && !strcmp(token, res_key))
        {
            data.res[0] = atoi(strtok(NULL, space));
            data.res[1] = atoi(strtok(NULL, space));
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, sphere_key))
        {
            token = strtok(NULL, space);
            strcpy(data.spheres[numSpheres].name, strdup(token));
            data.spheres[numSpheres].position[0] = atof(strtok(NULL, space));
            data.spheres[numSpheres].position[1] = atof(strtok(NULL, space));
            data.spheres[numSpheres].position[2] = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale[0] = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale[1] = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale[2] = atof(strtok(NULL, space));
            data.spheres[numSpheres].color[0] = atof(strtok(NULL, space));
            data.spheres[numSpheres].color[1] = atof(strtok(NULL, space));
            data.spheres[numSpheres].color[2] = atof(strtok(NULL, space));
            data.spheres[numSpheres].whatever[0] = atof(strtok(NULL, space));
            data.spheres[numSpheres].whatever[1] = atof(strtok(NULL, space));
            data.spheres[numSpheres].whatever[2] = atof(strtok(NULL, space));
            data.spheres[numSpheres].whatever[3] = atof(strtok(NULL, space));
            data.spheres[numSpheres].specular_exponent = atoi(strtok(NULL, space));

            numSpheres++;
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, light_key))
        {
            token = strtok(NULL, space);
            strcpy(data.lights[numLights].name, strdup(token));
            data.lights[numLights].position[0] = atof(strtok(NULL, space));
            data.lights[numLights].position[1] = atof(strtok(NULL, space));
            data.lights[numLights].position[2] = atof(strtok(NULL, space));
            data.lights[numLights].intensity[0] = atof(strtok(NULL, space));
            data.lights[numLights].intensity[1] = atof(strtok(NULL, space));
            data.lights[numLights].intensity[2] = atof(strtok(NULL, space));

            numLights++;
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, background_key))
        {
            data.background_color[0] = atof(strtok(NULL, space));
            data.background_color[1] = atof(strtok(NULL, space));
            data.background_color[2] = atof(strtok(NULL, space));
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, ambient_key))
        {
            data.ambient[0] = atof(strtok(NULL, space));
            data.ambient[1] = atof(strtok(NULL, space));
            data.ambient[2] = atof(strtok(NULL, space));
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, output_key))
        {
            token = strtok(NULL, newline);
            data.out_filename = strdup(token);
            key_found = 1;
        }
    }

    printf("%sVariables processed from file: \n", prefix_title);
    printf("%sPlanes:       -%.1f- -%.1f- -%.1f- -%.1f- -%.1f-\n", prefix_body, data.planes[0], data.planes[1], data.planes[2], data.planes[3], data.planes[4]);
    printf("%sResolution:   -%d- -%d-\n", prefix_body, data.res[0], data.res[1]);
    for (i = 0; i < numSpheres; i++)
    {
        printf("%sSphere:       -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%i-\n", prefix_body, data.spheres[i].name, data.spheres[i].position[0], data.spheres[i].position[1], data.spheres[i].position[2], data.spheres[i].scale[0], data.spheres[i].scale[1], data.spheres[i].scale[2], data.spheres[i].color[0], data.spheres[i].color[1], data.spheres[i].color[2], data.spheres[i].whatever[0], data.spheres[i].whatever[1], data.spheres[i].whatever[2], data.spheres[i].whatever[3], data.spheres[i].specular_exponent);
    }
    for (i = 0; i < numLights; i++)
    {
        printf("%sLight:        -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f- -%.1f-\n", prefix_body, data.lights[i].name, data.lights[i].position[0], data.lights[i].position[1], data.lights[i].position[2], data.lights[i].intensity[0], data.lights[i].intensity[1], data.lights[i].intensity[2]);
    }
    printf("%sBackground:   -%.1f- -%.1f- -%.1f-\n", prefix_body, data.background_color[0], data.background_color[1], data.background_color[2]);
    printf("%sAmbient:      -%.1f- -%.1f- -%.1f-\n", prefix_body, data.ambient[0], data.ambient[1], data.ambient[2]);
    printf("%sOutput File:  -%s-\n", prefix_body, data.out_filename);

    fclose(file);

    return data;
}

void generate_background(int *pixels, int width, int height, int r, int g, int b)
{
    printf("%sGenerating Background Color: [%d,%d,%d]\n", prefix_title, r, g, b);

    float scale = 128.0 / 200.0;
    int k = 0;
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            pixels[k] = r;
            pixels[k + 1] = g;
            pixels[k + 2] = b;
            k = k + 3;
        }
    }

    printf("%sDone generating background\n", prefix_title);
}

int save_image(int width, int height, char *filename, int *pixels)
{
    FILE *out_file;

    int i, j;

    printf("Saving image [%s]: %d x %d\n", filename, width, height);

    out_file = fopen(filename, "w");
    if (!out_file)
    {
        printf("%sProblem with file [%s], cannot be opened.\n", prefix_title, filename);
        exit(1);
    }

    fprintf(out_file, "P3\n");
    fprintf(out_file, "%i %i\n", width, height);
    fprintf(out_file, "255\n");
    int k = 0;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fprintf(out_file, " %d %d %d\n", pixels[k], pixels[k + 1], pixels[k + 2]);
        }
        fprintf(out_file, "\n");
    }
    fclose(out_file);
}

int draw_sphere(struct Vec3 center, float radius)
{
}