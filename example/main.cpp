#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/fetch.h>
#include <emscripten/bind.h>
#endif

#include "app.h"

void resizeWindow(int width, int height)
{
    std::cout << "Resizing: " << width << "," << height << "\n";
}

uint64_t counter = 0;

void step()
{
    std::cout << "step: " << counter++ << "\n";
}

#ifdef EMSCRIPTEN
EMSCRIPTEN_BINDINGS(resize_module)
{
    emscripten::function("resizeWindow", &resizeWindow);
}
#endif

int main(int argc, char *argv[])
{
#ifdef EMSCRIPTEN
    emscripten_set_main_loop(step, 0, 1);
#endif
    return 0;
}