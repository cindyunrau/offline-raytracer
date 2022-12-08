#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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
    char line[100];

    char *token;
    const char delim[10] = " \t\n\r\v\f";

    char *dataTemp[20];
    struct Data data;

    int numSpheres = 0;
    int numLights = 0;
    int key_found;

    while (fgets(line, len, file))
    {
        key_found = 0;

        token = strtok(line, delim);

        if (token == NULL || is_empty(token))
        {
            key_found = 1;
        }

        for (i = 0; i < 5; i++)
        {
            if (!key_found && !strcmp(token, plane_key[i]))
            {
                token = strtok(NULL, delim);
                int matches = 0;
                while (token != NULL)
                {
                    if (!is_empty(token))
                    {
                        data.planes[i] = atof(token);
                        matches++;
                    }
                    token = strtok(NULL, delim);
                }
                key_found = 1;
            }
        }
        if (!key_found && !strcmp(token, res_key))
        {
            token = strtok(NULL, delim);
            int matches = 0;
            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    data.res[matches] = atoi(token);
                    matches++;
                }
                token = strtok(NULL, delim);
            }
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, sphere_key))
        {
            token = strtok(NULL, delim);
            int matches = 0;

            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    dataTemp[matches] = token;
                    matches++;
                }
                token = strtok(NULL, delim);
            }
            strcpy(data.spheres[numSpheres].name, strdup(dataTemp[0]));
            data.spheres[numSpheres].position = vec3_new(atof(dataTemp[1]), atof(dataTemp[2]), atof(dataTemp[3]));
            data.spheres[numSpheres].scale = vec3_new(atof(dataTemp[4]), atof(dataTemp[5]), atof(dataTemp[6]));
            data.spheres[numSpheres].color = vec3_new(atof(dataTemp[7]), atof(dataTemp[8]), atof(dataTemp[9]));
            data.spheres[numSpheres].lighting[0] = atof(dataTemp[10]);
            data.spheres[numSpheres].lighting[1] = atof(dataTemp[11]);
            data.spheres[numSpheres].lighting[2] = atof(dataTemp[12]);
            data.spheres[numSpheres].lighting[3] = atof(dataTemp[13]);
            data.spheres[numSpheres].specular_exponent = atoi(dataTemp[14]);

            key_found = 1;
            numSpheres++;
        }
        else if (!key_found && !strcmp(token, light_key))
        {
            token = strtok(NULL, delim);
            int matches = 0;

            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    dataTemp[matches] = token;
                    matches++;
                }
                token = strtok(NULL, delim);
            }

            strcpy(data.lights[numLights].name, strdup(dataTemp[0]));
            data.lights[numLights].position = pointh_new(atof(dataTemp[1]), atof(dataTemp[2]), atof(dataTemp[3]));
            data.lights[numLights].intensity = vec3_new(atof(dataTemp[4]), atof(dataTemp[5]), atof(dataTemp[6]));

            numLights++;
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, background_key))
        {
            token = strtok(NULL, delim);
            int matches = 0;

            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    dataTemp[matches] = token;
                    matches++;
                }
                token = strtok(NULL, delim);
            }
            data.background_color = vec3_new(atof(dataTemp[0]), atof(dataTemp[1]), atof(dataTemp[2]));
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, ambient_key))
        {
            token = strtok(NULL, delim);
            int matches = 0;

            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    dataTemp[matches] = token;
                    matches++;
                }
                token = strtok(NULL, delim);
            }
            data.ambient = vec3_new(atof(dataTemp[0]), atof(dataTemp[1]), atof(dataTemp[2]));
            key_found = 1;
        }
        else if (!key_found && !strcmp(token, output_key))
        {
            token = strtok(NULL, delim);
            while (token != NULL)
            {
                if (!is_empty(token))
                {
                    data.out_filename = strdup(token);
                }
                token = strtok(NULL, delim);
            }
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
        printf("%sSphere:       -%s- -%s- -%s- -%s- -%.1f- -%.1f- -%.1f- -%.1f- -%i-\n", prefix_body, data.spheres[i].name, vec3_tostring(data.spheres[i].position), vec3_tostring(data.spheres[i].scale), vec3_tostring(data.spheres[i].color), data.spheres[i].lighting[0], data.spheres[i].lighting[1], data.spheres[i].lighting[2], data.spheres[i].lighting[3], data.spheres[i].specular_exponent);
    }
    for (i = 0; i < numLights; i++)
    {
        printf("%sLight:        -%s- -%s- -%s-\n", prefix_body, data.lights[i].name, vech_tostring(data.lights[i].position), vec3_tostring(data.lights[i].intensity));
    }
    printf("%sBackground:   -%.2f- -%.2f- -%.2f-\n", prefix_body, data.background_color.x, data.background_color.y, data.background_color.z);
    printf("%sAmbient:      -%.2f- -%.2f- -%.2f-\n", prefix_body, data.ambient.x, data.ambient.y, data.ambient.z);
    printf("%sOutput File:  -%s-\n", prefix_body, data.out_filename);

    fclose(file);

    return data;
}

