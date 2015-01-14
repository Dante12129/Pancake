#include "include/Pancake/System/Library.hpp"

#include <iostream>

#include <SDL2/SDL_loadso.h>

namespace pcke
{
    Library::Library(const std::string& name) : Library()
    {
        load(name);
    }

    Library::~Library()
    {
        if(lib)
        {
            SDL_UnloadObject(lib);
            lib = nullptr;
        }
    }

    bool Library::load(const std::string& name)
    {
        //Add the correct suffix based on platform
        std::string full_name = name;
        #ifdef PANCAKE_WINDOWS
        full_name += ".dll";
        #elif defined(PANCAKE_UNIX)
        full_name += ".so";
        #endif

        //Try to load the library with the correct suffix
        lib = SDL_LoadObject(full_name.c_str());
        if(!lib)
        {
            std::cerr << "Error loading a library: " << SDL_GetError() << std::endl;
        }

        return loaded;
    }

    void* Library::getSymbol(const std::string& name) const
    {
        auto func = SDL_LoadFunction(lib, name.c_str());
        if(!func)
        {
            std::cerr << "Error getting a function from library: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        return func;
    }
}
