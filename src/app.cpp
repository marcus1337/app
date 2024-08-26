#include "app.h"
#include "util/init.h"
#include "render/asset_manager.h"

using namespace appf;

App::App()
{
    if (initSDL())
    {
        AssetManager::init();
        initialized = true;
    }
}

App::~App()
{
    AssetManager::shutDown();
    if (ini::sdlInitialized)
    {
        ini::quitSDL();
    }
}

bool App::isIntialized() const
{
    return initialized;
}

bool App::initSDL() const
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