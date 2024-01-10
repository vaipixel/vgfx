//
// Created by Anatta Feng on 2024/1/7.
//
#pragma once

#include "vgfx/core/Canvas.h"
#include "Context.h"
#include "SurfaceOptions.h"

namespace vgfx {


    class Surface {
    public:
        static std::shared_ptr<Surface>
        Make(Context *context, int width, int height, bool alphaOnly = false, int sampleCount = 1,
             bool mipMapped = false, const SurfaceOptions *options = nullptr);

    };

}

