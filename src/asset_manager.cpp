#include "asset_manager.h"

using namespace appf;

void AssetManager::init()
{
    if (assetManager)
    {
        shutDown();
    }
    assetManager = new AssetManager();
}

void AssetManager::shutDown()
{
    delete assetManager;
    assetManager = nullptr;
}

AssetManager::AssetManager()
{
}
AssetManager::~AssetManager()
{
}

AssetManager &AssetManager::instance()
{
    return *assetManager;
}
