//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

namespace vgfx {

struct Point {
  float x;
  float y;
  static const Point &Zero() {
    static const Point zero = Point::Make(0, 0);
    return zero;
  }

  static constexpr Point Make(float x, float y) {
    return {x, y};
  }

  static constexpr Point Make(int x, int y) {
    return {static_cast<float >(x), static_cast<float >(y)};
  }

  bool isZero() const {
    return (0 == x) & (x == y);
  }
  void set(float xValue, float yValue) {
    x = xValue;
    y = yValue;
  }

  void offset(float dx, float dy) {
    x += dx;
    y += dy;
  }

  float length() const {
    return Point::Length(x, y);
  }

  friend bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
  }

  friend bool operator!=(const Point &a, const Point &b) {
    return a.x != b.x && a.y != b.y;
  }
};

} // vgfx