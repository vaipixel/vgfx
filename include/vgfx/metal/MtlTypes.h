//
// Created by Anatta Feng on 2024/1/13.
//

namespace vgfx {
/**
 * Types for interacting with Metal resources created externally to VGFX. Holds the MTLTexture as a
 * const void*.
 */
struct MtlTextureInfo {
  /**
   * Pointer to MTLTexture.
   */
  const void *texture = nullptr;
};
}