#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

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

            void bind() const;
            void unbind() const;
            static void setActiveUnit(GLenum unit);

            static GLuint getActiveUnit();
            static GLuint getActive();

        private:
            bool created = false;
            GLuint tex;

            glm::uvec2 size;
    };
}

#endif // TEXTURE_HPP
