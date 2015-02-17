// Qt
#include <QtCore/QDateTime>
#include <QtCore/QDir>
// Hb
#include <outputs/HbLogFileOutput.h>
#include <HbLogMessage.h>


using namespace hb::log;

const quint32 HbLogFileOutput::msMaxFileSize = 100000000; // 100 Mo.
const QString HbLogFileOutput::msDefaultPath = "log";

HbLogFileOutput::HbLogFileOutput( const QString & path, quint32 max_size, HbLogger::Levels level ) :
    HbLogAbstractOutput( HbLogAbstractOutput::OUTPUT_FILE, level )
{
    mPath = ( path.isEmpty() ? msDefaultPath : path );

    max_size *= 1000000; // To bytes.
    mMaxSize = ( ( max_size > msMaxFileSize ) ? msMaxFileSize : max_size );
    if( max_size == 0)
    {
        mMaxSize = msMaxFileSize;
    }

    createLogFile();
}

HbLogFileOutput::~HbLogFileOutput()
{
    closeLogFile();
}

bool HbLogFileOutput::isValid() const
{
    return mFile.isOpen();
}

void HbLogFileOutput::closeLogFile()
{
    mStream.setDevice( 0 );
    if(mFile.isOpen())
    {
        mFile.flush();
        mFile.close();
    }
}

void HbLogFileOutput::createLogFile()
{
    closeLogFile();

    QString filename = QDateTime::currentDateTime().toString( QStringLiteral( "yyyy-MM-dd_hh-mm-ss-zzz" ) );
    QString filepath = QStringLiteral( "%1/%2.log" ).arg( mPath ).arg( filename );

    mFile.setFileName( filepath );

    if( !QDir( mPath ).exists() )
    {
        QDir().mkdir( mPath );
    }

    if( !mFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "HbLogFileOutput: Error while opening file \"%s\": %s",
            HbLatin1(mFile.fileName()), HbLatin1(mFile.errorString()));
    }

    mStream.setDevice( &mFile );
}

void HbLogFileOutput::processMessage( const HbLogMessage & message )
{
    if( mFile.size() >= mMaxSize)
    {
        createLogFile();
    }

    if( mFile.isWritable() )
    {
        mStream << HbLogMessage::toRaw( message ) << QChar( QChar::LineFeed );
        mStream.flush();
    }
}
