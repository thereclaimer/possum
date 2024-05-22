#ifndef POSSUM_HANDLE_HPP
#define POSSUM_HANDLE_HPP

#include "possum-types.hpp"

/************************************
 * This is how you interact with data contained in Possum
 * The handle is the better pointer, because this is an opaque reference
 * the internal pointer to the data can change, but the handle will
 * always remain constant and enforce ownership of the data. There are
 * ways to get an actual pointer to the data if you want it, but
 * most of the time using this handle should be sufficient
 ***********************************/
typedef u64 PossumHandle; 

enum PossumHandleType : s8 {
    POSSUM_HANDLE_TYPE_INVALID = 0,
    POSSUM_HANDLE_TYPE_ARENA   = 1
};

api PossumHandle
possum_handle_create(
    PossumHandleType type
);

#endif //POSSUM_HANDLE_HPP