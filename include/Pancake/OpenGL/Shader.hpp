#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glload/gl_3_3.h>

namespace pcke
{
    class Shader
    {
        public:
            enum class Type
            {
                Vertex = GL_VERTEX_SHADER,
                Fragment = GL_FRAGMENT_SHADER,
                Geometry = GL_GEOMETRY_SHADER,
                None = 534
            };

            friend class ShaderProgram;

        public:
            Shader() = default;
            ~Shader();

            bool loadFromFile(const std::string& filename, Type type);
            bool loadFromMemory(const std::string& src, Type type);

        private:
            GLuint shader;
            bool created = false;

            bool create(const std::string& src, Type type);
    };
}

#endif // SHADER_HPP
