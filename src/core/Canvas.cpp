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

void Canvas::setMatrix(const Matrix &matrix) {
  state->matrix = matrix;
}

void Canvas::resetMatrix() {
  state->matrix.reset();
}

void Canvas::concat(const Matrix &matrix) {
  state->matrix.preConcat(matrix);
}

float Canvas::getAlpha() const {
  return state->alpha;
}
void Canvas::setAlpha(float newAlpha) {
  state->alpha = newAlpha;
}

BlendMode Canvas::getBlendMode() const {
  return state->blendMode;
}

void Canvas::setBlendMode(BlendMode blendMode) {
  state->blendMode = blendMode;
}

Path Canvas::getTotalClip() const {
  return state->clip;
}

void Canvas::clipRect(const Rect &rect) {
  Path path = {};
  path.addRect(rect);
  clipPath(path);
}

void Canvas::clipPath(const Path &path) {
  auto clipPath = path;
  clipPath.transform(state->matrix);
  state->clip.addPath(clipPath, PathOp::Intersect);
  state->clipID = NextClipID();
}

void Canvas::clear(const vgfx::Color &color) {
  auto oldBlend = getBlendMode();
  setBlendMode(BlendMode::Src);
  Paint paint;
  paint.setColor(color);
  auto rect = Rect::MakeWH(surface->width(), surface->height());
  drawRect(rect, paint);
  setBlendMode(oldBlend);
}

static bool AffectsAlpha(const ColorFilter *colorFilter) {
  return colorFilter && !colorFilter->isAlphaUnchanged();
}

bool Canvas::nothingToDraw(const vgfx::Paint &paint) const {
  switch (getBlendMode()) {
    case BlendMode::SrcOver:
    case BlendMode::SrcATop:
    case BlendMode::DstOut:
    case BlendMode::DstOver:
    case BlendMode::Plus:
      if (0 == getAlpha() || 0 == paint.getAlpha()) {
        return !AffectsAlpha(paint.getColorFilter().get()) && paint.getImageFilter() == nullptr;
      }
      break;
    case BlendMode::Dst:return true;
    default:break;
  }
  return false;
}
void Canvas::drawRect(const vgfx::Rect &rect, const vgfx::Paint &paint) {
  Path path = {};
  path.addRect(rect);
  drawPath(path, paint);
}

static Paint CleanPaintForDrawImage(const Paint *paint) {
  Paint cleaned;
  if (paint) {
    cleaned = *paint;
    cleaned.setStyle(PaintStyle::Fill);
  }
  return cleaned;
}

void Canvas::flush() {
  surface->flush();
}

Context *Canvas::getContext() const {
  return surface->getContext();
}

Surface *Canvas::getSurface() const {
  return surface;
}

const SurfaceOptions *Canvas::surfaceOptions() const {
  return surface->options();
}

std::shared_ptr<TextureProxy> Canvas::getClipTexture() {
  if (clipID != state->clipID) {
    _clipSurface = nullptr;
  }
  if (_clipSurface == nullptr) {
    _clipSurface = Surface::Make(getContext(), surface->width(), surface->height(), true);
    if (_clipSurface == nullptr) {
      _clipSurface = Surface::Make(getContext(), surface->width(), surface->height());
    }
  }
  if (_clipSurface == nullptr) {
    return nullptr;
  }
  if (clipID != state->clipID) {
    auto clipCanvas = _clipSurface->getCanvas();
    clipCanvas->clear();
    Paint paint = {};
    paint.setColor(Color::White());
    clipCanvas->drawPath(state->clip, paint);
    clipID = state->clipID;
  }
  return _clipSurface->getTextureProxy();
}

static constexpr float BOUNDS_TO_LERANCE = 1e-3f;

/**
 * Returns true if the given rect counts as aligned with pixel boundaries.
 */
static bool IsPixelAligned(const Rect &rect) {
  return fabsf(roundf(rect.left) - rect.left) <= BOUNDS_TO_LERANCE &&
      fabsf(roundf(rect.top) - rect.top) <= BOUNDS_TO_LERANCE &&
      fabsf(roundf(rect.right) - rect.right) <= BOUNDS_TO_LERANCE &&
      fabsf(roundf(rect.bottom) - rect.bottom) <= BOUNDS_TO_LERANCE;
}

void FlipYIfNeeded(Rect* rect, const Surface* surface) {
  if (surface->origin() == ImageOrigin::BottomLeft) {
    auto height = rect->height();
    rect->top = static_cast<float >(surface->height()) - rect->bottom;
    rect->bottom = rect->top + height;
  }
}

std::pair<std::optional<Rect>, bool> Canvas::getClipRect(const vgfx::Rect *drawBounds) {
  auto rect = Rect::MakeEmpty();
  if (state->clip.asRect(&rect)) {
    if (drawBounds != nullptr && !rect.intersect(*drawBounds)) {
      return {{}, false};
    }
    FlipYIfNeeded(&rect, surface);
    if (IsPixelAligned(rect)) {
      rect.round();
      if (rect != Rect::MakeWH(surface->width(), surface->height())) {
        return {rect, true};
      } else {
        return {Rect::MakeEmpty(), false};
      }
    } else {
      return {rect, false};
    }
  }
  return {{}, false};
}

std::unique_ptr<FragmentProcessor> Canvas::getClipMask(const vgfx::Rect &deviceBounds, vgfx::Rect *scissorRect) {
  const auto &clipPath = state->clip;
  if (clipPath.contains(deviceBounds)) {
    return nullptr;
  }
  auto [rect, useScissor] = getClipRect();
  if (rect.has_value()) {
    if (!rect->isEmpty()) {
      *scissorRect = *rect;
      if (!useScissor) {
        scissorRect->roundOut();
        return AARectEffect::Make(*rect);
      }
    }
  }
}
Canvas::~Canvas() {
  vgfx::PrintLog("Destroy Canvas");
  delete drawContext;
}

}