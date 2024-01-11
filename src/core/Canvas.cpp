//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/core/Canvas.h"
#include "utils/Logger.h"

namespace vgfx {
    Canvas::Canvas(vgfx::Surface *surface) {

    }

    Canvas::~Canvas() {
        vgfx::logd("Destroy Canvas");
    }


}