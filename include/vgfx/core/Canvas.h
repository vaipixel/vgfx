//
// Created by Anatta Feng on 2024/1/7.
//

#ifndef VGFX_CANVAS_H
#define VGFX_CANVAS_H

#include "vgfx/gpu/Surface.h"

namespace vgfx {
    /**
     * Canvas provides an interface for drawing, and how the drawing is clipped and transformed. Canvas
     * contains a stack of opacity, blend mode, matrix and clip values. Each Canvas draw call transforms
     * the geometry of the object by the concatenation of all matrix values in the stack. The
     * transformed geometry is clipped by the intersection of all of clip values in the stack.
     */
    class Canvas {
    public:
        explicit Canvas(Surface *surface);

        ~Canvas();

        /**
         * Retrieves the context associated with this Surface.
         * @return
         */
        Context *getContext() const;

        /**
         * Returns the Surface this canvas draws into.
         * @return
         */
        Surface *getSurface() const;

        /**
         * Returns the SurfaceOptions associated with the Canvas. Returns nullptr if the Canvas is not
         * created from a surface.
         * @return
         */
        const SurfaceOptions *surfaceOptions() const;

        /**
         * Save alpha, blend mode, matrix, and clip. Calling restore() discards changes to them,
         * restoring them to their state when save() was called. Saved Canvas state is put on a stack,
         * multiple calls to save() should be balanced by an equal number of calls to restore().
         */
        void save();

        /**
         * Removes changes to alpha, blend mode, matrix and clips since Canvas state was last saved.
         * The state is removed from the stack. Does nothing if th stack is empty.
         */
        void restore();

        Matrix getMatrix() const;

        void draw();
    };

}
#endif //VGFX_CANVAS_H
