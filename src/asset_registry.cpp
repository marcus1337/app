#include "render/asset_registry.h"
#include "util/util.h"

using namespace appf;

/*
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        return Error("Invalid path " + dirPath.string());
    }
*/


namespace fs = std::filesystem;

void AssetRegistry::loadFiles(const fs::path &dirPath)
{
    for (const auto &entry : fs::recursive_directory_iterator(dirPath))
    {
        if (fs::is_regular_file(entry))
        {
            loadFile(entry);
        }
    }
}

void AssetRegistry::addPath(const fs::path &entry)
{
    filepaths.insert({entry.filename(), entry});
}

std::shared_ptr<SDL_Surface> AssetRegistry::getImageSurface(const File &file) const
{
    auto path = file.getPath(filepaths);
    if (!assetData.imageData.imageSurfaces.contains(path))
    {
        return nullptr;
    }
    return assetData.imageData.imageSurfaces.at(path);
}

bool AssetRegistry::loadFile(const fs::path &entry)
{
    if (assetData.loadFile(entry))
    {
        addPath(entry);
        return true;
    }
    return false;
}

std::optional<Error> AssetRegistry::storeTextSurface(const TextSpec &textSpec)
{
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(nullptr, &SDL_FreeSurface);
    auto font = assetData.textData.getFont(textSpec.fontSpec);
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
    assetData.textData.textSurfaces[textSpec] = std::move(surface);
    return std::nullopt;
}

std::shared_ptr<SDL_Surface> AssetRegistry::getTextSurface(const TextSpec &textSpec) const
{
    return assetData.textData.getTextSurface(textSpec);
}
