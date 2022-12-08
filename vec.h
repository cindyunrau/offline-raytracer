#ifndef RT_VEC_H
#define RT_VEC_H

/* STRUCTS */
/**************************************************************************/

// Vector of floats, size 3
struct Vec3
{
    float x;
    float y;
    float z;
};

// Homogeneous vector or point, size 4
// homo = 0 => vector
// homo = 1 => point
struct VecH
{
    float x;
    float y;
    float z;
    int homo;
};

// Simulated ray of light, consisting of a homogeneous point and a homogeneous vector
struct Ray
{
    struct VecH point;
    struct VecH vector;
};

/* VEC3 FUNCTIONS */
/**************************************************************************/

// Converts struct Vec3 to formatted char *
// Don't forget to free(toString);
char *vec3_tostring(struct Vec3 vector);

// Vec3 constructor
struct Vec3 vec3_new(float x, float y, float z);

// Calculates length of vector
float vec3_len(struct Vec3 vector);

// Adds scalar to vector
struct Vec3 vec3_addscalar(struct Vec3 vector, float scalar);

// Adds two vectors
struct Vec3 vec3_addvec(struct Vec3 vector1, struct Vec3 vector2);

// Multiplies a vector by a scalar
struct Vec3 vec3_multscalar(struct Vec3 vector, float scalar);

// Calculates the unit vector of a vector
struct Vec3 vec3_unit(struct Vec3 vector);

/* VECH FUNCTIONS */
/**************************************************************************/

// Converts struct VecH to formatted char *
// Don't forget to free(toString);
char *vech_tostring(struct VecH vector);

// VecH constructor for homogeneous vectors
struct VecH vech_new(float x, float y, float z);

// VecH constructor for homogeneous points
struct VecH pointh_new(float x, float y, float z);

// VecH setter for homogeneous vectors
int vech_set(struct VecH *vec, float x, float y, float z);

// VecH setter for homogeneous points
int pointh_set(struct VecH *vec, float x, float y, float z);

// Calculates length of homogeneous vector
float vech_len(struct VecH vector);

// Multiplies homogeneous vector by -1
struct VecH vech_neg(struct VecH vector);

// Adds scalar to homogeneous vector
struct VecH vech_addscalar(struct VecH vector, float scalar);

// Adds two homogeneous vectors
struct VecH vech_addvec(struct VecH vector1, struct VecH vector2);

// Adds homogeneous point and homogeneous vector
struct VecH vech_addpoint(struct VecH vector1, struct VecH vector2);

// Subtracts two homogeneous vectors
struct VecH vech_subvec(struct VecH vector1, struct VecH vector2);

// Subtracts two homogeneous points
struct VecH pointh_subpoint(struct VecH point1, struct VecH point2);

// Multiplies a homogeneous vector or point by a scalar
struct VecH vech_multscalar(struct VecH vector, float scalar);

// Calculates the dot product of two homogeneous vectors
float vech_dot(struct VecH vector1, struct VecH vector2);

// Calculates the cross product of two homogeneous vectors
struct VecH vech_cross(struct VecH vector1, struct VecH vector2);

// Calculates the unit vector of a homogeneous vector
struct VecH vech_unit(struct VecH vector);

// Calculates the absolute value of a vector
struct VecH vech_abs(struct VecH vector);

/* COLOR FUNCTIONS */
/**************************************************************************/

// Converts struct Vec3 to formatted char *
// Don't forget to free(toString);
char *color_tostring(struct Vec3 color);

// Converts colour float values [0,1] to int values [0,maxVal]
int color_transform(float color_val, int maxVal);

/* RAY FUNCTIONS */
/**************************************************************************/

// Converts struct Ray to formatted char *
// Don't forget to free(toString);
char *ray_tostring(struct Ray ray);

// Gets the value of the ray at 'time' t
// Solves equation: P(t) = A + tb
struct VecH ray_at(struct Ray ray, float t);

/* MATRIX FUNCTIONS */
/**************************************************************************/

// Inverts the given scale matrix
struct Vec3 scale_inverse(struct Vec3 vector);

// Inverts the given translation matrix
struct Vec3 translate_inverse(struct Vec3 vector);

// Multiply the vector/point by the scale matrix
struct VecH vech_scale(struct VecH vector, struct Vec3 scale);

// Multiply the vector and point of a Ray by the scale matrix
struct Ray ray_scale(struct Ray ray, struct Vec3 scale);

// Multiply the vector and point of a Ray by the inverse scale matrix
struct Ray ray_scale_i(struct Ray ray, struct Vec3 scale);

// Multiply the vector/point by the translation matrix
struct VecH vech_translate(struct VecH vector, struct Vec3 translate);

// Multiply the vector and point of a Ray by the translation matrix
struct Ray ray_translate(struct Ray ray, struct Vec3 translate);

// Multiply the vector and point of a Ray by the inverse translation matrix
struct Ray ray_translate_i(struct Ray ray, struct Vec3 translate);

struct Ray ray_ts_i(struct Ray ray, struct Vec3 translate, struct Vec3 scale);

void vec3_addvec_s(struct Vec3 *vec1, struct Vec3 vec2);

float pointh_distpoint(struct VecH point1, struct VecH point2);

struct VecH vech_invtranspose(struct VecH vector, struct Vec3 scale);

#endif