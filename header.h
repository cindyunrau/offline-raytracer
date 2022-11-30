#ifndef RT_UTIL_H
#define RT_UTIL_H

const char *prefix_title;

struct Sphere
{
    char name[20 + 1];
    float position[3];
    float scale[3];
    float color[3];
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
    float background_color[3];
    float ambient[3];
    char *out_filename;
};

struct Data processFile(char *filename);

void generate_background(int *pixels, int width, int height, int r, int g, int b);

int save_image(int width, int height, char *filename, int *pixels);

#endif