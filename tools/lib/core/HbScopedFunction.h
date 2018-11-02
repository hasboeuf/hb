/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
