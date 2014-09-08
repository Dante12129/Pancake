#ifndef VBO_HPP
#define VBO_HPP

#include <glload/gl_3_3.h>

namespace pcke
{
    class VBO
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
            VBO(Type type);
            ~VBO();

            void setData(GLsizeiptr size, void* data, GLenum usage);
            void updateData(GLintptr offset, GLsizeiptr size, void* data);

            void bind();
            void unbind();

        private:
            GLuint vbo;
            GLenum type;

            static GLenum toGL(Type type);
    };
}
#endif // VBO_HPP
