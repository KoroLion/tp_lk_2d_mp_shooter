#ifndef SRC_INCLUDE_UTILS_HPP_
#define SRC_INCLUDE_UTILS_HPP_

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif  // _WIN32

void sleep_ms(int ms);

void sleep_ms(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif  // _WIN32
}

#endif  // SRC_INCLUDE_UTILS_HPP_
