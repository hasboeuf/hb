#ifndef HBO2_H
#define HBO2_H

/*! \file HbO2.h */

// Qt
#include <QtCore/QDataStream>
#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Hb
#include <HbGlobal.h>
// Local
#include <HbLink.h>
#include <HbLinkConstant.h>

namespace hb {
namespace link {

/*!
 * HbO2 is the base class used by both client and server side.
 * Used during all the OAuth authentication flow.
 * Server side: master application that federates many client.
 * Client side: light application that connects to the server.
 */
class HB_LINK_DECL HbO2 : public QObject {
    Q_OBJECT

public:
    enum LinkStatus : quint8 { UNLINKED = 0, LINKING, LINKED };

    /*!
     * Retrieve URL data.
     * \param content Enriched URL.
     * \return URL data, key: parameter name, value: associated value.
     */
    static QHash<QString, QString> getUrlItems(const QString& content);

    HbO2(QObject* parent = nullptr);
    virtual ~HbO2() = default;

    /*!
     * Check if link could be done.
     * \return True if valid, false else.
     */
    virtual bool isValid() const;

    /*!
     * Process to the OAuth link phase.
     * \return True on success, false else.
     */
    virtual bool link() = 0;

    /*!
     * Return the last occured error.
     * \return Error string.
     */
    virtual const QString& errorString() const;

    /*!
     * Return the current link status.
     * \return Link status.
     */
    virtual LinkStatus linkStatus() const;

    /*!
     * Return the redirect Uri.
     * \return Redirect Uri.
     */
    virtual const QString& redirectUri() const;

    /*!
     * Return OAuth code.
     * \return Authentication code.
     */
    virtual const QString& code() const;

signals:

    /*!
     * Triggered when the link phase failed.
     * \param error Link error.
     */
    void linkFailed(QString error);
    /*!
     * Triggered when the link phase succeeded.
     */
    void linkSucceed();

protected:
    virtual const QUrl endPoint() const = 0; //!< Target specific.

    LinkStatus mLinkStatus;
    QString mErrorString;
    QString mCode;
    QString mRedirectUri;
};
} // namespace link
} // namespace hb

using hb::link::HbO2;

#endif // HBO2_H
