#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL_video.h>

namespace pcke
{
    class Context
    {
        public:
            ~Context();

        private:
            SDL_GLContext context;
            bool created = false;
    };
}

#endif // CONTEXT_HPP
