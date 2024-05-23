#ifndef POSSUM_MATH_HPP
#define POSSUM_MATH_HPP

#include "possum-types.hpp"

#define POSSUM_MATH_SIZE_KILOBYTE         1024
#define POSSUM_MATH_SIZE_KILOBYTES(size)  (size * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_MEGABTYTES(size) (POSSUM_MATH_SIZE_KILOBYTES(size)  * POSSUM_MATH_SIZE_KILOBYTE);
#define POSSUM_MATH_SIZE_GIABYTES(size)   (POSSUM_MATH_SIZE_MEGABTYTES(size) * POSSUM_MATH_SIZE_KILOBYTE);

#endif //POSSUM_MATH_HPP