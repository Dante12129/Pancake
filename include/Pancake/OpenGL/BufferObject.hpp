#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP

#include <glload/gl_3_3.h>

namespace pcke
{
    class BufferObject
    {
        public:
            enum class Type
            {
                None,
                Array,
                Index,
                Uniform
            };

        public:
            BufferObject(Type type);
            ~BufferObject();

            void setData(GLsizeiptr size, void* data, GLenum usage);
            void updateData(GLintptr offset, GLsizeiptr size, void* data);

            void bind() const;
            void unbind() const;

        private:
            GLuint buffer;
            GLenum type;

            static GLenum toGL(Type type);
    };
}
#endif // BUFFEROBJECT_HPP
