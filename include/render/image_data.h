
#pragma once
#include "util/pch.h"
#include "util/file.h"

namespace appf
{
    struct ImageData : public FileData
    {
        ImageData();
        virtual void loadFile(const std::filesystem::path &entry);
        std::map<std::filesystem::path, std::shared_ptr<SDL_Surface>> imageSurfaces;
    };
}