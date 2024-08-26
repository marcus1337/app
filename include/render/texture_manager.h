
#pragma once
#include "render/asset_manager.h"

namespace appf
{

    class TextureManager
    {
    public:
        static TextureManager &instance();

    private:
        TextureManager();
        ~TextureManager();
        TextureManager(const TextureManager &) = delete;
        TextureManager &operator=(const TextureManager &) = delete;
    };
}