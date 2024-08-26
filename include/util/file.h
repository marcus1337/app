#pragma once
#include "util/pch.h"

namespace appf
{
    struct File
    {
        File(const std::string &filename);
        File(const std::vector<std::string> &upperDirs, const std::string &filename);
        bool hasMatchingUpperDirs(const std::filesystem::path &path) const;
        std::filesystem::path getPath(const std::multimap<std::string, std::filesystem::path> &filepaths) const;
        std::string name;
        std::vector<std::string> upperDirs; // Sorted furthest away to most immediate.
    };
}