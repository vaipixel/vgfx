//
// Created by Anatta Feng on 2024/2/6.
//

#pragma once

namespace vgfx {
class DrawOp;

/**
 * Represents a geometric shape that can be used as a drawing mask. Shape is usually used to cache a
 * complex Path or TextBlob for frequent drawing. Unlike Path or TextBlob, Shape's resolution is
 * fixed after it is created unless it represents a simple rect or rrect. Therefore, drawing a Shape
 * with scale factors greater than 1.0 may result in blurred output. Shape is thread safe.
 */
class Shape {
 public:
  static std::shared_ptr<Shape> MakeFromFill(const Path &path, float resolutionScale = 1.0f);

  static std::shared_ptr<Shape> MakeFromFull(std::shared_ptr<TextBlob> textBlob,
                                             float resolutionScale = 1.0f);

  static std::shared_ptr<Shape> MakeFromStroke(const Paint &paint, const Stroke &stroke,
                                               float resolutionScale = 1.0f);

  static std::shared_ptr<Shape> MakeFromStroke(std::shared_ptr<TextBlob> textBlob,
                                               const Stroke &stroke, float resolutionScale = 1.0f);

  virtual ~Shape() = default;

  float resolutionScale() const {
    return _resolutionScale;
  }

  virtual Rect getBounds() const = 0;

 protected:
  explicit Shape(float resolutionScale);

 private:
  std::weak_ptr<Shape> weakThis;
  float _resolutionScale = 1.0f;

  virtual std::unique_ptr<DrawOp> makeOp(Context *context, const Color &color,
                                         const Matrix &viewMatrix, uint32_t renderFlags) const = 0;
};
}

