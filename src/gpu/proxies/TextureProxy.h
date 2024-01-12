//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "ResourceProxy.h"
#include "vgfx/gpu/ImageOrigin.h"

namespace vgfx {

    /**
     * This class delays the acquisition of textures until they are actually required.
     */
    class TextureProxy : public ResourceProxy {
    public:
        /**
         * Return the width of the texture.
         * @return
         */
        int width() const {
            return _width;
        }

        /**
         * Returns the height if the texture.
         * @return
         */
        int height() const {
            return _height;
        }

        bool hasMipmaps() const {
            return mipMapped;
        }

    private:
        int _width = 0;
        int _height = 0;
        bool mipMapped = false;
        bool _isAlphaOnly = false;
        ImageOrigin _origin = ImageOrigin::TopLeft;
        bool _externallyOwned = false;

        TextureProxy(int width, int height, bool mipMapped, bool isAlphaOnly,
                     ImageOrigin origin = ImageOrigin::TopLeft, bool externallyOwned = false);
    };

} // vgfx