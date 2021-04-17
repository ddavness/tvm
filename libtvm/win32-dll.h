#pragma once

#ifdef WIN32
    #ifdef __LIBTVM
        #define PUB __declspec(dllexport)
    #else
        #define PUB __declspec(dllimport)
    #endif
#else
    #define PUB
#endif
