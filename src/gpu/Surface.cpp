//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/gpu/Surface.h"
#include "utils/PixelFormatUtil.h"
#include "gpu/proxies/RenderTargetProxy.h"

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

}