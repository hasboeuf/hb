#ifndef HBSCOPEDFUNCTION_H
#define HBSCOPEDFUNCTION_H

/*! \file HbScopedFunction.h */

// System
#include <functional>
// Hb
#include <QtCore/QString>
// Local
#include <HbTools.h>

namespace hb {
namespace tools {
/*!
 * HbScopedFunction executes a function at destruction time.
 */
class HB_TOOLS_DECL HbScopedFunction {
public:
    using Callback = std::function<void()>;
    HbScopedFunction(Callback callback);
    ~HbScopedFunction();

private:
    Callback mCallback;
};
} // namespace tools
} // namespace hb

#endif // HBSCOPEDFUNCTION_H
