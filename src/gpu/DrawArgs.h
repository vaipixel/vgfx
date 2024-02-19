//
// Created by Anatta Feng on 2024/2/19.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "vgfx/core/Matrix.h"
#include "vgfx/core/SamplingOptions.h"
namespace vgfx {

class DrawArgs {
 public:
  DrawArgs(Context *context, uint32_t renderFlags, const Color &color, const Rect &drawRect,
           const Matrix &viewMatrix = Matrix::I(), const SamplingOptions &sampling = {})
      : context(context), renderFlags(renderFlags), color(color), drawRect(drawRect),
        viewMatrix(viewMatrix), sampling(sampling) {}

  Context *context = nullptr;
  uint32_t renderFlags = 0;
  Color color = Color::White();
  Rect drawRect = Rect::MakeEmpty();
  Matrix viewMatrix = Matrix::I();
  SamplingOptions sampling = {};
};

} // vgfx