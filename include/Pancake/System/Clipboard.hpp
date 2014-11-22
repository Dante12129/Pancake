#ifndef CLIPBOARD_HPP
#define CLIPBOARD_HPP

#include <string>

namespace pcke
{
    class Clipboard
    {
        public:
            static bool hasText();
            static std::string getText();
            static void setText(const std::string& text);
    };
}

#endif // CLIPBOARD_HPP
