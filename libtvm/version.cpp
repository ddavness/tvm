#include "libtvm/version.hpp"

#include <unicode/uchar.h>
#include <array>
#include <string>

using std::string;
using std::to_string;

int16_t tvm::version_major() {
    return TVM_VERSION_MAJOR;
}

int16_t tvm::version_minor() {
    return TVM_VERSION_MINOR;
}

int16_t tvm::version_patch() {
    return TVM_VERSION_PATCH;
}

string tvm::version() {
    return to_string(TVM_VERSION_MAJOR) + '.' + to_string(TVM_VERSION_MINOR) + '.' + to_string(TVM_VERSION_PATCH);
}

string tvm::unicode_version() {
    UVersionInfo v;
    std::array<char, U_MAX_VERSION_STRING_LENGTH> vcstr = {};
    u_getUnicodeVersion(static_cast<uint8_t*>(v));
    u_versionToString(static_cast<uint8_t*>(v), vcstr.data());

    return {vcstr.data()};
}
