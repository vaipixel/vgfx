//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

#include <string>
#include "vgfx/core/Font.h"
#include "vgfx/core/Typeface.h"
#include "vgfx/core/Point.h"
#include "vgfx/core/Rect.h"
#include "vgfx/core/Stroke.h"
#include "vgfx/core/Path.h"
namespace vgfx {
/**
 * TextBlob combines multiple glyphs, Font, and positions into an immutable container.
 */
class TextBlob {
 public:
  /**
   * Creates a new TextBlob from the given text. The text must be in utf-8 encoding. This function
   * uses the default character-to-glyph mapping from the Typeface in font. It does not perform
   * typeface fallback for characters not found in the Typeface. Glyphs are positioned based on
   * their default advances.
   */
  static std::shared_ptr<TextBlob> MakeFrom(const std::string& text, const Font& font);

  /**
   * Creates a new TextBlob from the given glyphs, positions and text font.
   */
  static std::shared_ptr<TextBlob> MakeFrom(const GlyphID glyphIDs[], const Point positions[],
                                            size_t glyphCount, const Font& font);

  virtual ~TextBlob() = default;

  /**
   * Returns true if this TextBlob has color glyphs, for example, color emojis.
   */
  virtual bool hasColor() const = 0;

  /**
   * Returns the bounds of the text blob's glyphs.
   */
  virtual Rect getBounds(const Stroke* stroke = nullptr) const = 0;

  /**
   * Creates a path corresponding to glyph shapes in the text blob. Copies the glyph fills to the
   * path if the stroke is not passed in, otherwise copies the glyph outlines to the path. If text
   * font is backed by bitmaps or cannot generate outlines, returns false and leaves the path
   * unchanged.
   */
  virtual bool getPath(Path* path, const Stroke* stroke = nullptr) const = 0;

};
}