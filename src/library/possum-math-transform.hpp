#ifndef POSSUM_MATH_TRANSFORM_HPP
#define POSSUM_MATH_TRANSFORM_HPP

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-mat3.hpp"
#include "possum-math-mat4.hpp"
#include "possum-math-trig.hpp"

typedef PossumMathMat4       PossumMathTransform;
typedef PossumMathTransform* PossumMathTransformPtr;

inline PossumMathTransform
possum_math_transform_translate(
    f32 tx,
    f32 ty,
    f32 tz) {

    PossumMathTransform t = possum_math_mat4_identity();

    t.row0_col3 = tx; 
    t.row1_col3 = ty; 
    t.row2_col3 = tz; 

    return(t);
}

inline PossumMathTransform
possum_math_transform_translate_vector(
    PossumMathVec3Ptr v3_t) {

    PossumMathTransform t = possum_math_mat4_identity();

    f32p v3_t_xyz = v3_t->xyz;

    t.row0_col3 = v3_t_xyz[POSSUM_MATH_VEC3_X]; 
    t.row1_col3 = v3_t_xyz[POSSUM_MATH_VEC3_Y]; 
    t.row2_col3 = v3_t_xyz[POSSUM_MATH_VEC3_Z]; 

    return(t);
}

inline PossumMathTransform
possum_math_transform_scale(
    f32 sx,
    f32 sy,
    f32 sz) {

    PossumMathTransform t = possum_math_mat4_identity();

    t.row0_col0 = sx; 
    t.row1_col1 = sy; 
    t.row2_col2 = sz; 

    return(t);
}

inline PossumMathTransform
possum_math_transform_scale_vector(
    PossumMathVec3Ptr v3_s) {

    PossumMathTransform t = possum_math_mat4_identity();

    f32p v3_s_xyz = v3_s->xyz;

    t.row0_col0 = v3_s_xyz[POSSUM_MATH_VEC3_X]; 
    t.row1_col1 = v3_s_xyz[POSSUM_MATH_VEC3_Y]; 
    t.row2_col2 = v3_s_xyz[POSSUM_MATH_VEC3_Z]; 

    return(t);
}

inline PossumMathTransform
possum_math_transform_translate_and_scale(
    f32 tx,
    f32 ty,
    f32 tz,    
    f32 sx,
    f32 sy,
    f32 sz) {

    PossumMathTransform t = possum_math_mat4_identity();

    t.row0_col0 = sx; 
    t.row0_col3 = tx; 
    t.row1_col1 = sy; 
    t.row1_col3 = ty; 
    t.row2_col2 = sz; 
    t.row2_col3 = tz; 

    return(t);
}

inline PossumMathTransform
possum_math_transform_translate_and_scale_vectors(
    PossumMathVec3Ptr v3_t,
    PossumMathVec3Ptr v3_s) {

    PossumMathTransform t = possum_math_mat4_identity();

    f32p v3_t_xyz = v3_t->xyz;    
    f32p v3_s_xyz = v3_s->xyz;
    
    t.row0_col0 = v3_s_xyz[POSSUM_MATH_VEC3_X];
    t.row0_col3 = v3_t_xyz[POSSUM_MATH_VEC3_X];
    t.row1_col1 = v3_s_xyz[POSSUM_MATH_VEC3_Y];
    t.row1_col3 = v3_t_xyz[POSSUM_MATH_VEC3_Y];
    t.row2_col2 = v3_s_xyz[POSSUM_MATH_VEC3_Z];
    t.row2_col3 = v3_t_xyz[POSSUM_MATH_VEC3_Z];

    return(t);
}

#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX                   0
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY                   1
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ                   2
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ANGLE_RADIANS        3
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R                4
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_SIN_R                5
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ONE_SUB_COS_R        6
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_ONE_SUB_COS_R     7
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_ONE_SUB_COS_R     8
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_ONE_SUB_COS_R     9
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RY_ONE_SUB_COS_R 10
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RZ_ONE_SUB_COS_R 11
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_RZ_ONE_SUB_COS_R 12
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_SIN_R            13
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_SIN_R            14
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_SIN_R            15
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ELEMENT_COUNT       16

