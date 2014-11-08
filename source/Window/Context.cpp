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

    bool Context::create(const Window& window, const ContextSettings& settings)
    {
        //Delete the context if it has been created before
        if(created)
        {
            SDL_GL_DeleteContext(context);
            created = false;
        }

        //Set the context settings
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, static_cast<int>(settings.profile));
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

        //Return whether creation failed or not
        return created;
    }
    bool Context::setActive(const Window& window, bool active)
    {
        bool result;

        if(active)
            result = SDL_GL_MakeCurrent(window.window, context);
        else
            result = SDL_GL_MakeCurrent(window.window, nullptr);

        if(!result)
            std::cerr << "Error setting active context: " << SDL_GetError() << std::endl;

        return result;
    }

    Context::operator bool() const
    {
        return context;
    }
}
