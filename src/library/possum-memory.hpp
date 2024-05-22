#ifndef POSSUM_MEMORY_HPP
#define POSSUM_MEMORY_HPP

#include "possum-types.hpp"
#include "possum-handle.hpp"
#include "possum-platform.hpp"

typedef struct        PossumMemory;
typedef PossumMemory* PossumMemoryPtr;

typedef struct             PossumMemoryArena;
typedef PossumMemoryArena* PossumMemoryArenaPtr; 

typedef struct                  PossumMemoryArenaTable;
typedef PossumMemoryArenaTable* PossumMemoryArenaTablePtr;

struct PossumMemoryArena {
    u16                  arena_table_index;
    u64                  size_bytes;
    PossumMemoryArenaPtr next;
};


#define POSSUM_MEMORY_ARENA_COUNT_MAX      1024
#define POSSUM_MEMORY_ARENA_INDEX_INVALID -1

struct PossumMemoryArenaTable {
    b8                   active[POSSUM_MEMORY_ARENA_COUNT_MAX];
    PossumMemoryArenaPtr arena_pointers[POSSUM_MEMORY_ARENA_COUNT_MAX];
};

struct PossumMemory {
    u64                    size_bytes;
    PossumMemoryArenaTable arena_table;
    PossumMemoryArenaPtr   arenas;
};

internal void
possum_memory_initialize();

api PossumHandle
possum_memory_arena_create(
    u64 arena_size_bytes);

#endif //POSSUM_MEMORY_HPP