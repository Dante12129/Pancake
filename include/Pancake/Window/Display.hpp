#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>

namespace pcke
{
    class Display
    {
        public:
            Display() = default;
            Display(int display);

            std::string getName() const;
            int getIndex() const;

        private:
            int index_ = 0;
    };
}

#endif // DISPLAY_HPP
