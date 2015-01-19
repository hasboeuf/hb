// Local
#include <contract/HbConnectionContract.h>

HbConnectionContract::HbConnectionContract() :
    HbNetworkContract( SERVICE_AUTH, CODE_CONNECTION_REQUEST )
{

}

bool HbConnectionContract::read( QDataStream & stream )
{
    stream >> mUsername;
    stream >> mPassword;

    return true;
}

bool HbConnectionContract::write( QDataStream & stream ) const
{
    stream << mUsername;
    stream << mPassword;

    return true;
}

QString HbConnectionContract::username() const
{
    return mUsername;
}

QString HbConnectionContract::passwork() const
{
    return mPassword;
}

void HbConnectionContract::setUsername( QString username )
{
    mUsername = username;
}

void HbConnectionContract::setPassword( QString password )
{
    mPassword = password;
}



