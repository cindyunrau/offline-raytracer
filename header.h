#ifndef RT_UTIL_H
#define RT_UTIL_H

const char *prefix_title;
const char *prefix_body;

struct Sphere
{
    char name[20 + 1];
    struct Vec3 position;
    struct Vec3 scale;
    struct Vec3 color;
    float lighting[4];
    int specular_exponent;
};

struct Light
{
    char name[20 + 1];
    struct VecH position;
    struct Vec3 intensity;
};

struct Data
{
    float planes[5];
    int res[2];
    struct Sphere spheres[15];
    struct Light lights[10];
    int numSpheres;
    int numLights;
    struct Vec3 background_color;
    struct Vec3 ambient;
    char *out_filename;
};

struct Data processFile(char *filename);

struct Vec3 ray_color(struct Ray ray, struct Sphere *spheres, int numSpheres, struct Light *lights, int numLights, struct Vec3 ambient, struct Vec3 background_color, int depth);

int is_empty(char *s);

#endif