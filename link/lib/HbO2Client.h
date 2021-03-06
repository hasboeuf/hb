#ifndef HBO2CLIENT_H
#define HBO2CLIENT_H

/*! \file HbO2Client.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbLinkLocalServer.h>
#include <HbO2.h>
#include <config/HbO2ClientConfig.h>

namespace hb {
namespace link {

/*!
 * HbO2Client provides client side authentication flow.
 * Abstract class.
 */
class HB_LINK_DECL HbO2Client : public HbO2 {
    Q_OBJECT

public:
    HbO2Client() = default;
    virtual ~HbO2Client() = default;

    virtual bool isValid() const override;

    virtual bool link() override;

    /*!
     * Return config.
     * \return Config.
     */
    virtual HbO2ClientConfig& config();
    /*!
     * Return const config.
     * \return Const config.
     */
    virtual const HbO2ClientConfig& config() const;

    /*!
     * Fired when auth code is received.
     * \param response_parameters Response parameters.
     */
    void onCodeResponseReceived(const QHash<QString, QString> response_parameters);

signals:
    /*!
     * Triggered during linking phase when user should give its approval on a web page.
     * Open default web browser.
     * \param url URL to open.
     */
    void openBrowser(const QUrl& url);

    /*!
     * Triggered when linking phase is done.
     * User can close its browser.
     */
    void closeBrowser();

protected:
    virtual const QHash<QString, QString> codeRequest() const = 0;
    virtual LinkStatus codeResponse(const QHash<QString, QString>& response) = 0;

    HbO2ClientConfig mConfig;

private:
    HbLinkLocalServer mReplyServer;
};
} // namespace link
} // namespace hb

using hb::link::HbO2Client;

#endif // HBO2CLIENT_H
