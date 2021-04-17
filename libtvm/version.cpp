#include "win32-dll.h"

#include "version.hpp"
#include <string>

using std::string;
using std::to_string;

PUB int16_t tvm::version_major() {
    return TVM_VERSION_MAJOR;
}

PUB int16_t tvm::version_minor() {
    return TVM_VERSION_MINOR;
}

PUB int16_t tvm::version_patch() {
    return TVM_VERSION_PATCH;
}

PUB string tvm::version() {
    return to_string(TVM_VERSION_MAJOR) + '.' + to_string(TVM_VERSION_MINOR) + '.' + to_string(TVM_VERSION_PATCH);
}
