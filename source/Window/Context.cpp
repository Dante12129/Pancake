#include "include\Pancake\Window\Context.hpp"

namespace pcke
{
    Context::~Context()
    {
        if(created)
            SDL_GL_DeleteContext(context);
    }

    void Context::setActive(bool active, SDL_Window* window)
    {
        if(active)
            SDL_GL_MakeCurrent(window, context);
        else
            SDL_GL_MakeCurrent(window, nullptr);
    }
}
