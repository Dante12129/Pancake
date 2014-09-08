#include "include\Pancake\OpenGL\Texture.hpp"

#include <iostream>

#include "include/Pancake/Graphics/Image.hpp"

namespace pcke
{
    Texture::Texture()
    {
        glGenTextures(1, &tex);
    }
    Texture::~Texture()
    {
        glDeleteTextures(1, &tex);
    }

    bool Texture::loadFromFile(const std::string& file)
    {
        Image image;
        return image.loadFromFile(file) && loadFromImage(image);
    }

    bool Texture::loadFromImage(const Image& img)
    {
        if(img.getSize().x > 0 && img.getSize().y > 0)
        {
            size = img.getSize();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixels());

            created = true;
        }
        else
        {
            created = false;
            std::cerr << "Error loading texure from image: dimension of 0" << std::endl;
        }

        return created;
    }

    void Texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, tex);
    }
    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    void Texture::setActiveUnit(GLenum unit)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
    }
}
