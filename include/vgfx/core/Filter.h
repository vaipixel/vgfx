//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <memory>
#include "vgfx/core/Image.h"
#include "vgfx/core/Matrix.h"
#include "vgfx/core/TileMode.h"
#include "vgfx/gpu/Context.h"

namespace vgfx {
/**
 * Filter is the base class for all filters, such as ImageFilter, ColorFilter, and MaskFilter.
 */
class Filter {
 public:
  virtual ~Filter() = default;

  /**
   * Returns the bounds of the filtered image by the given bounds of the source image.
   */
  virtual Rect filterBounds(const Rect& rect) const {
    return rect;
  }

 protected:
  /**
   * The returned processor is in the coordinate space of the source image.
   */
  virtual std::unique_ptr<FragmentProcessor> onFilterImage(std::shared_ptr<Image> source,
                                                           const DrawArgs& args, TileMode tileModeX,
                                                           TileMode tileModeY,
                                                           const SamplingOptions& sampling,
                                                           const Matrix* localMatrix) const = 0;

  friend class FilterImage;
};
} // vgfx