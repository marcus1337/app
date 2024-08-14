
#pragma once
#include "util/pch.h"

namespace appf
{

    class AssetManager
    {
    public:
        static void init();
        static void shutDown();
        static AssetManager &instance();

    private:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager &) = delete;
        AssetManager &operator=(const AssetManager &) = delete;
        static inline AssetManager *assetManager = nullptr;
    };

}