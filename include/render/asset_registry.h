
#pragma once
#include "util/pch.h"
#include "render/asset_data.h"

namespace appf
{
    class AssetRegistry
    {
    public:
        std::shared_ptr<SDL_Surface> getImageSurface(const File &file) const;
        std::optional<Error> storeTextSurface(const TextSpec &textSpec);
        std::shared_ptr<SDL_Surface> getTextSurface(const TextSpec &textSpec) const;
        void loadFiles(const std::filesystem::path &rootDir);

    private:
        bool loadFile(const std::filesystem::path &entry);
        void addPath(const std::filesystem::path &entry);

        std::multimap<std::string, std::filesystem::path> filepaths;
        AssetData assetData;
    };
}