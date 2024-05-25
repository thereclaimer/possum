#pragma once

#include <random>
#include <time.h>
#include <float.h>
#include <possum.hpp>

internal void
generate_values(
    const u64  count,
          f32p values) {

    const f32 scale = 1.0f / FLT_MAX;

    for (
        u64 index = 0;
        index < count;
        ++index) {

        values[index] = rand() * scale;
    }
}

int main(int argc, char** argv) {

    srand(time(0));

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
    possum_math_simd_multiply_f32_batch_4(
        values_count,
        values_a,
        values_b,
        values_c_simd);

    //everything should be equal
    for (
        u64 index = 0;
        index < values_count;
        ++index) {

        POSSUM_ASSERT(values_c_scalar[index] = values_c_simd[index]);
    }

    return(0);
}