#include "include\Pancake\OpenGL\Texture.hpp"

#include <iostream>

#include "include/Pancake/Graphics/Image.hpp"
#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    Texture::Texture()
    {
        glCheck(glGenTextures(1, &tex));
    }
    Texture::~Texture()
    {
        glCheck(glDeleteTextures(1, &tex));
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

            glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixels()));

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
        glCheck(glBindTexture(GL_TEXTURE_2D, tex));
    }
    void Texture::unbind()
    {
        glCheck(glBindTexture(GL_TEXTURE_2D, 0));
    }
    void Texture::setActiveUnit(GLenum unit)
    {
        glCheck(glActiveTexture(GL_TEXTURE0 + unit));
    }
}
