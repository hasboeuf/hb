#ifndef HBLOGLOCALSOCKETINPUT_H
#define HBLOGLOCALSOCKETINPUT_H

/*! \file HbLogLocalSocketInput.h */

// Qt
#include <QtCore/QScopedPointer>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <inputs/HbLogAbstractInput.h>

class QLocalSocket;
class QLocalServer;

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC
 * \brief The %HbLogLocalSocketInput class defines a local server input.
 */
class HbLogLocalSocketInput : public HbLogAbstractInput {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogLocalSocketInput)

public:
    HbLogLocalSocketInput(const QString& name = QString(), QObject* parent = nullptr);
    ~HbLogLocalSocketInput() override;

    QString name() const;

protected:
    void init() override;

private:
    void incomingConnection();
    void onReadyRead();
    void onClientDisconnected();

    QString mName;
    qint32 mExpected;
    QScopedPointer<QLocalServer> mLocalServer;
    QSet<QLocalSocket*> mClients;
};
} // namespace log
} // namespace hb

#endif
