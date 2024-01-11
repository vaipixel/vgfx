//
// Created by Anatta Feng on 2024/1/7.
//

#ifndef VGFX_CANVAS_H
#define VGFX_CANVAS_H

#include "vgfx/gpu/Surface.h"
#include "Matrix.h"
#include "BlendMode.h"
#include "Rect.h"
#include "Paint.h"

namespace vgfx {
    class Surface;

    class SurfaceOptions;
    class Context;

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

        /**
         * Returns the current total matrix.
         * @return
         */
        Matrix getMatrix() const;

        /**
         * Replaces transformation with specified matrix. Unlike concat(), any prior matrix state is
         * overwritten.
         * @param matrix  matrix to copy, replacing existing Matrix.
         */
        void setMatrix(const Matrix &matrix);

        /**
         * Sets Matrix to the identity matrix. Any prior matrix state is overwritten.
         */
        void resetMatrix();

        /**
         * Replaces the current Matrix with matrix premultiplied with the existing one. This has the
         * effect of transforming the drawn geometry by matrix, before transforming the result with the
         * existing Matrix.
         * @param matrix
         */
        void concat(const Matrix &matrix);

        /**
         * Returns the current global alpha.
         * @return
         */
        float getAlpha() const;

        /**
         * Replaces the global alpha with specified newAlpha.
         * @param newAlpha
         */
        void setAlpha(float newAlpha);

        /**
         * Returns the current global blend mode.
         * @return
         */
        BlendMode getBlendMode() const;

        /**
         * Replaces the global blend mode with specified new blend mode.
         * @param blendMode
         */
        void setBlendMode(BlendMode blendMode);

        /**
         * Draws a rectangle with specified paint, using current alpha, blend mode, clip and matrix.
         * @param rect
         * @param paint
         */
        void drawRect(const Rect &rect, const Paint &paint);

    private:
        Surface *surface = nullptr;
        std::shared_ptr<Surface> _clipSurface = nullptr;
        uint32_t clipID = 0;
        std::shared_ptr<CanvasState> state = nullptr;
        SurfaceDrawContext* drawContext = nullptr;

    };

}
#endif //VGFX_CANVAS_H
