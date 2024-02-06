//
// Created by Anatta Feng on 2024/1/25.
//

#pragma once

namespace vgfx {

/**
 * Describes how to interpret the alpha component of a pixel.
 */
enum class AlphaType {
  Unknown,
  Opaque,
  Premultiplied,
  Unpremultiplied,
};

} // vgfx