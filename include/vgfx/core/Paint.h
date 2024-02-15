//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include <memory>
#include "Color.h"
#include "Stroke.h"
#include "Shader.h"
namespace vgfx {

/**
 * Defines enumerations for Paint.setStyle().
 */
enum class PaintStyle {
  /**
   * Set to fill geometry.
   */
  Fill,
  /**
   * Set to stroke geometry.
   */
  Stroke
};

/**
 * Paint controls options applied when drawing
 */
class Paint {

 private:
  PaintStyle style = PaintStyle::Fill;
  Color color = Color::White();
  Stroke stroke = Stroke(0);
  std::shared_ptr<Shader> shader = nullptr;
  std::shared_ptr<MaskFilter> maskFilter = nullptr;
  std::shared_ptr<ColorFilter> colorFilter = nullptr;
  std::shared_ptr<ImageFilter> imageFilter = nullptr;
};

} // vgfx