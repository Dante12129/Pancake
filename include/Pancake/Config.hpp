#ifndef CONFIG_HPP
#define CONFIG_HPP

//Platform Detection
#if defined(_WIN32) //Check for Windows

    #define PANCAKE_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX //To make sure we don't get name conflicts with Windows things
    #endif

#elif defined(__linux__) //Check for Linux

    #define PANCAKE_LINUX

#elif
    #error Operating system not supported

#endif //Platform detection

#endif // CONFIG_HPP

