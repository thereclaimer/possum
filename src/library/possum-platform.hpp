#ifndef POSSUM_PLATFORM_HPP
#define POSSUM_PLATFORM_HPP

#include "possum-types.hpp"

typedef memory 
(*func_possum_platform_memory_allocate)
(
    u64 size
);

typedef void 
(*func_possum_platform_memory_free)
(
    handle, 
    u64
);

typedef  u64 
(*func_possum_platform_file_size)(
    handle file_path,
    b8     terminate);

typedef handle
(*func_possum_platform_file_open)(
    u8* file_path,
    b8  create_new);

typedef void
(*func_possum_platform_file_close)(
    handle file_handle);

typedef void
(*func_possum_platform_file_write)(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer);

typedef void
(*func_possum_platform_file_read)(
    handle file_handle,
    u64    offset,
    u64    allocated_buffer_size,
    memory allocated_buffer,
    b8     terminate);

typedef void
(*func_possum_platform_initialize_graphics_api)
(void);

typedef void
(*func_possum_platform_initialize_imgui)
(void);

typedef void
(*func_possum_platform_imgui_frame_start)
(void);

typedef void
(*func_possum_platform_imgui_frame_end)
(void);

typedef u64
(*func_possum_platform_ticks)
(void);

typedef f64
(*func_possum_platform_delta_time_ms)(
    u64 ticks_before,
    u64 ticks_after);

typedef void
(*func_possum_platform_sleep)(
    u64 time_ms);

struct PossumPlatformApi {
    func_possum_platform_file_size               file_size;
    func_possum_platform_file_read               file_read;
    func_possum_platform_file_write              file_write;
    func_possum_platform_file_open               file_open;
    func_possum_platform_file_close              file_close;
    func_possum_platform_memory_allocate         memory_allocate;
    func_possum_platform_memory_free             memory_free;
    func_possum_platform_initialize_graphics_api graphics_api_init;
    func_possum_platform_initialize_imgui        imgui_init;
    func_possum_platform_imgui_frame_start       imgui_frame_start;
    func_possum_platform_imgui_frame_end         imgui_frame_end;
    func_possum_platform_ticks                   ticks;
    func_possum_platform_delta_time_ms           delta_time_ms;
    func_possum_platform_sleep                   sleep;
};

global PossumPlatformApi platform_api;

inline void
possum_platform_api_initialize(
    func_possum_platform_file_size               file_size,
    func_possum_platform_file_read               file_read,
    func_possum_platform_file_write              file_write,
    func_possum_platform_file_open               file_open,
    func_possum_platform_file_close              file_close,
    func_possum_platform_memory_allocate         memory_allocate,
    func_possum_platform_memory_free             memory_free,
    func_possum_platform_initialize_graphics_api graphics_api_init,
    func_possum_platform_initialize_imgui        imgui_init,
    func_possum_platform_imgui_frame_start       imgui_frame_start,
    func_possum_platform_imgui_frame_end         imgui_frame_end,
    func_possum_platform_ticks                   ticks,
    func_possum_platform_delta_time_ms           delta_time_ms,
    func_possum_platform_sleep                   sleep) {

    platform_api.file_size = file_size;
    platform_api.file_read = file_read;
    platform_api.file_write = file_write;
    platform_api.file_open = file_open;
    platform_api.file_close = file_close;
    platform_api.memory_allocate = memory_allocate;
    platform_api.memory_free = memory_free;
    platform_api.graphics_api_init = graphics_api_init;
    platform_api.imgui_init = imgui_init;
    platform_api.imgui_frame_start = imgui_frame_start;
    platform_api.imgui_frame_end = imgui_frame_end;
    platform_api.ticks = ticks;
    platform_api.delta_time_ms = delta_time_ms;
    platform_api.sleep = sleep;
}


#define possum_platform_file_size         possum_platform_api.file_size
#define possum_platform_file_read         possum_platform_api.file_read
#define possum_platform_file_write        possum_platform_api.file_write
#define possum_platform_file_open         possum_platform_api.file_open
#define possum_platform_file_close        possum_platform_api.file_close
#define possum_platform_memory_allocate   possum_platform_api.memory_allocate
#define possum_platform_memory_free       possum_platform_api.memory_free
#define possum_platform_graphics_api_init possum_platform_api.graphics_api_init
#define possum_platform_imgui_init        possum_platform_api.imgui_init
#define possum_platform_imgui_frame_start possum_platform_api.imgui_frame_start
#define possum_platform_imgui_frame_end   possum_platform_api.imgui_frame_end
#define possum_platform_ticks             possum_platform_api.ticks
#define possum_platform_delta_time_ms     possum_platform_api.delta_time_ms
#define possum_platform_sleep             possum_platform_api.sleep











    


typedef struct                 PossumPlatformContext;
typedef PossumPlatformContext* PossumPlatformContextPtr;

#endif //POSSUM_PLATFORM_HPP