//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/core/Canvas.h"
#include "CanvasState.h"
#include "utils/Logger.h"
#include "gpu/SurfaceDrawContext.h"
#include <atomic>

namespace vgfx {
static uint32_t NextClipID() {
  static const uint32_t kFirstUnreservedClipID = 1;
  static std::atomic_uint32_t nextID{kFirstUnreservedClipID};
  uint32_t id;
  do {
    id = nextID++;
  } while (id < kFirstUnreservedClipID);
  return id;
}

Canvas::Canvas(vgfx::Surface *surface) : surface(surface), clipID(kDefaultClipID) {
  state = std::make_shared<CanvasState>();
  state->clip.addRect(0, 0, static_cast<float >(surface->width()),
                      static_cast<float >(surface->height()));
  state->clipID = NextClipID();
}

void Canvas::save() {
  auto canvasState = std::make_shared<CanvasState>();
  *canvasState = *state;
  savedStateList.push_back(canvasState);
}

void Canvas::restore() {
  if (savedStateList.empty()) {
    LOGW("savedStateList is empty");
    return;
  }
  state = savedStateList.back();
  savedStateList.pop_back();
}

Matrix Canvas::getMatrix() const {
  return state->matrix;
}

void Canvas::setMatrix(const vgfx::Matrix &matrix) {
  state->matrix = matrix;
}

void Canvas::resetMatrix() {
  state->matrix.reset();
}

Canvas::~Canvas() {
  vgfx::PrintLog("Destroy Canvas");
  delete drawContext;
}

void Canvas::clear(const vgfx::Color &color) {

}

}