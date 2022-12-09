#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vec.h"
#include "header.h"

/* VEC3 FUNCTIONS */
/**************************************************************************/

// Converts struct Vec3 to formatted char *
// Don't forget to free(toString);
char *vec3_tostring(struct Vec3 vector)
{
    char *toString = malloc(3 * 4 + 100);

    sprintf(toString, "[%.2f, %.2f, %.2f]", vector.x, vector.y, vector.z);

    return toString;
}

// Vec3 constructor
struct Vec3 vec3_new(float x, float y, float z)
{
    struct Vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;

    return vec;
}

// Calculates length of vector
float vec3_len(struct Vec3 vector)
{
    float length_square = (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
    return sqrt(length_square);
}

// Adds scalar to vector
struct Vec3 vec3_addscalar(struct Vec3 vector, float scalar)
{
    struct Vec3 result;

    result.x = vector.x + scalar;
    result.y = vector.y + scalar;
    result.z = vector.z + scalar;

    return result;
}

// Adds two vectors
struct Vec3 vec3_addvec(struct Vec3 vector1, struct Vec3 vector2)
{
    struct Vec3 result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;

    return result;
}

// Multiplies a vector by a scalar
struct Vec3 vec3_multscalar(struct Vec3 vector, float scalar)
{
    struct Vec3 result;

    result.x = vector.x * scalar;
    result.y = vector.y * scalar;
    result.z = vector.z * scalar;

    return result;
}

// Calculates the unit vector of a vector
struct Vec3 vec3_unit(struct Vec3 vector)
{
    struct Vec3 result;
    float length = vec3_len(vector);

    result.x = vector.x / length;
    result.y = vector.y / length;
    result.z = vector.z / length;

    return result;
}

/* VECH FUNCTIONS */
/**************************************************************************/

// Converts struct VecH to formatted char *
// Don't forget to free(toString);
char *vech_tostring(struct VecH vector)
{
    char *toString = malloc(3 * 4 + 100);

    sprintf(toString, "[%.2f, %.2f, %.2f, %d]", vector.x, vector.y, vector.z, vector.homo);

    return toString;
}

// VecH constructor for homogeneous vectors
struct VecH vech_new(float x, float y, float z)
{
    struct VecH vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.homo = 0;

    return vec;
}

// VecH constructor for homogeneous points
struct VecH pointh_new(float x, float y, float z)
{
    struct VecH point;
    point.x = x;
    point.y = y;
    point.z = z;
    point.homo = 1;

    return point;
}

// VecH setter for homogeneous vectors
int vech_set(struct VecH *vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->homo = 0;

    return 0;
}

// VecH setter for homogeneous points
int pointh_set(struct VecH *vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->homo = 1;

    return 0;
}

// Calculates length of homogeneous vector
float vech_len(struct VecH vector)
{
    float length_square = (vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z);
    return sqrt(length_square);
}

// Multiplies homogeneous vector by -1
struct VecH vech_neg(struct VecH vector)
{
    struct VecH sub;

    sub.x = -1.0 * vector.x;
    sub.y = -1.0 * vector.y;
    sub.z = -1.0 * vector.z;
    sub.homo = vector.homo;

    return sub;
}

// Adds scalar to homogeneous vector
struct VecH vech_addscalar(struct VecH vector, float scalar)
{
    struct VecH result;

    result.x = vector.x + scalar;
    result.y = vector.y + scalar;
    result.z = vector.z + scalar;
    result.homo = vector.homo;

    return result;
}

// Adds two homogeneous vectors
struct VecH vech_addvec(struct VecH vector1, struct VecH vector2)
{
    struct VecH result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    result.homo = vector1.homo;

    return result;
}

// VecH setter for homogeneous points
void vec3_addvec_s(struct Vec3 *vec1, struct Vec3 vec2)
{
    vec1->x += vec2.x;
    vec1->y += vec2.y;
    vec1->z += vec2.z;
}

// Adds homogeneous point and homogeneous vector
struct VecH vech_addpoint(struct VecH vector1, struct VecH vector2)
{
    struct VecH result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    result.homo = 1;

    return result;
}

// Subtracts two homogeneous vectors
struct VecH vech_subvec(struct VecH vector1, struct VecH vector2)
{
    struct VecH result;

    result.x = vector1.x - vector2.x;
    result.y = vector1.y - vector2.y;
    result.z = vector1.z - vector2.z;
    result.homo = 0;

    return result;
}

float pointh_distpoint(struct VecH point1, struct VecH point2)
{
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2) + pow(point1.z - point2.z, 2));
}

// Subtracts two homogeneous points
struct VecH pointh_subpoint(struct VecH point1, struct VecH point2)
{
    struct VecH result;

    result.x = point1.x - point2.x;
    result.y = point1.y - point2.y;
    result.z = point1.z - point2.z;
    result.homo = 1; // todo doublecheck these homo coords

    return result;
}

// Multiplies a homogeneous vector or point by a scalar
struct VecH vech_multscalar(struct VecH vector, float scalar)
{
    struct VecH result;

    result.x = vector.x * scalar;
    result.y = vector.y * scalar;
    result.z = vector.z * scalar;
    result.homo = vector.homo;

