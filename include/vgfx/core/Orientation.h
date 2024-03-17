//
// Created by Anatta Feng on 2024/3/16.
//

#pragma once
#include "vgfx/core/Matrix.h"
namespace vgfx {

/**
 * These values match the orientation www.exif.org/Exif2-2.PDF.
 */
enum class Orientation {
  /**
   * Default
   */
  TopLeft = 1,
  /**
   * Reflected across y-axis
   */
  TopRight = 2,
  /**
   * Rotated 180
   */
  BottomRight = 3,
  /**
   * Reflected across x-axis
   */
  BottomLeft = 4,
  /**
   * Reflected across x-axis, Rotated 90 CCW
   */
  LeftTop = 5,
  /**
   * Rotated 90 CW
   */
  RightTop = 6,
  /**
   * Reflected across x-axis, Rotated 90 CW
   */
  RightBottom = 7,
  /**
   * Rotated 90 CCW
   */
  LeftBottom = 8
};

/**
 * Given an orientation and the width and height of the source data, returns a matrix that
 * transforms the source rectangle [0, 0, w, h] to a correctly oriented destination rectangle, with
 * the upper left corner still at [0, 0].
 */
Matrix OrientationToMatrix(Orientation orientation, int width, int height);

/**
 * Return true if the orientation includes a 90-degree rotation, in which case, the width
 * and height of the source data are swapped relative to a correctly oriented destination.
 */
bool OrientationSwapsWidthHeight(Orientation origin);

} // vgfx