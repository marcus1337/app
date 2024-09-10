
#pragma once
#include "util/pch.h"
#include "util/error.h"
#include "util/file.h"
#include "render/text_spec.h"
#include "render/text_data.h"
#include "render/image_data.h"

namespace appf
{
    struct AssetData
    {
        TextData textData;
        ImageData imageData;
        bool loadFile(const std::filesystem::path &entry);
    };
}