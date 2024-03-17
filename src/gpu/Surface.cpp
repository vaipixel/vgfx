//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/gpu/Surface.h"
#include "DrawingManager.h"
#include "core/PixelBuffer.h"
#include "gpu/ProxyProvider.h"
#include "gpu/RenderContext.h"
#include "images/TextureImage.h"
#include "utils/PixelFormatUtil.h"
#include "utils/Logger.h"

namespace vgfx {
std::shared_ptr<Surface> Surface::Make(vgfx::Context *context, int width, int height, bool alphaOnly,
                                       int sampleCount, bool mipMapped,
                                       const vgfx::SurfaceOptions *options) {
  return Make(context, width, height, alphaOnly ? ColorType::ALPHA_8 : ColorType::RGBA_8888,
              sampleCount, mipMapped, options);
}

std::shared_ptr<Surface> Surface::Make(vgfx::Context *context, int width, int height, vgfx::ColorType colorType,
                                       int sampleCount, bool mipMapped,
                                       const vgfx::SurfaceOptions *options) {
  auto pixelFormat = ColorTypeToPixelFormat(colorType);
  auto proxy = RenderTargetProxy::Make(context, width, height, pixelFormat, sampleCount, mipMapped);
  auto surface = MakeFrom(std::move(proxy), options);
  if (surface != nullptr) {
    surface->getCanvas()->clear();
  }
  return surface;
}

std::shared_ptr<Surface> Surface::MakeFrom(vgfx::Context *context,
                                           const BackendRenderTarget &renderTarget,
                                           ImageOrigin origin, const SurfaceOptions *options) {
  auto proxy = RenderTargetProxy::MakeFrom(context, renderTarget, origin);
  return MakeFrom(std::move(proxy), options);
}

std::shared_ptr<Surface> Surface::MakeFrom(vgfx::Context *context,
                                           const vgfx::BackendTexture &backendTexture,
                                           ImageOrigin origin, int sampleCount,
                                           const SurfaceOptions *options) {
  auto proxy = RenderTargetProxy::MakeFrom(context, backendTexture, sampleCount, origin);
  return MakeFrom(std::move(proxy), options);
}

std::shared_ptr<Surface>
Surface::MakeFrom(vgfx::Context *context, vgfx::HardwareBufferRef hardwareBuffer, int sampleCount,
                  const vgfx::SurfaceOptions *options) {
  auto proxy = RenderTargetProxy::MakeFrom(context, hardwareBuffer, sampleCount);
  return MakeFrom(std::move(proxy), options);
}

std::shared_ptr<Surface> Surface::MakeFrom(std::shared_ptr<RenderTargetProxy> renderTargetProxy,
                                           const vgfx::SurfaceOptions *options) {
  if (renderTargetProxy == nullptr) {
    LOGD("renderTargetProxy is nullptr");
    return nullptr;
  }
  return std::shared_ptr<Surface>(new Surface(std::move(renderTargetProxy), options));
}

Surface::Surface(std::shared_ptr<RenderTargetProxy> proxy, const vgfx::SurfaceOptions *options)
    : renderTargetProxy(proxy) {
  DEBUG_ASSERT(this->renderTargetProxy != nullptr);
  if (options != nullptr) {
    surfaceOptions = *options;
  }
  renderContext = new RenderContext(renderTargetProxy);
}

Surface::~Surface() {
  delete canvas;
  delete renderContext;
}

Context *Surface::getContext() const {
  return renderTargetProxy->getContext();
}

int Surface::width() const {
  return renderTargetProxy->width();
}

int Surface::height() const {
  return renderTargetProxy->height();
}

ImageOrigin Surface::origin() const {
  return renderTargetProxy->origin();
}

std::shared_ptr<TextureProxy> Surface::getTextureProxy() {
  if (!renderTargetProxy->isTextureBackend()) {
    return nullptr;
  }
  auto drawingManager = getContext()->drawingManager();
  drawingManager->addTextureResolveTask(renderTargetProxy);
  return renderTargetProxy->getTextureProxy();
}

BackendRenderTarget Surface::getBackendRenderTarget() {
  flush();
  auto renderTarget = renderTargetProxy->getRenderTarget();
  if (renderTarget == nullptr) {
    return {};
  }
  return renderTarget->getBackendRenderTarget();
}

}