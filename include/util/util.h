#pragma once
#include "util/pch.h"

namespace appf
{
    namespace gfx
    {
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> makeImageSurface(const std::filesystem::path &pngPath);
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> makeFont(const std::filesystem::path &ttfPath, int ptsize);
    }

}