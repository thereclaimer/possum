#include "possum.hpp"
#include "possum-platform-win32.cpp"


PossumContextPtr possum_context;

external PossumContextPtr
possum_initialize() {

    //for now, we'll just malloc it

    possum_context = (PossumContextPtr)malloc(sizeof(PossumContext));

    possum_platform_win32_initialize();
    // possum_memory_initialize();

    return(possum_context);
}