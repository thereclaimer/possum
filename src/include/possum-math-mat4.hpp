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

#define POSSUM_MATH_MAT4_R0C0 0
#define POSSUM_MATH_MAT4_R0C1 1
#define POSSUM_MATH_MAT4_R0C2 2
#define POSSUM_MATH_MAT4_R0C3 3

#define POSSUM_MATH_MAT4_R1C0 4
#define POSSUM_MATH_MAT4_R1C1 5
#define POSSUM_MATH_MAT4_R1C2 6
#define POSSUM_MATH_MAT4_R1C3 7

#define POSSUM_MATH_MAT4_R2C0 8
#define POSSUM_MATH_MAT4_R2C1 9
#define POSSUM_MATH_MAT4_R2C2 10
#define POSSUM_MATH_MAT4_R2C3 11

#define POSSUM_MATH_MAT4_R3C0 12
#define POSSUM_MATH_MAT4_R3C1 13
#define POSSUM_MATH_MAT4_R3C2 14
#define POSSUM_MATH_MAT4_R3C3 15

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

inline PossumMathMat4
possum_math_mat4_multiply() {

    PossumMathMat4 m4c = {0};

    return(m4c);
}


// inline PossumMathMat4
// possum_math_mat4_multiply(
//     PossumMathMat4Ptr m4a,
//     PossumMathMat4Ptr m4b) {

//     PossumMathMat4 m4c = {0};

//     f32p m4a_m = m4a->m;    
//     f32p m4b_m = m4b->m;    

//     //ROW 0
//     m4c.m[POSSUM_MATH_MAT4_R0C0] = 
//         (m4a_m[POSSUM_MATH_MAT4_R0C0] * m4b_m[POSSUM_MATH_MAT4_R0C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C1] * m4b_m[POSSUM_MATH_MAT4_R1C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C2] * m4b_m[POSSUM_MATH_MAT4_R2C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C3] * m4b_m[POSSUM_MATH_MAT4_R3C0]); 
    
//     m4c.m[POSSUM_MATH_MAT4_R0C1] = 
//         (m4a_m[POSSUM_MATH_MAT4_R0C0] * m4b_m[POSSUM_MATH_MAT4_R0C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C1] * m4b_m[POSSUM_MATH_MAT4_R1C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C2] * m4b_m[POSSUM_MATH_MAT4_R2C1]) +
//         (m4a_m[POSSUM_MATH_MAT4_R0C3] * m4b_m[POSSUM_MATH_MAT4_R3C1]);
    
//     m4c.m[POSSUM_MATH_MAT4_R0C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R0C0] * m4b_m[POSSUM_MATH_MAT4_R0C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C1] * m4b_m[POSSUM_MATH_MAT4_R1C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C2] * m4b_m[POSSUM_MATH_MAT4_R2C2]) +
//         (m4a_m[POSSUM_MATH_MAT4_R0C3] * m4b_m[POSSUM_MATH_MAT4_R3C2]);

//     m4c.m[POSSUM_MATH_MAT4_R0C3] = 
//         (m4a_m[POSSUM_MATH_MAT4_R0C0] * m4b_m[POSSUM_MATH_MAT4_R0C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C1] * m4b_m[POSSUM_MATH_MAT4_R1C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R0C2] * m4b_m[POSSUM_MATH_MAT4_R2C3]) +
//         (m4a_m[POSSUM_MATH_MAT4_R0C3] * m4b_m[POSSUM_MATH_MAT4_R3C3]);
    
//     //ROW 1
//     m4c.m[POSSUM_MATH_MAT4_R1C0] = 
//         (m4a_m[POSSUM_MATH_MAT4_R1C0] * m4b_m[POSSUM_MATH_MAT4_R0C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C1] * m4b_m[POSSUM_MATH_MAT4_R1C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C2] * m4b_m[POSSUM_MATH_MAT4_R2C0]);
//         (m4a_m[POSSUM_MATH_MAT4_R1C3] * m4b_m[POSSUM_MATH_MAT4_R3C0]);
    
//     m4c.m[POSSUM_MATH_MAT4_R1C1] = 
//         (m4a_m[POSSUM_MATH_MAT4_R1C0] * m4b_m[POSSUM_MATH_MAT4_R0C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C1] * m4b_m[POSSUM_MATH_MAT4_R1C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C2] * m4b_m[POSSUM_MATH_MAT4_R2C1]) +
//         (m4a_m[POSSUM_MATH_MAT4_R1C3] * m4b_m[POSSUM_MATH_MAT4_R3C1]);
    
