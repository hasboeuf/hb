/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGOOGLEREQUESTER_H
#define HBGOOGLEREQUESTER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
// Local
#include <HbLink.h>
#include <google/api/HbGoogleObject.h>
#include <network/HbHttpRequester.h>

namespace hb {
namespace link {

class HbO2ServerGoogle;

/*!
 * HbGoogleRequester is a Http requester specific for Google.
 */
class HB_LINK_DECL HbGoogleRequester : public HbHttpRequester {
    Q_OBJECT

    //! \todo hide HbHttpRequester signals.
public:
    HbGoogleRequester();
    virtual ~HbGoogleRequester() = default;

    /*!
     * Return Google user informations.
     * \param auth Linked HbO2ServerGoogle.
     * \return Request uid or 0 if request failed to start.
     * \sa requestCompleted
     */
    quint64 requestUser(HbO2ServerGoogle* auth);

private slots:
    void onRequestFinished(quint64 request_id, const QJsonDocument& doc); //!< From HbHttpRequester
    void onRequestError(quint64 request_id, const QString& error);        //!< From HbHttpRequester

signals:
    /*!
     * Triggered when a Google request gets completed.
     * \param request_id Request uid.
     * \param object Google object or nullptr on failure.
     */
    void requestCompleted(quint64 request_id, HbGoogleObject* object);

private:
    QHash<quint64, HbGoogleObject::ObjectType> mRequestTypes;
};
} // namespace link
} // namespace hb

using hb::link::HbGoogleRequester;

#endif // HBGOOGLEREQUESTER_H
