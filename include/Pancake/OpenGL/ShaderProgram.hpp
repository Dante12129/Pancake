#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <map>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/fwd.hpp>
#include <glload/gl_3_3.h>

namespace pcke
{
    class Shader;
    class Texture;

    class ShaderProgram
    {
        public:
            ShaderProgram();
            ~ShaderProgram();

            //Extension-querying functions
            bool binarySupported() const;
            bool interfaceSupported() const;
            bool separationSupported() const;
            bool glsl420Supported() const;

            //Shader functions
            void addShader(Shader& shader);
            void removeShader(Shader& shader);

            //Linking functions
            bool link();

            //Activation functions
            void bind();
            void unbind();

            //Important getters
            GLuint getHandle() const;
            static GLuint getBound();

            //Uniform-setting functions
            void setUniform(const std::string& name, float value);
            void setUniform(const std::string& name, float first, float second);
            void setUniform(const std::string& name, float first, float second, float third);
            void setUniform(const std::string& name, float first, float second, float third, float fourth);
            void setUniform(const std::string& name, const glm::mat4& matrix);
            void setUniform(const std::string& name, Texture& tex);

            //Binary Functions
            int getBinarySize() const;
            std::pair<GLenum, std::unique_ptr<char[]>> getBinary() const;
            void setBinary(GLenum format, const void* binary, GLsizei length);

            //Parameter-interaction functions
            int getValue(GLenum param) const;
            void setValue(GLenum param, int value);

        private:
            bool linked = false;
            GLuint program;

            //Uniform caching
            std::map<std::string, GLuint> uniform_locations;
            GLuint uniformLocation(const std::string& name);
    };

    //Cast unique_ptr to void*
    void* void_cast(std::unique_ptr<char[]>& data);
}

#endif // SHADERPROGRAM_HPP
