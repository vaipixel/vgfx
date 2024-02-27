//
// Created by Anatta Feng on 2024/2/27.
//

#pragma once

#include <string>
#include <unordered_map>
namespace vgfx {
/**
 * Reflected description of a uniform variable in the GPU program.
 */
struct Uniform {
  /**
   * Possible types of a uniform variable.
   */
  enum class Type {
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
  };

  std::string name;
  Type type;

  /**
   * Returns the size of the uniform in bytes.
   */
  size_t size() const;
};

/**
 * An object representing the collection of uniform variables in a GPU program.
 */
class UniformBuffer {
 private:
  std::string nameSuffix = "";
  std::unordered_map<std::string, size_t> uniformMap = {};

  void onSetData(const std::string &name, const void *data, size_t size);

};

} // vgfx