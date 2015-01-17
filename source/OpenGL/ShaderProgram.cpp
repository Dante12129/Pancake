#include "include/Pancake/OpenGL/ShaderProgram.hpp"

#include <iostream>
#include <memory>

#include <glm/gtc/type_ptr.hpp>
#include <glload/gl_load.h>

#include "include/Pancake/OpenGL/Extensions.hpp"
#include "include/Pancake/OpenGL/Shader.hpp"
#include "include/Pancake/OpenGL/Texture.hpp"
#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    ShaderProgram::ShaderProgram() : program_(glCreateProgram())
    {}
    ShaderProgram::~ShaderProgram()
    {
        glCheck(glDeleteProgram(program_));
    }

    void ShaderProgram::addShader(Shader& shader)
    {
        glCheck(glAttachShader(program_, shader.shader_));
    }
    void ShaderProgram::removeShader(Shader& shader)
    {
        glCheck(glDetachShader(program_, shader.shader_));
    }

    bool ShaderProgram::link()
    {
        uniform_locations_.clear();

        if(ext::programBinary())
            setValue(GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
        glCheck(glLinkProgram(program_));

        GLint status;
        glCheck(glGetProgramiv(program_, GL_LINK_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLint log_length;
            glCheck(glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &log_length));

            std::unique_ptr<GLchar[]> log(new GLchar[log_length + 1]);
            glCheck(glGetProgramInfoLog(program_, log_length, 0, log.get()));
            std::cerr << "Error linking shader program: " << log.get() << std::endl;
            linked_ = false;
        }
        else
            linked_ = true;

        return linked_;
    }

    void ShaderProgram::bind() const
    {
        glCheck(glUseProgram(program_));
    }
    void ShaderProgram::unbind() const
    {
        glCheck(glUseProgram(0));
    }
    void ShaderProgram::bindTextures() const
    {
        for(const auto& i : textures_)
        {
            //Activate the appropriate texture unit and texture
            Texture::setActiveUnit(i.first);
            i.second.second->bind();

            if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
            {
                //Get the currently-bound program and bind this program
                auto previous = getBound();
                bind();

                //Set the uniform
                glCheck(glUniform1i(i.second.first, i.first));

                //Set the previous values back
                glCheck(glUseProgram(previous));

            }
            else //If we can do uniforms without binding
            {
                //Set the uniform with this program
                glCheck(glProgramUniform1i(program_, i.second.first, i.first));
            }
        }

        //Reset the active texture unit to 0
        Texture::setActiveUnit(0);
    }

    GLuint ShaderProgram::getHandle() const
    {
        return program_;
    }
    GLuint ShaderProgram::getBound()
    {
        int value;
        glCheck(glGetIntegerv(GL_CURRENT_PROGRAM, &value));

        return value;
    }

    void ShaderProgram::setUniform(const std::string& name, float value)
    {
        if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
        {
            //Get the currently-bound program and bind this program
            auto previous = getBound();
            bind();

            //Set the uniform
            glCheck(glUniform1f(uniformLocation(name), value));

            //Set the previous program back
            glCheck(glUseProgram(previous));
        }
        else //If we can do uniforms without binding
        {
            //Set the uniform with this program
            glCheck(glProgramUniform1f(program_, uniformLocation(name), value));
        }
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second)
    {
        if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
        {
            //Get the currently-bound program and bind this program
            auto previous = getBound();
            bind();

            //Set the uniform
            glCheck(glUniform2f(uniformLocation(name), first, second));

            //Set the previous program back
            glCheck(glUseProgram(previous));
        }
        else //If we can do uniforms without binding
        {
            //Set the uniform with this program
            glCheck(glProgramUniform2f(program_, uniformLocation(name), first, second));
        }
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third)
    {
        if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
        {
            //Get the currently-bound program and bind this program
            auto previous = getBound();
            bind();

            //Set the uniform
            glCheck(glUniform3f(uniformLocation(name), first, second, third));

            //Set the previous program back
            glCheck(glUseProgram(previous));
        }
        else //If we can do uniforms without binding
        {
            //Set the uniform with this program
            glCheck(glProgramUniform3f(program_, uniformLocation(name), first, second, third));
        }
    }
    void ShaderProgram::setUniform(const std::string& name, float first, float second, float third, float fourth)
    {
        if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
        {
            //Get the currently-bound program and bind this program
            auto previous = getBound();
            bind();

            //Set the uniform
            glCheck(glUniform4f(uniformLocation(name), first, second, third, fourth));

            //Set the previous program back
            glCheck(glUseProgram(previous));
        }
        else //If we can do uniforms without binding
        {
            //Set the uniform with this program
            glCheck(glProgramUniform4f(program_, uniformLocation(name), first, second, third, fourth));
        }
    }
    void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
    {
        if(!ext::separateShaderObjects()) //If we can't do uniforms without binding
        {
            //Get the currently-bound program and bind this program
            auto previous = getBound();
            bind();

            //Set the uniform
            glCheck(glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));

            //Set the previous program back
            glCheck(glUseProgram(previous));
        }
        else //If we can do uniforms without binding
        {
            //Set the uniform with this program
            glCheck(glProgramUniformMatrix4fv(program_, uniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
        }
    }
    void ShaderProgram::setUniform(const std::string& name, const Texture& tex, GLuint unit)
    {
        //Try to find the cached info
        auto it = textures_.find(unit);

        if(it != textures_.end()) //If the unit was found
        {
            //Replace the texture and uniform location
            it->second = std::make_pair(uniformLocation(name), &tex);
        }
        else //If the unit was not found
        {
            //Save the texture unit and the texture we want to associate with it
            textures_.insert(std::make_pair(unit, std::make_pair(uniformLocation(name), &tex)));
        }
    }

    int ShaderProgram::getBinarySize() const
    {
        if(ext::programBinary())
            return getValue(GL_PROGRAM_BINARY_LENGTH);
        else
            return 0;
    }
    std::pair<GLenum, std::unique_ptr<char[]>> ShaderProgram::getBinary() const
    {
        if(ext::programBinary())
        {
            GLenum format = 0;
            std::unique_ptr<char[]> binary(new char[getBinarySize()]);

            glCheck(glGetProgramBinary(program_, getBinarySize(), nullptr, &format, void_cast(binary)));

            return std::make_pair(format, std::move(binary));
        }
        else
            return std::make_pair(0, nullptr);
    }
    void ShaderProgram::setBinary(GLenum format, const void* binary, GLsizei length)
    {
        if(ext::programBinary())
            glCheck(glProgramBinary(program_, format, binary, length));
    }

    int ShaderProgram::getValue(GLenum param) const
    {
        int value;
        glCheck(glGetProgramiv(program_, param, &value));

        return value;
    }
    void ShaderProgram::setValue(GLenum param, int value)
    {
        glCheck(glProgramParameteri(program_, param, value));
    }

    //Private methods
    GLuint ShaderProgram::uniformLocation(const std::string& name)
    {
        GLuint location = -2;

        //Try to find cached location
        auto loc_it = uniform_locations_.find(name);

        //If the location wasn't found, insert it
        if(loc_it == uniform_locations_.cend())
        {
            location = glCheck(glGetUniformLocation(program_, name.c_str()));
            uniform_locations_.insert(std::make_pair(name, location));
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

