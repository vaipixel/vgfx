//
// Created by Anatta Feng on 2024/1/25.
//

#pragma once

#include <memory>
#include <string>

namespace vgfx {

    /**
     * Data holds an immutable data buffer. Not only is the Data immutable, but the actual pointer
     * returned by data() or bytes() is guaranteed to always be the same for the life of this instance.
     */
    class Data {
    public:
        static std::shared_ptr<Data> MakeFromFile(const std::string &filePath);

        static std::shared_ptr<Data> MakeWithCopy(const void *data, size_t length);

        static std::shared_ptr<Data> MakeWithoutCopy(const void *data, size_t length);

        typedef void (*ReleaseProc)(const void *data, void *context);

        static void DeleteProc(const void *data, void *context);

    private:
        const void *_data = nullptr;
        size_t _size = 0;
        ReleaseProc releaseProc = nullptr;
        void *releaseContext = nullptr;

        Data(const void *data, size_t length, ReleaseProc releaseProc, void *context);
    };

} // vgfx