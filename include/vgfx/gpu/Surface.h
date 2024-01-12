//
// Created by Anatta Feng on 2024/1/7.
//
#pragma once

#include "vgfx/core/Canvas.h"
#include "Context.h"
#include "SurfaceOptions.h"
#include "vgfx/core/ColorType.h"

namespace vgfx {

    /**
     * The Surface class is responsible for managing the pixels that a Canvas draws into. The Surface
     * takes care of allocating a Canvas that will draw into the surface. Call surface->getCanvas() to
     * use that Canvas (but don't delete it, it is owned by the surface). The Surface always has
     * non-zero dimensions. If there is a request for a new surface, and either of the requested
     * dimensions is zero, then nullptr will be returned.
     */
    class Surface {
    public:
        /**
         * Create a new Surface on GPU indicated by context. Allocates memory for pixels based on the
         * width, height, and color type (alpha only). A Surface with MSAA enabled is returned if the
         * sample count is greater than 1. Return nullptr if the size is invalid or the alpha-only
         * textures are not renderable in the GPU backend.
         * @param context
         * @param width
         * @param height
         * @param alphaOnly
         * @param sampleCount
         * @param mipMapped
         * @param options
         * @return
         */
        static std::shared_ptr<Surface> Make(Context *context, int width, int height,
                                             bool alphaOnly = false, int sampleCount = 1,
                                             bool mipMapped = false,
                                             const SurfaceOptions *options = nullptr);

        static std::shared_ptr<Surface> Make(Context *context, int width, int height, ColorType colorType,
                                             int sampleCount = 1, bool mipMapped = false,
                                             const SurfaceOptions *options = nullptr);

    };

}

