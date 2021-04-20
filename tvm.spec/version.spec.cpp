#include <string>
#include <catch2/catch.hpp>

#include "libtvm/version.hpp"

using std::string;

SCENARIO("Versions are outputted correctly", "[version]") {
    WHEN("Each version component is requested") {
        int16_t M = tvm::version_major();
        int16_t m = tvm::version_minor();
        int16_t p = tvm::version_patch();

        THEN("It is equal to the current version as in the CMake file") {
            REQUIRE(M == 0);
            REQUIRE(m == 0);
            REQUIRE(p == 1);
        }
    }
    WHEN("The version string is requested") {
        string v = tvm::version();

        THEN("It is equal to the current version as in the CMake file") {
            REQUIRE(v == "0.0.1");
        }
    }
}
