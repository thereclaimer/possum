#pragma once

#include <random>
#include <time.h>
#include <float.h>
#include <possum.hpp>

internal void
generate_values(
    const u64  count,
          f32p values) {

    for (
        u64 index = 0;
        index < count;
        ++index) {

        u32 value = rand() % 100 + 1;

        values[index] = (f32)value;
    }
}

internal void
simd_example_8f32() {

    const u64 values_count = 1024;

    //generate a bunch of values
    f32 values_a[values_count];
    f32 values_b[values_count];

    generate_values(values_count,values_a);
    generate_values(values_count,values_b);
    
    //do a simple batch of multiplies
    f32 values_c_scalar[values_count];
    possum_math_f32_multiply_batch(
        values_count,
        values_a,
        values_b,
        values_c_scalar);

    //now to a simd batch of multiplies
    f32 values_c_simd[values_count];
    possum_math_simd_multiply_4f32_batch(
        values_count,
        values_a,
        values_b,
        values_c_simd);

    //everything should be equal
    for (
        u64 index = 0;
        index < values_count;
        ++index) {

        POSSUM_ASSERT(values_c_scalar[index] == values_c_simd[index]);
    }
}

internal void
simd_example_4f32() {

    const u64 values_count = 1024;

    //generate a bunch of values
    f32 values_a[values_count];
    f32 values_b[values_count];

    generate_values(values_count,values_a);
    generate_values(values_count,values_b);
    
    //do a simple batch of multiplies
    f32 values_c_scalar[values_count];
    possum_math_f32_multiply_batch(
        values_count,
        values_a,
        values_b,
        values_c_scalar);

    //now to a simd batch of multiplies
    f32 values_c_simd[values_count];
    possum_math_simd_multiply_4f32_batch(
        values_count,
        values_a,
        values_b,
        values_c_simd);

    //everything should be equal
    for (
        u64 index = 0;
        index < values_count;
        ++index) {

        POSSUM_ASSERT(values_c_scalar[index] == values_c_simd[index]);
    }
}

int main(int argc, char** argv) {

    srand(time(0));

    simd_example_4f32();
    simd_example_8f32();

    return(0);
}