#ifndef POSSUM_MATH_SIMD_8F32_HPP
#define POSSUM_MATH_SIMD_8F32_HPP

#include <immintrin.h> 
#include "possum-types.hpp"

//this register can store 8 f32 values
typedef __m256 reg8f32;

struct                    PossumMathSimdValues8f32;
typedef PossumMathSimdValues8f32* PossumMathSimdValues8f32Ptr;


#define possum_math_simd_reg8f32_load(f32_addr)                 _mm256_loadu_ps(f32_addr) 
#define possum_math_simd_reg8f32_store(f32_addr,reg8f32_a)      _mm256_storeu_ps(f32_addr,reg8f32_a)
#define possum_math_simd_reg8f32_multiply(reg8f32_a, reg8f32_b) _mm256_mul_ps(reg8f32_a, reg8f32_b) 
#define possum_math_simd_reg8f32_add(reg8f32_a, reg8f32_b)      _mm256_add_ps(reg8f32_a, reg8f32_b) 
#define possum_math_simd_reg8f32_subtract(reg8f32_a, reg8f32_b) _mm256_sub_ps(reg8f32_a, reg8f32_b) 

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
possum_math_simd_multiply_8f32(
    PossumMathSimdValues8f32Ptr in_8f32_a,
    PossumMathSimdValues8f32Ptr in_8f32_b,
    PossumMathSimdValues8f32Ptr out_8f32_c) {

    //load registers a and b
    reg8f32 register_a = possum_math_simd_reg8f32_load(in_8f32_a->values);
    reg8f32 register_b = possum_math_simd_reg8f32_load(in_8f32_b->values);

    //multiply
    reg8f32 register_c = possum_math_simd_reg8f32_multiply(register_a,register_b);

    //write back 
    possum_math_simd_reg8f32_store(out_8f32_c->values,register_c); 
}

inline void
possum_math_simd_add_8f32(
    PossumMathSimdValues8f32Ptr in_8f32_a,
    PossumMathSimdValues8f32Ptr in_8f32_b,
    PossumMathSimdValues8f32Ptr out_8f32_c) {

    //load registers a and b
    reg8f32 register_a = possum_math_simd_reg8f32_load(in_8f32_a->values);
    reg8f32 register_b = possum_math_simd_reg8f32_load(in_8f32_b->values);

    //multiply
    reg8f32 register_c = possum_math_simd_reg8f32_add(register_a,register_b);

    //write back 
    possum_math_simd_reg8f32_store(out_8f32_c->values,register_c); 
}

inline void
possum_math_simd_multiply_8f32_batch(
    const u64  count,
    const f32p in_a,
    const f32p in_b,
          f32p out_c) {

    const u64 remainder      = count % 8;
    const u64 count_adjusted = count - remainder;

    f32p batch_a = NULL;
    f32p batch_b = NULL;

    reg8f32 register_a;
    reg8f32 register_b;
    reg8f32 register_c;

    //do the simd multiplies 4 values at a time
    for (
        u64 index = 0;
        index < count_adjusted;
        index += 8) {

        //load registers a and b
        register_a = possum_math_simd_reg8f32_load(&in_a[index]);
        register_b = possum_math_simd_reg8f32_load(&in_b[index]);

        //multiply
        register_c = possum_math_simd_reg8f32_multiply(register_a,register_b);

        //write back
        possum_math_simd_reg8f32_store(&out_c[index],register_c); 
    }

    //do normal multiplies on the remainders that could not be batched
    for (
        u64 index = count_adjusted;
        index < count;
        ++index) {

        out_c[index] = in_a[index] * in_b[index];
    }
}

inline void
possum_math_simd_add_8f32_batch(
    const u64  count,
    const f32p in_a,
    const f32p in_b,
          f32p out_c) {

    const u64 remainder      = count % 8;
    const u64 count_adjusted = count - remainder;

    f32p batch_a = NULL;
    f32p batch_b = NULL;

    reg8f32 register_a;
    reg8f32 register_b;
    reg8f32 register_c;

    //do the simd multiplies 4 values at a time
    for (
        u64 index = 0;
        index < count_adjusted;
        index += 8) {

        //load registers a and b
        register_a = possum_math_simd_reg8f32_load(&in_a[index]);
        register_b = possum_math_simd_reg8f32_load(&in_b[index]);

        //multiply
        register_c = possum_math_simd_reg8f32_add(register_a,register_b);

        //write back
        possum_math_simd_reg8f32_store(&out_c[index],register_c); 
    }

    //do normal multiplies on the remainders that could not be batched
    for (
        u64 index = count_adjusted;
        index < count;
        ++index) {

        out_c[index] = in_a[index] + in_b[index];
    }
}


#endif //POSSUM_MATH_SIMD_8F32_HPP