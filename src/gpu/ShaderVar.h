//
// Created by Anatta Feng on 2024/2/28.
//

#pragma once

#include <string>
#include "ShaderLanguageType.h"
namespace vgfx {

enum class ShaderFlags : unsigned {
  None = 0,
  Vertex = 1 << 0,
  Fragment = 1 << 1,
//  VGFX_MARK_AS_BITMASK_ENUM(Fragment)
};

class ShaderVar {
 public:
  enum class TypeModifier {
    None,
    Attribute,
    Varying,
    Uniform,
    Out,
  };

  ShaderVar() = default;

  ShaderVar(std::string name, ShaderLanguageType type) : _type(type), _name(std::move(name)) {
  }

  ShaderVar(std::string name, ShaderLanguageType type, TypeModifier typeModifier) :
      _type(type), _typeModifier(typeModifier), _name(std::move(name)) {
  }

  void setName(const std::string &name) {
    _name = name;
  }

  const std::string &name() const {
    return _name;
  }

  void setType(ShaderLanguageType type) {
    _type = type;
  }

  ShaderLanguageType type() const {
    return _type;
  }

  void setTypeModifier(TypeModifier type) {
    _typeModifier = type;
  }

  TypeModifier typeModifier() const {
    return _typeModifier;
  }
 private:
  ShaderLanguageType _type = ShaderLanguageType::Void;
  TypeModifier _typeModifier = TypeModifier::None;
  std::string _name;
};

} // vgfx