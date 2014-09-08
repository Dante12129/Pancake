//File adapted from SFML source code, https://github.com/LaurentGomila/SFML

#ifndef GLCHECK_HPP
#define GLCHECK_HPP

#include <string>

namespace pcke
{
    #ifdef PCKE_DEBUG

        // In debug mode, perform a test on every OpenGL call
        #define glCheck(x) x; pcke::glCheckError(__FILE__, __LINE__);

    #else

        // Else, we don't add any overhead
        #define glCheck(call) (call)

    #endif

    void glCheckError(const char* file, unsigned int line);
} // namespace pcke

#endif //GLCHECK_HPP
