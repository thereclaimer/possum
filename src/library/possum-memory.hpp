#ifndef POSSUM_MEMORY_HPP
#define POSSUM_MEMORY_HPP

#include <cstring>

#include "possum-types.hpp"
#include "possum-handle.hpp"
#include "possum-platform.hpp"


typedef struct PossumMemory;
typedef struct PossumMemoryArena;
typedef struct PossumMemoryBlock;
typedef struct PossumMemoryArenaHeader;
typedef struct PossumMemoryArenaBody; 
typedef struct PossumMemoryArenaFooter;

typedef PossumMemory*            PossumMemoryPtr;
typedef PossumMemoryArena*       PossumMemoryArenaPtr; 
typedef PossumMemoryBlock*       PossumMemoryBlockPtr;
typedef PossumMemoryArenaHeader* PossumMemoryArenaHeaderPtr;
typedef PossumMemoryArenaBody*   PossumMemoryArenaBodyPtr; 
typedef PossumMemoryArenaFooter* PossumMemoryArenaFooterPtr;


//the block is how an arena is divided up
//all blocks are linked together, if it is
//free the external handle pointer will be null
struct PossumMemoryBlock {
    u64                  size_bytes;
    memory               memory;
    handle               external_handle;
    PossumMemoryBlockPtr next;
};

//header is all static data and the size will never change
struct PossumMemoryArenaHeader {
    u16                  arena_table_index;
    u16                  counter_instance;
    u64                  total_size_bytes;
    char                 tag[32];
};

//the body is the actual data divided up by blocks
//its the actual requested size
struct PossumMemoryArenaBody {
    u64    arena_memory_size_bytes;
    memory arena_memory;
};

//the footer is at the end of the arena
//it tracks block reservations and points to the next arena
struct PossumMemoryArenaFooter {
    memory               block_memory;
    PossumMemoryBlockPtr blocks;
    PossumMemoryArenaPtr next;
};

struct PossumMemoryArena {
    PossumMemoryArenaHeader header; //static arena info
    PossumMemoryArenaBody   body;   //block memory
    PossumMemoryArenaFooter footer; //bookkeeping and next arena
};

#define POSSUM_MEMORY_ARENA_COUNT_MAX      1024
#define POSSUM_MEMORY_ARENA_INDEX_INVALID -1

enum PossumMemoryErrorCode {
    POSSUM_MEMORY_ERROR_CODE_INVALID              = -1,
    POSSUM_MEMORY_ERROR_CODE_MAX_ARENAS           = -2,
    POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE     = -3,
    POSSUM_MEMORY_ERROR_CODE_INVALID_ARENA_HANDLE = -4
};

enum PossumMemoryManagementStrategy {
    POSSUM_MEMORY_MANAGEMENT_STRATEGY_STACK = 0,
    POSSUM_MEMORY_MANAGEMENT_STRATEGY_HEAP  = 1
};

struct PossumMemoryTraversal {
    PossumMemoryArenaPtr tail_arena;
    memory               tail_arena_end;
    u64                  used_memory_bytes;                  
};

struct PossumMemory {
    u64                    size_bytes;
    u16                    arena_counter;
    PossumMemoryArenaPtr   arena_pointers[POSSUM_MEMORY_ARENA_COUNT_MAX];
    PossumMemoryArenaPtr   arena_list;
    memory                 arena_memory;
};

#define POSSUM_MEMORY_BASE_SIZE_BYTES sizeof(PossumMemory);

inline u64
possum_memory_arena_required_size_bytes(
    u64 requested_size_bytes) {

    u64 required_size_bytes = 
        sizeof(PossumMemoryArena)       +
        requested_size_bytes;
    
    return(required_size_bytes);
}

inline PossumMemoryArenaPtr
possum_memory_arena_from_memory(
    u64    requested_memory_size_bytes,
    u64    base_memory_size_bytes,
    memory base_memory) {

    //recast our memory to an arena
    PossumMemoryArenaPtr arena = (PossumMemoryArenaPtr)base_memory;
    *arena = {0};

    //we got the new memory, so initialize the new arena
    PossumMemoryArenaHeaderPtr arena_header = &arena->header; 
    PossumMemoryArenaBodyPtr   arena_body   = &arena->body; 
    PossumMemoryArenaFooterPtr arena_footer = &arena->footer; 

    //header
    arena_header->total_size_bytes = base_memory_size_bytes;

    //body
    memory arena_memory = 
        base_memory                     + 
        sizeof(PossumMemoryArenaHeader) + 
        sizeof(PossumMemoryArenaBody);
    
    arena_body->arena_memory_size_bytes = requested_memory_size_bytes;
    arena_body->arena_memory            = arena_memory;

    //footer
    memory block_memory = arena_memory + requested_memory_size_bytes;
    arena_footer->block_memory = block_memory;
    arena_footer->blocks       = NULL;

    return(arena);
}

internal void
possum_memory_initialize();

api PossumHandle
possum_memory_arena_create(
    const u64   arena_size_bytes,
    const char* arena_tag);

api b8
possum_memory_arena_handle_valid(
    PossumHandle handle);

api memory
possum_memory_arena_reserve_block(
    PossumHandle arena_handle,
    u64          block_size_bytes,
    u64          block_offset = 0);

api void
possum_memory_arena_free_block(
    memory block);


#endif //POSSUM_MEMORY_HPP