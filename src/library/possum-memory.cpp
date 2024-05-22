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


external PossumHandle
possum_memory_arena_create(
    u64 arena_size_bytes) {
    
    auto possum_memory_arena_table                = &possum_memory->arena_table;
    auto possum_memory_arena_table_active         = possum_memory_arena_table->active;
    auto possum_memory_arena_table_arena_pointers = possum_memory_arena_table->arena_pointers;

    PossumHandle arena_handle = {0};

    u16 new_arena_index;

    for (
        u16 arena_table_index = 0;
        arena_table_index < POSSUM_MEMORY_ARENA_COUNT_MAX;
        ++arena_table_index) {
        
        //if the arena index is available, activate it
        if (!possum_memory_arena_table_active[arena_table_index]) {
            possum_memory_arena_table_active[arena_table_index] = true;
            new_arena_index = arena_table_index;
        }
    }

    return(arena_handle);
}