//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

#include <memory>
#include "vgfx/core/Rect.h"
#include "Image.h"
#include "Matrix.h"
#include "TileMode.h"
#include "gpu/ops/DrawOp.h"
#include "gpu/DrawArgs.h"
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
  virtual Rect filterBounds(const Rect &rect) const {
    return rect;
  }

 protected:
  virtual std::unique_ptr<DrawOp> onMakeDrawOp(std::shared_ptr<Image> source, const DrawArgs &args,
                                               const Matrix *localMatrix, TileMode tileModeX,
                                               TileMode tileModeY) const = 0;

  /**
   * The returned processor is in the coordinate space of the source image.
   */
  virtual std::unique_ptr<FragmentProcessor> onMakeFragmentProcessor(std::shared_ptr<Image> source,
                                                                     const DrawArgs *args,
                                                                     const Matrix *localMatrix,
                                                                     TileMode tileModeX,
                                                                     TileMode tileModeY) const = 0;

};

} // vgfx