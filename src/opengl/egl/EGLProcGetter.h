//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "opengl/GLProcGetter.h"

namespace vgfx {

    class EGLProcGetter : public GLProcGetter {
    public:
        void *getProcAddress(const char *name) const override;
    };

} // vgfx