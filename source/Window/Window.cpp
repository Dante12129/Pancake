#include "include/Pancake/Window/Window.hpp"

#include <iostream>

#include <SDL2/SDL_opengl.h>
#include "include/Pancake/Graphics/color.hpp"
#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    Window::Window(const std::string& title, int width, int height, WindowSettings wsettings, const ContextSettings& csettings) : Window()
    {
        create(title, width, height, wsettings, csettings);
    }
    Window::Window(SDL_Window* win) : Window()
    {
        create(win);
    }
    Window::~Window()
    {
        //Destroy the window
        close();
    }

    bool Window::create(const std::string& title, int width, int height, WindowSettings wsettings, const ContextSettings& csettings)
    {
        //Destroy the current window owned by this object if one exists
        close();

        //Create window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, static_cast<int>(wsettings));
        if(window == nullptr)
        {
            std::cerr << "Window creation error: " << SDL_GetError();
            return false;
        }

        //Create GL Context
        context.create(*this, csettings);
        if(!context)
        {
            std::cerr << "Context creation error in window (creating from scratch).";
            return false;
        }

        return true;
    }
    bool Window::create(SDL_Window* win)
    {
        //Destroy the current window owned by this object if one exists
        close();

        //Take ownership of the window
        window = win;

        //Create GL Context
        context.create(*this);
        if(!context)
        {
            std::cerr << "Context creation error in window (creating from SDL_Window).";
            return false;
        }

        return true;
    }
    void Window::close()
    {
        if(window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }

    bool Window::pollEvent(SDL_Event& event)
    {
        bool result = SDL_PollEvent(&event);
        if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                glCheck(glViewport(0, 0, event.window.data1, event.window.data2));
            }
        }
        if(event.type == SDL_KEYDOWN)
        {
            if(!key_repeat && event.key.repeat)
                return false;
        }
        return result;
    }

    void Window::clear(const Color& color)
    {
        glCheck(glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f));
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
    }
    void Window::display()
    {
        SDL_GL_SwapWindow(window);
    }

    bool Window::setVerticalSyncEnabled(bool enable)
    {
        if(enable)
            return !SDL_GL_SetSwapInterval(1);
        else
            return !SDL_GL_SetSwapInterval(0);

    }
    void Window::setKeyRepeatEnabled(bool enable)
    {
        key_repeat = enable;
    }
    void Window::setActive(bool enable)
    {
        context.setActive(*this, enable);
    }

    glm::uvec2 Window::getPosition() const
    {
        int x, y;
        SDL_GetWindowPosition(window, &x, &y);

        return {x, y};
    }
    Uint32 Window::getId() const
    {
        return SDL_GetWindowID(window);
    }


    WindowSettings operator |(WindowSettings left, WindowSettings right)
    {
        return static_cast<WindowSettings>(static_cast<int>(left) | static_cast<int>(right));
    }

    WindowSettings operator &(WindowSettings left, WindowSettings right)
    {
        return static_cast<WindowSettings>(static_cast<int>(left) & static_cast<int>(right));
    }

    bool any(WindowSettings settings)
    {
        return settings != WindowSettings::None;
    }
}
