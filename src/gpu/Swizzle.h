//
// Created by Anatta Feng on 2024/2/17.
//

#pragma once

#include <cstdint>
#include "vgfx/core/Color.h"
namespace vgfx {

class Swizzle {
 public:
  constexpr Swizzle() : Swizzle("rgba") {

  }

  constexpr bool operator==(const Swizzle &that) const {
    return key == that.key;
  }

  constexpr bool operator!=(const Swizzle &that) const {
    return !(*this == that);
  }

  /**
 * Compact representation of the swizzle suitable for a key.
 */
  constexpr uint16_t asKey() const {
    return key;
  }

  /**
   * 4 char null terminated string consisting only of chars 'r', 'g', 'b', 'a'.
   */
  const char *c_str() const {
    return swiz;
  }

  char operator[](int index) const {
    return swiz[index];
  }

  static constexpr Swizzle RGBA() {
    return Swizzle("rgba");
  }
  static constexpr Swizzle AAAA() {
    return Swizzle("aaaa");
  }
  static constexpr Swizzle RRRR() {
    return Swizzle("rrrr");
  }
  static constexpr Swizzle RRRA() {
    return Swizzle("rrra");
  }
  static constexpr Swizzle RGRG() {
    return Swizzle("rgrg");
  }
  static constexpr Swizzle RARA() {
    return Swizzle("rara");
  }

  Color applyTo(const Color &color) const;

 private:
  char swiz[5];
  uint16_t key = 0;

  static constexpr int CToI(char c) {
    switch (c) {
      case 'r':return 0;
      case 'g':return 1;
      case 'b':return 2;
      case 'a':return 3;
      case '1':return 4;
      default:return -1;
    }
  }

  static constexpr uint16_t MakeKey(const char c[4]) {
    return static_cast<uint16_t >((CToI(c[0]) << 0) | (CToI(c[1]) << 4) | (CToI(c[2]) << 8) |
        (CToI(c[3]) << 12));
  }

  constexpr explicit Swizzle(const char c[4]) : swiz{c[0], c[1], c[2], c[3], '\0'}, key(MakeKey(c)) {

  }
};

} // vgfx