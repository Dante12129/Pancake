#include "include\Pancake\Window\Context.hpp"

#include <iostream>

#include "include/Pancake/Window/Window.hpp"

namespace pcke
{
    Context::~Context()
    {
        if(created)
            SDL_GL_DeleteContext(context);
    }

    bool Context::create(const Window& window, int major, int minor)
    {
        //Delete the context if it has been created before
        if(created)
        {
            SDL_GL_DeleteContext(context);
            created = false;
        }

        //Set the context settings
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        #ifdef PCKE_DEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        #endif //PCKE_DEBUG

        //Create the context and check for errors
        context = SDL_GL_CreateContext(window.window);
        if(!context)
        {
            std::cerr << "Error creating a context: " << SDL_GetError() << std::endl;
            created = false;
        }
        else
            created = true;

        return created;
    }
    void Context::setActive(bool active, SDL_Window* window)
    {
        if(active)
            SDL_GL_MakeCurrent(window, context);
        else
            SDL_GL_MakeCurrent(window, nullptr);
    }
}
