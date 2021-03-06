#ifndef REQUESTSUMCONTRACT_H
#define REQUESTSUMCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local
#include <ResponseSumContract.h> // Covariance

namespace hb {
namespace networkexample {

class RequestSumContract : public HbNetworkContract {
public:
    RequestSumContract();
    virtual ~RequestSumContract() = default;
    RequestSumContract(const RequestSumContract& source);
    RequestSumContract& operator=(const RequestSumContract& source);

    virtual ResponseSumContract* takeReply() const;

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual qint32 intA() const;
    virtual void setIntA(qint32 a);

    virtual qint32 intB() const;
    virtual void setIntB(qint32 b);

protected:
    virtual RequestSumContract* create() const override;

    qint32 mIntA;
    qint32 mIntB;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::RequestSumContract;

#endif // REQUESTSUMCONTRACT_H
