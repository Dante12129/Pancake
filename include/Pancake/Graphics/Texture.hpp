#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <SDL2/SDL_surface.h>

#include <glload/gl_3_3.h>
#include <glm/vec2.hpp>

namespace pcke
{
    class Image;

    class Texture
    {
        public:
            friend class ShaderProgram;

        public:
            Texture();
            ~Texture();

            bool loadFromFile(const std::string& file);
            bool loadFromImage(const Image& img);
            bool loadFromSurface(SDL_Surface* surface);

            void bind() const;
            void unbind() const;
            static void setActiveUnit(GLenum unit);

            static GLuint getActiveUnit();
            static GLuint getActive();
            static int getMaxSize();

        private:
            bool created_ = false;
            GLuint tex;

            glm::uvec2 size;
    };
}

#endif // TEXTURE_HPP
