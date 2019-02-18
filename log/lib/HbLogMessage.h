#ifndef HBLOGMESSAGE_H
#define HBLOGMESSAGE_H

/*! \file HbLogMessage.h */

// Hb
#include <HbLogContext.h>

namespace hb {
namespace log {
/*!
 * HbLogMessage class defines a log message.
 * TODOC.
 */
class HB_LOG_DECL HbLogMessage {
    Q_GADGET
public:
    enum Output {
        OUTPUT_NONE = 0,
        OUTPUT_LEVEL = 1 << 0,
        OUTPUT_TIME = 1 << 1,
        OUTPUT_APP = 1 << 2,
        OUTPUT_FILE = 1 << 3,
        OUTPUT_FUNCTION = 1 << 4,
        OUTPUT_LINE = 1 << 5,
        OUTPUT_MESSAGE = 1 << 6,
        OUTPUT_ALL =
            OUTPUT_LEVEL | OUTPUT_TIME | OUTPUT_APP | OUTPUT_FILE | OUTPUT_FUNCTION | OUTPUT_LINE | OUTPUT_MESSAGE
    };
    Q_ENUM(Output)
    HB_ENUM(Output)
    Q_DECLARE_FLAGS(Outputs, Output)

    static const QString msFieldSeparator;
    static const HbLogMessage* fromRaw(const QString& raw); //!< Use for export.
    static QString toRaw(const HbLogMessage& msg);          //!< Use for import.
    static void setPattern(const QString& format);

    HbLogMessage();
    HbLogMessage(HbLogger::Level level, const HbLogContext& context, qint64 timestamp, const QString& message);
    virtual ~HbLogMessage();

    HbLogger::Level level() const;
    QString levelStr(bool spacing = true) const;
    HbLogContext context() const;

    qint64 timestamp() const;
    QString timestampStr() const;
    QString message() const;

    QString toString() const;

    QByteArray toByteArray() const;
    void fromDataStream(QDataStream& stream);

    static QString msPattern;
    static Outputs msOutputs;

    HbLogger::Level mLevel;
    HbLogContext mContext;

    qint64 mTimestamp = 0;
    QString mMessage;
};

using HbLogMessagePtr = QSharedPointer<HbLogMessage>;
} // namespace log
} // namespace hb

Q_DECLARE_METATYPE(hb::log::HbLogMessage)

#endif // HBLOGMESSAGE_H
