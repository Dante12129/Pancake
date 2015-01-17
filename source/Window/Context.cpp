#include "include\Pancake\Window\Context.hpp"

#include <iostream>

#include "include/Pancake/Window/Window.hpp"

namespace pcke
{
    Context::Context() : context_(nullptr) {}
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
                context_ = SDL_GL_CreateContext(window.window_);

                //See if the minor version is supported
                if(context_)
                    break;
            }
            //See if the major version is supported
            if(context_)
                break;
        }

        //If a context hasn't been created by now, then there's a problem
        if(!context_)
        {
            std::cerr << "Error creating a context: " << SDL_GetError() << std::endl;
            created_ = false;
        }
        else
            created_ = true;

        //Return whether creation failed or not
        return created_;
    }
    void Context::free()
    {
        if(created_)
        {
            SDL_GL_DeleteContext(context_);
            created_ = false;
        }
    }

    bool Context::setActive(const Window& window, bool active)
    {
        bool result;

        if(active)
            result = SDL_GL_MakeCurrent(window.window_, context_);
        else
            result = SDL_GL_MakeCurrent(window.window_, nullptr);

        if(!result)
            std::cerr << "Error setting active context: " << SDL_GetError() << std::endl;

        return result;
    }

    Context::operator bool() const
    {
        return created_;
    }
}
