#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <Pancake/Graphics/Color.hpp>

namespace pcke
{
    class Vertex
    {
        public:
            glm::vec4 pos_;
            glm::vec2 tex_;
            Color color_;
    };
}

#endif // VERTEX_HPP
