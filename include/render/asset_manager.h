
#pragma once
#include "util/pch.h"
#include "util/error.h"
#include "util/file.h"
#include "render/text_spec.h"

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

        std::filesystem::path getPath(const File &file) const;
        std::optional<Error> loadFile(const std::filesystem::path &entry);
        void addPath(const std::filesystem::path &entry);
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> makeImageSurface(const std::filesystem::path &pngPath) const;
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> makeFont(const std::filesystem::path &ttfPath, int ptsize) const;

        std::shared_ptr<TTF_Font> getFont(const FontSpec &fontSpec) const;

        static inline AssetManager *assetManager = nullptr;
        std::map<std::string, std::vector<std::filesystem::path>> filepaths;
        std::map<std::filesystem::path, std::shared_ptr<SDL_Surface>> imageSurfaces;
        std::map<FontSpec, std::shared_ptr<TTF_Font>> fonts;
        std::map<TextSpec, std::shared_ptr<SDL_Surface>> textSurfaces;
    };
}