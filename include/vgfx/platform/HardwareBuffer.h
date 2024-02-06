//
// Created by Anatta Feng on 2024/1/13.
//

#pragma once

#if defined(__ANDROID__) || defined(ANDROID)
struct AHardwareBuffer;
#elif defined(__APPLE__)
struct __CVBuffer;
#endif

namespace vgfx {
#if defined(__ANDROID__) || defined(ANDROID)
typedef AHardwareBuffer *HardwareBufferRef;
#elif defined(__APPLE__)
typedef __CVBuffer* HardwareBufferRef;
#else
typedef void* HardwareBufferRef;
#endif

/**
 * Returns true if the current platform has hardware buffer support. Otherwise, return false.
 * @return
 */
bool HardwareBufferAvailable();
}