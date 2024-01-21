//
// Created by Anatta Feng on 2024/1/12.
//

#pragma once

#include "vgfx/gpu/Context.h"
#include "gpu/ResourceKey.h"

namespace vgfx {

    /**
     * The base class for all proxy-derived objects. It delays the acquisition of resources until they
     * are actually required.
     */
    class ResourceProxy {
    public:
        virtual ~ResourceProxy() = default;

        /**
         * Retrieves the context associated with this ResourceProxy.
         * @return
         */
        Context *getContext() const {
            return context;
        }

        /**
         * Return the ResourceKey associated with this ResourceProxy.
         * @return
         */
        const ResourceKey& getResourceKey() const {
            return resourceKey;
        }
    protected:
        Context *context = nullptr;
        ResourceKey resourceKey = {};

        ResourceProxy() = default;

        friend Context;
    };
}
