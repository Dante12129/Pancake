#include "include/Pancake/OpenGL/ShaderProgram.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/type_ptr.hpp>
#include <glload/gl_load.h>

#include "include/Pancake/OpenGL/Shader.hpp"
#include "include/Pancake/OpenGL/Texture.hpp"
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
    bool ShaderProgram::interfaceSupported() const
    {
        return ogl_IsVersionGEQ(4, 3) || glext_ARB_program_interface_query;
    }
    bool ShaderProgram::separationSupported() const
    {
        return ogl_IsVersionGEQ(4, 1) || glext_ARB_separate_shader_objects;
    }
    bool ShaderProgram::glsl420Supported() const
    {
        return ogl_IsVersionGEQ(4, 2) || glext_ARB_shading_language_420pack;
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
        uniform_locations.clear();

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
    GLuint ShaderProgram::getBound()
    {
        int value;
        glCheck(glGetIntegerv(GL_CURRENT_PROGRAM, &value));
        return value;
    }

    void ShaderProgram::setUniform(const std::string& name, float value)
    {
        bind();
        glCheck(glUniform1f(uniformLocation(name), value));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second)
    {
        bind();
        glCheck(glUniform2f(uniformLocation(name), first, second));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third)
    {
        bind();
        glCheck(glUniform3f(uniformLocation(name), first, second, third));
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third, float fourth)
    {
        bind();
        glCheck(glUniform4f(uniformLocation(name), first, second, third, fourth));
    }
    void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
    {
        bind();
        glCheck(glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    }
    void ShaderProgram::setUniform(const std::string& name, Texture& tex)
    {
        bind();
        tex.bind();
        glCheck(glUniform1i(uniformLocation(name), 0));
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

    //Private methods
    GLuint ShaderProgram::uniformLocation(const std::string& name)
    {
        GLuint location = -2;

        //Try to find cached location
        auto loc_it = uniform_locations.find(name);

        //If the location wasn't found, insert it
        if(loc_it == uniform_locations.cend())
        {
            location = glCheck(glGetUniformLocation(program, name.c_str()));
            uniform_locations.insert(std::make_pair(name, location));
        }
        else
            location = loc_it->second;

        return location;
    }

    //Free functions
    void* void_cast(std::unique_ptr<char[]>& data)
    {
        return static_cast<void*>(data.get());
    }
}

