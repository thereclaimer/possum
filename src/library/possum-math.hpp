#ifndef POSSUM_MATH_HPP
#define POSSUM_MATH_HPP

#include "possum-types.hpp"
#include "possum-math-simd.hpp"
#include "possum-math-vec2.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-mat4.hpp"
#include "possum-math-transform.hpp"

#define POSSUM_MATH_SIZE_KILOBYTE         1024
#define POSSUM_MATH_SIZE_KILOBYTES(size)  (size * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_MEGABTYTES(size) (POSSUM_MATH_SIZE_KILOBYTES(size)  * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_GIABYTES(size)   (POSSUM_MATH_SIZE_MEGABTYTES(size) * POSSUM_MATH_SIZE_KILOBYTE);

typedef PossumMathVec2      vec2f32;
typedef PossumMathVec3      vec3f32;
typedef PossumMathMat4      mat4f32;
typedef PossumMathTransform tfm4f32;

typedef vec2f32* vec2f32ptr;
typedef vec3f32* vec3f32ptr;
typedef mat4f32* mat4f32ptr;
typedef tfm4f32* tfm4f32ptr;

inline f32
possum_math_inverse_square_root_quake(
    f32 number){

    s64 i;
    f32 x2; 
    f32 y;

    const f32 three_halfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( s64 * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( f32 * ) &i;
    y  = y * ( three_halfs - ( x2 * y * y ) );   // 1st iteration
    // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return(y);
    }

inline void
possum_math_f32_add_batch(
    const u64  count,
    const f32p in_a,
    const f32p in_b,
          f32p out_c) {

    for(
        u64 index = 0;
        index < count;
        ++index) {

        out_c[index] = in_a[index] + in_b[index];
    }
}
inline void
possum_math_f32_multiply_batch(
    const u64  count,
    const f32p in_a,
    const f32p in_b,
          f32p out_c) {

    for(
        u64 index = 0;
        index < count;
        ++index) {

        out_c[index] = in_a[index] * in_b[index];
    }
}

#endif //POSSUM_MATH_HPP