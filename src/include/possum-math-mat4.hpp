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

        f32 values[16];
    };
};

typedef PossumMathMat4Row* PossumMathMat4RowPtr; 
typedef PossumMathMat4*    PossumMathMat4Ptr; 

inline PossumMathMat4
possum_math_mat4_identity() {

    PossumMathMat4 m4 = {0};
    
    m4.row0_col0 = 1.0f;
    m4.row1_col1 = 1.0f;
    m4.row2_col2 = 1.0f;
    m4.row3_col3 = 1.0f;

    return(m4);
}

static const PossumMathMat4 POSSUM_MATH_MAT4_IDENTITY = possum_math_mat4_identity();

#endif //POSSUM_MATH_MAT4_HPP