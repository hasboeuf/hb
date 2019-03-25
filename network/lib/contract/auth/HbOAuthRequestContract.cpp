// Local
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbOAuthRequestContract::HbOAuthRequestContract() : HbAuthRequestContract() {
}

HbOAuthRequestContract::HbOAuthRequestContract(const HbOAuthRequestContract& source) : HbAuthRequestContract(source) {
    if (&source != this) {
        mCode = source.mCode;
        mRedirectUri = source.mRedirectUri;
    }
}

HbOAuthRequestContract& HbOAuthRequestContract::operator=(const HbOAuthRequestContract& source) {
    if (&source != this) {
        HbAuthRequestContract::operator=(source);

        mCode = source.mCode;
        mRedirectUri = source.mRedirectUri;
    }

    return (*this);
}

HbOAuthRequestContract* HbOAuthRequestContract::create() const {
    return new HbOAuthRequestContract();
}

bool HbOAuthRequestContract::read(QDataStream& stream) {
    HbAuthRequestContract::read(stream);
    stream >> mCode;
    stream >> mRedirectUri;

    return true;
}

bool HbOAuthRequestContract::write(QDataStream& stream) const {
    HbAuthRequestContract::write(stream);
    stream << mCode;
    stream << mRedirectUri;

    return true;
}

QString HbOAuthRequestContract::code() const {
    return mCode;
}

QString HbOAuthRequestContract::redirectUri() const {
    return mRedirectUri;
}

void HbOAuthRequestContract::setCode(const QString& code) {
    mCode = code;
}

void HbOAuthRequestContract::setRedirectUri(const QString& redirect_uri) {
    mRedirectUri = redirect_uri;
}
