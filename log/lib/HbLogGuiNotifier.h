#ifndef HBLOGGUINOTIFIER_H
#define HBLOGGUINOTIFIER_H

/*! \file HbLogGuiNotifier.h */

// Qt
#include <QtCore/QObject>
// Hb
#include <HbLog.h>

namespace hb {
namespace log {

class HbLogMessage;

/*!
 * HbLogGuiNotifier is needed to add a gui output.
 * It is the middleman between HbLog and user class.
 * TODOC.
 */
class HB_LOG_DECL HbLogGuiNotifier : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogGuiNotifier)
    friend class HbLogGuiOutput;

public:
    HbLogGuiNotifier(QObject* parent = nullptr);
    virtual ~HbLogGuiNotifier() = default;

signals:
    void newLogMessage(const HbLogMessagePtr& message);
};
} // namespace log
} // namespace hb

#endif // HBLOGGUINOTIFIER_H
