
#include "render/text_data.h"

using namespace appf;

TextData::TextData() : FileData({".ttf"})
{
}

std::shared_ptr<TTF_Font> TextData::getFont(const FontSpec &fontSpec) const
{
    return fonts.contains(fontSpec) ? fonts.at(fontSpec) : nullptr;
}

std::shared_ptr<SDL_Surface> TextData::getTextSurface(const TextSpec &textSpec) const
{
    return textSurfaces.contains(textSpec) ? textSurfaces.at(textSpec) : nullptr;
}

void TextData::loadFile(const std::filesystem::path &entry)
{
    for (const auto &fontSize : {FontSize::Small, FontSize::Medium, FontSize::Large})
    {
        fonts[FontSpec{.filename = entry.filename(), .size = fontSize}] = appf::surf::makeFont(entry, static_cast<int>(fontSize));
    }
}
