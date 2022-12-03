#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vec.h"
#include "header.h"

// Global Constants
const char *prefix_title = ":RT:--    ";
const char *prefix_body = ":-----       ";
const char *plane_key[6] = {"NEAR", "LEFT", "RIGHT", "BOTTOM", "TOP"};
const char *res_key = "RES";
const char *sphere_key = "SPHERE";
const char *light_key = "LIGHT";
const char *background_key = "BACK";
const char *ambient_key = "AMBIENT";
const char *output_key = "OUTPUT";

// Helper Functions
void druck(char *string)
{
    char *prefix_title = ":RT:--    ";
    printf("%s%s\n", prefix_title, string);
}

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if (dup)
    {
        strcpy(dup, str);
    }
    return dup;
}

// Main Functions
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

    const int len = 100;
    char line[len];

    char *token;
    const char space[2] = " ";
    const char newline[2] = "\n";

    struct Data data;

    int numSpheres = 0;
    int numLights = 0;
    int key_found;

    while (fgets(line, len, file))
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
            data.spheres[numSpheres].position.x = atof(strtok(NULL, space));
            data.spheres[numSpheres].position.y = atof(strtok(NULL, space));
            data.spheres[numSpheres].position.z = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale.x = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale.y = atof(strtok(NULL, space));
            data.spheres[numSpheres].scale.z = atof(strtok(NULL, space));
            data.spheres[numSpheres].color.x = atof(strtok(NULL, space));
            data.spheres[numSpheres].color.y = atof(strtok(NULL, space));
            data.spheres[numSpheres].color.z = atof(strtok(NULL, space));
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

    data.numSpheres = numSpheres;
    data.numLights = numLights;

    printf("%sVariables processed from file: \n", prefix_title);
    printf("%sPlanes:       -%.1f- -%.1f- -%.1f- -%.1f- -%.1f-\n", prefix_body, data.planes[0], data.planes[1], data.planes[2], data.planes[3], data.planes[4]);
    printf("%sResolution:   -%d- -%d-\n", prefix_body, data.res[0], data.res[1]);
    for (i = 0; i < numSpheres; i++)
    {
        printf("%sSphere:       -%s- -%s- -%s- -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%i-\n", prefix_body, data.spheres[i].name, vec3_tostring(data.spheres[i].position), vec3_tostring(data.spheres[i].scale), vec3_tostring(data.spheres[i].color), data.spheres[i].whatever[0], data.spheres[i].whatever[1], data.spheres[i].whatever[2], data.spheres[i].whatever[3], data.spheres[i].specular_exponent);
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

// void generate_background(int width, int height, int r, int g, int b)
// {
//     printf("%sGenerating Background Color: [%d,%d,%d]\n", prefix_title, r, g, b);

//     float scale = 128.0 / 200.0;
//     int k = 0;
//     for (int i = 0; i < 200; i++)
//     {
//         for (int j = 0; j < 200; j++)
//         {
//             pixels[k] = r;
//             pixels[k + 1] = g;
//             pixels[k + 2] = b;
//             k = k + 3;
//         }
//     }

//     printf("%sDone generating background\n", prefix_title);
// }

// int save_image(int image_width, int image_height, float view_width, float view_height, float near_plane, char *filename)
// {
//     FILE *out_file;

//     int i, j;

//     printf("%sSaving image [%s]: %d x %d px\n", prefix_title, filename, image_width, image_height);

//     out_file = fopen(filename, "w");
//     if (!out_file)
//     {
//         printf("%sProblem with file [%s], cannot be opened.\n", prefix_body, filename);
//         exit(1);
//     }

//     fprintf(out_file, "P3\n");
//     fprintf(out_file, "%i %i\n", image_width, image_height);
//     fprintf(out_file, "255\n");

//     printf("%sRows generated: ", prefix_body);
//     printf("%3i %c", 0, 37);

//     for (i = image_height - 1; i >= 0; --i)
//     {
//         for (j = 0; j < image_width; ++j)
//         {
//             float u = -1.0 * (view_width / 2) + ((view_width / 2) * (2 * j) / image_width);
//             float v = -1.0 * (view_height / 2) + ((view_height / 2) * (2 * i) / image_height);
//             struct Ray eye;
//             eye.point = pointh_new(0.0, 0.0, 0.0);
//             eye.vector = vech_new(u, v, -1.0);

//             struct Vec3 pixel_color = ray_color(eye);
//             fprintf(out_file, " %d %d %d\n", color_transform(pixel_color.x, 255), color_transform(pixel_color.y, 255), color_transform(pixel_color.z, 255));
//         }
//         fprintf(out_file, "\n");

//         // Completion Percentage Generation (stdout)
//         printf("\b\b\b\b\b");
//         printf("%3i %c", ((i + 1) / image_height * 100), 37);
//         fflush(stdout);
//     }
//     fclose(out_file);

//     printf("\n");
//     printf("%sImage Saved [%s]:\n", prefix_title, filename);
// }

float sphere_intersection_v(struct Ray ray, int verbose)
{
    struct VecH v = ray.vector;
    struct VecH P = ray.point;
    float A = vech_dot(v, v);
    float B = vech_dot(P, v);
    float C = vech_dot(P, P) - 1;
    float dis = (B * B) - (A * C);

    if (verbose == 1)
    {
        printf("A: %.2f \n", A);
        printf("B: %.2f \n", B);
        printf("C: %.2f \n", C);
        printf("dis: %.2f \n", dis);
    }
    return dis;
}

struct Vec3 ray_color(struct Ray ray, struct Sphere *spheres, int numSpheres)
{
    int i;
    for (i = 0; i < numSpheres; i++)
    {
        struct Vec3 translate = spheres[i].position;
        struct Vec3 scale = spheres[i].scale;

        struct Ray rayT = ray_translate_i(ray, translate);
        struct Ray rayS = ray_scale_i(rayT, scale);

        float t = sphere_intersection_v(rayS, 0);

        if (t >= 0.0)
        {
            return spheres[i].color;
        }
    }

    struct Vec3 white = vec3_new(1.0, 1.0, 1.0);

    return white;
}

// printf("t value: %.2f\n", t);
//  struct VecH n = pointh_subpoint(ray_at(ray, t), pointh_new(0.0, 0.0, -1.0));
//  return vec3_multscalar(vec3_addscalar(vec3_new(n.x, n.y, n.z), 1), 0.5);

// struct Vec3 blue = vec3_new(0.5, 0.7, 1.0);
// struct Vec3 purple = vec3_new(0.5, 0.0, 0.5);
// struct Vec3 green = vec3_new(0.0, 1.0, 0.0);
// struct VecH unit = vech_unit(ray.vector);
// float t = 0.5 * (unit.y + 1.0);
// printf("t value: %.2f\n", t);
// return vec3_addvec(vec3_multscalar(white, (1.0 - t)), vec3_multscalar(blue, t));
