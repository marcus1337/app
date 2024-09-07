#pragma once
#include "util/pch.h"

namespace appf
{
    class FileData
    {
    public:
        FileData(std::set<std::string> extensions);
        virtual ~FileData() = default;
        virtual void loadFile(const std::filesystem::path &entry) = 0;
        bool canLoadFile(const std::filesystem::path &entry) const;

    private:
        std::set<std::string> extensions;
    };

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