// Qt
#include <QtCore/QMutex>
// Hb
#include <outputs/HbLogAbstractOutput.h>

using namespace hb::log;


HbLogAbstractOutput::HbLogAbstractOutput( OutputType type, HbLogger::Levels level )
{
	mType = type;
	mLevel = level;

    mpMutex = q_check_ptr( new QMutex() );
}

HbLogAbstractOutput::~HbLogAbstractOutput()
{
    delete mpMutex;
}


HbLogAbstractOutput::OutputType HbLogAbstractOutput::type() const
{
    return mType;
}

bool HbLogAbstractOutput::isValid() const
{
    return true;
}


void HbLogAbstractOutput::setLevel( HbLogger::Levels level )
{
    QMutexLocker locker( mpMutex );
    mLevel = level;
}

HbLogger::Levels HbLogAbstractOutput::level() const
{
    QMutexLocker locker( mpMutex );
	return mLevel;
}
