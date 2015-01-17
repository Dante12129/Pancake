#ifndef DTE_HPP
#define DTE_HPP

union SDL_Event;

namespace pcke
{
    class Pancake
    {
        public:
            Pancake();
            Pancake(int major, int minor);
            Pancake(const Pancake&) = delete;
            Pancake(Pancake&&) = delete;
            ~Pancake();

            Pancake& operator =(const Pancake&) = delete;
            Pancake& operator =(Pancake&&) = delete;

            int getMajorVersion();
            int getMinorVersion();

            bool pollEvents(SDL_Event& event);
    };
}

#endif // DTE_HPP
