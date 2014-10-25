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
            bool setActive(const Window& window, bool active);

            explicit operator bool() const;

        private:
            SDL_GLContext context;
            bool created = false;
    };
}

#endif // CONTEXT_HPP
