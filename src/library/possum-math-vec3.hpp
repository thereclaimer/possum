#ifndef POSSUM_MATH_VEC3_HPP
#define POSSUM_MATH_VEC3_HPP

#include <math.h>

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"

struct  PossumMathVec3;

typedef PossumMathVec3* PossumMathVec3Ptr;

struct PossumMathVec3 {

    union {

        struct {
            f32 x;
            f32 y;  
            f32 z;  
        };
    
        f32 xyz[3];
    };
};

#define POSSUM_MATH_VEC3_X 0
#define POSSUM_MATH_VEC3_Y 1
#define POSSUM_MATH_VEC3_Z 2

inline PossumMathVec3
possum_math_vec3_create(
    const f32 x,
    const f32 y,
    const f32 z) {

    PossumMathVec3 v3 = {0};
    v3.x = x;
    v3.y = y;
    v3.z = z;

    return(v3);
}

inline PossumMathVec3
possum_math_vec3_copy(
    const PossumMathVec3Ptr v3) {

    PossumMathVec3 v3_copy = {0};
    f32p v3_xyz = v3->xyz;

    v3_copy.x = v3_xyz[POSSUM_MATH_VEC3_X];
    v3_copy.y = v3_xyz[POSSUM_MATH_VEC3_Y];
    v3_copy.z = v3_xyz[POSSUM_MATH_VEC3_Z];

    return(v3_copy);
}

inline bool
possum_math_vec3_are_equal(
    const PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    bool equal = 
        (v3_a_xyz[POSSUM_MATH_VEC3_X] == v3_b_xyz[POSSUM_MATH_VEC3_X]) && 
        (v3_a_xyz[POSSUM_MATH_VEC3_Y] == v3_b_xyz[POSSUM_MATH_VEC3_Y]) && 
        (v3_a_xyz[POSSUM_MATH_VEC3_Z] == v3_b_xyz[POSSUM_MATH_VEC3_Z]);

    return(equal);
}

inline void
possum_math_vec3_scalar(
          PossumMathVec3Ptr v3,    
    const f32               scalar) {

    f32p v3_xyz = v3->xyz;

    v3_xyz[POSSUM_MATH_VEC3_X] *= scalar;
    v3_xyz[POSSUM_MATH_VEC3_Y] *= scalar;
    v3_xyz[POSSUM_MATH_VEC3_Z] *= scalar;
}

inline f32
possum_math_vec3_magnitude(
    const PossumMathVec3Ptr v3) {

    f32p v3_xyz = v3->xyz;

    f32 magnitude = 
        sqrtf(
            (v3_xyz[POSSUM_MATH_VEC3_X] * v3_xyz[POSSUM_MATH_VEC3_X]) +
            (v3_xyz[POSSUM_MATH_VEC3_Y] * v3_xyz[POSSUM_MATH_VEC3_Y]) +
            (v3_xyz[POSSUM_MATH_VEC3_Z] * v3_xyz[POSSUM_MATH_VEC3_Z])
        );

    return(magnitude);
}

inline void
possum_math_vec3_magnitude_batch(
    const u64               v3_count,
    const PossumMathVec3Ptr in_v3,
          f32p              out_magnitude) {

    f32p i_v3_xyz = NULL;

    for(
        u64 v3_index = 0;
        v3_index < v3_count;
        ++v3_index) {

        i_v3_xyz = in_v3[v3_index].xyz;

        out_magnitude[v3_index] = 
            sqrtf(
                (i_v3_xyz[POSSUM_MATH_VEC3_X] * i_v3_xyz[POSSUM_MATH_VEC3_X]) + 
                (i_v3_xyz[POSSUM_MATH_VEC3_Y] * i_v3_xyz[POSSUM_MATH_VEC3_Y]) +
                (i_v3_xyz[POSSUM_MATH_VEC3_Z] * i_v3_xyz[POSSUM_MATH_VEC3_Z]) 
            );
    }
}


