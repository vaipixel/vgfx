//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "atomic"

namespace vgfx {

    class UniqueID {
    public:
        static uint32_t Next();
    };

} // vgfx