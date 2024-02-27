//
// Created by Anatta Feng on 2024/2/27.
//

#pragma once

#include <memory>
#include "vgfx/core/Point.h"
#include "Texture.h"
#include "ProgramInfo.h"
#include "gpu/processors/FragmentProcessor.h"
namespace vgfx {

struct DstTextureInfo {
  bool requiresBarrier = false;
  Point offset = Point::Zero();
  std::shared_ptr<Texture> texture = nullptr;
};

/**
 * Pipeline is a ProgramInfo that uses a list of Processors to assemble a shader program and set API
 * state for a draw.
 */
class Pipeline : public ProgramInfo {
 public:
  Pipeline(std::unique_ptr<GeometryProcessor> geometryProcessor,
           std::vector<std::unique_ptr<FragmentProcessor>> fragmentProcessors,
           size_t numColorProcessors, BlendMode blendMode, const DstTextureInfo &dstTextureInfo,
           const Swizzle *outputSwizzle);

  size_t numColorFragmentProcessors() const {
    return numColorProcessors;
  }

  size_t numFragmentProcessors() const {
    return fragmentProcessors.size();
  }

  const GeometryProcessor* getGeometryProcessor() const {
    return geometryProcessor.get();
  }

  const FragmentProcessor* getFragmentProcessor(size_t index) const {
    return fragmentProcessors[index].get();
  }

  const XferProcessor *getXferProcessor() const;

  const Swizzle* outputSwizzle() const {
    return _outputSwizzle;
  }

  const Texture* dstTexture() const {
    return dstTextureInfo.texture.get();
  }

  const Point& dstTextureOffset() const {
    return dstTextureInfo.offset;
  }

  bool requiresBarrier() const override {
    return dstTextureInfo.requiresBarrier;
  }

  const BlendInfo* blendInfo() const override {
    return xferProcessor == nullptr ? &_blendInfo : nullptr;
  }

  void getUniforms(UniformBuffer *buffer) const override;

  std::vector<SamplerInfo> getSamplers() const override;

  void computeProgramKey(Context *context, BytesKey *programKey) const override;

  std::unique_ptr<Program> createProgram(Context *context) const override;

  /**
   * Returns the index of the processor in the pipeline. Returns -1 if the processor is not in the
   * pipeline.
   */
  int getProcessorIndex(const Processor *processor) const;

  std::string getMangledSuffix(const Processor *processor) const;

 private:std::unique_ptr<GeometryProcessoe> geometryProcessor = {};
  std::vector<std::unique_ptr<FragmentProcessor>> fragmentProcessors = {};
  std::unordered_map<const Processor *, int> processorIndices = {};
  // This value is also the index in fragmentProcessors where coverage processors begin.
  size_t numColorProcessors = 0;
  std::unique_ptr<XferProcessor> xferProcessor;
  BlendInfo _blendInfo = {};
  DstTextureInfo dstTextureInfo = {};
  const Swizzle *_outputSwizzle = nullptr;

  void updateProcessorIndices();
};

} // vgfx