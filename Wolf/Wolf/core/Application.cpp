#include <iostream>
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Wolf
{

    Application* Application::_instance = nullptr;
        
    bool Application::initialize(Window::Configuration config)
    {

        Application::_instance = this;
        /* Initialize the library */
        if (!glfwInit())
        {
            std::cout << "Unable to initialize glfw lib" << std::endl;
            glfwTerminate();
            return false;
        }

        /* Creates main window */
        if (!_mainWindow.Initialize(config))
        {
            glfwTerminate();
            return false;
        }
        _mainWindow.MakeContextCurrent();
        return true;
    }

    void Application::on_event(const Event& event)
    {
        // Updates from the overlays to the lowest
        auto layers = _layer_stack.get_layers();
        for (auto it = layers.rbegin(); it != layers.rend(); ++it)
        {
            if (event.Handled)
                return;

            (*it)->on_event(event);
        }

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
        //_mainWindow.MakeContextCurrent();
        _GraphicsContext = std::make_shared<GraphicsContext>(_mainWindow);
        _GraphicsContext->Init();


        _clock = Clock();
        _clock.Start();
        Clock deltaClock;
        deltaClock.Start();
        while (!_mainWindow.ShouldClose())
        {
            Time elapsed = deltaClock.Elapsed();
            deltaClock.Start();
            on_update(elapsed);
            _update_time = deltaClock.Elapsed();

            deltaClock.Start();

            //glClearColor(0, 0, 0, 1);
            //glClear(GL_COLOR_BUFFER_BIT);
            on_render();
            _GraphicsContext->SwapBuffers();
            
            _render_time = deltaClock.Elapsed();
            /* Poll for and process events */
            glfwPollEvents();
        }
    }
}