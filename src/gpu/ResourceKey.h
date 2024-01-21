//
// Created by Anatta Feng on 2024/1/22.
//

#pragma once

#include <cstdint>

namespace vgfx {
    class UniqueDomain;

    /**
     * ResourceKey allows a cod path to create cached resources for which it is the exclusive user.
     * The code path generates a unique domain which it sets on its keys. This guarantees that there are
     * no cross-domain collisions. Please refer to the comments in Resource::getResourceKey() for more
     * details.
     */
    class ResourceKey {
    public:
        static ResourceKey NewWeak();

        static ResourceKey NewStrong();

        ResourceKey() = default;

        ResourceKey(const ResourceKey &key);

        ResourceKey(ResourceKey &&key) noexcept;

        virtual ~ResourceKey();

        uint64_t domain() const;

        bool empty() const {
            return uniqueDomain == nullptr;
        }

        bool isStrong() const {
            return strong;
        }

    private:
        UniqueDomain *uniqueDomain = nullptr;
        bool strong = false;

        ResourceKey(UniqueDomain *block, bool strong);
    };
}