#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <SDL_events.h>
#include <SDL_video.h>

#include <glm/vec2.hpp>

namespace pcke
{
    class Color;

    class Window
    {
        public:
            friend class Context;

        public:

            Window(const std::string& title, int width, int height);
            ~Window();

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
}

#endif // WINDOW_HPP
