
#pragma once
#include "util/pch.h"
#include "util/error.h"

namespace appf
{

    struct File
    {
        File(const std::string &filename) : name(filename)
        {
        }
        File(const std::vector<std::string> &upperDirs, const std::string &filename) : name(filename), upperDirs(upperDirs)
        {
        }

        bool hasMatchingUpperDirs(const std::filesystem::path &path) const
        {
            int counter = upperDirs.size();
            auto tmpPath = path;
            while (counter-- > 0)
            {
                if (!tmpPath.has_parent_path() || tmpPath.parent_path().filename() != upperDirs[counter])
                {
                    return false;
                }
                tmpPath = tmpPath.parent_path();
            }
            return true;
        }

        bool isMatch(const std::filesystem::path &path) const
        {
            return hasMatchingUpperDirs(path) && path.filename() == name;
        }

        std::string name;
        std::vector<std::string> upperDirs; // Sorted furthest away to most immediate.
    };

    class AssetManager
    {
    public:
        static void init();
        static void shutDown();
        static AssetManager &instance();
        std::optional<Error> loadAssets(const std::filesystem::path &dirPath);

        std::shared_ptr<SDL_Surface> getImageSurface(const File &file) const;

    private:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager &) = delete;
        AssetManager &operator=(const AssetManager &) = delete;

        std::filesystem::path getPath(const File &file) const;
        std::optional<Error> loadFile(const std::filesystem::path &entry);
        void addPath(const std::filesystem::path &entry);
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> makeImageSurface(const std::filesystem::path &pngPath) const;

        static inline AssetManager *assetManager = nullptr;
        std::map<std::string, std::vector<std::filesystem::path>> filepaths;
        std::map<std::filesystem::path, std::shared_ptr<SDL_Surface>> imageSurfaces;
    };

}