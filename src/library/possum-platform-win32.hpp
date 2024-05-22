#ifndef POSSUM_PLATFORM_WIN32_HPP
#define POSSUM_PLATFORM_WIN32_HPP

#include "possum-platform.hpp"
#include <Windows.h>

//win32 platform context
struct PossumPlatformContext {
    HWND                        window_handle;
    HDC                         device_context;
    HGLRC                       opengl_context;
    u64                         window_style;
    u64                         window_ex_style;
    u64                         monitor_width_pixels;
    u64                         monitor_height_pixels;
    u64                         window_width_pixels;
    u64                         window_height_pixels;    
    bool                        full_screen;
    bool                        maximized;
};

internal void
possum_platform_win32_initialize();

internal memory
possum_platform_win32_memory_allocate(
    u64 memory_size_bytes);

#endif //POSSUM_PLATFORM_WIN32_HPP