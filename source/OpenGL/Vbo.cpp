#include "include/Pancake/OpenGL/Vbo.hpp"

namespace pcke
{
    VBO::VBO(Type type) : type(toGL(type))
    {
        glGenBuffers(1, &vbo);
    }
    VBO::~VBO()
    {
        glDeleteBuffers(1, &vbo);
    }

    void VBO::setData(GLsizeiptr size, void* data, GLenum usage)
    {
        bind();
        glBufferData(type, size, data, usage);
        unbind();
    }
    void VBO::updateData(GLintptr offset, GLsizeiptr size, void* data)
    {
        bind();
        glBufferSubData(type, offset, size, data);
        unbind();
    }

    void VBO::bind()
    {
        glBindBuffer(type, vbo);
    }
    void VBO::unbind()
    {
        glBindBuffer(type, 0);
    }

    GLenum VBO::toGL(Type type)
    {
        switch(type)
        {
            case Type::Array:
                return GL_ARRAY_BUFFER;
              break;
            case Type::Index:
                return GL_ELEMENT_ARRAY_BUFFER;
              break;
            case Type::Uniform:
                return GL_UNIFORM_BUFFER;
            break;
            default:
                return 0;
              break;
        }
    }
}
