#ifndef POSSUM_MATH_TRANSFORM_HPP
#define POSSUM_MATH_TRANSFORM_HPP

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-mat3.hpp"
#include "possum-math-trig.hpp"
#include "possum-math-direction.hpp"
#include "possum-math-quaternion.hpp"
#include "possum-math-mat4.hpp"

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

#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX                  0
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY                  1
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ                  2
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ANGLE_RADIANS       3
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_COS_R               4
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_SIN_R               5
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_ONE_SUB_COS_R       6
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RX_ONE_SUB_COS_R    7
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RY_ONE_SUB_COS_R    8
#define POSSUM_MATH_TRANSFORM_ROTATION_CACHE_RZ_ONE_SUB_COS_R    9
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

inline PossumMathTransform
possum_math_transform_rotate_radians_x(
    f32 angle_radians) {

    PossumMathTransform t = {0};

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_radians_y(
    f32 angle_radians) {

    PossumMathTransform t = {0};

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_radians_z(
    f32 angle_radians) {

    PossumMathTransform t = {0};

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_degrees_x(
    f32 angle_degrees) {

    PossumMathTransform t = {0};

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees);

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_degrees_y(
    f32 angle_degrees) {

    PossumMathTransform t = {0};

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees);

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

struct PossumMathTransformQuaternionCache {

    union {
        struct {
            f32 xx;
            f32 yy;
            f32 zz;
            f32 xy;
            f32 xz;
            f32 yz;
            f32 wx;
            f32 wy;
            f32 wz;
        };

        f32 c[9];
    };
};

#define POSSUM_MATH_QUATERNION_CACHE_XX 0
#define POSSUM_MATH_QUATERNION_CACHE_YY 1
#define POSSUM_MATH_QUATERNION_CACHE_ZZ 2
#define POSSUM_MATH_QUATERNION_CACHE_XY 3
#define POSSUM_MATH_QUATERNION_CACHE_XZ 4
#define POSSUM_MATH_QUATERNION_CACHE_YZ 5
#define POSSUM_MATH_QUATERNION_CACHE_WX 6
#define POSSUM_MATH_QUATERNION_CACHE_WY 7
#define POSSUM_MATH_QUATERNION_CACHE_WZ 8

inline PossumMathTransformQuaternionCache
possum_math_transform_quaternion_cache(
    PossumMathQuaternionPtr q) {

    PossumMathTransformQuaternionCache cache = {0};

    f32p q_wxyz = q->wxyz;

    cache.xx = q_wxyz[POSSUM_MATH_QUATERNION_X] * q_wxyz[POSSUM_MATH_QUATERNION_X];
    cache.yy = q_wxyz[POSSUM_MATH_QUATERNION_Y] * q_wxyz[POSSUM_MATH_QUATERNION_Y];
    cache.zz = q_wxyz[POSSUM_MATH_QUATERNION_Z] * q_wxyz[POSSUM_MATH_QUATERNION_Z];
    cache.xy = q_wxyz[POSSUM_MATH_QUATERNION_X] * q_wxyz[POSSUM_MATH_QUATERNION_Y];
    cache.xz = q_wxyz[POSSUM_MATH_QUATERNION_X] * q_wxyz[POSSUM_MATH_QUATERNION_Z];
    cache.yz = q_wxyz[POSSUM_MATH_QUATERNION_Y] * q_wxyz[POSSUM_MATH_QUATERNION_Z];
    cache.wx = q_wxyz[POSSUM_MATH_QUATERNION_W] * q_wxyz[POSSUM_MATH_QUATERNION_X];
    cache.wy = q_wxyz[POSSUM_MATH_QUATERNION_W] * q_wxyz[POSSUM_MATH_QUATERNION_Y];
    cache.wz = q_wxyz[POSSUM_MATH_QUATERNION_W] * q_wxyz[POSSUM_MATH_QUATERNION_Z];

    return(cache);
}

inline PossumMathTransform
possum_math_transform_rotate_quaternion(
    PossumMathQuaternionPtr q) {

    //cache our re-used operations
    PossumMathTransformQuaternionCache cache = possum_math_transform_quaternion_cache(q);
    f32p c = cache.c;

    PossumMathTransform t = {0};

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_YY]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_ZZ]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XY] - c[POSSUM_MATH_QUATERNION_CACHE_WZ]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XZ] + c[POSSUM_MATH_QUATERNION_CACHE_WY]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XY] + c[POSSUM_MATH_QUATERNION_CACHE_WZ]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_XX]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_ZZ]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_YZ] - c[POSSUM_MATH_QUATERNION_CACHE_WX]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XZ] - c[POSSUM_MATH_QUATERNION_CACHE_WY]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_YZ] + c[POSSUM_MATH_QUATERNION_CACHE_WX]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_XX]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_YY]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_quaternion_euler_radians(
    f32 radians_roll,
    f32 radians_pitch,
    f32 radians_yaw) {

    //get the quaternion
    PossumMathQuaternion q = 
        possum_math_quaternion_euler_angles_radians(
            radians_roll,
            radians_pitch,
            radians_yaw);

    //cache our re-used operations
    PossumMathTransformQuaternionCache cache = possum_math_transform_quaternion_cache(&q);
    f32p c = cache.c;

    PossumMathTransform t = {0};

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_YY]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_ZZ]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XY] - c[POSSUM_MATH_QUATERNION_CACHE_WZ]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XZ] + c[POSSUM_MATH_QUATERNION_CACHE_WY]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XY] + c[POSSUM_MATH_QUATERNION_CACHE_WZ]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_XX]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_ZZ]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_YZ] - c[POSSUM_MATH_QUATERNION_CACHE_WX]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_XZ] - c[POSSUM_MATH_QUATERNION_CACHE_WY]);
    t.m[POSSUM_MATH_MAT3_R3C1] = 2 * (c[POSSUM_MATH_QUATERNION_CACHE_YZ] + c[POSSUM_MATH_QUATERNION_CACHE_WX]);
    t.m[POSSUM_MATH_MAT3_R3C2] = 1.0f - (2 * c[POSSUM_MATH_QUATERNION_CACHE_XX]) - (2 * c[POSSUM_MATH_QUATERNION_CACHE_YY]);
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_rotate_degrees_z(
    f32 angle_degrees) {

    PossumMathTransform t = {0};

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees);

    f32 cos_r = cosf(angle_radians);
    f32 sin_r = sinf(angle_radians);

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = -sin_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = sin_r;
    t.m[POSSUM_MATH_MAT3_R3C1] = cos_r;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 1.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_camera_look_at(
    PossumMathDirectionPtr camera_direction,
    PossumMathVec3Ptr      camera_position) {

    PossumMathTransform t = {0};

    PossumMathVec3 camera_direction_forward = camera_direction->forward; 
    PossumMathVec3 camera_direction_right   = camera_direction->right; 
    PossumMathVec3 camera_direction_up      = camera_direction->up; 

    f32 translation_x = possum_math_vec3_dot(camera_position, &camera_direction_forward); 
    f32 translation_y = possum_math_vec3_dot(camera_position, &camera_direction_right); 
    f32 translation_z = possum_math_vec3_dot(camera_position, &camera_direction_up); 

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_right.x;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_right.y;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_right.z;
    t.m[POSSUM_MATH_MAT3_R3C3] = translation_x;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_up.x;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_up.y;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_up.z;
    t.m[POSSUM_MATH_MAT3_R3C3] = translation_y;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_forward.x;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_forward.y;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_forward.z;
    t.m[POSSUM_MATH_MAT3_R3C3] = translation_z;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C1] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C2] = 0.0f;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_camera_view(
    PossumMathDirectionPtr camera_direction,
    PossumMathVec3Ptr      camera_position) {

    PossumMathVec3 camera_direction_forward = camera_direction->forward; 
    PossumMathVec3 camera_direction_right   = camera_direction->right; 
    PossumMathVec3 camera_direction_up      = camera_direction->up; 

    f32 translation_x = possum_math_vec3_dot(camera_position, &camera_direction_forward); 
    f32 translation_y = possum_math_vec3_dot(camera_position, &camera_direction_right); 
    f32 translation_z = possum_math_vec3_dot(camera_position, &camera_direction_up); 

    PossumMathTransform t = {0};

    //row 0
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_right.x;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_up.x;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_forward.x;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 1
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_right.y;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_up.y;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_forward.y;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 2
    t.m[POSSUM_MATH_MAT3_R3C0] = camera_direction_right.z;
    t.m[POSSUM_MATH_MAT3_R3C1] = camera_direction_up.z;
    t.m[POSSUM_MATH_MAT3_R3C2] = camera_direction_forward.z;
    t.m[POSSUM_MATH_MAT3_R3C3] = 0.0f;
    
    //row 3
    t.m[POSSUM_MATH_MAT3_R3C0] = -translation_x;
    t.m[POSSUM_MATH_MAT3_R3C1] = -translation_y;
    t.m[POSSUM_MATH_MAT3_R3C2] = -translation_z;
    t.m[POSSUM_MATH_MAT3_R3C3] = 1.0f;

    return(t);
}

inline PossumMathTransform
possum_math_transform_trs(
    f32 translate_x,
    f32 translate_y,
    f32 translate_z,
    f32 scale_x,
    f32 scale_y,
    f32 scale_z,
    f32 radians_roll,
    f32 radians_pitch,
    f32 radians_yaw) {

    //get our individual transforms
    PossumMathTransform  translate  = possum_math_transform_translate(translate_x,translate_y,translate_z);
    PossumMathTransform  scale      = possum_math_transform_scale(scale_x, scale_y, scale_z);
    PossumMathTransform  rotation   = possum_math_transform_rotate_quaternion_euler_radians(radians_roll,radians_pitch,radians_yaw);

    //put together the trs transform
    //TODO: for some reason we're not picking up any new functions past the identity in mat4...

    return(rotation);
}



#endif //POSSUM_MATH_TRANSFORM_HPP