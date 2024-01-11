//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "vgfx/core/Matrix.h"

namespace vgfx {

    /**
     * Path contain geometry. Path may be empty, or contain one or more verbs that outline a figure.
     * Path always starts with a move verb to a Cartesian coordinate, and may be followed by additional
     * verbs that add lines or curves. dding a close verb makes the geometry into a continuous loop, a
     * closed contour. Path may contain any number of contours, each beginning with a move verb.
     */
    class Path {

    };

} // vgfx