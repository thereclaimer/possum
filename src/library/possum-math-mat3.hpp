#ifndef POSSUM_MATH_MAT3_HPP
#define POSSUM_MATH_MAT3_HPP


#include <math.h>

#include "possum-types.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-simd-4f32.hpp"

struct PossumMathMat3 {

    union {

        struct {

            f32 row0_col0;
            f32 row0_col1;
            f32 row0_col2;

            f32 row1_col0;
            f32 row1_col1;
            f32 row1_col2;
            
            f32 row2_col0;
            f32 row2_col1;
            f32 row2_col2;
        };

        union {

            struct {
                PossumMathVec3 row0;
                PossumMathVec3 row1;
                PossumMathVec3 row2;
            };

            PossumMathVec3 rows[3];
        };

        f32 m[9];
    };
};

typedef PossumMathMat3* PossumMathMat3Ptr;

#define POSSUM_MATH_MAT3_R0C0 0
#define POSSUM_MATH_MAT3_R0C1 1
#define POSSUM_MATH_MAT3_R0C2 2
#define POSSUM_MATH_MAT3_R1C0 3
#define POSSUM_MATH_MAT3_R1C1 4
#define POSSUM_MATH_MAT3_R1C2 5
#define POSSUM_MATH_MAT3_R2C0 6
#define POSSUM_MATH_MAT3_R2C1 7
#define POSSUM_MATH_MAT3_R2C2 8

internal PossumMathMat3
possum_math_mat3_identity() {

    PossumMathMat3 m3 = {0};

    m3.row0_col0 = 1.0f;
    m3.row1_col1 = 1.0f;
    m3.row2_col2 = 1.0f;

    return(m3);
}

internal PossumMathMat3
possum_math_mat3_multiply_m3(
    PossumMathMat3Ptr m3a,
    PossumMathMat3Ptr m3b) {

    PossumMathMat3 m3c = {0};

    f32p m3a_m = m3a->m;
    f32p m3b_m = m3b->m;

    m3c.m[POSSUM_MATH_MAT3_R0C0] = 
        (m3a_m[POSSUM_MATH_MAT3_R0C0] * m3b_m[POSSUM_MATH_MAT3_R0C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C1] * m3b_m[POSSUM_MATH_MAT3_R1C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C2] * m3b_m[POSSUM_MATH_MAT3_R2C0]); 
    
    m3c.m[POSSUM_MATH_MAT3_R0C1] = 
        (m3a_m[POSSUM_MATH_MAT3_R0C0] * m3b_m[POSSUM_MATH_MAT3_R0C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C1] * m3b_m[POSSUM_MATH_MAT3_R1C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C2] * m3b_m[POSSUM_MATH_MAT3_R2C1]);
    
    m3c.m[POSSUM_MATH_MAT3_R0C2] = 
        (m3a_m[POSSUM_MATH_MAT3_R0C0] * m3b_m[POSSUM_MATH_MAT3_R0C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C1] * m3b_m[POSSUM_MATH_MAT3_R1C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R0C2] * m3b_m[POSSUM_MATH_MAT3_R2C2]);
    
    m3c.m[POSSUM_MATH_MAT3_R1C0] = 
        (m3a_m[POSSUM_MATH_MAT3_R1C0] * m3b_m[POSSUM_MATH_MAT3_R0C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C1] * m3b_m[POSSUM_MATH_MAT3_R1C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C2] * m3b_m[POSSUM_MATH_MAT3_R2C0]);
    
    m3c.m[POSSUM_MATH_MAT3_R1C1] = 
        (m3a_m[POSSUM_MATH_MAT3_R1C0] * m3b_m[POSSUM_MATH_MAT3_R0C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C1] * m3b_m[POSSUM_MATH_MAT3_R1C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C2] * m3b_m[POSSUM_MATH_MAT3_R2C1]);
    
    m3c.m[POSSUM_MATH_MAT3_R1C2] = 
        (m3a_m[POSSUM_MATH_MAT3_R1C0] * m3b_m[POSSUM_MATH_MAT3_R0C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C1] * m3b_m[POSSUM_MATH_MAT3_R1C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R1C2] * m3b_m[POSSUM_MATH_MAT3_R2C2]);
    
    m3c.m[POSSUM_MATH_MAT3_R2C0] = 
        (m3a_m[POSSUM_MATH_MAT3_R2C0] * m3b_m[POSSUM_MATH_MAT3_R0C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C1] * m3b_m[POSSUM_MATH_MAT3_R1C0]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C2] * m3b_m[POSSUM_MATH_MAT3_R2C0]);
    
    m3c.m[POSSUM_MATH_MAT3_R2C1] = 
        (m3a_m[POSSUM_MATH_MAT3_R2C0] * m3b_m[POSSUM_MATH_MAT3_R0C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C1] * m3b_m[POSSUM_MATH_MAT3_R1C1]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C2] * m3b_m[POSSUM_MATH_MAT3_R2C1]);
    
    m3c.m[POSSUM_MATH_MAT3_R2C2] = 
        (m3a_m[POSSUM_MATH_MAT3_R2C0] * m3b_m[POSSUM_MATH_MAT3_R0C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C1] * m3b_m[POSSUM_MATH_MAT3_R1C2]) + 
        (m3a_m[POSSUM_MATH_MAT3_R2C2] * m3b_m[POSSUM_MATH_MAT3_R2C2]);

    return(m3c);
}

internal PossumMathVec3
possum_math_mat3_multiply_v3(
    PossumMathMat3Ptr m3,
    PossumMathVec3Ptr v3) {

    PossumMathVec3 v3_new = {0};

    f32p v3_xyz = v3->xyz;
    f32p m3_m   = m3->m;

    v3_new.x = 
        (v3_xyz[POSSUM_MATH_VEC3_X] * m3_m[POSSUM_MATH_MAT3_R0C0]) +
        (v3_xyz[POSSUM_MATH_VEC3_Y] * m3_m[POSSUM_MATH_MAT3_R0C1]) +
        (v3_xyz[POSSUM_MATH_VEC3_Z] * m3_m[POSSUM_MATH_MAT3_R0C2]);

    v3_new.y = 
        (v3_xyz[POSSUM_MATH_VEC3_X] * m3_m[POSSUM_MATH_MAT3_R1C0]) +
        (v3_xyz[POSSUM_MATH_VEC3_Y] * m3_m[POSSUM_MATH_MAT3_R1C1]) +
        (v3_xyz[POSSUM_MATH_VEC3_Z] * m3_m[POSSUM_MATH_MAT3_R1C2]);

    v3_new.z = 
        (v3_xyz[POSSUM_MATH_VEC3_X] * m3_m[POSSUM_MATH_MAT3_R2C0]) +
        (v3_xyz[POSSUM_MATH_VEC3_Y] * m3_m[POSSUM_MATH_MAT3_R2C1]) +
        (v3_xyz[POSSUM_MATH_VEC3_Z] * m3_m[POSSUM_MATH_MAT3_R2C2]);

    return(v3_new);
}


#endif //POSSUM_MATH_MAT3_HPP