#pragma once
#include "util/pch.h"
#include "util/error.h"

namespace appf
{
    namespace ini
    {
        std::optional<Error> initSDL()
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            {
                return Error(SDL_GetError());
            }
            else if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
            {
                return Error("Failed to init IMG_INIT_PNG: " + std::string(IMG_GetError()));
            }
            return std::nullopt;
        }

        std::optional<Error> initAll()
        {
            if (auto error = initSDL(); error.has_value())
                return error;
            return std::nullopt;
        }
    }
}