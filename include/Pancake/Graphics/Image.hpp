#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <SDL2/SDL_surface.h>

#include <glm/vec2.hpp>

namespace pcke
{
    class Image
    {
        public:            
            bool loadFromFile(const std::string& file);
            bool loadFromSurface(SDL_Surface* surface);

            glm::uvec2 getSize() const;
            const std::uint8_t* getPixels() const;

        private:
            bool created_ = false;
            std::vector<std::uint8_t> data_;

            glm::uvec2 size_;
    };
}

#endif // IMAGE_HPP
