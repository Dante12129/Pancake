#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec4.hpp>

#include "Pancake/Graphics/Color.hpp"

namespace pcke
{
    class Vertex
    {
        public:
            glm::vec4 pos;
            Color color;
    };
}

#endif // VERTEX_HPP
