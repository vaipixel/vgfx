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

  PathFillType getFillType() const;

  void setFillType(PathFillType fillType);

  bool isInverseFillType() const;

 private:
  std::shared_ptr<PathRef> pathRef = nullptr;

  PathRef *writableRef();

  friend class PathRef;
};

} // vgfx