#include "render/image_data.h"
#include "render/surface.h"

using namespace appf;

ImageData::ImageData() : FileData({".png"})
{
}

void ImageData::loadFile(const std::filesystem::path &entry)
{
    imageSurfaces[entry.string()] = surf::makeImageSurface(entry);
}

