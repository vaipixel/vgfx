//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include <memory>
#include "vgfx/core/Matrix.h"
#include "vgfx/core/PathFillType.h"
#include "core/PathRef.h"

namespace vgfx {

/**
 * Path contain geometry. Path may be empty, or contain one or more verbs that outline a figure.
 * Path always starts with a move verb to a Cartesian coordinate, and may be followed by additional
 * verbs that add lines or curves. dding a close verb makes the geometry into a continuous loop, a
 * closed contour. Path may contain any number of contours, each beginning with a move verb.
 */
class Path {
 public:
  /**
   * Creates an empty path.
   */
  Path();

  /**
   * Compares a abd b; returns true if they are equivalent.
   * @param a
   * @param b
   * @return
   */
  friend bool operator==(const Path &a, const Path &b);

  /**
   * Compares a and b; returns true if they are not equivalent.
   * @param a
   * @param b
   * @return
   */
  friend bool operator!=(const Path &a, const Path &b);

  /**
   * Returns PathFillType, the rule used to fill Path. PathFillType of a new Path is Path
   * FillType::Winding.
   */
  PathFillType getFillType() const;

  /**
   * Sets PathFillType, the rule used to fill Path.
   */
  void setFillType(PathFillType fillType);

  /**
   * Returns if PathFillType is InverseWinding or InverseEvenOdd.
   */
  bool isInverseFillType() const;

  /**
   * Replaces PathFillType with its inverse.
   */
  void toggleInverseFillType();

  /**
   * Returns true if Path is equivalent to Rect when filled, Otherwise returns false, and leaves
   * rect unchanged. The rect may be smaller than the Path bounds. Path bounds may include
   * PathVerb::Move points that do not alter the area drawn by the returned rect.
  */
  bool asRect(Rect *rect) const;

  /**
   * Returns true if Path is equivalent to RRect when filled, Otherwise returns false, and leaves
   * rRect unchanged.
   */
  bool asRRect(RRect *rRect) const;

 private:
  std::shared_ptr<PathRef> pathRef = nullptr;

  PathRef *writableRef();

  friend class PathRef;
};

} // vgfx