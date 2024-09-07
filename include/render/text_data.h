
#pragma once
#include "util/pch.h"
#include "render/surface.h"
#include "util/file.h"

namespace appf
{
    struct TextData : public FileData
    {
        TextData();
        std::map<FontSpec, std::shared_ptr<TTF_Font>> fonts;
        std::map<TextSpec, std::shared_ptr<SDL_Surface>> textSurfaces;
        std::shared_ptr<TTF_Font> getFont(const FontSpec &fontSpec) const;
        std::shared_ptr<SDL_Surface> getTextSurface(const TextSpec &textSpec) const;
        void loadFile(const std::filesystem::path &entry);
    };
}