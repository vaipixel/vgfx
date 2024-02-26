//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include "vgfx/core/Filter.h"

namespace vgfx {
/**
 * ColorFilter is the base class for filters that perform color transformations in the drawing
 * pipeline.
 */
class ColorFilter : public Filter {
 public:
  /**
   * Creates a new ColorFilter that transforms the input color into its corresponding brightness.
   */
  static std::shared_ptr<ColorFilter> Luma();

  /**
   * Creates a new ColorFilter that applies blends between the constant color (src) and input color
   * (dst) based on the BlendMode.
   */
  static std::shared_ptr<ColorFilter> Blend(Color color, BlendMode mode);

  /**
   * Creates a new ColorFilter that transforms the color using the given matrix.
   */
  static std::shared_ptr<ColorFilter> Matrix(const std::array<float, 20> &rowMajor);

  /**
   * Returns true if the filter is guaranteed to never change the alpha of a color it filters.
   */
  virtual bool isAlphaUnchanged() const {
    return false;
  }
 protected:
  std::unique_ptr<FragmentProcessor> onFilterImage(std::shared_ptr<Image> source,
                                                   const DrawArgs &args,
                                                   const Matrix *localMatrix,
                                                   TileMode tileModeX,
                                                   TileMode tileModeY) const override;
 private:
  virtual std::unique_ptr<FragmentProcessor> asFragmentProcessor() const = 0;
};

} // vgfx