/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLINKCONSTANT_H
#define HBLINKCONSTANT_H

/*! \file HbLinkConstant.h
 * This file contains all needed constants to correctly implement OAuth protocol.
 */

#include <QtCore/QString>

// General
const QString ENRICHED_URI_BASE    = QStringLiteral( "http://localhost/?" );
const QString REDIRECT_URI         = QStringLiteral( "http://localhost:%1/" );

// Request
const QString OAUTH2_RESPONSE_TYPE = QStringLiteral( "response_type" );
const QString OAUTH2_CLIENT_ID     = QStringLiteral( "client_id" );
const QString OAUTH2_CLIENT_SECRET = QStringLiteral( "client_secret" );
const QString OAUTH2_REDIRECT_URI  = QStringLiteral( "redirect_uri" );
const QString OAUTH2_SCOPE         = QStringLiteral( "scope" );
const QString OAUTH2_CODE          = QStringLiteral( "code" );
const QString OAUTH2_TOKEN         = QStringLiteral( "token" );
const QString OAUTH2_GRANT_TYPE    = QStringLiteral( "grant_type" );

const QString OAUTH2_GRANT_CODE    = QStringLiteral( "code" );

// Reply
const QString OAUTH2_ACCESS_TOKEN  = QStringLiteral( "access_token" );
const QString OAUTH2_REFRESH_TOKEN = QStringLiteral( "refresh_token" );
const QString OAUTH2_EXPIRES_IN    = QStringLiteral( "expires_in" );

// Facebook
// reply
const QString FB_INPUT_TOKEN          = QStringLiteral( "input_token" );
const QString FB_TOKEN                = QStringLiteral( "access_token" );
const QString FB_EXPIRES_IN           = QStringLiteral( "expires" );
// permissions
const QString FB_PERMISSION_EMAIL     = QStringLiteral( "email" );
const QString FB_PERMISSION_FRIENDS   = QStringLiteral( "user_friends" );
// object
const QString FB_OBJECT_ID            = QStringLiteral( "id" );
// user
const QString FB_USER_FIRST_NAME      = QStringLiteral( "first_name" );
const QString FB_USER_LAST_NAME       = QStringLiteral( "last_name" );
const QString FB_USER_LINK            = QStringLiteral( "link" );
const QString FB_USER_EMAIL           = QStringLiteral( "email" );
const QString FB_USER_GENDER          = QStringLiteral( "gender" );
const QString FB_USER_LOCALE          = QStringLiteral( "locale" );
const QString FB_USER_VERIFIED        = QStringLiteral( "verified" );
const QString FB_USER_TIMEZONE        = QStringLiteral( "timezone" );

#endif // HBLINKCONSTANT_H
