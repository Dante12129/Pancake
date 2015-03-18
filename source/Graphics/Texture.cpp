#include "include\Pancake\Graphics\Texture.hpp"

#include <iostream>

#include "include/Pancake/Graphics/Image.hpp"
#include "source/Graphics/GLCheck.hpp"

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

            bind();
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
            glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
            glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixels()));
            glCheck(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

            unbind();
            created_ = true;
        }
        else
        {
            created_ = false;
            std::cerr << "Error loading texure from image: dimension of 0" << std::endl;
        }

        return created_;
    }
    bool Texture::loadFromSurface(SDL_Surface* surface)
    {
        Image image;
        return image.loadFromSurface(surface) && loadFromImage(image);
    }

    void Texture::bind() const
    {
        glCheck(glBindTexture(GL_TEXTURE_2D, tex));
    }
    void Texture::unbind() const
    {
        glCheck(glBindTexture(GL_TEXTURE_2D, 0));
    }
    void Texture::setActiveUnit(GLenum unit)
    {
        glCheck(glActiveTexture(GL_TEXTURE0 + unit));
    }

    GLuint Texture::getActiveUnit()
    {
        int object;
        glCheck(glGetIntegerv(GL_ACTIVE_TEXTURE, &object));

        return object;
    }
    GLuint Texture::getActive()
    {
        int object;
        glCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, & object));

        return object;
    }
    int Texture::getMaxSize()
    {
        int size = 0;
        glCheck(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));

        return size;
    }
}
