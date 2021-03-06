#ifndef MESSAGECONTRACT_H
#define MESSAGECONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local

namespace hb {
namespace networkexample {

class MessageContract : public HbNetworkContract {
public:
    MessageContract();
    virtual ~MessageContract() = default;
    MessageContract(const MessageContract& source);
    MessageContract& operator=(const MessageContract& source);

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual const QString& message() const;
    virtual void setMessage(const QString& message);

protected:
    virtual MessageContract* create() const override;

    QString mMessage;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::MessageContract;

#endif // MESSAGECONTRACT_H