//     m4c.m[POSSUM_MATH_MAT4_R1C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R1C0] * m4b_m[POSSUM_MATH_MAT4_R0C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C1] * m4b_m[POSSUM_MATH_MAT4_R1C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C2] * m4b_m[POSSUM_MATH_MAT4_R2C2]) +
//         (m4a_m[POSSUM_MATH_MAT4_R1C3] * m4b_m[POSSUM_MATH_MAT4_R3C2]);
    
//     m4c.m[POSSUM_MATH_MAT4_R1C3] = 
//         (m4a_m[POSSUM_MATH_MAT4_R1C0] * m4b_m[POSSUM_MATH_MAT4_R0C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C1] * m4b_m[POSSUM_MATH_MAT4_R1C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R1C2] * m4b_m[POSSUM_MATH_MAT4_R2C3]) +
//         (m4a_m[POSSUM_MATH_MAT4_R1C3] * m4b_m[POSSUM_MATH_MAT4_R3C3]);

//     //ROW 2
//     m4c.m[POSSUM_MATH_MAT4_R2C0] = 
//         (m4a_m[POSSUM_MATH_MAT4_R2C0] * m4b_m[POSSUM_MATH_MAT4_R0C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C1] * m4b_m[POSSUM_MATH_MAT4_R1C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C2] * m4b_m[POSSUM_MATH_MAT4_R2C0]) +
//         (m4a_m[POSSUM_MATH_MAT4_R2C3] * m4b_m[POSSUM_MATH_MAT4_R3C0]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C1] = 
//         (m4a_m[POSSUM_MATH_MAT4_R2C0] * m4b_m[POSSUM_MATH_MAT4_R0C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C1] * m4b_m[POSSUM_MATH_MAT4_R1C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C2] * m4b_m[POSSUM_MATH_MAT4_R2C1]) +
//         (m4a_m[POSSUM_MATH_MAT4_R2C3] * m4b_m[POSSUM_MATH_MAT4_R3C1]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R2C0] * m4b_m[POSSUM_MATH_MAT4_R0C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C1] * m4b_m[POSSUM_MATH_MAT4_R1C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C2] * m4b_m[POSSUM_MATH_MAT4_R2C2]) +
//         (m4a_m[POSSUM_MATH_MAT4_R2C3] * m4b_m[POSSUM_MATH_MAT4_R3C2]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R2C0] * m4b_m[POSSUM_MATH_MAT4_R0C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C1] * m4b_m[POSSUM_MATH_MAT4_R1C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R2C2] * m4b_m[POSSUM_MATH_MAT4_R2C3]) +
//         (m4a_m[POSSUM_MATH_MAT4_R2C3] * m4b_m[POSSUM_MATH_MAT4_R3C3]);

//     //ROW 3
//     m4c.m[POSSUM_MATH_MAT4_R2C0] = 
//         (m4a_m[POSSUM_MATH_MAT4_R3C0] * m4b_m[POSSUM_MATH_MAT4_R0C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C1] * m4b_m[POSSUM_MATH_MAT4_R1C0]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C2] * m4b_m[POSSUM_MATH_MAT4_R2C0]) +
//         (m4a_m[POSSUM_MATH_MAT4_R3C3] * m4b_m[POSSUM_MATH_MAT4_R3C0]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C1] = 
//         (m4a_m[POSSUM_MATH_MAT4_R3C0] * m4b_m[POSSUM_MATH_MAT4_R0C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C1] * m4b_m[POSSUM_MATH_MAT4_R1C1]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C2] * m4b_m[POSSUM_MATH_MAT4_R2C1]) +
//         (m4a_m[POSSUM_MATH_MAT4_R3C3] * m4b_m[POSSUM_MATH_MAT4_R3C1]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R3C0] * m4b_m[POSSUM_MATH_MAT4_R0C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C1] * m4b_m[POSSUM_MATH_MAT4_R1C2]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C2] * m4b_m[POSSUM_MATH_MAT4_R2C2]) +
//         (m4a_m[POSSUM_MATH_MAT4_R3C3] * m4b_m[POSSUM_MATH_MAT4_R3C2]);
    
//     m4c.m[POSSUM_MATH_MAT4_R2C2] = 
//         (m4a_m[POSSUM_MATH_MAT4_R3C0] * m4b_m[POSSUM_MATH_MAT4_R0C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C1] * m4b_m[POSSUM_MATH_MAT4_R1C3]) + 
//         (m4a_m[POSSUM_MATH_MAT4_R3C2] * m4b_m[POSSUM_MATH_MAT4_R2C3]) +
//         (m4a_m[POSSUM_MATH_MAT4_R3C3] * m4b_m[POSSUM_MATH_MAT4_R3C3]);

//     return(m4c);
// }


#endif //POSSUM_MATH_MAT4_HPP