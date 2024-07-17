#pragma once
#include "util/pch.h"
#include "util/dialog.h"

namespace appf
{
    class Error
    {
    public:
        Error(const std::string &msg);
        const std::string &getMessage() const;
        void spawnDialog() const;

    private:
        std::string message;
    };

}