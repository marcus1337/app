#include "render/image_data.h"
#include "util/util.h"

using namespace appf;

ImageData::ImageData() : FileData({".png"})
{
}

void ImageData::loadFile(const std::filesystem::path &entry)
{
    imageSurfaces[entry.string()] = gfx::makeImageSurface(entry);
}

