#pragma once
#ifndef WOLF_APPLICATION_H
#define WOLF_APPLICATION_H

#include "Window.h"
#include "Layer.h"
#include "Time.h"
#include "GraphicsContext.h"


namespace Wolf
{
    class Application
    {


    public:

        Application()
        {
            _clock = Clock();
            _layer_stack = LayerStack();
        }
        bool initialize(Window::Configuration config);
        void run();
        void on_event(Event* event);
        void on_update(const Time& time);
        void on_render();
        void add_layer(Layer* layer) { _layer_stack.add(layer); }
        void set_imgui_layer(Layer* layer) { _imgui_layer = layer; _layer_stack.add_overlay(layer); }
        bool remove_layer(Layer* layer) { return _layer_stack.remove(layer); }
        void add_overlay(Layer* layer) { _layer_stack.add_overlay(layer); }
        Window* get_main_window() { return &_mainWindow; }
        void quit();

        inline static Application* get() {
            if (_instance == nullptr)
                _instance = new Application();

            return _instance;
        }

        inline const Time& get_update_time() { return _update_time; }
        inline const Time& get_render_time() { return _render_time; }
    
    private:
        static Application* _instance;
        Window _mainWindow;
        LayerStack _layer_stack;
        Clock _clock;
        Time _render_time;
        Time _update_time;
        Layer* _imgui_layer;
        std::shared_ptr<GraphicsContext> _graphics_context;
    };
}
#endif
