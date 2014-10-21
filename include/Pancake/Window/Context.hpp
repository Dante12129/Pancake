#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL_video.h>

namespace pcke
{
    class Window;

    class Context
    {
        public:
            ~Context();

            bool create(const Window& window, int major, int minor);
            bool setActive(bool active, SDL_Window* window);

        private:
            SDL_GLContext context;
            bool created = false;
    };
}

#endif // CONTEXT_HPP
