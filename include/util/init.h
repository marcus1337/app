#pragma once
#include "util/pch.h"
#include "util/error.h"

namespace appf
{
    namespace ini
    {
        std::optional<Error> initSDL();
        std::optional<Error> initAll();
        void shutDownAll();
    }
}