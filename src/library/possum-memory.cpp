#pragma once

#include "possum-memory.hpp"

PossumMemoryPtr possum_memory;

internal void
possum_memory_initialize() {

    //fuck it, we're gonna reserve the most amount of memory we can
    u64 core_memory_size = 0xFFFFFFFF;

    //use the platform to reserve the memory
    memory core_memory = possum_platform_memory_allocate(core_memory_size);

    //initialize the memory structure
    possum_memory = (PossumMemoryPtr)core_memory;
    *possum_memory = {0};
    possum_memory->size_bytes = core_memory_size;
}

internal PossumMemoryTraversal
possum_memory_arena_travese() {

    //the starting size is the size of the memory structure
    u64 memory_size_bytes = sizeof(PossumMemory);

    //traverse to the end of the arenas
    PossumMemoryArenaPtr arena_ptr = NULL;
    for (
        arena_ptr = possum_memory->arenas;
        arena_ptr != NULL && arena_ptr->next != NULL;
        arena_ptr = arena_ptr->next) {

        memory_size_bytes += 
            sizeof(PossumMemoryArena) + arena_ptr->size_bytes;

    }

    memory base_memory = (memory)possum_memory;

    PossumMemoryTraversal traversal = {0};
    traversal.used_memory_bytes = memory_size_bytes;
    traversal.tail_arena        = arena_ptr;
    traversal.tail_arena_end    = base_memory + memory_size_bytes;

    return(traversal);
}

external PossumHandle
possum_memory_arena_create(
    const u64   arena_size_bytes,
    const char* arena_tag) {
    
    auto possum_memory_arena_table                = &possum_memory->arena_table;
    auto possum_memory_arena_table_active         = possum_memory_arena_table->active;
    auto possum_memory_arena_table_arena_pointers = possum_memory_arena_table->arena_pointers;

    PossumHandle arena_handle = {0};
    arena_handle.type = POSSUM_HANDLE_TYPE_ARENA;
    arena_handle.uid  = POSSUM_MEMORY_ARENA_INDEX_INVALID;

    for (
        u16 arena_table_index = 0;
        arena_table_index < POSSUM_MEMORY_ARENA_COUNT_MAX;
        ++arena_table_index) {
        
        //if the arena index is available, activate it
        if (!possum_memory_arena_table_active[arena_table_index]) {
            possum_memory_arena_table_active[arena_table_index] = true;
            arena_handle.uid = arena_table_index;
            break;
        }
    }

    //if we didn't find an index, we're done
    if (arena_handle.uid == POSSUM_MEMORY_ARENA_INDEX_INVALID) {
        arena_handle.uid = POSSUM_MEMORY_ERROR_CODE_MAX_ARENAS;
        return(arena_handle);
    }

    //we need to set the memory of the new arena
    memory               new_arena_memory = NULL;
    PossumMemoryArenaPtr new_arena        = NULL; 

    if (possum_memory->arenas == NULL) {
        //this is the first arena, so just set it
        memory base_memory    = (memory)possum_memory;
        new_arena_memory      = base_memory + POSSUM_MEMORY_BASE_SIZE_BYTES;
        new_arena             = (PossumMemoryArenaPtr)new_arena_memory;
        possum_memory->arenas = new_arena; 
    } 
    else {

        //we've got arenas already, so append the new one to the last one
        PossumMemoryArenaPtr tail_arena = NULL;

        u64 memory_used_bytes = POSSUM_MEMORY_BASE_SIZE_BYTES;

        for (
            tail_arena = possum_memory->arenas;
            tail_arena->next != NULL;
            tail_arena = tail_arena->next) {
            
            //while we're at it, we're going to make sure we actually have the space
            memory_used_bytes += POSSUM_MEMORY_ARENA_SIZE_BYTES(tail_arena);
        }

        //make sure we have enough space, if not we're done
        if (memory_used_bytes + arena_size_bytes > possum_memory->size_bytes) {
            arena_handle.uid = POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE;
            return(arena_handle);
        }

        //set the memory of the new arena
        memory tail_arena_memory = (memory)tail_arena;
        memory new_arena_memory  = tail_arena_memory + tail_arena->size_bytes;

        new_arena = (PossumMemoryArenaPtr)new_arena_memory;
        tail_arena->next = new_arena;
    }

    //initialize the new arena
    new_arena->arena_table_index = arena_handle.uid;
    new_arena->size_bytes        = arena_size_bytes;
    new_arena->next              = NULL;
    strcpy(
        new_arena->tag,
        arena_tag
    );

    //set the address in the arena table
    possum_memory_arena_table_arena_pointers[arena_handle.uid] = new_arena;

    return(arena_handle);
}