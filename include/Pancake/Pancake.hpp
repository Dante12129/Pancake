#ifndef DTE_HPP
#define DTE_HPP

namespace pcke
{
    class Pancake
    {
        public:
            Pancake();
            Pancake(int major, int minor);
            Pancake(const Pancake& other) = delete;
            Pancake(Pancake&&) = delete;
            ~Pancake();

            Pancake& operator=(const Pancake& other) = delete;
            Pancake& operator=(Pancake&& other) = delete;

            int getMajorVersion();
            int getMinorVersion();
    };
}

#endif // DTE_HPP
