#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>

namespace pcke
{
    class Library
    {
        public:
            Library() = default;
            Library(const std::string& name);
            ~Library();

            bool load(const std::string& name);

            void* getSymbol(const std::string& name) const;

        private:
            void* lib_ = nullptr;
            bool loaded_ = false;
    };
}

#endif // LIBRARY_HPP
