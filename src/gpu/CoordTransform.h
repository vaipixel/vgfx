//
// Created by Anatta Feng on 2024/2/25.
//

#pragma once

#include "vgfx/core/Matrix.h"
#include "gpu/proxies/TextureProxy.h"
namespace vgfx {

struct CoordTransform {
  CoordTransform() = default;
  explicit CoordTransform(Matrix matrix, const TextureProxy *proxy = nullptr,
                          const Point &alphaStart = Point::Zero())
      : matrix(matrix), textureProxy(proxy), alphaStart(alphaStart) {
  }

  Matrix getTotalMatrix() const;

  Matrix matrix = Matrix::I();
  const TextureProxy *textureProxy = nullptr;
  Point alphaStart = Point::Zero();
};

} // vgfx