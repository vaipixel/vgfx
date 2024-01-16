//
// Created by Anatta Feng on 2024/1/17.
//

#pragma once

namespace vgfx {

    /**
     * RGBA color value, holding four floating point components. Color components are always in a known
     * order.
     */
    struct Color {
        /**
         * Red component.
         */
        float red;

        /**
         * Green component.
         */
        float green;

        /**
         * Blue component.
         */
        float blue;

        /**
         * Alpha component.
         */
        float alpha;
    };

} // vgfx