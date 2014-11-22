#include "include\Pancake\System\Clipboard.hpp"

#include <iostream>

#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_error.h>

namespace pcke
{
    bool Clipboard::hasText()
    {
        return SDL_HasClipboardText();
    }
    std::string Clipboard::getText()
    {
        auto mem = SDL_GetClipboardText();
        if(!mem)
        {
            std::cerr << "Error getting clipboard text: " << SDL_GetError() << std::endl;
            SDL_free(mem);
            return "";
        }
        else
        {
            std::string text(mem);
            SDL_free(mem);
            return text;
        }
    }
    void Clipboard::setText(const std::string& text)
    {
        if(SDL_SetClipboardText(text.c_str()))
        {
            std::cerr << "Error setting clipboard text: " << SDL_GetError() << std::endl;
        }
    }
}
