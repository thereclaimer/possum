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

func_possum_platform_file_size                possum_platform_file_size;
func_possum_platform_file_read                possum_platform_file_read;
func_possum_platform_file_write               possum_platform_file_write;
func_possum_platform_file_open                possum_platform_file_open;
func_possum_platform_file_close               possum_platform_file_close;
func_possum_platform_memory_allocate          possum_platform_memory_allocate;
func_possum_platform_memory_free              possum_platform_memory_free;
func_possum_platform_initialize_graphics_api  possum_platform_graphics_api_init;
func_possum_platform_initialize_imgui         possum_platform_imgui_init;
func_possum_platform_imgui_frame_start        possum_platform_imgui_frame_start;
func_possum_platform_imgui_frame_end          possum_platform_imgui_frame_end;
func_possum_platform_ticks                    possum_platform_ticks;
func_possum_platform_delta_time_ms            possum_platform_delta_time_ms;
func_possum_platform_sleep                    possum_platform_sleep;


typedef struct                 PossumPlatformContext;
typedef PossumPlatformContext* PossumPlatformContextPtr;

#endif //POSSUM_PLATFORM_HPP