inline void
possum_math_vec3_magnitude_batch_by_4(
    const u64               v3_count,
    const PossumMathVec3Ptr in_v3,
          f32p              out_magnitude) {

    PossumMathVec3 i_v3[4];
    f32            i_v3_x[4];
    f32            i_v3_y[4];
    f32            i_v3_z[4];
    f32            i_v3_x_square[4];
    f32            i_v3_y_square[4];
    f32            i_v3_z_square[4];
    f32            i_v3_x_y_z_square[4];
    f32            i_v3_magnitude[4];

    for(
        u64 v3_index = 0;
        v3_index < v3_count;
        v3_index += 4) {

        i_v3[0] = in_v3[v3_index];
        i_v3[1] = in_v3[v3_index + 1];
        i_v3[2] = in_v3[v3_index + 2];
        i_v3[3] = in_v3[v3_index + 3];

        i_v3_x[0] = i_v3[0].x;
        i_v3_x[1] = i_v3[1].x;
        i_v3_x[2] = i_v3[2].x;
        i_v3_x[3] = i_v3[3].x;

        i_v3_y[0] = i_v3[0].y;
        i_v3_y[1] = i_v3[1].y;
        i_v3_y[2] = i_v3[2].y;
        i_v3_y[3] = i_v3[3].y;

        i_v3_z[0] = i_v3[0].z;
        i_v3_z[1] = i_v3[1].z;
        i_v3_z[2] = i_v3[2].z;
        i_v3_z[3] = i_v3[3].z;

        i_v3_x_square[0] = i_v3_x[0] * i_v3_x[0];
        i_v3_x_square[1] = i_v3_x[1] * i_v3_x[1];
        i_v3_x_square[2] = i_v3_x[2] * i_v3_x[2];
        i_v3_x_square[3] = i_v3_x[3] * i_v3_x[3];

        i_v3_y_square[0] = i_v3_y[0] * i_v3_y[0];
        i_v3_y_square[1] = i_v3_y[1] * i_v3_y[1];
        i_v3_y_square[2] = i_v3_y[2] * i_v3_y[2];
        i_v3_y_square[3] = i_v3_y[3] * i_v3_y[3];

        i_v3_z_square[0] = i_v3_z[0] * i_v3_z[0];
        i_v3_z_square[1] = i_v3_z[1] * i_v3_z[1];
        i_v3_z_square[2] = i_v3_z[2] * i_v3_z[2];
        i_v3_z_square[3] = i_v3_z[3] * i_v3_z[3];

        i_v3_x_y_z_square[0] = i_v3_x_square[0] + i_v3_y_square[0] + i_v3_z_square[0];
        i_v3_x_y_z_square[1] = i_v3_x_square[1] + i_v3_y_square[1] + i_v3_z_square[1]; 
        i_v3_x_y_z_square[2] = i_v3_x_square[2] + i_v3_y_square[2] + i_v3_z_square[2]; 
        i_v3_x_y_z_square[3] = i_v3_x_square[3] + i_v3_y_square[3] + i_v3_z_square[3]; 

        i_v3_magnitude[0] = sqrtf(i_v3_x_y_z_square[0]);
        i_v3_magnitude[1] = sqrtf(i_v3_x_y_z_square[1]);
        i_v3_magnitude[2] = sqrtf(i_v3_x_y_z_square[2]);
        i_v3_magnitude[3] = sqrtf(i_v3_x_y_z_square[3]);

        out_magnitude[v3_index]     = i_v3_magnitude[0];
        out_magnitude[v3_index + 1] = i_v3_magnitude[1];
        out_magnitude[v3_index + 2] = i_v3_magnitude[2];
        out_magnitude[v3_index + 3] = i_v3_magnitude[3];
    }
}

inline void
possum_math_vec3_magnitude_batch_simd(
    const u64               v3_count,
    const PossumMathVec3Ptr in_v3,
          f32p              out_magnitude) {

    PossumMathVec3 i_v3[4];
    f32            i_v3_x[4];
    f32            i_v3_y[4];
    f32            i_v3_z[4];

    reg4f32 register_i_v3_x;
    reg4f32 register_i_v3_y;
    reg4f32 register_i_v3_z;
    reg4f32 register_i_v3_x_square;
    reg4f32 register_i_v3_y_square;
    reg4f32 register_i_v3_z_square;

    reg4f32 register_i_v3_x_y_z_square;
    reg4f32 register_i_v3_magnitude;
    
    for(
        u64 v3_index = 0;
        v3_index < v3_count;
        v3_index += 4) {

        i_v3[0]   = in_v3[v3_index];
        i_v3[1]   = in_v3[v3_index + 1];
        i_v3[2]   = in_v3[v3_index + 2];
        i_v3[3]   = in_v3[v3_index + 3];

        i_v3_x[0] = i_v3[0].x;
        i_v3_x[1] = i_v3[1].x;
        i_v3_x[2] = i_v3[2].x;
        i_v3_x[3] = i_v3[3].x;

        i_v3_y[0] = i_v3[0].y;
        i_v3_y[1] = i_v3[1].y;
        i_v3_y[2] = i_v3[2].y;
        i_v3_y[3] = i_v3[3].y;

        i_v3_z[0] = i_v3[0].z;
        i_v3_z[1] = i_v3[1].z;
        i_v3_z[2] = i_v3[2].z;
        i_v3_z[3] = i_v3[3].z;

        register_i_v3_x              = possum_math_simd_reg4f32_load(i_v3_x);
        register_i_v3_y              = possum_math_simd_reg4f32_load(i_v3_y);
        register_i_v3_z              = possum_math_simd_reg4f32_load(i_v3_z);

        register_i_v3_x_square       = possum_math_simd_reg4f32_multiply(register_i_v3_x,register_i_v3_x);
        register_i_v3_y_square       = possum_math_simd_reg4f32_multiply(register_i_v3_y,register_i_v3_y);
        register_i_v3_z_square       = possum_math_simd_reg4f32_multiply(register_i_v3_z,register_i_v3_z);

        register_i_v3_x_y_z_square   = possum_math_simd_reg4f32_add(register_i_v3_x_square,register_i_v3_y_square);
        register_i_v3_x_y_z_square   = possum_math_simd_reg4f32_add(register_i_v3_x_y_z_square,register_i_v3_z_square);
        
        register_i_v3_magnitude      = possum_math_simd_reg4f32_sqrtf(register_i_v3_x_y_z_square);

        possum_math_simd_reg4f32_store(&out_magnitude[v3_index],register_i_v3_magnitude);
    }
}

