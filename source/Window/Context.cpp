#include "include\Pancake\Window\Context.hpp"

#include <iostream>

#include "include/Pancake/Window/Window.hpp"

namespace pcke
{
    Context::Context() : context(nullptr) {}
    Context::~Context()
    {
        free();
    }

    bool Context::create(const Window& window, const ContextSettings& settings)
    {
        //Delete the context if it has been created before
        free();

        //Set context options, trying the highest version
        for(int major = settings.major; major > 0; --major)
        {
            for(int minor = settings.minor; minor > 0; --minor)
            {
                //Set the context settings
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                #ifdef PCKE_DEBUG
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
                #endif //PCKE_DEBUG

                //Create the context with the current flags
                context = SDL_GL_CreateContext(window.window);

                //See if the minor version is supported
                if(context)
                    break;
            }
            //See if the major version is supported
            if(context)
                break;
        }

        //If a context hasn't been created by now, then there's a problem
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
    void Context::free()
    {
        if(created)
        {
            SDL_GL_DeleteContext(context);
            created = false;
        }
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
        return created;
    }
}
