//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include <vector>
#include "vgfx/gpu/Surface.h"
#include "vgfx/core/Matrix.h"
#include "vgfx/core/BlendMode.h"
#include "vgfx/core/Rect.h"
#include "vgfx/core/Paint.h"
#include "vgfx/core/Color.h"
#include "vgfx/core/Path.h"
#include "vgfx/core/SamplingOptions.h"
#include "vgfx/core/Shape.h"
#include "vgfx/core/Font.h"
#include "vgfx/core/Typeface.h"
#include "gpu/processors/FragmentProcessor.h"
#include "TextBlob.h"

namespace vgfx {
class Surface;

class SurfaceOptions;

class Context;

struct CanvasState;

class SurfaceDrawContext;

/**
 * Canvas provides an interface for drawing, and how the drawing is clipped and transformed. Canvas
 * contains a stack of opacity, blend mode, matrix and clip values. Each Canvas draw call transforms
 * the geometry of the object by the concatenation of all matrix values in the stack. The
 * transformed geometry is clipped by the intersection of all of clip values in the stack.
 */
class Canvas {
 public:
  explicit Canvas(Surface *surface);

  ~Canvas();

  /**
   * Retrieves the context associated with this Surface.
   * @return
   */
  Context *getContext() const;

  /**
   * Returns the Surface this canvas draws into.
   * @return
   */
  Surface *getSurface() const;

  /**
   * Returns the SurfaceOptions associated with the Canvas. Returns nullptr if the Canvas is not
   * created from a surface.
   * @return
   */
  const SurfaceOptions *surfaceOptions() const;

  /**
   * Save alpha, blend mode, matrix, and clip. Calling restore() discards changes to them,
   * restoring them to their state when save() was called. Saved Canvas state is put on a stack,
   * multiple calls to save() should be balanced by an equal number of calls to restore().
   */
  void save();

  /**
   * Removes changes to alpha, blend mode, matrix and clips since Canvas state was last saved.
   * The state is removed from the stack. Does nothing if th stack is empty.
   */
  void restore();

  /**
   * Translates the current matrix by dx along the x-axis and dy along the y-axis. Mathematically,
   * it replaces the current matrix with a translation matrix premultiplied with the current matrix.
   * This has the effect of moving the drawing by (dx, dy) before transforming the result with the
   * current matrix.
   * @param dx
   * @param dy
   */
  void translate(float dx, float dy);

  /**
   * Scales the current matrix by sx  along the x-axis and sy along the y-axis. Mathematically, it
   *  replaces the current matrix with a scale matrix premultiplied with the current matrix. This has
   *  the effect of scaling the drawing by (sx, sy) before transforming the result with the current
   *  matrix.
   * @param sx
   * @param sy
   */
  void scale(float sx, float sy);

  /**
   * Rotates the current matrix by degrees. Positive values rotate the drawing clockwise.
   * Mathematically, it replaces the current matrix with a rotation matrix premultiplied with the
   * current matrix. This has the effect of rotating the drawing by degrees before transforming the
   * result with the current matrix.
   */
  void rotate(float degrees);

  /**
   * Rotates the current matrix by degrees around the point (px, py). Positive values rotate the
   * drawing clockwise. Mathematically, it replaces the current matrix with a rotation matrix
   * premultiplied with the current matrix. This has the effect of rotating the drawing around the
   * point (px, py) by degrees before transforming the result with the current matrix.
   */
  void rotate(float degrees, float px, float py);

  /**
   * Skews the current matrix by sx along the x-axis and sy along the y-axis. A positive value of sx
   * skews the drawing right as y-axis values increase; a positive value of sy skews the drawing
   * down as x-axis values increase. Mathematically, it replaces the current matrix with a skew
   * matrix premultiplied with the current matrix. This has the effect of skewing the drawing by
   * (sx, sy) before transforming the result with the current matrix.
   */
  void skew(float sx, float sy);

  /**
   * Replaces the current Matrix with matrix premultiplied with the existing one. This has the
   * effect of transforming the drawn geometry by matrix, before transforming the result with the
   * existing Matrix.
   */
  void concat(const Matrix &matrix);

  /**
   * Returns the current total matrix.
   * @return
   */
  Matrix getMatrix() const;

  /**
   * Replaces transformation with specified matrix. Unlike concat(), any prior matrix state is
   * overwritten.
   * @param matrix  matrix to copy, replacing existing Matrix.
   */
  void setMatrix(const Matrix &matrix);

  /**
   * Sets Matrix to the identity matrix. Any prior matrix state is overwritten.
   */
  void resetMatrix();

  /**
   * Returns the current total clip Path.
   */
  Path getTotalClip() const;

  /**
   * Returns the current global alpha.
   * @return
   */
  float getAlpha() const;

  /**
   * Replaces the global alpha with specified newAlpha.
   * @param newAlpha
   */
  void setAlpha(float newAlpha);

  /**
   * Returns the current global blend mode.
   * @return
   */
  BlendMode getBlendMode() const;

  /**
   * Replaces the global blend mode with specified new blend mode.
   * @param blendMode
   */
  void setBlendMode(BlendMode blendMode);

