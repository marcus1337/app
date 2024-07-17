#pragma once
#include "util/pch.h"

namespace appf
{
    namespace dialog
    {
        void showError(const std::string &msg)
        {
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_ERROR,
                "Error",
                msg.c_str(),
                nullptr);
        }
    }
}