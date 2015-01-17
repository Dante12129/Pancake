#include "include/Pancake/OpenGL/Shader.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    Shader::~Shader()
    {
        if(created_)
            glCheck(glDeleteShader(shader_));
    }

    bool Shader::loadFromFile(const std::string& filename, Type type)
    {
        std::ifstream file(filename);
        if(file.is_open())
        {
            std::string line;
            std::stringstream src;
            while(std::getline(file, line))
            {
                src << line << '\n';
            }
            return create(src.str(), type);
        }
        else
        {
            std::cerr << "Problem opening shader file." << std::endl;
            return false;
        }
    }
    bool Shader::loadFromMemory(const std::string& src, Type type)
    {
        return create(src, type);
    }

    bool Shader::create(const std::string& src, Type type)
    {
        shader_ = glCheck(glCreateShader(static_cast<GLenum>(type)));

        auto c_src = src.c_str();
        glCheck(glShaderSource(shader_, 1, &c_src, 0));
        glCheck(glCompileShader(shader_));

        GLint status;
        glCheck(glGetShaderiv(shader_, GL_COMPILE_STATUS, &status));
        if(status == GL_FALSE)
        {
            GLint log_length;
            glCheck(glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &log_length));

            std::unique_ptr<GLchar[]> log(new GLchar[log_length + 1]);
            glCheck(glGetShaderInfoLog(shader_, log_length, 0, log.get()));

            std::cerr << "Error compiling shader: " << log.get() << std::endl;
            return false;
        }

        created_ = true;
        return true;
    }
}
