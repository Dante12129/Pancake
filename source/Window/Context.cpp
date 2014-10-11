#include "include\Pancake\Window\Context.hpp"

namespace pcke
{
    Context::~Context()
    {
        if(created)
            SDL_GL_DeleteContext(context);
    }
}
