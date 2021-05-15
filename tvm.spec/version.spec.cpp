#include "libtvm/version.hpp"

#include <catch2/catch.hpp>
#include <unicode/uchar.h>
#include <string>

#define MACRO_EXP(x) #x
#define MSTR(x) MACRO_EXP(x)

using std::string;

SCENARIO("Versions are outputted correctly", "[version]") {
    WHEN("Each version component is requested") {
        int16_t M = tvm::version_major();
        int16_t m = tvm::version_minor();
        int16_t p = tvm::version_patch();

        THEN("It is equal to the current version as in the CMake file") {
            REQUIRE(M == TVM_VERSION_MAJOR);
            REQUIRE(m == TVM_VERSION_MINOR);
            REQUIRE(p == TVM_VERSION_PATCH);
        }
    }
    WHEN("The version string is requested") {
        string v = tvm::version();

        THEN("It is equal to the current version as in the CMake file") {
            REQUIRE(v == (MSTR(TVM_VERSION_MAJOR) "." MSTR(TVM_VERSION_MINOR) "." MSTR(TVM_VERSION_PATCH)));
        }
    }
    WHEN("The unicode version is requested") {
        string uv = tvm::unicode_version();

        THEN("It is equal to the version macro given by ICU") {
            REQUIRE(uv == U_UNICODE_VERSION);
        }
    }
}
