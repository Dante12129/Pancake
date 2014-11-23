#include "include\Pancake\System\Info.hpp"

#include <SDL2/SDL_platform.h>

namespace pcke
{
    std::string getPlatform()
    {
        return SDL_GetPlatform();
    }
}
