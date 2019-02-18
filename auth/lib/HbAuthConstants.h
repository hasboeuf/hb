#ifndef HBAUTHCONSTANTS_H
#define HBAUTHCONSTANTS_H

#include <QtCore/QString>

struct AuthKeys {
    const QString accessToken = QStringLiteral("access_token");
    const QString apiKey = QStringLiteral("api_key");
    const QString clientIdentifier = QStringLiteral("client_id");
    const QString clientSharedSecret = QStringLiteral("client_secret");
    const QString code = QStringLiteral("code");
    const QString error = QStringLiteral("error");
    const QString errorDescription = QStringLiteral("error_description");
    const QString errorUri = QStringLiteral("error_uri");
    const QString expiresIn = QStringLiteral("expires_in");
    const QString grantType = QStringLiteral("grant_type");
    const QString redirectUri = QStringLiteral("redirect_uri");
    const QString refreshToken = QStringLiteral("refresh_token");
    const QString responseType = QStringLiteral("response_type");
    const QString scope = QStringLiteral("scope");
    const QString state = QStringLiteral("state");
    const QString tokenType = QStringLiteral("token_type");
};

struct FacebookScope {
    const QString email = QStringLiteral("email");
    const QString friends = QStringLiteral("user_friends");
};

struct GoogleScope {
    const QString email = QStringLiteral("email");
    const QString profile = QStringLiteral("profile");
};

struct FacebookObject {
    // request
    const QString field = QStringLiteral("fields");
    const QString proof = QStringLiteral("appsecret_proof");
    // object
    const QString id = QStringLiteral("id");
    const QString error = QStringLiteral("error");
    const QString errorCode = QStringLiteral("code");
    const QString errorMessage = QStringLiteral("message");
    // user
    const QString firstName = QStringLiteral("first_name");
    const QString lastName = QStringLiteral("last_name");
    const QString link = QStringLiteral("link");
    const QString email = QStringLiteral("email");
    const QString gender = QStringLiteral("gender");
    const QString locale = QStringLiteral("locale");
    const QString verified = QStringLiteral("verified");
    const QString timezone = QStringLiteral("timezone");
};

struct GoogleObject {
    // object
    const QString id = QStringLiteral("id");
    const QString error = QStringLiteral("error");
    const QString errorCode = QStringLiteral("code");
    const QString errorMessage = QStringLiteral("message");
    // user
    const QString firstName = QStringLiteral("given_name");
    const QString lastName = QStringLiteral("family_name");
    const QString link = QStringLiteral("link");
    const QString email = QStringLiteral("email");
    const QString gender = QStringLiteral("gender");
    const QString locale = QStringLiteral("locale");
    const QString verified = QStringLiteral("verified_email");
    const QString picture = QStringLiteral("picture");
};

#endif // HBAUTHCONSTANTS_H
