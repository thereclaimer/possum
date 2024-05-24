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
struct PossumHandle {
    union {
        
        struct {
            
            //this is the type of handle it is
            //you can look at this and always know
            //what type of data this handle is for
            u8 type;
            
            //this is the unique id of whatever the handle is for
            //most likely an index in an array
            //it is signed so that the system that created it
            //can use this as an error code
            s16 uid;

            //this is data specific to the system that created the handle
            //its whatever data is meaningful to help associate the handle
            //with unique data
            u16 meta;
        };

        u64 value;
    };
};

enum PossumHandleType : u8 {
    POSSUM_HANDLE_TYPE_INVALID = 0,
    POSSUM_HANDLE_TYPE_ARENA   = 1
};

api PossumHandle
possum_handle_create(
    PossumHandleType type
);

#endif //POSSUM_HANDLE_HPP