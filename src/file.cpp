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
    auto counter = upperDirs.size();
    auto tmpPath = path;
    while (counter-- > 0)
    {
        if (!tmpPath.has_parent_path() || tmpPath.parent_path().filename() != upperDirs[counter])
        {
            return false;
        }
        tmpPath = tmpPath.parent_path();
    }
    return true;
}

bool File::isMatch(const std::filesystem::path &path) const
{
    return hasMatchingUpperDirs(path) && path.filename() == name;
}
