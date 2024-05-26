#ifndef POSSUM_MATH_HPP
#define POSSUM_MATH_HPP

#include "possum-types.hpp"
#include "possum-math-simd.hpp"
#include "possum-math-vec2.hpp"
#include "possum-math-vec3.hpp"
#include "possum-math-mat4.hpp"

#define POSSUM_MATH_SIZE_KILOBYTE         1024
#define POSSUM_MATH_SIZE_KILOBYTES(size)  (size * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_MEGABTYTES(size) (POSSUM_MATH_SIZE_KILOBYTES(size)  * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_GIABYTES(size)   (POSSUM_MATH_SIZE_MEGABTYTES(size) * POSSUM_MATH_SIZE_KILOBYTE);

typedef PossumMathVec2 vec2f32;
typedef PossumMathVec3 vec3f32;
typedef PossumMathMat4 mat4f32;

typedef vec2f32* vec2f32ptr;
typedef vec3f32* vec3f32ptr;
typedef mat4f32* mat4f32ptr;


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