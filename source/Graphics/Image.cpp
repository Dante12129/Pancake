#include "include\Pancake\Graphics\Image.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace pcke
{
    bool Image::loadFromFile(const std::string& file)
    {
        int width, height, channels;
        unsigned char* image_data = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if(image_data && width && height)
        {
            size_.x = width;
            size_.y = height;

            data_.resize(width * height * 4);
            memcpy(&data_[0], image_data, data_.size());

            created_ = true;
        }
        else
        {
            created_ = false;
            std::cerr << "Error loading image from file: " << stbi_failure_reason() << std::endl;
        }

        stbi_image_free(image_data);
        return created_;
    }
    bool Image::loadFromSurface(SDL_Surface* surface)
    {
        SDL_Surface* new_surface = surface;

        //Convert the surface to the format we use
        if(surface->format->format != SDL_PIXELFORMAT_RGBA8888)
            new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);

        //Lock if the texture must be locked
        if(SDL_MUSTLOCK(new_surface))
            SDL_LockSurface(new_surface);

        if(new_surface->w > 0 &&  new_surface->h > 0)
        {
            size_ = {new_surface->w, new_surface->h};

            data_.resize(size_.x * size_.y * 4);
            memcpy(&data_[0], new_surface->pixels, data_.size());

            created_ = true;
        }
        else
        {
            created_ = false;
            std::cerr << "Error loading image from surface: dimension of 0" << std::endl;
        }

        //Unlock surface if it must be locked
        if(SDL_MUSTLOCK(new_surface))
            SDL_UnlockSurface(new_surface);

        return created_;
    }

    glm::uvec2 Image::getSize() const
    {
        return size_;
    }
    const std::uint8_t* Image::getPixels() const
    {
        return &data_.front();
    }
}
