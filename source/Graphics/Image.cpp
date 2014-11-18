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
            size.x = width;
            size.y = height;

            data.resize(width * height * 4);
            memcpy(&data[0], image_data, data.size());

            created = true;
        }
        else
        {
            created = false;
            std::cerr << "Error loading image from file: " << stbi_failure_reason() << std::endl;
        }

        stbi_image_free(image_data);
        return created;
    }

    glm::uvec2 Image::getSize() const
    {
        return size;
    }
    const std::uint8_t* Image::getPixels() const
    {
        return &data.front();
    }
}
