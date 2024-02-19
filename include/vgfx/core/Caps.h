//
// Created by Anatta Feng on 2024/2/17.
//

#pragma once

#include "vgfx/gpu/PixelFormat.h"
#include "gpu/Swizzle.h"
namespace vgfx {

class Caps {
 public:
  virtual ~Caps() = default;

  virtual const Swizzle &getWriteSwizzle(PixelFormat pixelFormat) const = 0;

  virtual bool isFormatRenderable(PixelFormat pixelFormat) const = 0;

  virtual int getSampleCount(int requestedCount, PixelFormat pixelFormat) const = 0;

  virtual int getMaxMipmapLevel(int width, int height) const = 0;

  bool floatIs32Bits = true;
  int maxTextureSize = 0;
  bool semaphoreSupport = false;
};

} // vgfx