// Qt
#include <QtCore/QDateTime>
#include <QtCore/QDir>
// Hb
#include <outputs/HbLogFileOutput.h>
#include <HbLogMessage.h>


using namespace hb::log;


HbLogFileOutput::HbLogFileOutput( const QString & path, quint32 max_size, HbLogger::Levels level ) :
    HbLogAbstractOutput( HbLogAbstractOutput::OUTPUTmFile, level )
{
    QString filename = QDateTime::currentDateTime().toString( QStringLiteral( "yyyy-MM-dd_hh-mm" ) );
	mMaxSize = max_size;
    quint32 instance = 0;

    do mFile.setFileName( QStringLiteral( "%1/%2%3.log" ).arg( path ).arg( filename ).arg( instance++ ) );
    while( mFile.exists() );

    if( !QDir( path ).exists() )
        QDir().mkdir( path );

    if( !mFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "HbLogFileOutput: Error while opening file \"%s\": %s", 
			HbLatin1(mFile.fileName()), HbLatin1(mFile.errorString()));
    }

    mStream.setDevice( &mFile );
}

HbLogFileOutput::~HbLogFileOutput()
{
	mFile.flush();
    mFile.close();
}


bool HbLogFileOutput::isValid() const
{
    return mFile.isOpen();
}


const QString & HbLogFileOutput::fieldSeparator()
{
    static QString separator = QStringLiteral( "###" );
    return separator;
}


void HbLogFileOutput::processMessage( const HbLogMessage & message )
{
    if( mFile.isWritable() )
    {
        mStream << message.level() << fieldSeparator()
                << message.timeTag() << fieldSeparator()
                << message.context().owner() << fieldSeparator()
                << message.context().line() << fieldSeparator()
                << message.context().file() << fieldSeparator()
                << message.context().function() << fieldSeparator()
                << message.message() << QChar( QChar::LineFeed );
    }
}
