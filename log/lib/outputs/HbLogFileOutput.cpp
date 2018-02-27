// Qt
#include <QtCore/QDateTime>
#include <QtCore/QDir>
// Hb
#include <outputs/HbLogFileOutput.h>
#include <HbLogMessage.h>


using namespace hb::log;

const quint32 HbLogFileOutput::msMaxFileSize = 100000000; // 100 Mo.
const QString HbLogFileOutput::msDefaultPath = "log";

HbLogFileOutput::HbLogFileOutput( const QString & path, quint32 maxSize, QObject * parent ) :
    HbLogAbstractOutput( parent )
{
    mPath = ( path.isEmpty() ? msDefaultPath : path );

    maxSize *= 1000000; // To bytes.
    mMaxSize = ( ( maxSize > msMaxFileSize ) ? msMaxFileSize : maxSize );
    if( maxSize == 0)
    {
        mMaxSize = msMaxFileSize;
    }
}

HbLogFileOutput::~HbLogFileOutput()
{
    closeLogFile();
}

void HbLogFileOutput::init()
{
    mFile.reset( new QFile() );
    mStream.reset( new QTextStream() );
    createLogFile();
}

void HbLogFileOutput::closeLogFile()
{
    mStream->setDevice( 0 );
    if( mFile->isOpen() )
    {
        mFile->flush();
        mFile->close();
    }
}

void HbLogFileOutput::createLogFile()
{
    closeLogFile();

    QString filename = QDateTime::currentDateTime().toString( QStringLiteral( "yyyy-MM-dd_hh-mm-ss-zzz" ) );
    QString filepath = QStringLiteral( "%1/%2.log" ).arg( mPath ).arg( filename );

    mFile->setFileName( filepath );

    if( !QDir( mPath ).exists() )
    {
        QDir().mkdir( mPath );
    }

    if( !mFile->open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        // TODO remove qdebug
        qDebug( "HbLogFileOutput: Error while opening file \"%s\": %s",
                HbLatin1( mFile->fileName() ), HbLatin1( mFile->errorString() ) );
    }

    mStream->setDevice( mFile.data() );
}

void HbLogFileOutput::processMessage( const HbLogMessage & message )
{
    if( mFile->size() >= mMaxSize)
    {
        createLogFile();
    }

    if( mFile->isWritable() )
    {
        (* mStream.data()) << HbLogMessage::toRaw( message ) << QChar( QChar::LineFeed );
        mStream->flush();
    }
}
