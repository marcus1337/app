#pragma once
#include "util/pch.h"
#include "util/error.h"

namespace appf
{
    namespace ini
    {
        std::optional<Error> initSDL();
        std::optional<Error> initSDLFlags();
        std::optional<Error> initSDLImage();
        std::optional<Error> initSDLAudio();
        std::optional<Error> initSDLTTF();
        inline bool sdlInitialized = false;

        void quitSDL();
    }
}