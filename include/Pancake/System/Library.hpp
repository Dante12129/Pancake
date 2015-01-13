#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>

namespace pcke
{
    class Library
    {
        public:
            ~Library();

            void* getSymbol(const std::string& name);

        private:
            void* lib = nullptr;
    };
}

#endif // LIBRARY_HPP
