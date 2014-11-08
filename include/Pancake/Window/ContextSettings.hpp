#ifndef CONTEXTSETTINGS_HPP
#define CONTEXTSETTINGS_HPP

#include <string>

#include <SDL2/SDL_video.h>

namespace pcke
{
    enum class Profile
    {
        None = 0,
        Core = SDL_GL_CONTEXT_PROFILE_CORE,
        Compatibility = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
    };

    Profile operator |(Profile left, Profile right);
    Profile operator &(Profile left, Profile right);

    bool any(Profile profile);
    std::string toString(Profile profile);

    struct ContextSettings
    {
        ContextSettings();

        int major, minor;
        Profile profile;
    };
}

#endif // CONTEXTSETTINGS_HPP
