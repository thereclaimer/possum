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

internal PossumMathMat3
possum_math_mat3_identity() {

    PossumMathMat3 m3 = {0};

    m3.row0_col0 = 1.0f;
    m3.row1_col1 = 1.0f;
    m3.row2_col2 = 1.0f;

    return(m3);
}

internal PossumMathMat3
possum_math_mat3_multiply_m3a_m3b(
    PossumMathMat3Ptr m3a,
    PossumMathMat3Ptr m3b) {

    PossumMathMat3 m3c = {0};

    m3c.m[0] = 
    m3c.m[1] = 
    m3c.m[2] = 
    m3c.m[3] = 
    m3c.m[4] = 
    m3c.m[5] = 
    m3c.m[6] = 
    m3c.m[7] = 
    m3c.m[8] = 

}

#endif //POSSUM_MATH_MAT3_HPP