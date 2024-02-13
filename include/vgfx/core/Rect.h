//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "Point.h"
namespace vgfx {

/**
 * Rect holds four float coordinates describing the upper and lower bounds of a rectangle. Rect may
 * be created from outer bounds or from position, width, and height. Rect describes an area; if its
 * right is less than or equal to its left, or if its bottom is less than or equal to its top, it is
 * considered empty.
 */
struct Rect {
  /**
   * smaller x-axis bounds.
   */
  float left;
  /**
   * smaller y-axis bounds.
   */
  float top;
  /**
   * larger x-axis bounds.
   */
  float right;
  /**
   * larger y-axis bounds.
   */
  float bottom;

  /**
   * Returns constructed Rect set to (0, 0, 0, 0).
   */
  static constexpr Rect MakeEmpty() {
    return {0, 0, 0, 0};
  }
};

struct RRect {
  Rect rect = Rect::MakeEmpty();
  Point radii = Point::Zero();

  void scale(float scaleX, float scaleY);
};
}
