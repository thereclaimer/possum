#ifndef POSSUM_MATH_DIRECTION_HPP
#define POSSUM_MATH_DIRECTION_HPP

#include "possum-math-vec3.hpp"

struct PossumMathDirection  {
    PossumMathVec3 forward;
    PossumMathVec3 right;
    PossumMathVec3 up;
};

typedef PossumMathDirection* PossumMathDirectionPtr;

inline PossumMathVec3
possum_math_direction_up_global() {

    PossumMathVec3 up_global = {0};
    
    up_global.y = 1.0f;

    return(up_global);
}

inline PossumMathDirection
possum_math_direction_default() {
    
    PossumMathDirection direction = {0};

    direction.forward.z =   1.0f;
    direction.right.x   =   1.0f;
    direction.up.y      =   1.0f;

    return(direction);
}

inline PossumMathDirection
possum_math_direction_look_at(
    PossumMathVec3Ptr position,
    PossumMathVec3Ptr target) {

    //calculate the forward vector
    PossumMathVec3 position_diff_target = possum_math_vec3_difference_a_to_b(position,target);
    PossumMathVec3 look_at_forward      = possum_math_vec3_normalize(&position_diff_target);

    //calculate the right vector
    PossumMathVec3 global_up               = possum_math_direction_up_global();
    PossumMathVec3 global_up_cross_forward = possum_math_vec3_cross(&global_up,&look_at_forward);
    PossumMathVec3 look_at_right           = possum_math_vec3_normalize(&global_up_cross_forward);

    //calculate the up vector
    PossumMathVec3 forward_cross_right = possum_math_vec3_cross(&look_at_forward,&look_at_right);
    PossumMathVec3 look_at_up          = possum_math_vec3_normalize(&forward_cross_right);

    //put the look at direction together
    PossumMathDirection look_at = {0};
    look_at.forward = look_at_forward;
    look_at.right   = look_at_right;
    look_at.up      = look_at_up;

    return(look_at);
}

#endif //POSSUM_MATH_DIRECTION_HPP