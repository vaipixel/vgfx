//
// Created by Anatta Feng on 2024/1/17.
//

#pragma once

#include "vgfx/core/ColorType.h"
#include "vgfx/core/AlphaType.h"
#include <cstddef>

namespace vgfx {

    /**
     * ImageInfo describes the properties for and area of pixels.
     */
    class ImageInfo {
    public:
        static bool IsValidSize(int width, int height);

        static ImageInfo Make(int width, int height, ColorType colorType,
                              AlphaType alphaType = AlphaType::Premultiplied, size_t rowBytes = 0);
    };

} // vgfx