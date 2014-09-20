#include "include/Pancake/OpenGL/BufferObject.hpp"

#include "source/OpenGL/GLCheck.hpp"

namespace pcke
{
    BufferObject::BufferObject(Type type) : type(toGL(type))
    {
        glCheck(glGenBuffers(1, &buffer));
    }
    BufferObject::~BufferObject()
    {
        glCheck(glDeleteBuffers(1, &buffer));
    }

    void BufferObject::setData(GLsizeiptr size, void* data, GLenum usage)
    {
        bind();
        glCheck(glBufferData(type, size, data, usage));
        unbind();
    }
    void BufferObject::updateData(GLintptr offset, GLsizeiptr size, void* data)
    {
        bind();
        glCheck(glBufferSubData(type, offset, size, data));
        unbind();
    }

    void BufferObject::bind()
    {
        glCheck(glBindBuffer(type, buffer));
    }
    void BufferObject::unbind()
    {
        glCheck(glBindBuffer(type, 0));
    }

    GLenum BufferObject::toGL(Type type)
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
