//
// Created by Anatta Feng on 2024/1/13.
//

#pragma once

#include "vgfx/core/ImageInfo.h"
#include "vgfx/gpu/PixelFormat.h"

#if defined(__ANDROID__) || defined(ANDROID)
struct AHardwareBuffer;
#elif defined(__APPLE__)
struct __CVBuffer;
#endif

namespace vgfx {
#if defined(__ANDROID__) || defined(ANDROID)
typedef AHardwareBuffer* HardwareBufferRef;
#elif defined(__APPLE__)
// __CVBuffer == CVPixelBufferRef
typedef __CVBuffer* HardwareBufferRef;
#else
typedef void* HardwareBufferRef;
#endif

/**
 * Returns true if the current platform has hardware buffer support. Otherwise, returns false.
 */
bool HardwareBufferAvailable();

/**
 * Returns true if the given hardware buffer object is valid and can be bind to a texture.
 * Otherwise, returns false.
 */
bool HardwareBufferCheck(HardwareBufferRef buffer);

/**
 * Allocates a hardware buffer for a given size and pixel format (alphaOnly). Returns nullptr if
 * allocation fails. The returned buffer has a reference count of 1, and the caller must call
 * HardwareBufferRelease() when finished with it.
 */
HardwareBufferRef HardwareBufferAllocate(int width, int height, bool alphaOnly = false);

/**
 * Retains a reference on the given hardware buffer object. This prevents the object from being
 * deleted until the last reference is removed.
 */
HardwareBufferRef HardwareBufferRetain(HardwareBufferRef buffer);

/**
 * Removes a reference that was previously acquired with HardwareBufferRetain().
 */
void HardwareBufferRelease(HardwareBufferRef buffer);

/**
 * Locks and returns the base address of the hardware buffer. Returns nullptr if the lock fails for
 * any reason and leave the buffer unchanged. The caller must call HardwareBufferUnlock() when
 * finished with the buffer.
 */
void* HardwareBufferLock(HardwareBufferRef buffer);

/**
 * Unlocks the base address of the hardware buffer. Call this to balance a successful call to
 * HardwareBufferLock().
 */
void HardwareBufferUnlock(HardwareBufferRef buffer);

/**
 * Returns an ImageInfo describing the width, height, color type, alpha type, and row bytes of the
 * given hardware buffer object. Returns an empty ImageInfo if the buffer is nullptr or not
 * recognized.
 */
ImageInfo HardwareBufferGetInfo(HardwareBufferRef buffer);

/**
 * Returns the pixel format of the texture generated from the given hardware buffer object. Returns
 * PixelFormat::Unknown if the buffer is nullptr or not recognized.
 */
PixelFormat HardwareBufferGetPixelFormat(HardwareBufferRef buffer);
}