//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <memory>
#include "vgfx/core/Color.h"
#include "vgfx/core/Image.h"
#include "vgfx/core/SamplingOptions.h"
#include "vgfx/core/TileMode.h"
#include "vgfx/core/BlendMode.h"
#include "vgfx/core/Point.h"
#include "Matrix.h"
#include "gpu/processors/FragmentProcessor.h"
#include "ColorFilter.h"
namespace vgfx {

/**
 * Shaders specify the source color(s) for what is being drawn. If a paint has no shader, then the
 * paint's color is used. If the paint has a shader, then the shader's color(s) are used instead,
 * but they are modulated by the paint's alpha. Shaders are in
 */
class Shader {
 public:
  static std::shared_ptr<Shader> MakeColorShader(Color color);

  static std::shared_ptr<Shader> MakeImageShader(std::shared_ptr<Image> image,
                                                 TileMode tileModeX = TileMode::Clamp,
                                                 TileMode tileModeY = TileMode::Clamp,
                                                 SamplingOptions sampling = SamplingOptions());

  static std::shared_ptr<Shader> MakeBlend(BlendMode mode, std::shared_ptr<Shader> dst,
                                           std::shared_ptr<Shader> src);

  static std::shared_ptr<Shader> MakeLinearGradient(const Point &startPoint, const Point &endPoint,
                                                    const std::vector<Color> &colors,
                                                    const std::vector<float> &positions);

  static std::shared_ptr<Shader> MakeRadialGradient(const Point &center, float redius,
                                                    const std::vector<Color> &colors,
                                                    const std::vector<float> &positions);

  static std::shared_ptr<Shader> MakeSweepGradient(const Point &center, float startAngle,
                                                   float endAngle, const std::vector<Color> &colors,
                                                   const std::vector<float> &positions);

  virtual ~Shader() = default;

  virtual bool isOpaque() const {
    return false;
  }

  virtual std::shared_ptr<Shader> makeWithMatrix(const Matrix &viewMatrix) const;

  std::shared_ptr<Shader> makeWithColorFilter(std::shared_ptr<ColorFilter> colorFilter) const;

 protected:
  std::weak_ptr<Shader> weakThis;
  virtual std::unique_ptr<FragmentProcessor> onMakeFragmentProcessor(
      const DrawArgs &args, const Matrix *localMatrix) const = 0;
};

} // vgfx