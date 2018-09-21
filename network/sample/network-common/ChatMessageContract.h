/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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

    virtual const QString& message() const final;
    virtual void setMessage(const QString& message) final;

protected:
    virtual ChatMessageContract* create() const override;

protected:
    QString mMessage;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::ChatMessageContract;

#endif // CHATMESSAGECONTRACT_H
