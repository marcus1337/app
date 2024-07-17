#pragma once
#include "util/pch.h"
#include "util/dialog.h"

namespace appf
{
    class Error
    {
    public:
        Error(const std::string &msg) : message(msg) {}

        const std::string &getMessage() const &
        {
            return message;
        }

        void spawnDialog() const
        {
            dialog::showError(getMessage());
        }

    private:
        std::string message;
    };

}