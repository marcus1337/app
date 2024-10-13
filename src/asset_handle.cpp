#include "render/asset_handle.h"

using namespace appf;

void AssetHandle::init()
{
    shutDown();
    handle = new AssetHandle();
}

void AssetHandle::shutDown()
{
    delete handle;
    handle = nullptr;
}

AssetHandle &AssetHandle::instance()
{
    if (!handle)
    {
        init();
    }
    return *handle;
}
