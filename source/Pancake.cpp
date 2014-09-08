#include "include/Pancake/Pancake.hpp"

#include <iostream>

#include <SDL.h>

#include <glload/gl_load.h>

namespace pcke
{
    Pancake::Pancake()
    {
        //Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO))
            std::cerr << "SDL couldn't be initialized." << std::endl;

        //Set context options
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        //Create dummy window and context for OpenGL
        auto dummy_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
        auto dummy_context = SDL_GL_CreateContext(dummy_window);

        //Initialize OpenGL
        if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
            std::cerr << "OpenGL functions unable to be loaded." << std::endl;

        //Destroy the dummy window, as it's not needed
        SDL_GL_DeleteContext(dummy_context);
        SDL_DestroyWindow(dummy_window);
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
