//
// Created by Anatta Feng on 2024/1/29.
//

#pragma once

#include <memory>
#include <string>

namespace vgfx {

    /**
     * Stream represents a source of bytes. Subclasses can be backed by memory, or a file, or something
     * else. Stream is not thread safe.
     */
    class Stream {

    public:
        virtual ~Stream() = default;

        /**
         * Attempts to open the specified file as a stream, returns nullptr on failure.
         * @param filePath
         * @return
         */
        static std::unique_ptr <Stream> MakeFromFile(const std::string &filePath);

        /**
         * Returns the total length of the stream. If this cannot be done, returns 0.
         * @return
         */
        virtual size_t size() const = 0;

        /**
         * Seeks to an absolute position in the stream. If this cannot be done, returns false. If an
         * attempt is made to seek past the end of the stream, the position will set to the end of the
         * stream.
         * @param position
         * @return
         */
        virtual bool seek(size_t position) = 0;

        /**
         * Seeks to an relative offset in the stream. If this cannot be done, returns false. If an attempt
         * is make to move to a position outside the stream, the position will be set to the closest point
         * within the stream (beginning or end).
         * @param offset
         * @return
         */
        virtual bool move(int offset) = 0;

        /**
         * Reads size number of bytes. Copy size bytes into buffer, return how many were copied.
         * @param buffer
         * @param size
         * @return
         */
        virtual size_t read(void *buffer, size_t size) = 0;

        /**
         * Rewinds to the beginning of the stream. Returns true if the stream is known to be ai the
         * beginning after this call returns.
         * @return
         */
        virtual bool rewind() = 0;
    };

} // vgfx