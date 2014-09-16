#include "include/Pancake/Pancake.hpp"

#include <iostream>
#include <stdexcept>

#include <SDL.h>

#include <glload/gl_load.h>

namespace pcke
{
    Pancake::Pancake()
    {
        //Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO))
            std::cerr << "SDL couldn't be initialized." << std::endl;

        //Create dummy window and context for OpenGL
        auto dummy_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
        SDL_GLContext dummy_context;

        //Set context options, trying the highest version
        for(int major = 4; major > 0; --major)
        {
            for(int minor = 5; minor > 0; --minor)
            {

                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                //#ifdef PCKE_DEBUG
                //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
                //#endif //PCKE_DEBUG

                //Create the context with the current flags
                dummy_context = SDL_GL_CreateContext(dummy_window);

                //See if the version is supported
                if(dummy_context)
                    break;
            }
            if(dummy_context)
                break;
        }

        //If a context hasn't been created by now, then there's a problem
        if(!dummy_context)
        {
            std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
            throw std::runtime_error("Error in Pancake constructor.");
        }

        //Initialize OpenGL
        if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
            std::cerr << "OpenGL functions unable to be loaded." << std::endl;

        //Check the OpenGL version
        if(!ogl_IsVersionGEQ(3, 3))
        {
            std::cerr << "OpenGL is not at least version 3.3" << std::endl;
            throw std::runtime_error("OpenGL is not at least version 3.3");
        }

        //Destroy the dummy window, as it's not needed
        SDL_GL_DeleteContext(dummy_context);
        SDL_DestroyWindow(dummy_window);

        //Output confirmation
        #ifdef PCKE_DEBUG
        std::cout << "Pancake initialized successfully." << std::endl;
        #endif //PCKE_DEBUG

    }
    Pancake::~Pancake()
    {
        //Shutdown SDL
        SDL_Quit();
    }

    int Pancake::getMajorVersion()
    {
        return ogl_GetMajorVersion();
    }
    int Pancake::getMinorVersion()
    {
        return ogl_GetMinorVersion();
    }
}
