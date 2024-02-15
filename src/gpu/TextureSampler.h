//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include "vgfx/gpu/Context.h"
namespace vgfx {
enum class TextureType { Unknown, TwoD, Rectangle, External };

/**
 * TextureSampler stores the sampling parameters for a backend texture uint.
 */
class TextureSampler {
 public:
  /**
   * Creates a new TextureSampler which wraps the specified backend texture. The caller is
   * responsible for managing the lifetime of the backendTexture.
   */
  static std::unique_ptr<TextureSampler> MakeFrom(Context *context,
                                                  const BackendTexture &backendTexture);

  virtual ~TextureSampler() = default;

  /**
   * The pixel format of the sampler.
   */
  PixelFormat format = PixelFormat::RGBA_8888;

  int maxMipmapLevel = 0;

  /**
   * Returns the TextureType of TextureSampler.
   */
  virtual TextureType type() const {
    return TextureType::TwoD;
  }

  /**
   * Returns true if the TextureSampler has mipmap levels.
   */
  bool hasMipmaps() const {
    return maxMipmapLevel > 0;
  }

  /**
   * Retrieves the backend texture with the specified size.
   */
  virtual BackendTexture getBackendTexture(int width, int height) const = 0;

 protected:
  virtual void computeKey(Context *context, BytesKey *bytesKey) const = 0;
};

} // vgfx