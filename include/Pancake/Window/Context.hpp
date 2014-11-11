#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL2/SDL_video.h>

#include <Pancake/Window/ContextSettings.hpp>

namespace pcke
{
    class Window;
    struct ContextSettings;

    class Context
    {
        public:
            Context();
            Context(const Context&) = delete;
            Context(Context&&) = delete;
            ~Context();

            Context& operator =(const Context&) = delete;
            Context& operator =(Context&&) = delete;

            bool create(const Window& window, const ContextSettings& settings = ContextSettings());

            bool setActive(const Window& window, bool active);

            explicit operator bool() const;

        private:
            SDL_GLContext context;
            bool created = false;
    };
}

#endif // CONTEXT_HPP
