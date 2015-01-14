#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>

namespace pcke
{
    class Library
    {
        public:
            ~Library();

            bool load();

            void* getSymbol(const std::string& name) const;

        private:
            void* lib = nullptr;
    };
}

#endif // LIBRARY_HPP
