#include "render/asset_data.h"

using namespace appf;

bool AssetData::loadFile(const std::filesystem::path &entry)
{
    bool loaded = false;
    for (auto fileLoader : std::vector<FileData *>({&imageData, &textData}))
    {
        if (fileLoader->canLoadFile(entry))
        {
            fileLoader->loadFile(entry);
            loaded = true;
        }
    }
    return loaded;
}
