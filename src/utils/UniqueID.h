//
// Created by 冯旭超 on 2024/1/7.
//

#pragma once

#include "atomic"

namespace vgfx {

    class UniqueID {
    public:
        static uint32_t Next();
    };

} // vgfx