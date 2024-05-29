#ifndef POSSUM_MATH_MAT4_HPP
#define POSSUM_MATH_MAT4_HPP

#include <math.h>

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"

struct PossumMathMat4Row {
    f32 col0; 
    f32 col1; 
    f32 col2; 
    f32 col3; 
};

struct PossumMathMat4 {

    union {

        struct {

            f32 row0_col0;
            f32 row0_col1;
            f32 row0_col2;
            f32 row0_col3;

            f32 row1_col0;
            f32 row1_col1;
            f32 row1_col2;
            f32 row1_col3;
            
            f32 row2_col0;
            f32 row2_col1;
            f32 row2_col2;
            f32 row2_col3;

            f32 row3_col0;
            f32 row3_col1;
            f32 row3_col2;
            f32 row3_col3;
        };

        union {

            struct {
                PossumMathMat4Row row0;
                PossumMathMat4Row row1;
                PossumMathMat4Row row2;
                PossumMathMat4Row row3;
            };

            PossumMathMat4Row rows[4];
        };

        f32 m[16];
    };
};

//ROW 0 
#define POSSUM_MATH_MAT3_R0C0 0
#define POSSUM_MATH_MAT3_R0C1 1
#define POSSUM_MATH_MAT3_R0C2 2
#define POSSUM_MATH_MAT3_R0C3 3

//ROW 1 
#define POSSUM_MATH_MAT3_R1C0 4
#define POSSUM_MATH_MAT3_R1C1 5
#define POSSUM_MATH_MAT3_R1C2 6
#define POSSUM_MATH_MAT3_R1C3 7

//ROW 2 
#define POSSUM_MATH_MAT3_R2C0 8
#define POSSUM_MATH_MAT3_R2C1 9
#define POSSUM_MATH_MAT3_R2C2 10
#define POSSUM_MATH_MAT3_R2C3 11

//ROW 3 
#define POSSUM_MATH_MAT3_R3C0 12
#define POSSUM_MATH_MAT3_R3C1 13
#define POSSUM_MATH_MAT3_R3C2 14
#define POSSUM_MATH_MAT3_R3C3 15

inline PossumMathMat4
possum_math_mat4_identity() {

    PossumMathMat4 m4 = {0};

    m4.row0_col0 = 1.0f;
    m4.row1_col1 = 1.0f;
    m4.row2_col2 = 1.0f;
    m4.row3_col3 = 1.0f;

    return(m4);
}

#endif //POSSUM_MATH_MAT4_HPP