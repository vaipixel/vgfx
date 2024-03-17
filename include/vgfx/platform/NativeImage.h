//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once

#if defined(__EMSCRIPTEN__)
#include <emscripten/val.h>
#elif defined(__ANDROID__) || defined(ANDROID)

class _jobject;

#elif defined(__APPLE__)

struct CGImage;

#endif

namespace vgfx {
#if defined(__EMSCRIPTEN__)

typedef emscripten::val NativeImageRef;

#elif defined(__ANDROID__) || defined(ANDROID)

typedef _jobject *NativeImageRef;

#elif defined(__APPLE__)

typedef CGImage* NativeImageRef;

#else

struct NativeImage {};

typedef NativeImage* NativeImageRef;

#endif
}// vgfx