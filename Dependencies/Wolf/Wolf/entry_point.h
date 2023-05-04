#ifndef WOLF_ENTRY_POINT
#define WOLF_ENTRY_POINT
#include <iostream>
#include "core/Application.h"
#include "imgui_layer/imgui_layer.h"

namespace Wolf
{
    static void init()
    {
        std::cout << "Welcome to wolf engine v" << WOLF_ENGINE_VERSION << std::endl;
    }
}

#endif