    return result;
}

// Calculates the dot product of two homogeneous vectors
float vech_dot(struct VecH vector1, struct VecH vector2)
{
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

// Calculates the cross product of two homogeneous vectors
struct VecH vech_cross(struct VecH vector1, struct VecH vector2)
{
    struct VecH result;

    result.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
    result.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
    result.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);
    result.homo = vector1.homo;

    return result;
}

// Calculates the unit vector of a homogeneous vector
struct VecH vech_unit(struct VecH vector)
{
    struct VecH result;
    float length = vech_len(vector);

    result.x = vector.x / length;
    result.y = vector.y / length;
    result.z = vector.z / length;
    result.homo = vector.homo;

    return result;
}

// Calculates the absolute value of a vector
struct VecH vech_abs(struct VecH vector)
{
    struct VecH result;

    result.x = abs(vector.x);
    result.y = abs(vector.y);
    result.z = abs(vector.z);
    result.homo = vector.homo;

    return result;
}

/* COLOR FUNCTIONS */
/**************************************************************************/

// Converts struct Vec3 to formatted char *
// Don't forget to free(toString);
char *color_tostring(struct Vec3 color)
{
    char *toString = malloc(50); // todo make all malloc more precise

    sprintf(toString, "[r: %.2f, g: %.2f, b: %.2f]", color.x, color.y, color.z);

    return toString;
}

// Converts colour float values [0,1] to int values [0,maxVal]
int color_transform(float color_val, int maxVal)
{
    if (color_val > 1.0)
    {
        color_val = 1.0;
    }
    int color = color_val * maxVal;

    return color;
}

/* RAY FUNCTIONS */
/**************************************************************************/

// Converts struct Ray to formatted char *
// Don't forget to free(toString);
char *ray_tostring(struct Ray ray)
{
    char *toString = malloc(100);

    sprintf(toString, "S: %s c: %s", vech_tostring(ray.point), vech_tostring(ray.vector));

    return toString;
}

// Gets the value of the ray at 'time' t
// Solves equation: P(t) = A + tb
struct VecH ray_at(struct Ray ray, float t)
{
    struct VecH point;

    point = vech_addpoint(ray.point, vech_multscalar(ray.vector, t));

    return point;
}

/* MATRIX FUNCTIONS */
/**************************************************************************/

// Inverts the given scale matrix
struct Vec3 scale_inverse(struct Vec3 vector)
{
    struct Vec3 result;

    result.x = 1.0 / vector.x;
    result.y = 1.0 / vector.y;
    result.z = 1.0 / vector.z;

    return result;
}

// Inverts the given translation matrix
struct Vec3 translate_inverse(struct Vec3 vector)
{
    struct Vec3 result;

    result.x = -1.0 * vector.x;
    result.y = -1.0 * vector.y;
    result.z = -1.0 * vector.z;

    return result;
}

// Multiply the vector/point by the scale matrix
// Not necessary to multiply whole matrix since many values = 0
struct VecH vech_scale(struct VecH vector, struct Vec3 scale)
{
    struct VecH result;

    result.x = vector.x * scale.x;
    result.y = vector.y * scale.y;
    result.z = vector.z * scale.z;
    result.homo = vector.homo;

    return result;
}

// Multiply the vector and point of a Ray by the scale matrix
struct Ray ray_scale(struct Ray ray, struct Vec3 scale)
{
    struct Ray result;

    result.point = vech_scale(ray.point, scale);
    result.vector = vech_scale(ray.vector, scale);

    return result;
}

// Multiply the vector and point of a Ray by the inverse scale matrix
struct Ray ray_scale_i(struct Ray ray, struct Vec3 scale)
{
    return ray_scale(ray, scale_inverse(scale));
}

// Multiply the vector/point by the translation matrix
// Not necessary to multiply whole matrix since many values = 0
struct VecH vech_translate(struct VecH vector, struct Vec3 translate)
{
    struct VecH result;

    result.x = vector.x + translate.x * vector.homo;
    result.y = vector.y + translate.y * vector.homo;
    result.z = vector.z + translate.z * vector.homo;
    result.homo = vector.homo;

    return result;
}

// Multiply the vector and point of a Ray by the translation matrix
struct Ray ray_translate(struct Ray ray, struct Vec3 translate)
{
    struct Ray result;

    result.point = vech_translate(ray.point, translate);
    result.vector = vech_translate(ray.vector, translate);

    return result;
}

// Multiply the vector and point of a Ray by the inverse translation matrix
struct Ray ray_translate_i(struct Ray ray, struct Vec3 translate)
{
    return ray_translate(ray, translate_inverse(translate));
}

struct Ray ray_ts_i(struct Ray ray, struct Vec3 translate, struct Vec3 scale)
{
    return ray_scale_i(ray_translate_i(ray, translate), scale);
}

struct VecH vech_invtranspose(struct VecH vector, struct Vec3 scale)
{
    struct VecH result;

    result.x = vector.x * (1 / scale.x);
    result.y = vector.y * (1 / scale.y);
    result.z = vector.z * (1 / scale.z);
    result.homo = 0;

    return result;
}
