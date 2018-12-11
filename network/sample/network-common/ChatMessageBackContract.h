/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef CHATMESSAGEBACKCONTRACT_H
#define CHATMESSAGEBACKCONTRACT_H

// Qt
// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
// Local

namespace hb {
namespace networkexample {

class ChatMessageBackContract : public HbNetworkContract {
public:
    ChatMessageBackContract();
    virtual ~ChatMessageBackContract() = default;
    ChatMessageBackContract(const ChatMessageBackContract& source);
    ChatMessageBackContract& operator=(const ChatMessageBackContract& source);

    virtual QString toString() const;

    virtual bool read(QDataStream& stream);
    virtual bool write(QDataStream& stream) const;

    virtual const QString& message() const;
    virtual void setMessage(const QString& message);

    virtual const QString& author() const;
    virtual void setAuthor(const QString& author);

protected:
    virtual ChatMessageBackContract* create() const override;

protected:
    QString mMessage;
    QString mAuthor;
};
} // namespace networkexample
} // namespace hb

using hb::networkexample::ChatMessageBackContract;

#endif // CHATMESSAGEBACKCONTRACT_H