  /**
   * Replaces clip with the intersection of clip and rect. The resulting clip is aliased; pixels are
   * fully contained by the clip. The rect is transformed by the current Matrix before it is combined
   * with clip.
   */
  void clipRect(const Rect &rect);

  /**
   * Replaces clip with the intersection of clip and path. The path is transformed by Matrix before
   * it is combined with clip.
   */
  void clipPath(const Path &path);

  /**
   * Fills clip with color. This has the effect of replacing all pixels contained by clip with
   * colors.
   * @param color
   */
  void clear(const Color &color = Color::Transparent());

  /**
   * Draws a rectangle with specified paint, using current alpha, blend mode, clip and matrix.
   * @param rect
   * @param paint
   */
  void drawRect(const Rect &rect, const Paint &paint);

  /**
   * Draw a path with using current clip, matrix and specified paint.
   * @param path
   * @param paint
   */
  void drawPath(const Path &path, const Paint &paint);

  /**
   * Draws a shape with using current clip, matrix and specified paint.
   * @param share
   * @param paint
   */
  void drawShape(std::shared_ptr<Shape> share, const Paint &paint);

  /**
   * Draws an image, with its top-left corner at (left, top), using current clip, matrix and
   * optional paint. If image->hasMipmaps() is true, uses FilterMode::Linear and MipmapMode::Linear
   * as the sampling options, Otherwise, uses FilterMode::Linear and MipmapMode::None as the
   * sampling options.
   * @param image
   * @param left
   * @param top
   * @param paint
   */
  void drawImage(std::shared_ptr<Image> image, float left, float top, const Paint *paint = nullptr);

  /**
   * Draws a Image, with its top-left corner at (0, 0), using current alpha, clip and matrix
   * premultiplied with existing Matrix. If image->hasMipmaps() is true, uses FilterMode::Linear
   * as the sampling options. Otherwise, uses FilterMode::Linear and MipmapMode::None as the
   * sampling options.
   * @param image
   * @param matrix
   * @param paint
   */
  void drawImage(std::shared_ptr<Image> image, const Matrix &matrix, const Paint *paint = nullptr);

  /**
   * Draws an image, with its top-left corner at (0, 0), using current clip, matrix and optional
   * paint. If image->hasMipmaps() is true, uses FilterMode::Linear and MipmapMode::Linear as the
   * sampling options. Otherwise, uses FilterMode:Linear and MipmapMode::None as the sampling
   * options.
   * @param image
   * @param paint
   */
  void drawImage(std::shared_ptr<Image> image, const Paint *paint = nullptr);

  /**
   * Draws an image, with its top-left corner at (0, 0), using current clip, matrix, sampling
   * options and optional paint.
   */
  void drawImage(std::shared_ptr<Image> image, SamplingOptions sampling,
                 const Paint *paint = nullptr);

  /**
   * Draws text, with origin at (x, y), using clip, matrix, font, and paint. The text must be in
   * utf-8 encoding. This function uses the default character-to-glyph mapping from the Typeface in
   * font. It does not perform typeface fallback for characters not found in the Typeface. Glyphs
   * are positioned based on their default advances.
   */
  void drawSimpleText(const std::string &text, float x, float y, const Font &font,
                      const Paint &paint);

  /**
   * Draw an array of glyphs with specified font, using current alpha, blend mode, clip and Matrix.
   */
  void drawGlyphs(const GlyphID glyphIDs[], const Point positions[], size_t glyphCount,
                  const Font &font, const Paint &paint);

  // TODO(pengweilv): Support blend mode, atlas as source, colors as destination, colors can be
  //  nullptr.
  void drawAtlas(std::shared_ptr<Image> atlas, const Matrix matrix[], const Rect tex[],
                 const Color colors[], size_t count, SamplingOptions sampling = SamplingOptions());

  /**
   * Triggers the immediate execution of all pending draw operations.
   */
  void flush();
 private:
  Surface *surface = nullptr;
  std::shared_ptr<Surface> _clipSurface = nullptr;
  uint32_t clipID = 0;
  std::shared_ptr<CanvasState> state = nullptr;
  SurfaceDrawContext *drawContext = nullptr;
  std::vector<std::shared_ptr<CanvasState>> savedStateList = {};

  bool nothingToDraw(const Paint &paint) const;

  std::shared_ptr<TextureProxy> getClipTexture();

  std::pair<std::optional<Rect>, bool> getClipRect(const Rect *drawBounds = nullptr);

  std::unique_ptr<FragmentProcessor> getClipMask(const Rect &deviceBounds, Rect *scissorRect);

  Rect clipLocalBounds(Rect localBounds);

  void drawMask(const Rect &bounds, std::shared_ptr<TextureProxy> mask,
                const Paint &paint);

  void drawColorGlyphs(const GlyphID glyphIDs[], const Point positions[], size_t glyphCount,
                       const Font &font, const Paint &paint);
  void drawMaskGlyphs(std::shared_ptr<TextBlob> textBlob, const Paint &paint);
  bool drawAsClear(const Path &path, const Paint &paint);
  Color getInputColor(const Paint &paint);
  bool getProcessors(const DrawArgs& args, const Paint& paint, DrawOp* drawOp);
  void addDrawOp(std::unique_ptr<DrawOp> op, const DrawArgs& args, const Paint& paint,
                 bool aa = false);
};

}
