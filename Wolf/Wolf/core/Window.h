#pragma once
#ifndef WOLF_WINDOW_H
#define WOLF_WINDOW_H
#include "Event.h"
#include <vector>
#include <iostream>

namespace Wolf
{

    struct WindowUserData
    {
        void* windowPtr;
    };

    class Window
    {

    public:
        struct Configuration
        {
            uint32_t width = 600;
            uint32_t height = 600;
            const char* title = "App";
            bool fullscreen = false;
        };

    public:
        Window() = default;
        bool Initialize(Window::Configuration config);
        void* GetNativePtr() const { return _windowPtr; }
        bool ShouldClose();
        void MakeContextCurrent();

    private:
        WindowUserData _userData;
        void* _windowPtr;
    };
}
#endif