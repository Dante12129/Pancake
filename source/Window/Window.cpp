#include "include/Pancake/Window/Window.hpp"

#include <sstream>
#include <stdexcept>

#include <SDL2/SDL_opengl.h>
#include "include/Pancake/Graphics/color.hpp"
#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    Window::Window(const std::string& title, int width, int height, WindowSettings settings) : window(nullptr),
        context(nullptr)
    {
        //Stream for errors
        std::stringstream error;

        //Create window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, static_cast<int>(settings));
        if(window == nullptr)
        {
            error << "Window creation error: " << SDL_GetError();
            throw std::runtime_error(error.str());
        }

        //Create GL Context
        context = SDL_GL_CreateContext(window);
        if(context == nullptr)
        {
            error << "Context creation error: " << SDL_GetError();
            throw std::runtime_error(error.str());
        }
    }
    Window::Window(SDL_Window* win) : window(nullptr)
    {
        //Stream for errors
        std::stringstream error;

        //Take ownership of the window
        window = win;

        //Create GL Context
        context = SDL_GL_CreateContext(window);
        if(context == nullptr)
        {
            error << "Context creation error: " << SDL_GetError();
            throw std::runtime_error(error.str());
        }
    }
    Window::~Window()
    {
        //Destroy the context and window
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
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
        SDL_GL_MakeCurrent(window, context);
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
