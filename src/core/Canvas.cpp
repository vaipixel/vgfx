//
// Created by 冯旭超 on 2024/1/7.
//

#include "vgfx/core/Canvas.h"
#include "utils/Logger.h"

namespace vgfx {
    Canvas::Canvas() {
        vgfx::logd("Create Canvas");
    }

    Canvas::~Canvas() {
        vgfx::logd("Destroy Canvas");
    }

    void Canvas::draw() {
        vgfx::logd("draw");
    }
}