#pragma once

#if defined(__linux__)
    #define ION_PLATFORM_LINUX
#elif defined(_WIN32)
    #define ION_PLATFORM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
#else
    #error "Unsupported platform."
#endif