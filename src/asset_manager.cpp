#include "render/asset_manager.h"
#include "render/surface.h"

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
    filepaths.insert({entry.filename(), entry});
}

std::shared_ptr<SDL_Surface> AssetManager::getImageSurface(const File &file) const
{
    auto path = file.getPath(filepaths);
    if (!imageSurfaces.contains(path))
    {
        return nullptr;
    }
    return imageSurfaces.at(path);
}

std::optional<Error> AssetManager::loadFile(const fs::path &entry)
{
    addPath(entry);
    std::string ext = entry.extension();
    if (ext == ".png")
    {
        imageSurfaces[entry.string()] = surf::makeImageSurface(entry);
    }
    if (ext == ".wav")
    {
    }
    if (ext == ".ttf")
    {
        textData.loadFile(entry);
    }
    return std::nullopt;
}

std::optional<Error> AssetManager::storeTextSurface(const TextSpec &textSpec)
{
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(nullptr, &SDL_FreeSurface);
    auto font = textData.getFont(textSpec.fontSpec);
    assert(font != nullptr);
    if (font == nullptr)
    {
        return Error("Font not found");
    }
    surface.reset(TTF_RenderText_Blended(font.get(), textSpec.text.data(), textSpec.color));
    assert(surface != nullptr);
    if (surface == nullptr)
    {
        return Error("Surface creation failed.");
    }
    textData.textSurfaces[textSpec] = std::move(surface);
    return std::nullopt;
}

std::shared_ptr<SDL_Surface> AssetManager::getTextSurface(const TextSpec &textSpec) const
{
    return textData.getTextSurface(textSpec);
}
