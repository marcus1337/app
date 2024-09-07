
#pragma once
#include "render/asset_data.h"

/*
AssetManager;
Manages the lifecycle of various asset types (e.g., images, sounds, fonts) by loading them from disk and
providing centralized access for other components.
*/

namespace appf
{
    class AssetManager
    {
    public:
        static void init();
        static void shutDown();
        static AssetManager &instance();
        std::optional<Error> loadAssets(const std::filesystem::path &dirPath);

        std::shared_ptr<SDL_Surface> getImageSurface(const File &file) const;
        std::optional<Error> storeTextSurface(const TextSpec &textSpec);
        std::shared_ptr<SDL_Surface> getTextSurface(const TextSpec &textSpec) const;

    private:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager &) = delete;
        AssetManager &operator=(const AssetManager &) = delete;

        bool loadFile(const std::filesystem::path &entry);
        void addPath(const std::filesystem::path &entry);

        static inline AssetManager *assetManager = nullptr;
        std::multimap<std::string, std::filesystem::path> filepaths;
        AssetData assetData;
    };
}