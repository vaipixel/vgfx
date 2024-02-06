//
// Created by Anatta Feng on 2024/1/15.
//

#pragma once

#include "Resource.h"
#include "vgfx/core/ImageInfo.h"
#include "vgfx/gpu/ImageOrigin.h"
#include "Backend.h"

namespace vgfx {
/**
 * RenderTarget represents a 2D buffer of pixels that can be rendered to.
 */
class RenderTarget : public Resource {

 public:
  static std::shared_ptr<RenderTarget> MakeFrom(Context *context,
                                                const BackendRenderTarget &rederTarget,
                                                ImageOrigin origin);

  virtual bool readPixels(const ImageInfo &dstInfo, void *dstPixels, int srcX = 0,
                          int srcY = 0) const = 0;

 private:
  int _width = 0;
  int _height = 0;
  ImageOrigin _origin = ImageOrigin::TopLeft;
  int _sampleCount = 1;
};
}