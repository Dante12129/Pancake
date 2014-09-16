#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/fwd.hpp>
#include <glload/gl_3_3.h>

#include "Pancake/Utility/VoidPointer.hpp"

namespace pcke
{
    class Shader;

    class ShaderProgram
    {
        public:
            ShaderProgram();
            ~ShaderProgram();

            //Extension-querying functions
            bool binarySupported() const;

            //Shader functions
            void addShader(Shader& shader);
            void removeShader(Shader& shader);

            //Linking functions
            bool link();

            //Activation functions
            void bind();
            void unbind();

            //Uniform-setting functions
            void setUniform(const std::string& name, float value);
            void setUniform(const std::string& name, float first, float second);
            void setUniform(const std::string& name, float first, float second, float third);
            void setUniform(const std::string& name, float first, float second, float third, float fourth);
            void setUniform(const std::string& name, const glm::mat4& matrix);

            //Binary Functions
            int getBinarySize() const;
            std::pair<GLenum*, VoidPointer> getBinary() const;
            void setBinary(GLenum format, const void* binary, GLsizei length);

            //Parameter-interaction functions
            int getValue(GLenum param) const;
            void setValue(GLenum param, int value);

        private:
            bool linked = false;
            GLuint program;
    };
}

#endif // SHADERPROGRAM_HPP
