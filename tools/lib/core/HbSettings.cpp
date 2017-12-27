// Qt
#include <QtCore/QCoreApplication>
// Local
#include <core/HbSettings.h>

using namespace hb::tools;

QSettings::Scope HbSettings::msScope = QSettings::UserScope;
QSettings::Format HbSettings::msFormat = QSettings::IniFormat;

HbSettings::HbSettings( QObject * parent ) :
    QObject( parent ),
    mIsValid( true ),
    mSettings( msFormat, msScope, QCoreApplication::organizationName(), QCoreApplication::applicationName() )
{
    // Empty application name is not required as useful for cross-applications development.
    if( mSettings.organizationName().isEmpty() ||
        !mSettings.isWritable() )
    {
        mIsValid = false;
    }
}

bool HbSettings::write( const QString key, const QVariant & data )
{
    if( !mIsValid ) return false;

    mSettings.setValue( key, data );
    mSettings.sync();

    return true;
}

QVariant HbSettings::read( const QString & key )
{
    if( !mIsValid ) return QVariant();

    return mSettings.value( key );
}

void HbSettings::remove( const QString & key )
{
    mSettings.remove( key );
}

void HbSettings::init( QSettings::Scope scope, QSettings::Format format )
{
    HbSettings::msScope = scope;
    HbSettings::msFormat = format;
}
