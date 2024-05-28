#ifndef POSSUM_MATH_TRIG_HPP
#define POSSUM_MATH_TRIG_HPP

#include <math.h>
#include "possum-types.hpp"

#define POSSUM_MATH_TRIG_PI                  3.14159265
#define POSSUM_MATH_TRIG_PI_OVER_180         0.01745329
#define POSSUM_MATH_TRIG_180_OVER_PI        57.29577957


inline f32
possum_math_trig_degrees_to_radians(
    f32 degrees) {
    
    f32 radians = degrees * POSSUM_MATH_TRIG_PI_OVER_180;
    return(radians);
}

inline f32
possum_math_trig_radians_to_degrees(
    f32 radians) {
    
    f32 degrees = radians * POSSUM_MATH_TRIG_180_OVER_PI;
    return(radians);
}

#endif //POSSUM_MATH_TRIG_HPP