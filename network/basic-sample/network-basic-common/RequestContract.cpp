// Local
#include <Protocol.h>
#include <RequestContract.h>

using namespace hb::network;
using namespace hb::networkexample;

RequestContract::RequestContract() : HbNetworkContract(Protocol::SERVICE_QUESTION, Protocol::CODE_CLT_REQUEST) {
    mRequest = "";
    mReply = new ResponseContract();
}

RequestContract::RequestContract(const RequestContract& source) : HbNetworkContract(source) {
    if (&source != this) {
        mRequest = source.mRequest;
    }
}

RequestContract& RequestContract::operator=(const RequestContract& source) {
    if (&source != this) {
        HbNetworkContract::operator=(source);

        mRequest = source.mRequest;
    }

    return (*this);
}

RequestContract* RequestContract::create() const {
    return new RequestContract();
}

ResponseContract* RequestContract::takeReply() const {
    return HbNetworkContract::takeReply()->value<ResponseContract>();
}

QString RequestContract::toString() const {
    return QString("%1,request=%2").arg(HbNetworkContract::toString()).arg(mRequest);
}

bool RequestContract::read(QDataStream& stream) {
    stream >> mRequest;

    return true;
}

bool RequestContract::write(QDataStream& stream) const {
    stream << mRequest;

    return true;
}

void RequestContract::setRequest(const QString& request) {
    mRequest = request;
}

const QString& RequestContract::request() const {
    return mRequest;
}
