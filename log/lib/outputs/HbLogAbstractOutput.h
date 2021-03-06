#ifndef HBLOGABSTRACTOUTPUT_H
#define HBLOGABSTRACTOUTPUT_H

/*! \file HbLogAbstractOutput.h */

// Hb
#include <HbLog.h>
#include <core/HbUid.h>
// Local

namespace hb {
namespace log {
/*!
 * TODOC.
 */
class HbLogAbstractOutput : public QObject, public HbUid<CLASS_LOG> {
    Q_DISABLE_COPY(HbLogAbstractOutput)
    friend class HbLoggerPool;

public:
    HbLogAbstractOutput(QObject* parent = nullptr);
    virtual ~HbLogAbstractOutput() = default;

protected:
    virtual void init() = 0;
    virtual void processMessage(const HbLogMessagePtr& message) = 0;
};
} // namespace log
} // namespace hb

#endif // HBLOGABSTRACTOUTPUT_H
