//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

namespace vgfx {
/**
 * PathFillType selects the rule used to fill Path.
 */
enum class PathFillType {
  /**
   * Enclosed by a non-zero sum of contour directions.
   */
  Winding,
  /**
   * Enclosed by an odd number of contours.
   */
  EvenOdd,
  /**
   * Enclosed by a zero sum of contour directions.
   */
  InverseWinding,
  /**
   * Enclosed by an even number of contours.
   */
  InverseEvenOdd,
};

/**
 * The logical operations that can be performed when combining two paths.
 */
enum class PathOp {
  /**
   * Appended to destination unaltered.
   */
  Append,
  /**
   * Subtract the op path from the destination path.
   */
  Difference,
  /**
   * Intersect the two paths.
   */
  Intersect,
  /**
   * Union (inclusive-or) the two paths.
   */
  Union,
  /**
   * Exclusive-or the two paths.
   */
  XOR,
};
}