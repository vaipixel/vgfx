//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/gpu/Surface.h"
#include "utils/PixelFormatUtil.h"
#include "gpu/proxies/RenderTargetProxy.h"
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
                                               const vgfx::BackendRenderTarget &renderTarget,
                                               vgfx::ImageOrigin origin, const vgfx::SurfaceOptions *options) {
        auto proxy = RenderTargetProxy::MakeFrom(context, renderTarget, origin);
        return MakeFrom(std::move(proxy), options);
    }

    std::shared_ptr<Surface> Surface::MakeFrom(vgfx::Context *context,
                                               const vgfx::BackendTexture &backendTexture,
                                               vgfx::ImageOrigin origin,
                                               int sampleCount, const vgfx::SurfaceOptions *options) {
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
            logd("renderTargetProxy is nullptr");
            return nullptr;
        }
        return std::shared_ptr<Surface>(new Surface(std::move(renderTargetProxy), options));
    }

}