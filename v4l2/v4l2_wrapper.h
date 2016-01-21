/*
 *  v4l2_wrapper.h
 *
 *  Copyright (C) 2014 Intel Corporation
 *    Author: Zhao, Halley<halley.zhao@intel.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA
 */

#include <stdint.h>
#include <stddef.h>
#if ANDROID
#else
    #if __ENABLE_X11__
    #include <X11/Xlib.h>
    #endif
    #include <EGL/egl.h>
#endif
#include "VideoCommonDefs.h"

#ifndef v4l2_wrapper_h
#define v4l2_wrapper_h
#ifndef V4L2_EVENT_RESOLUTION_CHANGE
    #define V4L2_EVENT_RESOLUTION_CHANGE 5
#endif

#ifdef __cplusplus
extern "C" {
#endif
int32_t YamiV4L2_Open(const char* name, int32_t flags);
int32_t YamiV4L2_Close(int32_t fd);
int32_t YamiV4L2_FrameMemoryType(int32_t fd, VideoDataMemoryType memory_type);
int32_t YamiV4L2_Ioctl(int32_t fd, int request, void* arg);
int32_t YamiV4L2_Poll(int32_t fd, bool poll_device, bool* event_pending);
int32_t YamiV4L2_SetDevicePollInterrupt(int32_t fd);
int32_t YamiV4L2_ClearDevicePollInterrupt(int32_t fd);
void* YamiV4L2_Mmap(void* addr, size_t length,
                     int prot, int flags, int fd, unsigned int offset);
int32_t YamiV4L2_Munmap(void* addr, size_t length);
#if ANDROID
#else
    #if __ENABLE_X11__
    /// it should be called before driver initialization (immediate after _Open()).
    int32_t YamiV4L2_SetXDisplay(int32_t fd, Display *x11Display);
    #endif
    int32_t YamiV4L2_UseEglImage(int fd, EGLDisplay eglDisplay, EGLContext eglContext, unsigned int buffer_index, void* egl_image);
    int32_t YamiV4L2_SetDrmFd(int32_t fd, int drm_fd);
#endif
#ifdef __cplusplus
} // extern "C"
#endif

#endif

