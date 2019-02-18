#ifndef HBTIMEOUTNETWORKREPLIES_H
#define HBTIMEOUTNETWORKREPLIES_H

/*! \file HbTimeoutNetworkReplies.h */

// Qt
#include <QtCore/QList>
#include <QtCore/QObject>
// Local
#include <HbTools.h>
#include <network/HbTimeoutNetworkReply.h>

namespace hb {
namespace tools {
/*!
 * HbTimeoutNetworkReplies manage multiple HbTimeoutNetworkReply.
 * \sa HbTimeoutNetworkReply
 */
class HB_TOOLS_DECL HbTimeoutNetworkReplies : public QObject {
    Q_OBJECT

public:
    HbTimeoutNetworkReplies(QObject* parent = nullptr);
    virtual ~HbTimeoutNetworkReplies();

    quint64 add(QNetworkReply* reply, quint32 timeout = HbTimeoutNetworkReply::msDefaultTimeout);

    void remove(QNetworkReply* reply);

    quint64 id(QNetworkReply* reply) const;

    void onFinished();

private:
    QHash<QNetworkReply*, quint64> mReplies;
};
} // namespace tools
} // namespace hb

using hb::tools::HbTimeoutNetworkReplies;

#endif // HBTIMEOUTNETWORKREPLIES_H