struct PossumMathTransformRotationCache {
    union {
        struct {
            f32 rx;
            f32 ry;
            f32 rz;
            f32 angle_radians;
            f32 cos_r;
            f32 sin_r;
            f32 one_sub_cos_r;
            f32 rx_one_sub_cos_r;
            f32 ry_one_sub_cos_r;
            f32 rz_one_sub_cos_r;
            f32 rx_ry_one_sub_cos_r;
            f32 rx_rz_one_sub_cos_r;
            f32 ry_rz_one_sub_cos_r;
            f32 rx_sin_r;
            f32 ry_sin_r;
            f32 rz_sin_r;
        };

        f32 c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ELEMENT_COUNT];
    };
};

inline PossumMathTransformRotationCache
possum_math_transform_rotation_cache(
    const f32 rx,
    const f32 ry,
    const f32 rz,
    const f32 angle_radians) {

    PossumMathTransformRotationCache cache = {0};

    cache.cos_r               = cosf(angle_radians);
    cache.sin_r               = sinf(angle_radians);
    cache.one_sub_cos_r       = 1.0f - cache.cos_r;
    cache.rx_one_sub_cos_r    = cache.rx * cache.one_sub_cos_r;
    cache.ry_one_sub_cos_r    = cache.ry * cache.one_sub_cos_r;
    cache.rz_one_sub_cos_r    = cache.rz * cache.one_sub_cos_r;
    cache.rx_ry_one_sub_cos_r = cache.rx * cache.ry_one_sub_cos_r;
    cache.rx_rz_one_sub_cos_r = cache.rx * cache.rz_one_sub_cos_r;
    cache.ry_rz_one_sub_cos_r = cache.ry * cache.rz_one_sub_cos_r;
    cache.rx_sin_r            = cache.rx * cache.sin_r;
    cache.ry_sin_r            = cache.ry * cache.sin_r;
    cache.rz_sin_r            = cache.rz * cache.sin_r;

    return(cache);
}

inline PossumMathTransform
possum_math_transform_rotate_radians(
    const f32 rx,
    const f32 ry,
    const f32 rz,
    const f32 angle_radians) {

    //cache re-used calculations
    const PossumMathTransformRotationCache cache = 
        possum_math_transform_rotation_cache(
            rx,
            ry,
            rz,
            angle_radians);

    PossumMathTransform t = {0};

    //row 0
    t.m[POSSUM_MATH_MAT3_R0C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_ONE_SUB_COS_R] * rx);
    t.m[POSSUM_MATH_MAT3_R0C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RY_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R0C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RZ_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R0C3] = 0.0f;

    //row 1
    t.m[POSSUM_MATH_MAT3_R1C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RY_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R1C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_ONE_SUB_COS_R] * ry);
    t.m[POSSUM_MATH_MAT3_R1C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_RZ_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R1C3] = 0.0f;

    //row 2
    t.m[POSSUM_MATH_MAT3_R2C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RZ_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R2C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_RZ_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R2C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_ONE_SUB_COS_R] * rz);
    t.m[POSSUM_MATH_MAT3_R2C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;
    
    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_degrees(
    const f32 rx,
    const f32 ry,
    const f32 rz,
    const f32 angle_degrees) {

    //convert degrees to radians
    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees);

    //cache re-used calculations
    const PossumMathTransformRotationCache cache = 
        possum_math_transform_rotation_cache(
            rx,
            ry,
            rz,
            angle_radians);

    PossumMathTransform t = {0};

    //row 0
    t.m[POSSUM_MATH_MAT3_R0C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_ONE_SUB_COS_R] * rx);
    t.m[POSSUM_MATH_MAT3_R0C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RY_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R0C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RZ_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R0C3] = 0.0f;

    //row 1
    t.m[POSSUM_MATH_MAT3_R1C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RY_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R1C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_ONE_SUB_COS_R] * ry);
    t.m[POSSUM_MATH_MAT3_R1C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_RZ_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R1C3] = 0.0f;

    //row 2
    t.m[POSSUM_MATH_MAT3_R2C0] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_RZ_ONE_SUB_COS_R]) - (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R2C1] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_RZ_ONE_SUB_COS_R]) + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_SIN_R]);
    t.m[POSSUM_MATH_MAT3_R2C2] = (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R])               + (cache.c[POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_ONE_SUB_COS_R] * rz);
    t.m[POSSUM_MATH_MAT3_R2C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;
    
    return(t);
}

#endif //POSSUM_MATH_TRANSFORM_HPP