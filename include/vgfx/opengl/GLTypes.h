//
// Created by Anatta Feng on 2024/1/13.
//

#pragma once

namespace vgfx {
    /**
     * Types for interacting with GL textures created externally to VGFX.
     */
    struct GLTextureInfo {
        /**
         * The id of this texture.
         */
        unsigned id = 0;
        /**
         * The target of this texture.
         */
        unsigned target = 0x0DE1;  // GL_TEXTURE_2D;
        /**
         * The pixel format of this texture.
         */
        unsigned format = 0x8058;  // GL_RGBA8
    };

    /**
     * Types for interacting with GL frame buffers created externally to VGFX.
     */
    struct GLFrameBufferInfo {
        /**
         * The id of this frame buffer.
         */
        unsigned id = 0;

        /**
         * The pixel format of this frame buffer.
         */
        unsigned format = 0x8058;  // GL_RGBA8
    };
}
