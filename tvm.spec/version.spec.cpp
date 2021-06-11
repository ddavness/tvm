#include "libtvm/version.hpp"

#include <doctest/doctest.h>
#include <unicode/uchar.h>
#include <string>

#define MACRO_EXP(x) #x
#define MSTR(x) MACRO_EXP(x)

using std::string;

TEST_SUITE("Library versioning") {
    TEST_CASE("Version components are equal to those specified in the CMake file") {
        int16_t M = tvm::version_major();
        int16_t m = tvm::version_minor();
        int16_t p = tvm::version_patch();

        CHECK(M == TVM_VERSION_MAJOR);
        CHECK(m == TVM_VERSION_MINOR);
        CHECK(p == TVM_VERSION_PATCH);
    }
    TEST_CASE("The version string is equal to the one specified in the CMake file") {
        CHECK(tvm::version() == (MSTR(TVM_VERSION_MAJOR) "." MSTR(TVM_VERSION_MINOR) "." MSTR(TVM_VERSION_PATCH)));
    }
    TEST_CASE("Unicode version is equal to the one exported by ICU") {
        CHECK(tvm::unicode_version() == U_UNICODE_VERSION);
    }
}
