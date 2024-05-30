#ifndef POSSUM_MATH_QUATERNION_HPP
#define POSSUM_MATH_QUATERNION_HPP

#include "possum-types.hpp"

struct PossumMathQuaternion {
    union {

        struct {
            f32 w;
            f32 x;
            f32 y;
            f32 z;
        };

        f32 wxyz[4];
    };
};

#define POSSUM_MATH_QUATERNION_W 0
#define POSSUM_MATH_QUATERNION_X 1
#define POSSUM_MATH_QUATERNION_Y 2
#define POSSUM_MATH_QUATERNION_Z 3

typedef PossumMathQuaternion* PossumMathQuaternionPtr;

inline PossumMathQuaternion
possum_math_quaternion_angle_radians_x(
    f32 angle_radians) {

    f32 angle_radians_half = angle_radians * 0.5f; 

    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;

    return(q);
}


inline PossumMathQuaternion
possum_math_quaternion_angle_radians_y(
    f32 angle_radians) {

    f32 angle_radians_half = angle_radians * 0.5f; 

    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;
    q.y = sin_r; 

    return(q);
}

inline PossumMathQuaternion
possum_math_quaternion_angle_radians_z(
    f32 angle_radians) {

    f32 angle_radians_half = angle_radians * 0.5f; 
    
    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;
    q.z = sin_r;

    return(q);
}

inline PossumMathQuaternion
possum_math_quaternion_angle_degrees_x(
    f32 angle_degrees) {

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees); 

    f32 angle_radians_half = angle_radians * 0.5f; 

    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;

    return(q);
}


inline PossumMathQuaternion
possum_math_quaternion_angle_degrees_y(
    f32 angle_degrees) {

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees); 

    f32 angle_radians_half = angle_radians * 0.5f; 

    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;
    q.y = sin_r; 

    return(q);
}

inline PossumMathQuaternion
possum_math_quaternion_angle_degrees_z(
    f32 angle_degrees) {

    f32 angle_radians = possum_math_trig_degrees_to_radians(angle_degrees); 

    f32 angle_radians_half = angle_radians * 0.5f; 
    
    f32 cos_r = cosf(angle_radians_half);
    f32 sin_r = sinf(angle_radians_half);

    PossumMathQuaternion q = {0};

    q.w = cos_r;
    q.z = sin_r;

    return(q);
}

struct PossumMathQuaternionCache {
    union {

        struct {
            f32 cos_roll;
            f32 sin_roll;
            f32 cos_pitch;
            f32 sin_pitch;
            f32 cos_yaw;
            f32 sin_yaw;
        };

        f32 c[6];
    };
};

inline PossumMathQuaternionCache
possum_math_quaternion_cache(
    f32 radians_roll,
    f32 radians_pitch,
    f32 radians_yaw) {

    PossumMathQuaternionCache cache = {0};

    f32 half_radians_roll  = radians_roll  * 0.5f;
    f32 half_radians_pitch = radians_pitch * 0.5f;
    f32 half_radians_yaw   = radians_yaw   * 0.5f;

    cache.cos_roll  = cosf(half_radians_roll);
    cache.sin_roll  = sinf(half_radians_roll);
    cache.cos_pitch = cosf(half_radians_pitch);
    cache.sin_pitch = sinf(half_radians_pitch);
    cache.cos_yaw   = cosf(half_radians_yaw);
    cache.sin_yaw   = sinf(half_radians_yaw);

    return(cache);
}

#define POSSUM_MATH_QUATERNION_CACHE_COS_ROLL  0
#define POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL  1
#define POSSUM_MATH_QUATERNION_CACHE_COS_PITCH 2
#define POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH 3
#define POSSUM_MATH_QUATERNION_CACHE_COS_YAW   4
#define POSSUM_MATH_QUATERNION_CACHE_SIN_YAW   5

inline PossumMathQuaternion
possum_math_quaternion_euler_angles_radians(
    f32 radians_roll,
    f32 radians_pitch,
    f32 radians_yaw) {

    PossumMathQuaternionCache cache =
        possum_math_quaternion_cache(
            radians_roll,
            radians_pitch,
            radians_yaw);

    f32p c = cache.c;

    PossumMathQuaternion q = {0};

    q.w = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) + 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.x = 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) - 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.y = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) + 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.z = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]) - 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]);

    return(q);
}

inline PossumMathQuaternion
possum_math_quaternion_euler_angles_degrees(
    f32 degrees_roll,
    f32 degrees_pitch,
    f32 degrees_yaw) {

    f32 radians_roll  = possum_math_trig_degrees_to_radians(degrees_roll); 
    f32 radians_pitch = possum_math_trig_degrees_to_radians(degrees_pitch); 
    f32 radians_yaw   = possum_math_trig_degrees_to_radians(degrees_yaw); 


    PossumMathQuaternionCache cache =
        possum_math_quaternion_cache(
            radians_roll,
            radians_pitch,
            radians_yaw);

    f32p c = cache.c;

    PossumMathQuaternion q = {0};

    q.w = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) + 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.x = 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) - 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.y = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]) + 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]);
    q.z = 
        (c[POSSUM_MATH_QUATERNION_CACHE_COS_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_COS_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_YAW]) - 
        (c[POSSUM_MATH_QUATERNION_CACHE_SIN_ROLL] * c[POSSUM_MATH_QUATERNION_CACHE_SIN_PITCH] * c[POSSUM_MATH_QUATERNION_CACHE_COS_YAW]);

    return(q);
}


inline PossumMathQuaternion
possum_math_quaternion_multiply(
    PossumMathQuaternionPtr q_a,
    PossumMathQuaternionPtr q_b) {
    
    f32p q_a_wxyz = q_a->wxyz;
    f32p q_b_wxyz = q_b->wxyz;

    PossumMathQuaternion q = {0};

    q.x = 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_W] * q_b_wxyz[POSSUM_MATH_QUATERNION_X]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_X] * q_b_wxyz[POSSUM_MATH_QUATERNION_W]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Y] * q_b_wxyz[POSSUM_MATH_QUATERNION_Z]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Z] * q_b_wxyz[POSSUM_MATH_QUATERNION_Y]);
    q.y = 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_W] * q_b_wxyz[POSSUM_MATH_QUATERNION_Y]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_X] * q_b_wxyz[POSSUM_MATH_QUATERNION_Z]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Y] * q_b_wxyz[POSSUM_MATH_QUATERNION_W]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Z] * q_b_wxyz[POSSUM_MATH_QUATERNION_X]);
    q.z = 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_W] * q_b_wxyz[POSSUM_MATH_QUATERNION_Z]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_X] * q_b_wxyz[POSSUM_MATH_QUATERNION_Y]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Y] * q_b_wxyz[POSSUM_MATH_QUATERNION_X]) + 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Z] * q_b_wxyz[POSSUM_MATH_QUATERNION_Y]);
    q.w = 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_W] * q_b_wxyz[POSSUM_MATH_QUATERNION_W]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_X] * q_b_wxyz[POSSUM_MATH_QUATERNION_X]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Y] * q_b_wxyz[POSSUM_MATH_QUATERNION_Y]) - 
        (q_a_wxyz[POSSUM_MATH_QUATERNION_Z] * q_b_wxyz[POSSUM_MATH_QUATERNION_Z]);

    return(q);
}

#endif //POSSUM_MATH_QUATERNION_HPP