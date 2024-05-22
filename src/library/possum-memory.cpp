#pragma once

#include "possum-memory.hpp"

PossumMemoryPtr possum_memory;

internal void
possum_memory_initialize() {

    //fuck it, we're gonna reserve the most amount of memory we can
    u64 core_memory_size = 0xFFFFFFFF;

    //use the platform to reserve the memory
    memory core_memory = possum_platform_memory_allocate(core_memory_size);

    POSSUM_NOP();
}