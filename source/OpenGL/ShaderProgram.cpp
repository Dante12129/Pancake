#include "include/Pancake/OpenGL/ShaderProgram.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/type_ptr.hpp>
#include <glload/gl_load.h>

#include "include/Pancake/OpenGL/Shader.hpp"
#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    ShaderProgram::ShaderProgram() : program(glCreateProgram())
    {}
    ShaderProgram::~ShaderProgram()
    {
        glCheck(glDeleteProgram(program));
    }

    bool ShaderProgram::binarySupported() const
    {
        return ogl_IsVersionGEQ(4, 1) || glext_ARB_get_program_binary;
    }

    void ShaderProgram::addShader(Shader& shader)
    {
        glCheck(glAttachShader(program, shader.shader));
    }
    void ShaderProgram::removeShader(Shader& shader)
    {
        glCheck(glDetachShader(program, shader.shader));
    }

    bool ShaderProgram::link()
    {
        if(binarySupported())
            setValue(GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
        glCheck(glLinkProgram(program));

        GLint status;
        glCheck(glGetProgramiv(program, GL_LINK_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLint log_length;
            glCheck(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length));

            std::unique_ptr<GLchar[]> log(new GLchar[log_length + 1]);
            glCheck(glGetProgramInfoLog(program, log_length, 0, log.get()));
            std::cerr << "Error linking shader program: " << log.get() << std::endl;
            linked = false;
        }
        else
            linked = true;

        return linked;
    }

    void ShaderProgram::bind()
    {
        glCheck(glUseProgram(program));
    }
    void ShaderProgram::unbind()
    {
        glCheck(glUseProgram(0));
    }

    GLuint ShaderProgram::getHandle() const
    {
        return program;
    }

    void ShaderProgram::setUniform(const std::string& name, float value)
    {
        bind();
        glCheck(glUniform1f(glGetUniformLocation(program, name.c_str()), value));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second)
    {
        bind();
        glCheck(glUniform2f(glGetUniformLocation(program, name.c_str()), first, second));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third)
    {
        bind();
        glCheck(glUniform3f(glGetUniformLocation(program, name.c_str()), first, second, third));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third, float fourth)
    {
        bind();
        glCheck(glUniform4f(glGetUniformLocation(program, name.c_str()), first, second, third, fourth));
    }
    void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
    {
        bind();
        glCheck(glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)));
    }

    int ShaderProgram::getBinarySize() const
    {
        if(binarySupported())
            return getValue(GL_PROGRAM_BINARY_LENGTH);
        else
            return 0;
    }
    std::pair<GLenum, std::unique_ptr<char[]>> ShaderProgram::getBinary() const
    {
        if(binarySupported())
        {
            GLenum format = 0;
            std::unique_ptr<char[]> binary(new char[getBinarySize()]);

            glCheck(glGetProgramBinary(program, getBinarySize(), nullptr, &format, void_cast(binary)));

            return std::make_pair(format, std::move(binary));
        }
        else
            return std::make_pair(0, nullptr);
    }
    void ShaderProgram::setBinary(GLenum format, const void* binary, GLsizei length)
    {
        if(binarySupported())
            glCheck(glProgramBinary(program, format, binary, length));
    }

    int ShaderProgram::getValue(GLenum param) const
    {
        int value;
        glCheck(glGetProgramiv(program, param, &value));
        return value;
    }
    void ShaderProgram::setValue(GLenum param, int value)
    {
        glCheck(glProgramParameteri(program, param, value));
    }


    void* void_cast(std::unique_ptr<char[]>& data)
    {
        return static_cast<void*>(data.get());
    }
}

