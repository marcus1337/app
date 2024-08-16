#pragma once
#include "util/pch.h"
#include "util/init.h"
#include "asset_manager.h"

// appf is shorthand for "app framework"
namespace appf
{

    class App
    {
    public:
        App()
        {
            if (initSDL())
            {
                AssetManager::init();
                initialized = true;
            }
        }

        ~App()
        {
            AssetManager::shutDown();
            if (ini::sdlInitialized)
            {
                ini::quitSDL();
            }
        }

        bool isIntialized() const
        {
            return initialized;
        }

    private:
        bool initialized = false;

        bool initSDL() const
        {
            if (!ini::sdlInitialized)
            {
                if (auto error = ini::initSDL(); error.has_value())
                {
                    std::cerr << error.value().getMessage() << "\n";
                    return false;
                }
            }
            return ini::sdlInitialized;
        }
    };

}