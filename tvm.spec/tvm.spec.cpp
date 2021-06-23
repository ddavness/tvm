#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdio>

#ifdef _WIN32
    #include <windows.h>
#endif

int main(int argc, char** argv) {
    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    return ctx.run();
}
