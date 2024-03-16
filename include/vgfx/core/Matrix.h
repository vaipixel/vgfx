//
// Created by Anatta Feng on 2024/1/11.
//

#pragma once

#include <cstring>
#include "vgfx/core/Rect.h"

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

  /**
   * Sets Matrix to translate by (tx, ty). Returned matrix is:
   *
   *       | 1 0 tx |
   *       | 0 1 ty |
   *       | 0 0  1 |
   *
   * @param tx  horizontal translation
   * @param ty  vertical translation
   * @return    Matrix with translation
   */
  static Matrix MakeTrans(float tx, float ty) {
    Matrix m = {};
    m.setTranslate(tx, ty);
    return m;
  }

  /**
   * Sets Matrix to:
   *
   *      | scaleX  skewX transX |
   *      | skewY  scaleY transY |
   *      |   0      0      1    |
   *
   * @param scaleX  horizontal scale factor
   * @param skewX   horizontal skew factor
   * @param transX  horizontal translation
   * @param skewY   vertical skew factor
   * @param scaleY  vertical scale factor
   * @param transY  vertical translation
   * @return        Matrix constructed from parameters
   */
  static Matrix MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY,
                        float transY) {
    Matrix m = {};
    m.setAll(scaleX, skewX, transX, scaleY, skewY, transY);
    return m;
  }

  /**
   * Returns true if Matrix is identity. The identity matrix is:
   *
   *       | 1 0 0 |
   *       | 0 1 0 |
   *       | 0 0 1 |
   *
   * @return  Returns true if the Matrix has no effect.
   */
  bool isIdentity() const {
    return values[0] == 1 && values[1] == 0 && values[2] == 0 && values[3] == 0 && values[4] == 1 &&
        values[5] == 0;
  }

  /**
   * Returns one matrix value.
   */
  float operator[](int index) const {
    return values[index];
  }

  /**
   * Returns writable Matrix value. */
  float &operator[](int index) {
    return values[index];
  }

  float get(int index) const {
    return values[index];
  }

  void set(int index, float value) {
    values[index] = value;
  }

  void get6(float buffer[6]) const {
    memcpy(buffer, values, 6 * sizeof(float));
  }

  void set6(const float buffer[6]) {
    memcpy(values, buffer, 6 * sizeof(float));
  }

  void get9(float buffer[9]) const;

  float getScaleX() const {
    return values[SCALE_X];
  }
  float getScaleY() const {
    return values[SCALE_Y];
  }

  float getSkewX() const {
    return values[SKEW_X];
  }

  float getSkewY() const {
    return values[SKEW_Y];
  }
  float getTranslateX() const {
    return values[TRANS_X];
  }
  float getTranslateY() const {
    return values[TRANS_Y];
  }

  void setScaleX(float v) { values[SCALE_X] = v; }

  void setScaleY(float v) {
    values[SCALE_Y] = v;
  }

  void setSkewX(float v) {
    values[SKEW_X] = v;
  }

  void setSkewY(float v) {
    values[SKEW_Y] = v;
  }

  void setTranslateX(float v) {
    values[TRANS_X] = v;
  }

  void setTranslateY(float v) {
    values[TRANS_Y] = v;
  }

  /**
   *
   * @param scaleX
   * @param skewX
   * @param transX
   * @param scaleY
   * @param skewY
   * @param transY
   */
  void setAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY);

  /**
   * Sets the Matrix to affine values, passed in column major order:
   *
   *      | a c tx |
   *      | b d ty |
   *      | 0    1 |
   *
   * @param a
   * @param b
   * @param c
   * @param d
   * @param tx
   * @param ty
   */
  void setAffine(float a, float b, float c, float d, float tx, float ty);

  /**
   * Sets Matrix to identity; which has no effect on mapped Point. Sets Matrix to:
   *
   *       | 1 0 0 |
   *       | 0 1 0 |
   *       | 0 0 1 |
   *
   * Also called setIdentity(); use the one that provides better inline documentation.
   */
  void reset();

  void setIdentity() {
    this->reset();
  }

  void setTranslate(float tx, float ty);

  /**
   * Sets Matrix to scale by sx and sy, about a pivot point at (px, py). The pivot point is
   * unchanged when mapped with Matrix.
   * @param sx  horizontal scale factor
   * @param sy  vertical scale factor
   * @param px  pivot on x-axis
   * @param py  pivot on y-axis
   */
  void setScale(float sx, float sy, float px, float py);

  /**
   * Sets Matrix to scale by sx and sy about at pivot point at (0, 0).
   * @param sx  horizontal scale factor
   * @param sy  vertical scale factor
   */
  void setScale(float sx, float sy);

  void setRotate(float degrees, float px, float py);

  void setRotate(float degrees);

  void setSinCos(float sinV, float cosV, float px, float py);

  void setSinCos(float sinV, float cosV);

  void setSkew(float kx, float ky, float px, float py);

  void setSkew(float kx, float ky);

  void setConcat(const Matrix &a, const Matrix &b);

  void preTranslate(float tx, float ty);

  void preScale(float sx, float sy);

  void preRotate(float degrees, float px, float py);

  void preRotate(float degrees);

  void preSkew(float kx, float ky, float px, float py);

  void preSkew(float kx, float ky);

  void preConcat(const Matrix &other);

  void postTranslate(float tx, float ty);

  void postScale(float sx, float sy, float px, float py);

  void postScale(float sx, float sy);

  void postRotate(float degrees, float px, float py);

  void postRotate(float degrees);

  void postSkew(float kx, float ky, float px, float py);

  void postSkew(float kx, float ky);

  void postConcat(const Matrix &other);

  bool invert(Matrix *inverse) const {
    if (this->isIdentity()) {
      if (inverse) {
        inverse->reset();
      }
      return true;
    }
    return this->invertNonIdentity(inverse);
  }

  bool invertible() const;

  void mapPoints(Point dst[], const Point src[], int count) const;

  void mapPoints(Point pts[], int count) const {
    this->mapPoints(pts, pts, count);
  }

  void mapXY(float x, float y, Point *result) const;

  Point mapXY(float x, float y) const {
    Point result = {};
    this->mapXY(x, y, &result);
    return result;
  }
  bool rectStaysRect() const;

  void mapRect(Rect *dst, const Rect &src) const;

  void mapRect(Rect *rect) const {
    mapRect(rect, *rect);
  }

  Rect mapRect(const Rect &src) const {
    Rect dst = {};
    mapRect(&dst, src);
    return dst;
  }

  friend bool operator==(const Matrix &a, const Matrix &b);

  friend bool operator!=(const Matrix &a, const Matrix &b) {
    return !(a == b);
  }

  float getMinScale() const;

  float getMaxScale() const;

  bool isFinite() const;

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
  bool invertNonIdentity(Matrix *inverse) const;
  bool getMinMaxScaleFactors(float results[2]) const;
};

} // vgfx