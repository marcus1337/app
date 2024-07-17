#include "app.h"
#include <emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    int main() {
        //std::cout << "Hello World WASM example!\n";
        return 0;
    }
}
