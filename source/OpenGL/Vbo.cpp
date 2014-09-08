#include "include/Pancake/OpenGL/Vbo.hpp"

#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    VBO::VBO(Type type) : type(toGL(type))
    {
        glCheck(glGenBuffers(1, &vbo));
    }
    VBO::~VBO()
    {
        glCheck(glDeleteBuffers(1, &vbo));
    }

    void VBO::setData(GLsizeiptr size, void* data, GLenum usage)
    {
        bind();
        glCheck(glBufferData(type, size, data, usage));
        unbind();
    }
    void VBO::updateData(GLintptr offset, GLsizeiptr size, void* data)
    {
        bind();
        glCheck(glBufferSubData(type, offset, size, data));
        unbind();
    }

    void VBO::bind()
    {
        glCheck(glBindBuffer(type, vbo));
    }
    void VBO::unbind()
    {
        glCheck(glBindBuffer(type, 0));
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
