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
        App();
        ~App();
        bool isIntialized() const;

    private:
        bool initialized = false;
        bool initSDL() const;
    };

}