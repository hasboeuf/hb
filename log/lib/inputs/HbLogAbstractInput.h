#ifndef HBLOGABSTRACTINPUT_H
#define HBLOGABSTRACTINPUT_H

/*! \file HbLogAbstractInput.h */

// Hb
#include <HbLog.h>
#include <core/HbUid.h>
// Local

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC.
 */
class HbLogAbstractInput : public QObject, public HbUid<CLASS_LOG> {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogAbstractInput)
    friend class HbLoggerPool;

public:
    HbLogAbstractInput(QObject* parent = nullptr);
    virtual ~HbLogAbstractInput() = default;

signals:
    void inputMessageReceived(HbLogMessage* message);

protected:
    virtual void init() = 0;
};
} // namespace log
} // namespace hb

#endif // HBLOGABSTRACTINPUT_H
