//
// Created by Anatta Feng on 2024/2/28.
//

#pragma once

namespace vgfx {

/**
 * Types of shader-language-specific boxed variables we can create.
 */
enum class ShaderLanguageType {
  Void,
  Float,
  Float2,
  Float3,
  Float4,
  Float2x2,
  Float3x3,
  Float4x4,
  Int,
  Int2,
  Int3,
  Int4,
  Texture2DSampler,
  TextureExternalSampler,
  Texture2DRectSampler,
};

} // vgfx