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

std::optional<Error> AssetManager::loadAssets(const fs::path &dirPath)
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
    const std::string &name = entry.filename();
    if (!filepaths.contains(name))
    {
        filepaths[name] = std::vector<fs::path>();
    }
    filepaths[name].push_back(entry);
}

std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> AssetManager::makeImageSurface(const std::filesystem::path &pngPath) const
{
    return std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(IMG_Load(pngPath.c_str()), &SDL_FreeSurface);
}

std::shared_ptr<SDL_Surface> AssetManager::getImageSurface(const File &file) const
{
    return imageSurfaces.at(getPath(file));
}

std::filesystem::path AssetManager::getPath(const File &file) const
{
    if (filepaths.contains(file.name))
    {
        for (const auto &path : filepaths.at(file.name))
        {
            if (file.isMatch(path))
            {
                return path;
            }
        }
    }
    return "";
}

std::optional<Error> AssetManager::loadFile(const fs::path &entry)
{
    addPath(entry);
    std::string ext = entry.extension();
    if (ext == ".png")
    {
        imageSurfaces[entry.string()] = makeImageSurface(entry);
    }
    if (ext == ".wav")
    {
    }
    if (ext == ".ttf")
    {
    }
    return std::nullopt;
}
