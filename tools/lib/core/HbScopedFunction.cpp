// Local
#include <core/HbScopedFunction.h>

using namespace hb::tools;

HbScopedFunction::HbScopedFunction(Callback callback) {
    mCallback = callback;
}

HbScopedFunction::~HbScopedFunction() {
    mCallback();
}
