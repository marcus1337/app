#include "asset_manager.h"

using namespace appf;

void AssetManager::init()
{
    if (assetManager)
    {
        shutDown();
    }
    assetManager = new AssetManager();
}

void AssetManager::shutDown()
{
    delete assetManager;
    assetManager = nullptr;
}

AssetManager::AssetManager()
{
}
AssetManager::~AssetManager()
{
}

AssetManager &AssetManager::instance()
{
    return *assetManager;
}

namespace fs = std::filesystem;

std::optional<Error> AssetManager::load(const fs::path &dirPath)
{
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        return Error("Invalid path " + dirPath.string());
    }

    for (const auto &entry : fs::recursive_directory_iterator(dirPath))
    {
        if (fs::is_regular_file(entry))
        {
            loadFile(entry);
        }
    }

    return std::nullopt;
}

void AssetManager::addPath(const fs::path &entry)
{
    const std::string& name = entry.filename();
    if (!filepaths.contains(name))
    {
        filepaths[name] = std::vector<fs::path>();
    }
    filepaths[name].push_back(entry);
}

std::optional<Error> AssetManager::loadFile(const fs::path &entry)
{
    addPath(entry);
    std::string ext = entry.extension();
    if (ext == ".png")
    {
    }
    if (ext == ".wav")
    {
    }
    if (ext == ".ttf")
    {
    }
    return std::nullopt;
}
