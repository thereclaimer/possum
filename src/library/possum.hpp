#ifndef POSSUM_HPP
#define POSSUM_HPP

#include "possum-types.hpp"
#include "possum-handle.hpp"
#include "possum-memory.hpp"
#include "possum-platform.hpp"

typedef struct         PossumContext;
typedef PossumContext* PossumContextPtr;

struct PossumContext {
    u32 x;
};

api PossumContextPtr
possum_initialize();

#endif //POSSUM_HPP