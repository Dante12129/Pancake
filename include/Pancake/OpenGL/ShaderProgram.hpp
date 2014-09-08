#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <string>

#include <glload/gl_3_3.h>
#include <glm/mat4x4.hpp>

namespace pcke
{
    class Shader;

    class ShaderProgram
    {
        public:
            ShaderProgram();
            ~ShaderProgram();

            void addShader(Shader& shader);
            void removeShader(Shader& shader);

            bool link();

            void bind();
            void unbind();

            void setUniform(const std::string& name, float value);
            void setUniform(const std::string& name, float first, float second);
            void setUniform(const std::string& name, float first, float second, float third);
            void setUniform(const std::string& name, float first, float second, float third, float fourth);
            void setUniform(const std::string& name, const glm::mat4& matrix);

        private:
            GLuint program;
    };
}

#endif // SHADERPROGRAM_HPP
