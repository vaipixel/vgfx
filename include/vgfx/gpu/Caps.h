//
// Created by Anatta Feng on 2024/2/17.
//

#pragma once

#include "vgfx/gpu/PixelFormat.h"
namespace vgfx {
class Swizzle;
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
  bool multisampleDisableSupport = false;
  /**
   * The CLAMP_TO_BORDER wrap mode for texture coordinates was added to desktop GL in 1.3, and
   * GLES 3.2, but is also available in extensions. Vulkan and Metal always have support.
   */
  bool clampToBorderSupport = true;
  bool npotTextureTileSupport = true;  // Vulkan and Metal always have support.
  bool mipmapSupport = true;
  bool textureBarrierSupport = false;
  bool frameBufferFetchSupport = false;
};

} // vgfx