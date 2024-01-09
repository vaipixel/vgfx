//
// Created by Anatta Feng on 2024/1/7.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "GLInterface.h"

namespace vgfx {

    class GLInterface;

    class GLContext : public Context {
    public:
        static GLContext *Unwrap(Context *context) {
            return static_cast<GLContext *>(context);
        }

        GLContext(Device *device, const GLInterface *glInterface);

    };

} // vgfx