struct Ray transform_ray(struct Ray ray, struct Sphere sphere)
{
    struct Vec3 translate = sphere.position;
    struct Vec3 scale = sphere.scale;

    return ray_ts_i(ray, translate, scale);
}

float intersection_distance(struct Ray ray, int verbose)
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
    if (dis >= 0)
    {
        float x = -1 * (B / A);
        float y = sqrt(dis) / A;
        float t1 = x - y;
        float t2 = x + y;

        if (t1 <= t2 && t1 >= 0.0)
        {
            return t1;
        }
        if (t2 <= t1 && t2 >= 0.0)
        {
            return t2;
        }
    }
    return -1.0;
}

int nearest_intersection(struct Ray ray, struct Sphere *spheres, int numSpheres)
{
    struct Ray rayTemp;

    float currDistance;
    float minDistance = INFINITY;
    int closestObj = -1;

    int p;
    for (p = 0; p < numSpheres; p++)
    {
        rayTemp = transform_ray(ray, spheres[p]);
        currDistance = intersection_distance(rayTemp, 0);

        if (currDistance >= 0.0 && currDistance < minDistance)
        {
            minDistance = currDistance;
            closestObj = p;
        }
    }
    return closestObj;
}

struct Vec3 ray_color(struct Ray ray, struct Sphere *spheres, int numSpheres, struct Light *lights, int numLights, struct Vec3 ambient, struct Vec3 background_color)
{
    int i = nearest_intersection(ray, spheres, numSpheres);

    if (i >= 0)
    {
        struct Ray rayT = transform_ray(ray, spheres[i]);

        float t = intersection_distance(rayT, 0);

        struct VecH intersection = ray_at(ray, t);
        struct VecH intersectionT = ray_at(rayT, t);
        struct VecH intersectionShifted = ray_at(ray, t + 0.0001);

        struct VecH n = vech_unit(vech_invtranspose(intersectionT, spheres[i].scale));

        // Color
        struct Vec3 localColor = vec3_new(spheres[i].color.x, spheres[i].color.y, spheres[i].color.z);
        struct Vec3 localIllum = vec3_new(0.0, 0.0, 0.0);

        // Ambient
        vec3_addvec_s(&localIllum, vec3_new(ambient.x * spheres[i].lighting[0], ambient.y * spheres[i].lighting[0], ambient.z * spheres[i].lighting[0]));

        int k;
        for (k = 0; k < numLights; k++)
        {
            struct VecH L = vech_unit(vech_subvec(lights[k].position, intersectionShifted));

            struct Ray shadowRay;
            shadowRay.point = intersectionShifted;
            shadowRay.vector = L;

            int j = nearest_intersection(shadowRay, spheres, numSpheres);
            int inShadow = 0;

            if (j >= 0)
            {
                struct Sphere closestObj = spheres[j];

                struct Ray shadowRayT = transform_ray(shadowRay, closestObj);
                float t2 = intersection_distance(shadowRayT, 0);

                float lightDistance = pointh_distpoint(lights[k].position, intersection);

                if (lightDistance > t2)
                {
                    inShadow = 1;
                }
            }

            // Local Illumination
            if (!inShadow)
            {
                float ndL = vech_dot(n, L);

                float diffuseS = ndL * spheres[i].lighting[1];
                struct Vec3 diffuse = vec3_multscalar(lights[k].intensity, diffuseS);
                vec3_addvec_s(&localIllum, diffuse);

                // Specular
                struct VecH R = vech_subvec(vech_multscalar(n, 2.0 * ndL), L);
                struct Vec3 specular = vec3_multscalar(lights[k].intensity, pow(vech_dot(R, ray.vector), spheres[i].specular_exponent));
                vec3_addvec_s(&localIllum, vec3_new(specular.x * spheres[i].lighting[2], specular.y * spheres[i].lighting[2], specular.z * spheres[i].lighting[2]));
            }
        }

        // Illumination * Object Color
        struct Vec3 color = vec3_new(localColor.x * localIllum.x, localColor.y * localIllum.y, localColor.z * localIllum.z);

        return color;
    }
    return background_color;
}

// Helper Functions
int is_empty(char *s)
{
    while (*s != '\0')
    {
        if (!isspace(*s))
            return 0;
        s++;
    }
    return 1;
}
