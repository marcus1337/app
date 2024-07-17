#include "util/error.h"

using namespace appf;

namespace dialog
{
    void showError(const std::string &msg)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            msg.c_str(),
            nullptr);
    }
}

Error::Error(const std::string &msg) : message(msg) {}

const std::string &Error::getMessage() const
{
    return message;
}

void Error::spawnDialog() const
{
    dialog::showError(getMessage());
}
