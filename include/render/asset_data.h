
#pragma once
#include "util/pch.h"
#include "util/error.h"
#include "util/file.h"
#include "render/text_spec.h"
#include "render/text_data.h"

namespace appf
{
    struct ImageData : public FileData
    {
        ImageData();
        virtual void loadFile(const std::filesystem::path &entry);
        std::map<std::filesystem::path, std::shared_ptr<SDL_Surface>> imageSurfaces;
    };
    struct AssetData
    {
        TextData textData;
        ImageData imageData;
        bool loadFile(const std::filesystem::path &entry);
    };
}