
#pragma once
#include "render/asset_registry.h"

/*
AssetHandle;
Manages the lifecycle of various asset types (e.g., images, sounds, fonts) by loading them from disk and
providing centralized access for other components.
*/

namespace appf
{
    class AssetHandle
    {
    public:
        static void init();
        static void shutDown();
        static AssetHandle &instance();
        AssetRegistry registry;

    private:
        AssetHandle() = default;
        ~AssetHandle() = default;
        AssetHandle(const AssetHandle &) = delete;
        AssetHandle &operator=(const AssetHandle &) = delete;
        static inline AssetHandle *handle = nullptr;
    };
}