#ifndef POSSUM_MATH_SIMD_8F32_HPP
#define POSSUM_MATH_SIMD_8F32_HPP

#include <immintrin.h> 
#include "possum-types.hpp"

//this register can store 8 f32 values
typedef __m256 reg8f32;

typedef struct                    PossumMathSimdValues8f32;
typedef PossumMathSimdValues8f32* PossumMathSimdValues8f32Ptr;


#define possum_math_simd_reg8f32_load(f32_addr)                 _mm_loadu_ps(f32_addr) 
#define possum_math_simd_reg8f32_store(f32_addr,reg8f32_a)      _mm_storeu_ps(f32_addr,reg8f32_a)
#define possum_math_simd_reg8f32_multiply(reg8f32_a, reg8f32_b) _mm_mul_ps(reg8f32_a, reg8f32_b) 
#define possum_math_simd_reg8f32_add(reg8f32_a, reg8f32_b)      _mm_add_ps(reg8f32_a, reg8f32_b) 
#define possum_math_simd_reg8f32_subtract(reg8f32_a, reg8f32_b) _mm_sub_ps(reg8f32_a, reg8f32_b) 


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



#endif //POSSUM_MATH_SIMD_8F32_HPP