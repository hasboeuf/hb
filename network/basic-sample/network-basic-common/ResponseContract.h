#ifndef RESPONSECONTRACT_H
#define RESPONSECONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local

namespace hb {
namespace networkexample {

class ResponseContract : public HbNetworkContract {
public:
    ResponseContract();
    virtual ~ResponseContract() = default;
    ResponseContract(const ResponseContract& source);
    ResponseContract& operator=(const ResponseContract& source);

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual const QString& response() const;
    virtual void setResponse(const QString& response);

protected:
    virtual ResponseContract* create() const override;

    QString mResponse;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::ResponseContract;

#endif // RESPONSECONTRACT_H
