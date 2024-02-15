//
// Created by Anatta Feng on 2024/2/15.
//

#pragma once

namespace vgfx {

/**
 * Cap draws at the beginning and end of an open path contour.
 */
enum class LineCap {
  /**
   * No stroke extension.
   */
  Butt,
  /**
   * Adds circle
   */
  Round,
  /**
   * Adds square
   */
  Square
};

/**
 * Join specifies how corners are drawn when a shape is stroked. Join affects the four corners
 * of a stroked rectangle, and the connected segments in a stroked path. Choose miter join to draw
 * sharp corners. Choose round join to draw a circle with a radius equal to the stroke width on
 * top of the corner. Choose bevel join to minimally connect the thick strokes.
 */
enum class LineJoin {
  /**
   * Extends to miter limit.
   */
  Miter,
  /**
   * Adds circle.
   */
  Round,
  /**
   * Connects outside edges.
   */
  Bevel
};

/**
 * Stroke controls options applied when stroking geometries (paths, glyphs).
 */
class Stroke {
 public:
  Stroke() = default;

  explicit Stroke(float width, LineCap cap = LineCap::Butt, LineJoin join = LineJoin::Miter,
                  float miterLimit = 4.0f)
      : width(width), cap(cap), join(join), miterLimit(miterLimit) {

  }
  /**
   * The thickness of the pen used to outline the paths or glyphs.
   */
  float width = 1.0;
  /**
   *  The geometry drawn at the beginning and end of strokes.
   */
  LineCap cap = LineCap::Butt;
  /**
   * The geometry drawn at the corners of strokes.
   */
  LineJoin join = LineJoin::Miter;
  /**
   * The limit at which a sharp corner is drawn beveled.
   */
  float miterLimit = 4.0f;
};

} // vgfx