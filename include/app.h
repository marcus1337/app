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
            if (auto error = ini::initSDL(); error.has_value())
            {
                std::cerr << error.value().getMessage() << "\n";
                return;
            }
            AssetManager::init();
            initialized = true;
        }

        ~App()
        {
            AssetManager::shutDown();
        }

        bool isIntialized() const
        {
            return initialized;
        }

    private:
        bool initialized = false;
    };

}