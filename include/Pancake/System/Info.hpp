#ifndef INFO_HPP
#define INFO_HPP

#include <string>

namespace pcke
{
    std::string getPlatform();

    class CPU
    {
        public:
            static int getCacheSize();
            static int getThreads();
            static int getRAM();
    };

    class GPU
    {
        public:
            static std::string getCurrentDriver();
    };
}

#endif // INFO_HPP
