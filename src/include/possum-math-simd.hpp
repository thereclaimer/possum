#ifndef POSSUM_MATH_SIMD_HPP 
#define POSSUM_MATH_SIMD_HPP

#include <immintrin.h> 
#include "possum-types.hpp"

//this register can store 4 f32 values
typedef __m128 reg4f32;

//this register can store 8 f32 values
typedef __m256 reg8f32;

struct PossumMathSimdValues4f32;
struct PossumMathSimdValues8f32;

typedef PossumMathSimdValues4f32* PossumMathSimdValues4f32Ptr;
typedef PossumMathSimdValues8f32* PossumMathSimdValues8f32Ptr;

#define possum_math_simd_reg4f32_load(f32_addr)                 _mm_loadu_ps(f32_addr) 
#define possum_math_simd_reg4f32_multiply(reg4f32_a, reg4f32_b) _mm_mul_ps(reg4f32_a, reg4f32_b) 
#define possum_math_simd_reg4f32_store(f32_addr,reg4f32_a)      _mm_storeu_ps(f32_addr,reg4f32_a)

struct PossumMathSimdValues4f32 {

    union {

        struct {
            f32 f32_0;
            f32 f32_1;
            f32 f32_2;
            f32 f32_3;
        };

        f32 values[4];
    };
};

struct PossumMathSimdValues8f32 {

    union {

        struct {
            f32 f32_0;
            f32 f32_1;
            f32 f32_2;
            f32 f32_3;
            f32 f32_4;
            f32 f32_5;
            f32 f32_6;
            f32 f32_7;
        };

        f32 values[8];
    };
};

inline void
possum_math_simd_multiply_4f32(
    PossumMathSimdValues4f32Ptr in_4f32_a,
    PossumMathSimdValues4f32Ptr in_4f32_b,
    PossumMathSimdValues4f32Ptr out_4f32_c) {

    //load registers a and b
    reg4f32 register_a = possum_math_simd_reg4f32_load(in_4f32_a->values);
    reg4f32 register_b = possum_math_simd_reg4f32_load(in_4f32_b->values);

    //multiply
    reg4f32 register_c = possum_math_simd_reg4f32_multiply(register_a,register_b);

    //write back 
    possum_math_simd_reg4f32_store(out_4f32_c->values,register_c); 
}

inline void
possum_math_simd_multiply_f32_batch_4(
    const u64  count,
    const f32p in_a,
    const f32p in_b,
          f32p out_c) {

    const u64 remainder      = count % 4;
    const u64 count_adjusted = count - remainder;

    f32p batch_a = NULL;
    f32p batch_b = NULL;

    reg4f32 register_a;
    reg4f32 register_b;
    reg4f32 register_c;

    //do the simd multiplies 4 values at a time
    for (
        u64 index = 0;
        index < count_adjusted;
        index += 4) {

        //load registers a and b
        register_a = possum_math_simd_reg4f32_load(&in_a[index]);
        register_b = possum_math_simd_reg4f32_load(&in_b[index]);

        //multiply
        register_c = possum_math_simd_reg4f32_multiply(register_a,register_b);

        //write back
        possum_math_simd_reg4f32_store(&out_c[index],register_c); 
    }

    //do normal multiplies on the remainders that could not be batched
    for (
        u64 index = count_adjusted;
        index < count;
        ++index) {

        out_c[index] = in_a[index] * in_b[index];
    }
}


#endif //POSSUM_MATH_SIMD_HPP