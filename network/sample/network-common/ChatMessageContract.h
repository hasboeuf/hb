#ifndef CHATMESSAGECONTRACT_H
#define CHATMESSAGECONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local

namespace hb {
namespace networkexample {

class ChatMessageContract : public HbNetworkContract {
public:
    ChatMessageContract();
    virtual ~ChatMessageContract() = default;
    ChatMessageContract(const ChatMessageContract& source);
    ChatMessageContract& operator=(const ChatMessageContract& source);

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual const QString& message() const;
    virtual void setMessage(const QString& message);

protected:
    virtual ChatMessageContract* create() const override;

    QString mMessage;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::ChatMessageContract;

#endif // CHATMESSAGECONTRACT_H
