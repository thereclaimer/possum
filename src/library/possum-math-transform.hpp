#ifndef POSSUM_MATH_TRANSFORM_HPP
#define POSSUM_MATH_TRANSFORM_HPP

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-mat3.hpp"
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

#endif //POSSUM_MATH_TRANSFORM_HPP