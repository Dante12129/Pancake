#include "include/Pancake/Window/Window.hpp"

#include <iostream>

#include <SDL2/SDL_syswm.h>

#include <glload/gl_3_3.h>

#include "include/Pancake/Graphics/color.hpp"
#include "source/Graphics/GLCheck.hpp"

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
        window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, static_cast<int>(wsettings));
        if(window_ == nullptr)
        {
            std::cerr << "Window creation error: " << SDL_GetError();
            return false;
        }

        //Create GL Context
        context_.create(*this, csettings);
        if(!context_)
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
        window_ = win;

        //Create GL Context
        context_.create(*this);
        if(!context_)
        {
            std::cerr << "Context creation error in window (creating from SDL_Window).";
            return false;
        }

        return true;
    }
    void Window::close()
    {
        if(window_)
        {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
    }

    void Window::processEvent(SDL_Event& event)
    {
        if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.windowID == getId())
            {
                if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    glCheck(glViewport(0, 0, event.window.data1, event.window.data2));
                }
            }
        }
    }

    void Window::clear(const Color& color)
    {
        glCheck(glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f));
        glCheck(glClear(GL_COLOR_BUFFER_BIT));
    }
    void Window::display()
    {
        SDL_GL_SwapWindow(window_);
    }

    bool Window::setVerticalSyncEnabled(bool enable)
    {
        if(enable)
            return !SDL_GL_SetSwapInterval(1);
        else
            return !SDL_GL_SetSwapInterval(0);

    }
    void Window::setActive(bool enable)
    {
        context_.setActive(*this, enable);
    }

    glm::uvec2 Window::getPosition() const
    {
        int x, y;
        SDL_GetWindowPosition(window_, &x, &y);

        return {x, y};
    }
    Uint32 Window::getId() const
    {
        return SDL_GetWindowID(window_);
    }
    Window::Handle Window::getNativeHandle() const
    {
        SDL_SysWMinfo info;
        SDL_GetWindowWMInfo(window_, &info);

        Handle handle;
        #if defined(PANCAKE_WINDOWS)
        handle = info.info.win.window;
        #elif defined (PANCAKE_LINUX)
        handle = info.info.x11.window;
        #endif

        return handle;
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
