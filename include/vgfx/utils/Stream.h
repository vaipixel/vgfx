//
// Created by Anatta Feng on 2024/1/29.
//

#pragma once

namespace vgfx {

    /**
     * Stream represents a source of bytes. Subclasses can be backed by memory, or a file, or something
     * else. Stream is not thread safe.
     */
    class Stream {

    public:
        virtual ~Stream() = default;
    };

} // vgfx