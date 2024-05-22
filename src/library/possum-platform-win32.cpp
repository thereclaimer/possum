#pragma once

#include "possum-platform.hpp"
#include "possum-platform-win32.hpp"

PossumPlatformContextPtr possum_platform_context;

internal void
possum_platform_win32_initialize() {

    platform_api.memory_allocate = possum_platform_win32_memory_allocate;     

}

internal memory
possum_platform_win32_memory_allocate(
    u64 memory_size_bytes) {

    memory allocated_memory = 
        (memory)VirtualAlloc(0,memory_size_bytes,MEM_COMMIT,PAGE_READWRITE);
    
    return(allocated_memory);
}