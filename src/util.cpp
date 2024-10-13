#include "util/util.h"

using namespace appf;

std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> gfx::makeImageSurface(const std::filesystem::path &pngPath)
{
    return std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(IMG_Load(pngPath.c_str()), &SDL_FreeSurface);
}
std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> gfx::makeFont(const std::filesystem::path &ttfPath, int ptsize)
{
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font(nullptr, &TTF_CloseFont);
    font.reset(TTF_OpenFont(ttfPath.c_str(), ptsize));
    assert(font != nullptr);
    return font;
}
