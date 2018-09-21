/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBFACEBOOKREQUESTER_H
#define HBFACEBOOKREQUESTER_H

/*! \file HbFacebookRequester.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
// Local
#include <HbLink.h>
#include <facebook/api/HbFacebookObject.h>
#include <network/HbHttpRequester.h>

namespace hb {
namespace link {

class HbO2ServerFacebook;

/*!
 * HbFacebookRequester is a Http requester specific for Facebook.
 */
class HB_LINK_DECL HbFacebookRequester : public HbHttpRequester {
    Q_OBJECT

    //! \todo hide HbHttpRequester signals.
public:
    HbFacebookRequester();
    virtual ~HbFacebookRequester() = default;

    /*!
     * Return Facebook user informations.
     * \param auth Linked HbO2ServerFacebook.
     * \return Request uid or 0 if request failed to start.
     * \sa requestCompleted
     */
    quint64 requestUser(HbO2ServerFacebook* auth);

private slots:
    void onRequestFinished(quint64 request_id, const QJsonDocument& doc); //!< From HbHttpRequester
    void onRequestError(quint64 request_id, const QString& error);        //!< From HbHttpRequester

signals:
    /*!
     * Triggered when a Facebook request gets completed.
     * \param request_id Request uid.
     * \param object Facebook object or nullptr on failure.
     */
    void requestCompleted(quint64 request_id, HbFacebookObject* object);

private:
    QHash<quint64, HbFacebookObject::ObjectType> mRequestTypes;
};
} // namespace link
} // namespace hb

using hb::link::HbFacebookRequester;

#endif // HBFACEBOOKREQUESTER_H
