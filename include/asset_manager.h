
#pragma once
#include "util/pch.h"
#include "util/error.h"

namespace appf
{

    class AssetManager
    {
    public:
        static void init();
        static void shutDown();
        static AssetManager &instance();
        std::optional<Error> load(const std::filesystem::path &dirPath);

    private:
        AssetManager();
        ~AssetManager();
        AssetManager(const AssetManager &) = delete;
        AssetManager &operator=(const AssetManager &) = delete;
        
        std::optional<Error> loadFile(const std::filesystem::path &entry);
        void addPath(const std::filesystem::path &entry);

        static inline AssetManager *assetManager = nullptr;
        std::map<std::string, std::vector<std::filesystem::path>> filepaths;
    };

}