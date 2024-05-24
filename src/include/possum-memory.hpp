#ifndef POSSUM_MEMORY_HPP
#define POSSUM_MEMORY_HPP

#include "possum-types.hpp"
#include "possum-handle.hpp"

#define POSSUM_MEMORY_ARENA_COUNT_MAX      1024
#define POSSUM_MEMORY_ARENA_INDEX_INVALID -1

typedef void* PossumMemory;
typedef void* PossumMemoryArena;
typedef void* PossumMemoryArenaTable;

enum PossumMemoryErrorCode {
    POSSUM_MEMORY_ERROR_CODE_INVALID          = -1,
    POSSUM_MEMORY_ERROR_CODE_MAX_ARENAS       = -2,
    POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE = -3
};

api PossumHandle
possum_memory_arena_create(
    const u64   arena_size_bytes,
    const char* arena_tag);

api b8
possum_memory_arena_handle_valid(
    PossumHandle handle);


//reserve the next available block in the arena
api memory
possum_memory_arena_reserve_block(
    PossumHandle arena_handle,
    u64          block_size_bytes,
    u64          block_offset = 0);

//free a block
api void
possum_memory_arena_free_block(
    memory block);

#endif //POSSUM_MEMORY_HPP