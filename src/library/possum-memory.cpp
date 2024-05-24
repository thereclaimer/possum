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
    possum_memory->size_bytes     = core_memory_size;
    possum_memory->arena_counter  = 0;
    possum_memory->arena_list     = NULL;
    possum_memory->arena_memory   = core_memory + POSSUM_MEMORY_BASE_SIZE_BYTES;
}

internal PossumMemoryTraversal
possum_memory_arena_travese() {

    //the starting size is the size of the memory structure
    u64 memory_size_bytes = sizeof(PossumMemory);

    //traverse to the end of the arenas
    PossumMemoryArenaPtr arena_ptr = NULL;
    for (
        arena_ptr = possum_memory->arena_list;
        arena_ptr != NULL && arena_ptr->footer.next != NULL;
        arena_ptr = arena_ptr->footer.next) {

        memory_size_bytes += arena_ptr->header.total_size_bytes;
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
    
    auto possum_memory_arena_pointers = possum_memory->arena_pointers;

    PossumHandle arena_handle = {0};
    arena_handle.type = POSSUM_HANDLE_TYPE_ARENA;
    arena_handle.uid  = POSSUM_MEMORY_ARENA_INDEX_INVALID;

    //this is the actual space the new arena is gonna take up
    u64 arena_required_size = possum_memory_arena_required_size_bytes(arena_size_bytes);
    
    //sanity check, make sure the base memory can hold it
    if (arena_required_size > possum_memory->size_bytes) {
        arena_handle.uid = POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE;
        return(arena_handle);
    }

    for (
        u16 arena_index = 0;
        arena_index < POSSUM_MEMORY_ARENA_COUNT_MAX;
        ++arena_index) {
        
        if (!possum_memory_arena_pointers[arena_index]) {
            arena_handle.uid = arena_index;
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

    if (possum_memory->arena_list == NULL) {
        //this is the first arena, so just set it
        memory base_memory        = (memory)possum_memory;
        new_arena_memory          = base_memory + POSSUM_MEMORY_BASE_SIZE_BYTES;
        
        new_arena = 
            possum_memory_arena_from_memory(
                arena_size_bytes,
                arena_required_size,
                new_arena_memory);

        possum_memory->arena_list = new_arena; 
    } 
    else {

        //we've got arenas already, so append the new one to the last one
        PossumMemoryArenaPtr tail_arena = NULL;

        u64 memory_used_bytes = POSSUM_MEMORY_BASE_SIZE_BYTES;

        for (
            tail_arena = possum_memory->arena_list;
            tail_arena->footer.next != NULL;
            tail_arena = tail_arena->footer.next) {
            
            //while we're at it, we're going to make sure we actually have the space
            memory_used_bytes += tail_arena->header.total_size_bytes;
        }

        //make sure we have enough space, if not we're done
        if (memory_used_bytes + arena_size_bytes > possum_memory->size_bytes) {
            arena_handle.uid = POSSUM_MEMORY_ERROR_CODE_NOT_ENOUGH_SPACE;
            return(arena_handle);
        }

        //set the memory of the new arena
        memory tail_arena_memory = (memory)tail_arena;
        memory new_arena_memory  = tail_arena_memory + tail_arena->header.total_size_bytes;

        new_arena = 
            possum_memory_arena_from_memory(
                arena_size_bytes,
                arena_required_size,
                new_arena_memory);

        tail_arena->footer.next = new_arena;
    }

    //set the arena details
    new_arena->header.counter_instance = possum_memory->arena_counter;
    strcpy(
        new_arena->header.tag,
        arena_tag);


    //set the address in the arena table
    possum_memory_arena_pointers[arena_handle.uid] = new_arena;

    //incriment the counter
    ++possum_memory->arena_counter;
    arena_handle.meta = new_arena->header.counter_instance;

    return(arena_handle);
}

external b8
possum_memory_arena_handle_valid(
    PossumHandle handle) {

    //first, make sure we have an active arena handle
    b8 is_arena    = handle.type == POSSUM_HANDLE_TYPE_ARENA;
    if (!is_arena) {
        return(false);
    }

    //get the arena and make sure its active
    PossumMemoryArenaPtr arena_ptr = possum_memory->arena_pointers[handle.uid];
    if (arena_ptr == NULL) {
        return(false);
    }

    //if so, make sure the instance matches the arena
    b8 valid = (arena_ptr->header.counter_instance == handle.meta);

    //if the handle is for an active arena that matches the instance in the handle meta, its valid 
    return(valid);
}

internal PossumMemoryArenaPtr
possum_memory_arena_get(
    PossumHandle arena_handle) {

    //first, make sure we have an active arena handle
    b8 is_arena    = arena_handle.type == POSSUM_HANDLE_TYPE_ARENA;
    if (!is_arena) {
        return(false);
    }

    //get the arena and make sure its active
    PossumMemoryArenaPtr arena_ptr = possum_memory->arena_pointers[arena_handle.uid];
    if (arena_ptr == NULL) {
        return(false);
    }

    //if so, make sure the instance matches the arena
    b8 valid = (arena_ptr->header.counter_instance == arena_handle.meta);

    //if the handle is for an active arena that matches the instance in the handle meta, its valid 
    return(valid ? arena_ptr : NULL);     
}

internal u64
possum_memory_arena_used_size_bytes(
    PossumMemoryArenaPtr arena_ptr) {

    auto arena_footer_blocks = arena_ptr->footer.blocks;

    if (!arena_footer_blocks) {
        return(0);
    }

    u64 arena_used_size_bytes = 0;

    for (
        PossumMemoryBlockPtr memory_block = arena_footer_blocks;
        memory_block->next != NULL;
        memory_block = memory_block->next) {

        arena_used_size_bytes +=
            memory_block->external_handle ?
                memory_block->size_bytes  :
                0;
    }

    return(arena_used_size_bytes);
}

external memory
possum_memory_arena_reserve_block(
    PossumHandle arena_handle,
    u64          block_size_bytes,
    u64          block_offset) {

    //make sure we got a valid arena
    PossumMemoryArenaPtr arena_ptr = possum_memory_arena_get(arena_handle);
    if (arena_ptr == NULL) {
        return(NULL);
    }

    //get the sizes
    u64 arena_memory_size_bytes      = arena_ptr->body.arena_memory_size_bytes;     
    u64 arena_memory_used_size_bytes = possum_memory_arena_used_size_bytes(arena_ptr);

    //sanity check, make sure our reservation isn't bigger than the arena
    if (block_size_bytes > arena_memory_size_bytes) {
        return(NULL);
    }

    //iterate through the blocks and find one available that can fit
    PossumMemoryBlockPtr free_block = NULL;
    for (
        PossumMemoryBlockPtr block = arena_ptr->footer.blocks;
        block->next != NULL;
        block = block->next) {

        if (
            block->external_handle == NULL && 
            block->size_bytes >= block_size_bytes) {
            
            free_block = block;
        }
    }

    //if there's no block we can reserve from, we're done
    if (!free_block) {
        return(NULL);
    }

    //we have a block, so we need to subdivide it

    return(NULL);
}
