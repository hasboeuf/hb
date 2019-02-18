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

    virtual const QString& request() const;
    virtual void setRequest(const QString& request);

protected:
    virtual RequestContract* create() const override;

    QString mRequest;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::RequestContract;

#endif // REQUESTCONTRACT_H
