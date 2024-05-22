#ifndef POSSUM_MEMORY_HPP
#define POSSUM_MEMORY_HPP

#include "possum-types.hpp"
#include "possum-handle.hpp"

typedef struct        PossumMemory;
typedef PossumMemory* PossumMemoryPtr;

typedef struct             PossumMemoryArena;
typedef PossumMemoryArena* PossumMemoryArenaPtr; 

struct PossumMemoryArena {
    u64                  size_bytes;
    PossumMemoryArenaPtr next;
};

struct PossumMemory {
    PossumMemoryArenaPtr arenas;
};

internal void
possum_memory_initialize();

api PossumHandle
possum_memory_arena_create(
    u64 arena_size_bytes);

#endif //POSSUM_MEMORY_HPP