//
// Created by Anatta Feng on 2024/2/19.
//

#pragma once

#include "gpu/DrawArgs.h"
#include "gpu/ops/DrawOp.h"
namespace vgfx {
/**
 * MaskFilter is the base class for filters that perform transformations on the mask before drawing
 * it.
 */
class MaskFilter : public Filter {
 public:
  /**
   * Creates a new MaskFilter that draws the mask using the alpha channel of the given shader.
   * If inverted is true, the mask is inverted before drawing.
   */
  static std::shared_ptr<MaskFilter> MakeShader(std::shared_ptr<Shader> shader,
                                                bool inverted = false);

 protected:
  std::unique_ptr<FragmentProcessor> onFilterImage(std::shared_ptr<Image> source,
                                                   const DrawArgs &args, const Matrix *localMatrix,
                                                   TileMode tileModeX,
                                                   TileMode tileModeY) const override;
 private:
  virtual std::unique_ptr<FragmentProcessor> asFragmentProcessor(
      const DrawArgs &args, const Matrix *localMatrix) const = 0;
};

} // vgfx