inline void
possum_math_vec3_normalize(
    PossumMathVec3Ptr v3) {

    f32 magnitude = possum_math_vec3_magnitude(v3);
    
    f32 magnitude_inverse = 
        magnitude == 0.0f 
            ? 0.0f
            : 1.0f / magnitude; 

    possum_math_vec3_scalar(v3,magnitude_inverse);
}

inline PossumMathVec3
possum_math_vec3_add(
    const PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    PossumMathVec3 v3_c = {0};
    
    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    v3_c.x = v3_a_xyz[POSSUM_MATH_VEC3_X] + v3_b_xyz[POSSUM_MATH_VEC3_X];
    v3_c.y = v3_a_xyz[POSSUM_MATH_VEC3_Y] + v3_b_xyz[POSSUM_MATH_VEC3_Y];
    v3_c.z = v3_a_xyz[POSSUM_MATH_VEC3_Z] + v3_b_xyz[POSSUM_MATH_VEC3_Z];

    return(v3_c);
}

inline PossumMathVec3
possum_math_vec3_add_batch(
    const u64               count,
    const PossumMathVec3Ptr in_v3_a,
    const PossumMathVec3Ptr in_v3_b,
          PossumMathVec3Ptr out_v3_c) {

    PossumMathVec3 i_v3_c = {0};

    f32p in_v3_a_xyz;
    f32p in_v3_b_xyz;

    for (
        u64 index = 0;
        index < count;
        ++index) {

        in_v3_a_xyz = in_v3_a[index].xyz;
        in_v3_b_xyz = in_v3_b[index].xyz;
        
        i_v3_c = {0};
        i_v3_c.x = in_v3_a_xyz[POSSUM_MATH_VEC3_X] + in_v3_b_xyz[POSSUM_MATH_VEC3_X];
        i_v3_c.y = in_v3_a_xyz[POSSUM_MATH_VEC3_Y] + in_v3_b_xyz[POSSUM_MATH_VEC3_Y];
        i_v3_c.z = in_v3_a_xyz[POSSUM_MATH_VEC3_Z] + in_v3_b_xyz[POSSUM_MATH_VEC3_Z];

        out_v3_c[index] = i_v3_c;
    }
}

inline void
possum_math_vec3_add_b_to_a(
          PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    v3_a_xyz[POSSUM_MATH_VEC3_X] += v3_b_xyz[POSSUM_MATH_VEC3_X];
    v3_a_xyz[POSSUM_MATH_VEC3_Y] += v3_b_xyz[POSSUM_MATH_VEC3_Y];
    v3_a_xyz[POSSUM_MATH_VEC3_Z] += v3_b_xyz[POSSUM_MATH_VEC3_Z];
}

inline void
possum_math_vec3_subtract_b_from_a(
          PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    v3_a_xyz[POSSUM_MATH_VEC3_X] -= v3_b_xyz[POSSUM_MATH_VEC3_X];
    v3_a_xyz[POSSUM_MATH_VEC3_Y] -= v3_b_xyz[POSSUM_MATH_VEC3_Y];
    v3_a_xyz[POSSUM_MATH_VEC3_Z] -= v3_b_xyz[POSSUM_MATH_VEC3_Z];
}

