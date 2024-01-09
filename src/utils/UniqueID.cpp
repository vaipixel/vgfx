//
// Created by Anatta Feng on 2024/1/7.
//

#include "UniqueID.h"

namespace vgfx {
    static std::atomic_uint32_t IDCount = {1};

    uint32_t UniqueID::Next() {
        return IDCount++;
    }
} // vgfx