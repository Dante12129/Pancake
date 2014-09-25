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

            void bind();
            void unbind();
            static void setActiveUnit(GLenum unit);

        private:
            bool created = false;
            GLuint tex;

            glm::uvec2 size;
    };
}

#endif // TEXTURE_HPP
