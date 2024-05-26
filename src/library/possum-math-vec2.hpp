#ifndef POSSUM_MATH_VEC2_HPP
#define POSSUM_MATH_VEC2_HPP

#include <math.h>

#include "possum-types.hpp"
#include "possum-math-simd-4f32.hpp"

struct  PossumMathVec2;
typedef PossumMathVec2* PossumMathVec2Ptr;

struct PossumMathVec2 {

    union {

        struct {
            f32 x;
            f32 y;  
        };
    
        f32 values[2];
    };
    
};

inline PossumMathVec2
possum_math_vec2_create(
    const f32 x,
    const f32 y) {

    PossumMathVec2 v2 = {0};
    v2.x = x;
    v2.y = y;

    return(v2);
}

inline PossumMathVec2
possum_math_vec2_copy(
    const PossumMathVec2Ptr v2) {

    PossumMathVec2 v2_copy = {0};
    v2_copy.x = v2->x;
    v2_copy.y = v2->y;

    return(v2_copy);
}

inline bool
possum_math_vec2_are_equal(
    const PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    bool equal = 
        (v2_a->x == v2_b->x) && 
        (v2_a->y == v2_b->y);

    return(equal);
}

inline void
possum_math_vec2_scalar(
          PossumMathVec2Ptr v2,    
    const f32               scalar) {

    v2->x *= scalar;
    v2->y *= scalar;
}

inline f32
possum_math_vec2_magnitude(
    const PossumMathVec2Ptr v2) {

    f32 v2_x = v2->x;
    f32 v2_y = v2->y;

    f32 magnitude = 
        sqrtf(
            (v2_x * v2_x) +
            (v2_y * v2_y)
        );

    return(magnitude);
}

inline void
possum_math_vec2_magnitude_batch(
    const u64               v2_count,
    const PossumMathVec2Ptr in_v2,
          f32p              out_magnitude) {

    PossumMathVec2 i_v2 = {0};

    for(
        u64 v2_index = 0;
        v2_index < v2_count;
        ++v2_index) {

        i_v2 = in_v2[v2_index];

        out_magnitude[v2_index] = 
            sqrtf(
                (i_v2.x * i_v2.x) + 
                (i_v2.y * i_v2.y)  
            );
    }
}

inline void
possum_math_vec2_magnitude_batch_by_4(
    const u64               v2_count,
    const PossumMathVec2Ptr in_v2,
          f32p              out_magnitude) {

    PossumMathVec2 i_v2[4];
    f32            i_v2_x[4];
    f32            i_v2_y[4];
    f32            i_v2_x_square[4];
    f32            i_v2_y_square[4];
    f32            i_v2_x_and_y_square[4];
    f32            i_v2_magnitude[4];

    for(
        u64 v2_index = 0;
        v2_index < v2_count;
        v2_index += 4) {

        i_v2[0] = in_v2[v2_index];
        i_v2[1] = in_v2[v2_index + 1];
        i_v2[2] = in_v2[v2_index + 2];
        i_v2[3] = in_v2[v2_index + 3];

        i_v2_x[0] = i_v2[0].x;
        i_v2_x[1] = i_v2[1].x;
        i_v2_x[2] = i_v2[2].x;
        i_v2_x[3] = i_v2[3].x;

        i_v2_y[0] = i_v2[0].y;
        i_v2_y[1] = i_v2[1].y;
        i_v2_y[2] = i_v2[2].y;
        i_v2_y[3] = i_v2[3].y;

        i_v2_x_square[0] = i_v2_x[0] * i_v2_x[0];
        i_v2_x_square[1] = i_v2_x[1] * i_v2_x[1];
        i_v2_x_square[2] = i_v2_x[2] * i_v2_x[2];
        i_v2_x_square[3] = i_v2_x[3] * i_v2_x[3];

        i_v2_y_square[0] = i_v2_y[0] * i_v2_y[0];
        i_v2_y_square[1] = i_v2_y[1] * i_v2_y[1];
        i_v2_y_square[2] = i_v2_y[2] * i_v2_y[2];
        i_v2_y_square[3] = i_v2_y[3] * i_v2_y[3];

        i_v2_x_and_y_square[0] = i_v2_x_square[0] + i_v2_y_square[0];
        i_v2_x_and_y_square[1] = i_v2_x_square[1] + i_v2_y_square[1]; 
        i_v2_x_and_y_square[2] = i_v2_x_square[2] + i_v2_y_square[2]; 
        i_v2_x_and_y_square[3] = i_v2_x_square[3] + i_v2_y_square[3]; 

        i_v2_magnitude[0] = sqrtf(i_v2_x_and_y_square[0]);
        i_v2_magnitude[1] = sqrtf(i_v2_x_and_y_square[1]);
        i_v2_magnitude[2] = sqrtf(i_v2_x_and_y_square[2]);
        i_v2_magnitude[3] = sqrtf(i_v2_x_and_y_square[3]);

        out_magnitude[v2_index]     = i_v2_magnitude[0];
        out_magnitude[v2_index + 1] = i_v2_magnitude[1];
        out_magnitude[v2_index + 2] = i_v2_magnitude[2];
        out_magnitude[v2_index + 3] = i_v2_magnitude[3];
    }
}

