#ifndef POSSUM_HPP
#define POSSUM_HPP

#include "possum-types.hpp"
#include "possum-handle.hpp"

struct PossumContext {
    u32 x;
};

typedef PossumContext* PossumContextPtr;

PossumContextPtr possum_context;

api void
possum_initialize();

#endif //POSSUM_HPP