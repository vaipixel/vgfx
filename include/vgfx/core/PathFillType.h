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

/**
 * PathVerb instructs Path how to interpret one or more Point, manage contour, and terminate Path.
 */
enum class PathVerb {
  /**
   * PathIterator returns 1 point.
   */
  Move,
  /**
   * PathIterator returns 2 points.
   */
  Line,
  /**
   * PathIterator returns 3 points.
   */
  Quad,
  /**
   * PathIterator returns 4 points.
   */
  Cubic,
  /**
   * PathIterator returns 0 points.
   */
  Close,
};

/**
 * Zero to four Point are stored in points, depending on the returned PathVerb
 */
using PathInterator = std::function<void(PathVerb verb, const Point points[4], void *info)>;
}