//
// Created by Anatta Feng on 2024/2/28.
//

#pragma once

#include "Processor.h"
#include "FragmentProcessor.h"
#include "gpu/ShaderLanguageType.h"
#include "gpu/ShaderVar.h"
namespace vgfx {

class GeometryProcessor : public Processor {
 public:
  // Use only for easy-to-use aliases.
  using FPCoordTransformIterator = FragmentProcessor::CoordTransformIterator;

  class Attribute {
   public:
    Attribute() = default;
    Attribute(std::string name, ShaderLanguageType gpuType) : _name(std::move(name)), _gpuType(gpuType) {
    }

    bool isInitialized() const {
      return !_name.empty();
    }

    const std::string& name() const {
      return _name;
    }

    ShaderLanguageType gpuType() const {
      return _gpuType;
    }

    size_t sizeAlign4() const;

    ShaderVar asShaderVar() const {
      return {_name, _gpuType, ShaderVar::TypeModifier::Attribute};
    }

    void computeKey(BytesKey* bytesKey) const {
      bytesKey->write(isInitialized() ? static_cast<uint32_t>(_gpuType) : ~0u);
    }
   private:
    std::string _name;
    ShaderLanguageType _gpuType = ShaderLanguageType::Float;

  };
  const std::vector<const Attribute *> &vertexAttributes() const {
    return attributes;
  }

  void computeProcessorKey(Context* context, BytesKey* bytesKey) const override;
 private:
  std::vector<const Attribute *> attributes = {};

  virtual void onComputeProcessorKey(BytesKey *) const {
  }
};

} // vgfx