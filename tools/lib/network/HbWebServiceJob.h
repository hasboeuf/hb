/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBWEBSERVICEJOB_H
#define HBWEBSERVICEJOB_H

/*! \file HbWebServiceJob.h */

// Qt
#include <QtCore/QEventLoop>
#include <QtCore/QObject>
// Local
#include <HbTools.h>
#include <network/HbWebServiceResult.h>

namespace hb {
namespace tools {
/*!
 * Object representing a request created by HbWebServiceController
 * Its an abstract layer on top of QNetworkReply allowing to hide retries and cancelling complexity.
 */
class HB_TOOLS_DECL HbWebServiceJob : public QObject {
    Q_OBJECT
    friend HbWebServiceController;

public:
    void cancel();
    bool waitForFinished(int timeout = 30000);
    HbWebServiceResult result() const;

signals:
    void cancelRequested();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void finished(const HbWebServiceResult& result);

protected:
    HbWebServiceJob(QObject* parent = nullptr);
    void setResult(const HbWebServiceResult& result);

private:
    bool mCancelling = false;
    HbWebServiceResult mResult;
    QEventLoop mEventLoop;
};
} // namespace tools
} // namespace hb

#endif // HBWEBSERVICEJOB_H
