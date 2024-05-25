#ifndef POSSUM_MATH_VEC2_HPP
#define POSSUM_MATH_VEC2_HPP

#include <math.h>

#include "possum-types.hpp"

typedef struct          PossumMathVec2;
typedef PossumMathVec2* PossumMathVec2Ptr;

struct PossumMathVec2 {
    f32 x;
    f32 y;  
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

inline f32
possum_math_vec2_magnitude_batch(
    const u64               v2_count,
    const PossumMathVec2Ptr in_v2,
          f32p              out_magnitude) {


    PossumMathVec2 i_v2      = {0};

    for(
        u64 v2_index = 0;
        v2_index < v2_count;
        v2_index) {

        i_v2 = in_v2[v2_index];

        out_magnitude[v2_index] = 
            sqrtf(
                (i_v2.x * i_v2.x) + 
                (i_v2.y * i_v2.y)  
            );
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
possum_math_vec2_add_new(
    const PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    PossumMathVec2 v2_c = {0};

    v2_c.x = v2_a->x + v2_b->x;
    v2_c.y = v2_a->y + v2_b->y;

    return(v2_c);
}

inline void
possum_math_vec2_add(
          PossumMathVec2Ptr v2_a,
    const PossumMathVec2Ptr v2_b) {

    v2_a->x += v2_b->x;
    v2_a->y += v2_b->y;
}

#endif //POSSUM_MATH_VEC2_HPP