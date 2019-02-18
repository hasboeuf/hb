#ifndef HBLOGLOCALSOCKETOUTPUT_H
#define HBLOGLOCALSOCKETOUTPUT_H

/*! \file HbLogLocalSocketOutput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <outputs/HbLogAbstractOutput.h>

class QLocalSocket;

namespace hb {
namespace log {
/*!
 * TODOC
 * \brief The %HbLogLocalSocketOutput class defines a local socket output.
 *
 * %HbLogLocalSocketOutput inherits from HbLogAbstractOutput.\n
 */
class HbLogLocalSocketOutput : public HbLogAbstractOutput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogLocalSocketOutput)

public:
    HbLogLocalSocketOutput(const QString& name = QString(), QObject* parent = nullptr);
    virtual ~HbLogLocalSocketOutput();

    const QString& name() const;

private:
    void processMessage(const HbLogMessagePtr& message) override;
    void init() override;

    void onReconnection();

    QString mName;
    QScopedPointer<QLocalSocket> mLocalSocket;
};
} // namespace log
} // namespace hb

#endif
