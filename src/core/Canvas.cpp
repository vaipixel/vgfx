//
// Created by Anatta Feng on 2024/1/7.
//

#include "vgfx/core/Canvas.h"
#include "utils/Logger.h"
#include <atomic>

namespace vgfx {
    static uint32_t NextClipID() {
        static const uint32_t kFirstUnreservedClipID = 1;
        static std::atomic_uint32_t nextID{kFirstUnreservedClipID};
        uint32_t id;
        do {
            id = nextID++;
        } while (id < kFirstUnreservedClipID);
        return id;
    }

    Canvas::Canvas(vgfx::Surface *surface) : surface(surface), clipID(kDefaultClipID) {
        drawContext = new SurfaceDrawContext(surface);
        state = std::make_shared<CanvasState>();
    }

    Canvas::~Canvas() {
        vgfx::logd("Destroy Canvas");
        delete drawContext;
    }


}