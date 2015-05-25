#include "include/Pancake/Graphics/BufferObject.hpp"

namespace pcke
{
    BufferObject::BufferObject(Type type) : type_(toGL(type))
    {
        glCheck(glGenBuffers(1, &buffer_));
    }
    BufferObject::~BufferObject()
    {
        glCheck(glDeleteBuffers(1, &buffer_));
    }

    void BufferObject::setData(GLsizeiptr size, void* data, GLenum usage)
    {
        bind();
        glCheck(glBufferData(type_, size, data, usage));
        unbind();
    }
    void BufferObject::updateData(GLintptr offset, GLsizeiptr size, void* data)
    {
        bind();
        glCheck(glBufferSubData(type_, offset, size, data));
        unbind();
    }

    void BufferObject::bind() const
    {
        glCheck(glBindBuffer(type_, buffer_));
    }
    void BufferObject::unbind() const
    {
        glCheck(glBindBuffer(type_, 0));
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
