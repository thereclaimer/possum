#pragma once

#include <possum.hpp>

struct MyStruct {
    u8  a;
    u16 b;
    u32 c;
};

int main(int argc, char** argv) {
    
    PossumContext possum = possum_initialize();
    
    //let's create some arenas
    u64 arena_size_bytes_1 = POSSUM_MATH_SIZE_KILOBYTES(1);
    u64 arena_size_bytes_2 = POSSUM_MATH_SIZE_KILOBYTES(2);
    u64 arena_size_bytes_3 = POSSUM_MATH_SIZE_KILOBYTES(3);

    PossumHandle arena_handle_1 = possum_memory_arena_create(arena_size_bytes_1,"arena 1");
    PossumHandle arena_handle_2 = possum_memory_arena_create(arena_size_bytes_2,"arena 2");
    PossumHandle arena_handle_3 = possum_memory_arena_create(arena_size_bytes_3,"arena 3");

    POSSUM_ASSERT(possum_memory_arena_handle_valid(arena_handle_1));
    POSSUM_ASSERT(possum_memory_arena_handle_valid(arena_handle_2));
    POSSUM_ASSERT(possum_memory_arena_handle_valid(arena_handle_3));

    //let's reserve some blocks in those arenas
    memory arena_1_block_1 = 
        possum_memory_arena_reserve_block(
            arena_handle_1,
            sizeof(MyStruct));

    return(0);
}