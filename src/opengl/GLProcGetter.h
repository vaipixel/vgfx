//
// Created by 冯旭超 on 2024/1/7.
//

#pragma once

#include <memory>

namespace vgfx {
    class GLProcGetter {
    public:
        static std::unique_ptr<GLProcGetter> Make();

        virtual ~GLProcGetter() = default;

        virtual void *getProcAddress(const char name[]) const = 0;
    };
}