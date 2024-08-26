
#pragma once
#include "util/pch.h"
#include "util/error.h"
#include "util/file.h"

namespace appf
{

    enum class FontSize
    {
        Small = 24,
        Medium = 32,
        Large = 48
    };

    struct FontSpec
    {
        std::string filename;
        FontSize size;
        bool operator<(const FontSpec &other) const
        {
            if (filename < other.filename)
                return true;
            if (filename > other.filename)
                return false;
            return size < other.size;
        }
    };

    struct TextSpec
    {
        std::string text;
        SDL_Color color;
        FontSpec fontSpec;

        bool operator<(const TextSpec &other) const
        {
            return std::tie(text, color.r, color.g, color.b, color.a, fontSpec) <
                   std::tie(other.text, other.color.r, other.color.g, other.color.b, other.color.a, other.fontSpec);
        }
    };

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