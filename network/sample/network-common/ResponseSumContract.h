/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef RESPONSESUMCONTRACT_H
#define RESPONSESUMCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local

namespace hb {
namespace networkexample {

class ResponseSumContract : public HbNetworkContract {
public:
    ResponseSumContract();
    virtual ~ResponseSumContract() = default;
    ResponseSumContract(const ResponseSumContract& source);
    ResponseSumContract& operator=(const ResponseSumContract& source);

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual qint32 result() const final;
    virtual void setResult(qint32 result) final;

protected:
    virtual ResponseSumContract* create() const override;

protected:
    qint32 mResult;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::ResponseSumContract;

#endif // RESPONSESUMCONTRACT_H
