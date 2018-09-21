/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef REQUESTCONTRACT_H
#define REQUESTCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local
#include <ResponseContract.h> // Covariance

namespace hb {
namespace networkexample {

class RequestContract : public HbNetworkContract {
public:
    RequestContract();
    virtual ~RequestContract() = default;
    RequestContract(const RequestContract& source);
    RequestContract& operator=(const RequestContract& source);

    virtual ResponseContract* takeReply() const;

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual const QString& request() const final;
    virtual void setRequest(const QString& request) final;

protected:
    virtual RequestContract* create() const override;

protected:
    QString mRequest;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::RequestContract;

#endif // REQUESTCONTRACT_H
