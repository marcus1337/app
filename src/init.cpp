#include "util/init.h"

namespace appf
{
    namespace ini
    {
        std::optional<Error> initSDL()
        {
            const std::vector<std::function<std::optional<Error>()>> initFunctions = {
                ini::initSDLFlags,
                ini::initSDLImage,
                ini::initSDLAudio,
                ini::initSDLTTF};
            for (const auto &initFunction : initFunctions)
                if (auto error = initFunction(); error.has_value())
                    return error;
            sdlInitialized = true;
            return std::nullopt;
        }

        std::optional<Error> initSDLFlags()
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
            {
                return Error(SDL_GetError());
            }
            return std::nullopt;
        }

        std::optional<Error> initSDLImage()
        {
            if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
            {
                return Error("Failed to init IMG_INIT_PNG: " + std::string(IMG_GetError()));
            }
            return std::nullopt;
        }

        std::optional<Error> initSDLAudio()
        {
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
            {
                return Error("Failed to initialize SDL_mixer: " + std::string(Mix_GetError()));
            }
            return std::nullopt;
        }

        std::optional<Error> initSDLTTF()
        {
            if (TTF_Init() == -1)
            {
                return Error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
            }
            return std::nullopt;
        }

        void quitSDL()
        {
            IMG_Quit();
            TTF_Quit();
            Mix_CloseAudio();
            Mix_Quit();
            SDL_Quit();
            sdlInitialized = false;
        }

    }
}