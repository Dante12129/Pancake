#include "include/Pancake/System/Library.hpp"

#include <iostream>

#include <SDL2/SDL_loadso.h>

namespace pcke
{
    Library::~Library()
    {
        if(lib)
        {
            SDL_UnloadObject(lib);
        }
    }

    void* Library::getSymbol(const std::string& name)
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
