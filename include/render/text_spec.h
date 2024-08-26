
#pragma once
#include "util/pch.h"

namespace appf
{

    enum class FontSize
    {
        Small = 24,
        Medium = 32,
        Large = 48
    };

    struct FontSpec
    {
        std::string filename;
        FontSize size;
        bool operator<(const FontSpec &other) const
        {
            if (filename < other.filename)
                return true;
            if (filename > other.filename)
                return false;
            return size < other.size;
        }
    };

    struct TextSpec
    {
        std::string text;
        SDL_Color color;
        FontSpec fontSpec;

        bool operator<(const TextSpec &other) const
        {
            return std::tie(text, color.r, color.g, color.b, color.a, fontSpec) <
                   std::tie(other.text, other.color.r, other.color.g, other.color.b, other.color.a, other.fontSpec);
        }
    };
}