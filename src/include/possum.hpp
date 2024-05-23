#ifndef POSSUM_HPP
#define POSSUM_HPP

#include "possum-types.hpp"
#include "possum-math.hpp"
#include "possum-handle.hpp"
#include "possum-memory.hpp"

typedef void* PossumContext;

api PossumContext
possum_initialize();

#endif //POSSUM_HPP