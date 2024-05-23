#pragma once

#include <possum.hpp>

int main(int argc, char** argv) {
    
    PossumContext possum = possum_initialize();
    
    u64 arena_size_bytes_1 = POSSUM_MATH_SIZE_KILOBYTES(1);
    u64 arena_size_bytes_2 = POSSUM_MATH_SIZE_KILOBYTES(1);
    u64 arena_size_bytes_3 = POSSUM_MATH_SIZE_KILOBYTES(1);

    PossumHandle arena_1 = possum_memory_arena_create(arena_size_bytes_1,"arena 1");
    PossumHandle arena_2 = possum_memory_arena_create(arena_size_bytes_2,"arena 2");
    PossumHandle arena_3 = possum_memory_arena_create(arena_size_bytes_3,"arena 3");

    return(0);
}