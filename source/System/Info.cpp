#include "include\Pancake\System\Info.hpp"

#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_video.h>

namespace pcke
{
    std::string getPlatform()
    {
        return SDL_GetPlatform();
    }

    int CPU::getCacheSize()
    {
        return SDL_GetCPUCacheLineSize();
    }
    int CPU::getThreads()
    {
        return SDL_GetCPUCount();
    }
    int CPU::getRAM()
    {
        return SDL_GetSystemRAM();
    }

    std::string GPU::getCurrentDriver()
    {
        return SDL_GetCurrentVideoDriver();
    }
}
