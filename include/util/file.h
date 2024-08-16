#pragma once
#include "util/pch.h"

namespace appf
{
    struct File
    {
        File(const std::string &filename) : name(filename)
        {
        }
        File(const std::vector<std::string> &upperDirs, const std::string &filename) : name(filename), upperDirs(upperDirs)
        {
        }

        bool hasMatchingUpperDirs(const std::filesystem::path &path) const
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

        bool isMatch(const std::filesystem::path &path) const
        {
            return hasMatchingUpperDirs(path) && path.filename() == name;
        }

        std::string name;
        std::vector<std::string> upperDirs; // Sorted furthest away to most immediate.
    };
}