
#pragma once
#include "util/pch.h"

namespace appf
{

    class TextureManager
    {
    public:
        std::shared_ptr<SDL_Texture> getTexture(const std::string &name) const;
        void makeCustomSurface(const std::string &name, int w, int h);
        std::shared_ptr<SDL_Surface> getCustomSurface(const std::string &name) const;
        TextureManager();
        ~TextureManager();

    private:
        std::map<std::string, std::shared_ptr<SDL_Surface>> customSurfaces;
    };
}