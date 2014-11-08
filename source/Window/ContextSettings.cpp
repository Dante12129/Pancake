#include "include\Pancake\Window\ContextSettings.hpp"

namespace pcke
{
    Profile operator |(Profile left, Profile right)
    {
        return static_cast<Profile>(static_cast<int>(left) | static_cast<int>(left));
    }
    Profile operator &(Profile left, Profile right)
    {
        return static_cast<Profile>(static_cast<int>(left) & static_cast<int>(left));
    }

    bool any(Profile profile)
    {
        return profile != Profile::None;
    }
    std::string toString(Profile profile)
    {
        switch(profile)
        {
            case Profile::None:
              break;
            case Profile::Core:
                return "Core";
              break;
            case Profile::Compatibility:
                return "Compatibility";
              break;
        }

        return "";
    }

    ContextSettings::ContextSettings() : major(4), minor(5), profile(Profile::Core) {}
}
