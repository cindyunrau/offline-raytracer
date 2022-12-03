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
    float whatever[4];
    int specular_exponent;
};

struct Light
{
    char name[20 + 1];
    float position[3];
    float intensity[3];
};

struct Data
{
    float planes[5];
    int res[2];
    struct Sphere spheres[15];
    struct Light lights[10];
    int numSpheres;
    int numLights;
    float background_color[3];
    float ambient[3];
    char *out_filename;
};

struct Data processFile(char *filename);

float sphere_intersection(struct VecH center, float radius, struct Ray ray);

float sphere_intersection_v(struct Ray ray, int verbose);

struct Vec3 ray_color(struct Ray ray, struct Sphere *spheres, int numSpheres);

// void generate_background(int *pixels, int width, int height, int r, int g, int b);

// int save_image(int image_width, int image_height, float view_width, float view_height, float near_plane, char *filename);
#endif