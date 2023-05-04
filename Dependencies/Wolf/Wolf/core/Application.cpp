#include <iostream>
#include "Application.h"
#include <GLFW/glfw3.h>
#include "../rendering/RenderCommand.h"


namespace Wolf
{

    Application* Application::_instance;
    
    

    bool Application::initialize(Window::Configuration config)
    {
        _instance = this;
        /* Initialize the library */
        if (!glfwInit())
        {
            std::cout << "Unable to initialize glfw lib" << std::endl;
            glfwTerminate();
            return false;
        }

        /* Creates main window */
        if (!_mainWindow.initialize(config))
        {
            glfwTerminate();
            return false;
        }
        _mainWindow.make_context_current();

        _graphics_context = GraphicsContext::create(_mainWindow);
        _graphics_context->init();

        return true;
    }

    void Application::on_event(Event* event)
    {
        // Updates from the overlays to the lowest
        auto layers = _layer_stack.get_layers();
        for (auto it = layers.rbegin(); it != layers.rend(); ++it)
        {
            if (event->handled)
                return;

            (*it)->on_event(event);
        }
        EventDispatcher disptacher = EventDispatcher(event);
        disptacher.dispatch<WindowResizeEvent>(
            EventType::WindowResize,

            [this](WindowResizeEvent* event){
                this->_graphics_context->on_viewport_resize(event->width, event->height);
                return false;
            }
        );
    }

    void Application::on_update(const Time& delta)
    {
        // Updates from the lowest layer to the overlays
        for (auto layer : _layer_stack.get_layers())
            layer->on_update(delta);

    }

    void Application::on_render()
    {
        // Renders from the lowest layer to the overlays
        for (auto layer : _layer_stack.get_layers())
            layer->on_render();

        // ImGui rendering
        for (auto layer : _layer_stack.get_layers())
            layer->on_ui_render_start();

        for (auto layer : _layer_stack.get_layers())
            layer->on_ui_render_finish();
    }

    void Application::quit()
    {
        _layer_stack.clear();
        glfwTerminate();
    }

    void Application::run()
    {
        _clock = Clock();
        _clock.start();

        Clock deltaClock, timingClock;
        deltaClock.start();
        while (!_mainWindow.should_close())
        {
            Time elapsed = deltaClock.elapsed();
            deltaClock.start();

            timingClock.start();
            on_update(elapsed);
            _update_time = timingClock.elapsed();

            timingClock.start();
            Rendering::RenderCommand::clear();
            on_render();
            _mainWindow.swap_buffers();            
            _render_time = timingClock.elapsed();
            /* Poll for and process events */
            _mainWindow.poll_events();
        }
    }
}