inline void
possum_math_vec2_magnitude_batch_simd(
    const u64               v2_count,
    const PossumMathVec2Ptr in_v2,
          f32p              out_magnitude) {

    PossumMathVec2 i_v2[4];
    f32            i_v2_x[4];
    f32            i_v2_y[4];

    reg4f32 register_i_v2_x;
    reg4f32 register_i_v2_y;
    reg4f32 register_i_v2_x_square;
    reg4f32 register_i_v2_y_square;
    reg4f32 register_i_v2_x_and_y_square;
    reg4f32 register_i_v2_magnitude;
    
    for(
        u64 v2_index = 0;
        v2_index < v2_count;
        v2_index += 4) {

        i_v2[0]   = in_v2[v2_index];
        i_v2[1]   = in_v2[v2_index + 1];
        i_v2[2]   = in_v2[v2_index + 2];
        i_v2[3]   = in_v2[v2_index + 3];

        i_v2_x[0] = i_v2[0].x;
        i_v2_x[1] = i_v2[1].x;
        i_v2_x[2] = i_v2[2].x;
        i_v2_x[3] = i_v2[3].x;

        i_v2_y[0] = i_v2[0].y;
        i_v2_y[1] = i_v2[1].y;
        i_v2_y[2] = i_v2[2].y;
        i_v2_y[3] = i_v2[3].y;

        register_i_v2_x              = possum_math_simd_reg4f32_load(i_v2_x);
        register_i_v2_y              = possum_math_simd_reg4f32_load(i_v2_y);
        register_i_v2_x_square       = possum_math_simd_reg4f32_multiply(register_i_v2_x,register_i_v2_x);
        register_i_v2_y_square       = possum_math_simd_reg4f32_multiply(register_i_v2_y,register_i_v2_y);
        register_i_v2_x_and_y_square = possum_math_simd_reg4f32_add(register_i_v2_x_square,register_i_v2_y_square);
        register_i_v2_magnitude      = possum_math_simd_reg4f32_sqrtf(register_i_v2_x_and_y_square);

        possum_math_simd_reg4f32_store(&out_magnitude[v2_index],register_i_v2_magnitude);
    }
}

inline void
possum_math_vec2_normalize(
    PossumMathVec2Ptr v2) {

    f32 magnitude = possum_math_vec2_magnitude(v2);
    
    f32 magnitude_inverse = 
        magnitude == 0.0f 
            ? 0.0f
            : 1.0f / magnitude; 

    possum_math_vec2_scalar(v2,magnitude_inverse);
}

inline PossumMathVec2
possum_math_vec2_add(
    const PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    PossumMathVec2 v2_c = {0};

    v2_c.x = v2_a->x + v2_b->x;
    v2_c.y = v2_a->y + v2_b->y;

    return(v2_c);
}

