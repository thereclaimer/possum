#ifndef POSSUM_MEMORY_HPP
#define POSSUM_MEMORY_HPP

#include <cstring>

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
    char                 tag[32];
    PossumMemoryArenaPtr next;
};


#define POSSUM_MEMORY_ARENA_COUNT_MAX      1024
#define POSSUM_MEMORY_ARENA_INDEX_INVALID -1

enum PossumMemoryErrorCode {
    POSSUM_MEMORY_ERROR_CODE_INVALID          = -1,
    POSSUM_MEMORY_ERROR_CODE_MAX_ARENAS       = -2,
    POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE = -3
};

struct PossumMemoryArenaTable {
    b8                   active[POSSUM_MEMORY_ARENA_COUNT_MAX];
    PossumMemoryArenaPtr arena_pointers[POSSUM_MEMORY_ARENA_COUNT_MAX];
};

struct PossumMemoryTraversal {
    PossumMemoryArenaPtr tail_arena;
    memory               tail_arena_end;
    u64                  used_memory_bytes;                  
};


struct PossumMemory {
    u64                    size_bytes;
    PossumMemoryArenaTable arena_table;
    PossumMemoryArenaPtr   arenas;
};

#define POSSUM_MEMORY_BASE_SIZE_BYTES             sizeof(PossumMemory);
#define POSSUM_MEMORY_ARENA_SIZE_BYTES(arena_ptr) (sizeof(PossumMemoryArena) + arena_ptr->size_bytes) 

internal void
possum_memory_initialize();

api PossumHandle
possum_memory_arena_create(
    const u64   arena_size_bytes,
    const char* arena_tag);

#endif //POSSUM_MEMORY_HPP