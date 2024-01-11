//
// Created by Anatta Feng on 2024/1/11.
//

#include "vgfx/core/Matrix.h"

namespace vgfx {
    const Matrix &Matrix::I() {
        // TODO
        static const Matrix identity = {};
        return identity;
    }
} // vgfx