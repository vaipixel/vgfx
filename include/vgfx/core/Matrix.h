//
// Created by Anatta Feng on 2024/1/11.
//

#pragma once

#include <cstring>

namespace vgfx {

    /**
     * Matrix holds a 3x2 matrix for transforming coordinates. This allows mapping Point and vectors
     * with translation, scaling, skewing, and rotation. Together these types of transformations are
     * known an affine transformations. Affine transformations preserve the straightness of lines while
     * transforming, so that parallel lines stay parallel. Matrix elements are in row major order.
     * Matrix does not have a constructor, so it must be explicitly initialized.
     */
    class Matrix {
    public:
        /**
         * Sets Matrix to scale by (sx, sy). Returned matrix is:
         *
         *       | sx  0  0 |
         *       |  0 sy  0 |
         *       |  0  0  1 |
         * @param sx  horizontal scale factor
         * @param sy  vertical scale factor
         * @return    Matrix with scale factors.
         */
        static Matrix MakeScale(float sx, float sy) {
            Matrix m = {};
            m.setScale(sx, sy);
            return m;
        }

        /**
         * Sets Matrix to scale by (c, scale). Returned matrix is:
         *
         *       | scale   0    0 |
         *       |   0   scale  0 |
         *       |   0    0     1 |
         * @param scale  horizontal and vertical scale factor
         * @return    Matrix with scale factors.
         */
        static Matrix MakeScale(float scale) {
            Matrix m = {};
            m.setScale(scale, scale);
            return m;
        }

        bool isIdentity() const {
            return values[0] == 1 && values[1] == 0 && values[2] == 0 && values[3] == 0 && values[4] == 1 &&
                   values[5] == 0;
        }

        /**
         * Sets Matrix to translate by (tx, ty).
         * @param tx  horizontal translation.
         * @param ty  vertical translation.
         */
        void setScale(float tx, float ty);

        /**
         * Returns reference to const identity Matrix. Returned Matrix is set to:
         *
         *       | 1 0 0 |
         *       | 0 1 0 |
         *       | 0 0 1 |
         *
         *   @return  const identity Matrix
         */
        static const Matrix &I();

    private:
        float values[6];

        /**
         * Matrix organizes its values in row order. These members correspond to each value in Matrix.
         */
        static constexpr int SCALE_X = 0;  //!< horizontal scale factor
        static constexpr int SKEW_X = 1;   //!< horizontal skew factor
        static constexpr int TRANS_X = 2;  //!< horizontal translation
        static constexpr int SKEW_Y = 3;   //!< vertical skew factor
        static constexpr int SCALE_Y = 4;  //!< vertical scale factor
        static constexpr int TRANS_Y = 5;  //!< vertical translation

        void setScaleTranslate(float sx, float sy, float tx, float ty);
    };

} // vgfx