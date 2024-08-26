#include "util/file.h"

using namespace appf;

File::File(const std::string &filename) : name(filename)
{
}
File::File(const std::vector<std::string> &upperDirs, const std::string &filename) : name(filename), upperDirs(upperDirs)
{
}

bool File::hasMatchingUpperDirs(const std::filesystem::path &path) const
{
    auto tmpPath = path;
    for (auto it = upperDirs.rbegin(); it != upperDirs.rend(); ++it)
    {
        if (!tmpPath.has_parent_path() || tmpPath.parent_path().filename() != *it)
        {
            return false;
        }
        tmpPath = tmpPath.parent_path();
    }
    return true;
}

std::filesystem::path File::getPath(const std::multimap<std::string, std::filesystem::path> &filepaths) const
{
    auto range = filepaths.equal_range(name);
    for (auto it = range.first; it != range.second; ++it)
    {
        if (hasMatchingUpperDirs(it->second))
        {
            return it->second;
        }
    }
    return {};
}
