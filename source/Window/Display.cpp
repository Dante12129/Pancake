#include "include/Pancake/Window/Display.hpp"

#include <SDL2/SDL_video.h>

namespace pcke
{
    Display::Display(int display) : index_(display) {}

    std::string Display::getName() const
    {
        return SDL_GetDisplayName(index_);
    }
    int Display::getIndex() const
    {
        return index_;
    }
}
