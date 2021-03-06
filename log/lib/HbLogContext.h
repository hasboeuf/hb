#ifndef HBLOGCONTEXT_H
#define HBLOGCONTEXT_H

/*! \file HbLogContext.h */

// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogger.h>

namespace hb {
namespace log {
/*!
 * HbLogContext represents the exact place of a log trace in the code.
 * Internal class.
 */
class HB_LOG_DECL HbLogContext {
public:
    HbLogContext();
    virtual ~HbLogContext() = default;
    HbLogContext(const QMessageLogContext& context);

    QString owner() const;
    qint32 thread() const;
    QString file() const;
    qint32 line() const;
    QString function() const;

    void setOwner(const QString& owner);
    void setThread(qint32 thread);
    void setFile(const QString& file);
    void setLine(qint32 line);
    void setFunction(const QString& function);

    void print(QtMsgType type, const QString& message) const;

    friend QDataStream& operator<<(QDataStream& stream, const HbLogContext& context);
    friend QDataStream& operator>>(QDataStream& stream, HbLogContext& context);

private:
    QString mOwner;
    qint32 mThread = 0;
    QString mFile;
    qint32 mLine = 0;
    QString mFunction;

    static QString msApplicationName;
};
} // namespace log
} // namespace hb

using hb::log::HbLogContext;

#endif // HBLOGCONTEXT_H
