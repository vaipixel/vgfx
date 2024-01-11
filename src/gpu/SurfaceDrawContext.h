//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "vgfx/gpu/Surface.h"

namespace vgfx {

    class SurfaceDrawContext {
    public:
        explicit SurfaceDrawContext(Surface *surface) : surface(surface) {

        }

    private:
        Surface *surface = nullptr;

    };

} // vgfx