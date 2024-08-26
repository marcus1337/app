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

std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> AssetManager::makeFont(const std::filesystem::path &ttfPath, int ptsize) const
{
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font(nullptr, &TTF_CloseFont);
    font.reset(TTF_OpenFont(ttfPath.c_str(), ptsize));
    assert(font != nullptr);
    return font;
}

std::shared_ptr<SDL_Surface> AssetManager::getImageSurface(const File &file) const
{
    auto path = getPath(file);
    if (!imageSurfaces.contains(path))
    {
        return nullptr;
    }
    return imageSurfaces.at(path);
}

std::shared_ptr<TTF_Font> AssetManager::getFont(const FontSpec &fontSpec) const
{
    return fonts.contains(fontSpec) ? fonts.at(fontSpec) : nullptr;
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
        for (const auto &fontSize : {FontSize::Small, FontSize::Medium, FontSize::Large})
        {
            fonts[FontSpec{.filename = entry.filename(), .size = fontSize}] = makeFont(entry, static_cast<int>(fontSize));
        }
    }
    return std::nullopt;
}

std::optional<Error> AssetManager::storeTextSurface(const TextSpec &textSpec)
{
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(nullptr, &SDL_FreeSurface);
    auto font = getFont(textSpec.fontSpec);
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
    textSurfaces[textSpec] = std::move(surface);
    return std::nullopt;
}

std::shared_ptr<SDL_Surface> AssetManager::getTextSurface(const TextSpec &textSpec) const
{
    return textSurfaces.contains(textSpec) ? textSurfaces.at(textSpec) : nullptr;
}
