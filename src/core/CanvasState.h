//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "vgfx/core/BlendMode.h"
#include "vgfx/core/Path.h"

namespace vgfx {
    static constexpr uint32_t kDefaultClipID = 0;
    struct CanvasState {
        float alpha = 1.0f;
        BlendMode blendMode = BlendMode::SrcOver;
        Matrix matrix = Matrix::I();
        Path clip = {};
        uint32_t clipID = kDefaultClipID;
    };
}