inline PossumMathVec2
possum_math_vec2_add_batch(
    const u64               count,
    const PossumMathVec2Ptr in_v2_a,
    const PossumMathVec2Ptr in_v2_b,
          PossumMathVec2Ptr out_v2_c) {

    PossumMathVec2 i_v2_a = {0};
    PossumMathVec2 i_v2_b = {0};
    PossumMathVec2 i_v2_c = {0};

    for (
        u64 index = 0;
        index < count;
        ++index) {

        i_v2_a = in_v2_a[index];
        i_v2_b = in_v2_b[index];
        
        i_v2_c = {0};
        i_v2_c.x = i_v2_a.x + i_v2_b.x;
        i_v2_c.y = i_v2_a.y + i_v2_b.y;

        out_v2_c[index] = i_v2_c;
    }
}

inline void
possum_math_vec2_add_b_to_a(
          PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    v2_a->x += v2_b->x;
    v2_a->y += v2_b->y;
}

inline void
possum_math_vec2_subtract_b_from_a(
          PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    v2_a->x -= v2_b->x;
    v2_a->y -= v2_b->y;
}

inline PossumMathVec2
possum_math_vec2_difference_a_to_b(
    const PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    PossumMathVec2 v2_c = {0};

    v2_c.x = v2_a->x - v2_b->x;
    v2_c.y = v2_a->y - v2_b->y;

    return(v2_c);
}

inline f32
possum_math_vec2_dot(
    const PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    f32 a_dot_b = 
        (v2_a->x * v2_b->x) +  
        (v2_a->y * v2_b->y);

    return(a_dot_b);
}

inline void
possum_math_vec2_dot_batch(
    const u64               v2_count,
    const PossumMathVec2Ptr in_v2_a,
    const PossumMathVec2Ptr in_v2_b,
          f32*              out_a_dot_b) {


    PossumMathVec2 v2_a   = {0};
    PossumMathVec2 v2_b   = {0};
    f32            v2_a_x = 0.0f;
    f32            v2_a_y = 0.0f;
    f32            v2_b_x = 0.0f;
    f32            v2_b_y = 0.0f;

    for (
        u64 index = 0;
        index < v2_count;
        ++index) {
        
        v2_a = in_v2_a[index]; 
        v2_b = in_v2_b[index]; 

        v2_a_x = v2_a.x; 
        v2_a_y = v2_a.y; 
        v2_b_x = v2_b.x;
        v2_b_y = v2_b.y;

        out_a_dot_b[index] =
            (v2_a_x * v2_b_x) +  
            (v2_a_y * v2_b_y); 
    }
}

inline PossumMathVec2
possum_math_vec2_project_a_onto_b(
    const PossumMathVec2Ptr in_v2_a,
    const PossumMathVec2Ptr in_v2_b) {

    f32 a_dot_b = possum_math_vec2_dot(in_v2_a,in_v2_b);
    f32 b_dot_b = possum_math_vec2_dot(in_v2_b,in_v2_b);

    f32 scalar = a_dot_b / b_dot_b;

    PossumMathVec2 projection = possum_math_vec2_copy(in_v2_b);
    possum_math_vec2_scalar(&projection,scalar);

    return(projection);
}

inline PossumMathVec2
possum_math_vec2_reject_a_from_b(
    const PossumMathVec2Ptr in_v2_a,
    const PossumMathVec2Ptr in_v2_b) {

    f32 a_dot_b = possum_math_vec2_dot(in_v2_a,in_v2_b);
    f32 b_dot_b = possum_math_vec2_dot(in_v2_b,in_v2_b);

    f32 scalar = a_dot_b / b_dot_b;

    PossumMathVec2 rejection = possum_math_vec2_difference_a_to_b(in_v2_a,in_v2_b);
    possum_math_vec2_scalar(&rejection,scalar);

    return(rejection);
}



#endif //POSSUM_MATH_VEC2_HPP