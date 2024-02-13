//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

#include <cmath>
namespace vgfx {

/**
 * Point holds two 32-bit floating point coordinates.
 */
struct Point {
  /**
   * x-axis value.
   */
  float x;
  /**
   * y-axis value.
   */
  float y;

  /**
   * Creates a Point set to (0, 0).
   */
  static const Point &Zero() {
    static const Point zero = Point::Make(0, 0);
    return zero;
  }

  /**
   * Creates a Point with specified x and y value.
   */
  static constexpr Point Make(float x, float y) {
    return {x, y};
  }

  /**
   * Creates a Point with specified x and y value.
   */
  static constexpr Point Make(int x, int y) {
    return {static_cast<float >(x), static_cast<float >(y)};
  }

  /**
   * Returns true if fX and fY are both zero.
   */
  bool isZero() const {
    return (0 == x) & (x == y);
  }

  /**
   * Sets fX to x and fY to y.
   */
  void set(float xValue, float yValue) {
    x = xValue;
    y = yValue;
  }

  /**
   * Adds offset (dx, dy) to Point.
   */
  void offset(float dx, float dy) {
    x += dx;
    y += dy;
  }

  /**
   * Returns the Euclidean distance from origin.
   */
  float length() const {
    return Point::Length(x, y);
  }

  /**
   * Returns true if a is equivalent to b.
   */
  friend bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
  }

  /**
   * Returns true if a is not equivalent to b.
   */
  friend bool operator!=(const Point &a, const Point &b) {
    return a.x != b.x && a.y != b.y;
  }

  /**
   * Returns a Point from b to a; computed as (a.fX - b.fX, a.fY - b.fY).
   */
  friend Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
  }

  /**
   * Returns Point resulting from Point a offset by Point b, computed as:
   * (a.fX + b.fX, a.fY + b.fY).
   */
  friend Point operator+(const Point &a, const Point &b) {
    return {a.x + b.x, a.y + b.y};
  }

  /**
   * Returns the Euclidean distance from origin.
   */
  static float Length(float x, float y) {
    return sqrt(x * x + y * y);
  }

  /**
   * Returns the Euclidean distance between a and b.
   */
  static float Distance(const Point &a, const Point &b) {
    return Length(a.x - b.x, a.y - b.y);
  }
};

} // vgfx