//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

namespace vgfx {

    /**
     * The base class for all proxy-derived objects. It delays the acquisition of resources until they
     * are actually required.
     */
    class ResourceProxy {
    public:
        virtual ~ResourceProxy() = default;
    };
}
