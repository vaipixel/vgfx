//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

#include "vgfx/core/ImageInfo.h"
#include "gpu/Texture.h"

namespace vgfx {
/**
 * RenderTarget represents a 2D buffer of pixels that can be rendered to.
 */
class RenderTarget : public Resource {

 public:
  static std::shared_ptr<RenderTarget> MakeFrom(Context *context,
                                                const BackendRenderTarget &rederTarget,
                                                ImageOrigin origin);

  /**
   * Creates a new RenderTarget which uses specified Texture as pixel storage. The caller must
   * ensure the texture is valid for the lifetime of the returned RenderTarget.
   */
  static std::shared_ptr<RenderTarget> MakeFrom(const Texture *texture,
                                                int sampleCount = 1);

  /**
   * Returns the display width of the render target.
   */
  int width() const {
    return _width;
  }

  /**
   * Returns the display height of the render target.
   */
  int height() const {
    return _height;
  }

  /**
   * Returns the origin of the render target, either ImageOrigin::TopLeft or
   * ImageOrigin::BottomLeft.
   */
  ImageOrigin origin() const {
    return _origin;
  }

  /**
   * Returns the sample count of the render target.
   */
  int sampleCount() const {
    return _sampleCount;
  }

  /**
   * Returns the pixel format of the render target.
   */
  virtual PixelFormat format() const = 0;

  size_t memoryUsage() const override {
    return 0;
  }

  /**
   * Retrieves the backend render target.
   */
  virtual BackendRenderTarget getBackendRenderTarget() const = 0;

  virtual bool readPixels(const ImageInfo &dstInfo, void *dstPixels, int srcX = 0,
                          int srcY = 0) const = 0;

 private:
  int _width = 0;
  int _height = 0;
  ImageOrigin _origin = ImageOrigin::TopLeft;
  int _sampleCount = 1;
};
}