inline PossumMathVec3
possum_math_vec3_difference_a_to_b(
    const PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    PossumMathVec3 v3_c = {0};

    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    v3_c.x = v3_a_xyz[POSSUM_MATH_VEC3_X] - v3_b_xyz[POSSUM_MATH_VEC3_X];
    v3_c.y = v3_a_xyz[POSSUM_MATH_VEC3_Y] - v3_b_xyz[POSSUM_MATH_VEC3_Y];
    v3_c.z = v3_a_xyz[POSSUM_MATH_VEC3_Z] - v3_b_xyz[POSSUM_MATH_VEC3_Z];

    return(v3_c);
}

inline f32
possum_math_vec3_dot(
    const PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {
    
    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    f32 a_dot_b = 
        (v3_a_xyz[POSSUM_MATH_VEC3_X] * v3_a_xyz[POSSUM_MATH_VEC3_X]) +  
        (v3_a_xyz[POSSUM_MATH_VEC3_Y] * v3_a_xyz[POSSUM_MATH_VEC3_Y]) +
        (v3_a_xyz[POSSUM_MATH_VEC3_Z] * v3_a_xyz[POSSUM_MATH_VEC3_Z]);

    return(a_dot_b);
}

inline void
possum_math_vec3_dot_batch(
    const u64               v3_count,
    const PossumMathVec3Ptr in_v3_a,
    const PossumMathVec3Ptr in_v3_b,
          f32*              out_a_dot_b) {

    f32p v3_a_xyz = NULL;
    f32p v3_b_xyz = NULL;

    for (
        u64 index = 0;
        index < v3_count;
        ++index) {

        v3_a_xyz = in_v3_a[index].xyz; 
        v3_b_xyz = in_v3_b[index].xyz; 

        out_a_dot_b[index] =
            (v3_a_xyz[POSSUM_MATH_VEC3_X] * v3_b_xyz[POSSUM_MATH_VEC3_X]) +  
            (v3_a_xyz[POSSUM_MATH_VEC3_Y] * v3_b_xyz[POSSUM_MATH_VEC3_Y]) + 
            (v3_a_xyz[POSSUM_MATH_VEC3_Z] * v3_b_xyz[POSSUM_MATH_VEC3_Z]); 
    }
}

inline PossumMathVec3
possum_math_vec3_project_a_onto_b(
    const PossumMathVec3Ptr in_v3_a,
    const PossumMathVec3Ptr in_v3_b) {

    f32 a_dot_b = possum_math_vec3_dot(in_v3_a,in_v3_b);
    f32 b_dot_b = possum_math_vec3_dot(in_v3_b,in_v3_b);

    f32 scalar = a_dot_b / b_dot_b;

    PossumMathVec3 projection = possum_math_vec3_copy(in_v3_b);
    possum_math_vec3_scalar(&projection,scalar);

    return(projection);
}

inline PossumMathVec3
possum_math_vec3_reject_a_from_b(
    const PossumMathVec3Ptr in_v3_a,
    const PossumMathVec3Ptr in_v3_b) {

    f32 a_dot_b = possum_math_vec3_dot(in_v3_a,in_v3_b);
    f32 b_dot_b = possum_math_vec3_dot(in_v3_b,in_v3_b);

    f32 scalar = a_dot_b / b_dot_b;

    PossumMathVec3 rejection = possum_math_vec3_difference_a_to_b(in_v3_a,in_v3_b);
    possum_math_vec3_scalar(&rejection,scalar);

    return(rejection);
}

inline PossumMathVec3
possum_math_vec3_cross(
    const PossumMathVec3Ptr v3_a,
    const PossumMathVec3Ptr v3_b) {

    PossumMathVec3 v3_cross = {0};

    f32p v3_a_xyz = v3_a->xyz;
    f32p v3_b_xyz = v3_b->xyz;

    v3_cross.x = (v3_a_xyz[POSSUM_MATH_VEC3_Y] * v3_b_xyz[POSSUM_MATH_VEC3_Z]) - (v3_a_xyz[POSSUM_MATH_VEC3_Z] * v3_b_xyz[POSSUM_MATH_VEC3_Y]);
    v3_cross.y = (v3_a_xyz[POSSUM_MATH_VEC3_Z] * v3_b_xyz[POSSUM_MATH_VEC3_X]) - (v3_a_xyz[POSSUM_MATH_VEC3_X] * v3_b_xyz[POSSUM_MATH_VEC3_Z]);
    v3_cross.z = (v3_a_xyz[POSSUM_MATH_VEC3_X] * v3_b_xyz[POSSUM_MATH_VEC3_Y]) - (v3_a_xyz[POSSUM_MATH_VEC3_Y] * v3_b_xyz[POSSUM_MATH_VEC3_X]);

    return(v3_cross);
}

#endif //POSSUM_MATH_VEC3_HPP