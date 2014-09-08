#include "include/Pancake/OpenGL/ShaderProgram.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "include/Pancake/OpenGL/Shader.hpp"

namespace pcke
{
    ShaderProgram::ShaderProgram() : program(glCreateProgram())
    {}
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program);
    }

    void ShaderProgram::addShader(Shader& shader)
    {
        glAttachShader(program, shader.shader);
    }
    void ShaderProgram::removeShader(Shader& shader)
    {
        glDetachShader(program, shader.shader);
    }

    bool ShaderProgram::link()
    {
        glLinkProgram(program);

        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint log_length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

            std::unique_ptr<GLchar[]> log(new GLchar[log_length + 1]);
            glGetProgramInfoLog(program, log_length, 0, log.get());
            std::cerr << "Error linking shader program: " << log.get() << std::endl;
            return false;
        }

        return true;
    }

    void ShaderProgram::bind()
    {
        glUseProgram(program);
    }
    void ShaderProgram::unbind()
    {
        glUseProgram(0);
    }

    void ShaderProgram::setUniform(const std::string& name, float value)
    {
        bind();
        glUniform1f(glGetUniformLocation(program, name.c_str()), value);
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second)
    {
        bind();
        glUniform2f(glGetUniformLocation(program, name.c_str()), first, second);
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third)
    {
        bind();
        glUniform3f(glGetUniformLocation(program, name.c_str()), first, second, third);
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third, float fourth)
    {
        bind();
        glUniform4f(glGetUniformLocation(program, name.c_str()), first, second, third, fourth);
    }
    void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
    {
        bind();
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
