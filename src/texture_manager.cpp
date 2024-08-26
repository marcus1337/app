#include "render/texture_manager.h"

using namespace appf;

TextureManager &TextureManager::instance()
{
    static TextureManager textureManager;
    return textureManager;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

