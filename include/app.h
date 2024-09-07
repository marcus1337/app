#pragma once
#include "util/pch.h"
#include "render/asset_handle.h"

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