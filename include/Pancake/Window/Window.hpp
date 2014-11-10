#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <glm/vec2.hpp>

namespace pcke
{
    class Color;

    enum class WindowSettings
    {
        None = 0,
        Fullscreen = SDL_WINDOW_FULLSCREEN,
        OpenGL = SDL_WINDOW_OPENGL,
        Hidden = SDL_WINDOW_HIDDEN,
        Shown = SDL_WINDOW_SHOWN,
        Borderless = SDL_WINDOW_BORDERLESS,
        Rezisable = SDL_WINDOW_RESIZABLE,
        Minimized = SDL_WINDOW_MINIMIZED,
        Maximized = SDL_WINDOW_MAXIMIZED,
        Foreign = SDL_WINDOW_FOREIGN,
        HighDPI = SDL_WINDOW_ALLOW_HIGHDPI,
        Default = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    };

    class Window
    {
        public:
            friend class Context;

        public:
            Window(const std::string& title, int width, int height, WindowSettings settings = WindowSettings::Default);
            Window(SDL_Window* win);
            Window(const Window&) = delete;
            Window(Window&&) = delete;
            ~Window();

            Window& operator =(const Window&) = delete;
            Window& operator =(Window&&) = delete;

            bool pollEvent(SDL_Event& event);

            void clear(const Color& color);
            void display();

            bool setVerticalSyncEnabled(bool enable);
            void setKeyRepeatEnabled(bool enable);
            void setActive(bool enable);

            glm::uvec2 getPosition() const;
            Uint32 getId() const;

        private:
            SDL_Window* window;
            SDL_GLContext context;
            bool key_repeat = false;
    };

    WindowSettings operator |(WindowSettings left, WindowSettings right);
    WindowSettings operator &(WindowSettings left, WindowSettings right);
    bool any(WindowSettings settings);
}

#endif // WINDOW_HPP
