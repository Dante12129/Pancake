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

            //Shader functions
            void addShader(Shader& shader);
            void removeShader(Shader& shader);

            //Linking functions
            bool link();

            //Activation functions
            void bind() const;
            void unbind() const;
            void bindTextures() const;

            //Important getters
            GLuint getHandle() const;
            static GLuint getBound();

            //Uniform-setting functions
            void setUniform(const std::string& name, float value);
            void setUniform(const std::string& name, float first, float second);
            void setUniform(const std::string& name, float first, float second, float third);
            void setUniform(const std::string& name, float first, float second, float third, float fourth);
            void setUniform(const std::string& name, const glm::mat4& matrix);
            void setUniform(const std::string& name, const Texture& tex, GLuint unit = 0);

            //Binary Functions
            int getBinarySize() const;
            std::pair<GLenum, std::unique_ptr<char[]>> getBinary() const;
            void setBinary(GLenum format, const void* binary, GLsizei length);

            //Parameter-interaction functions
            int getValue(GLenum param) const;
            void setValue(GLenum param, int value);

        private:
            bool linked_ = false;
            GLuint program_;

            //Uniform caching
            std::map<std::string, GLuint> uniform_locations_;
            GLuint uniformLocation(const std::string& name);

            //Texture caching
            std::map<GLuint, std::pair<GLuint, const Texture*>> textures_;
    };

    //Cast unique_ptr to void*
    void* void_cast(std::unique_ptr<char[]>& data);
}

#endif // SHADERPROGRAM_HPP
