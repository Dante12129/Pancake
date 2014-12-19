#include "include/Pancake/Pancake.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <glload/gl_load.h>

#include "include/Pancake/Window/Context.hpp"
#include "include/Pancake/Window/Window.hpp"

namespace pcke
{
    Pancake::Pancake()
    {
        //Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO))
        {
            std::cerr << "SDL couldn't be initialized: " << SDL_GetError() << std::endl;
        }

        //Initialize SDL_ttf
        if(TTF_Init())
        {
            std::cerr << "SDL_ttf couldn't be initialized: " << TTF_GetError() << std::endl;
        }

        //Create dummy window and context for OpenGL
        Window dummy_window("", 0, 0, WindowSettings::OpenGL | WindowSettings::Hidden);

        //Initialize OpenGL
        if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
        {
            std::cerr << "OpenGL functions unable to be loaded." << std::endl;
        }

        //Check the OpenGL version
        if(!ogl_IsVersionGEQ(3, 3))
        {
            std::cerr << "OpenGL is not at least version 3.3; some functionality may not work." << std::endl;
        }
    }
    Pancake::Pancake(int major, int minor)
    {
        //Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO))
            std::cerr << "SDL couldn't be initialized." << std::endl;

        //Create dummy window for OpenGL
        auto dummy_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

        //Set the context settings
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        #ifdef PCKE_DEBUG
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        #endif //PCKE_DEBUG

        //Create the context
        auto dummy_context = SDL_GL_CreateContext(dummy_window);

        //Check for errors
        if(!dummy_context)
        {
            std::cerr << "Error creating OpenGL context: " << SDL_GetError() << std::endl;
        }

        //Initialize OpenGL
        if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
            std::cerr << "OpenGL functions unable to be loaded." << std::endl;

        //Destroy the dummy window, as it's not needed
        SDL_GL_DeleteContext(dummy_context);
        SDL_DestroyWindow(dummy_window);
    }

    Pancake::~Pancake()
    {
        //Shutdown SDL and its extensions
        SDL_Quit();
        TTF_Quit();
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
