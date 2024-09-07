#include "render/asset_handle.h"
#include "render/surface.h"

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
