// Qt
#include <QtCore/QDebug>
// Hb
#include <HbLoggerStream.h>
#include <HbLogManager.h>

using namespace hb::log;

const char * HbLoggerStream::DEFAULT_LOCAL_SERVER_NAME = "HB_LOG";

HbLoggerStream::HbLoggerStream( HbLogManager * parent ) :
    QObject( parent )
{
    q_assert_x( parent, "HbLoggerStream", "HbLogManager not defined" );
}


void HbLoggerStream::onStreamStateChanged(quint32 id, HbLoggerStream::State state)
{
	if (state == HbLoggerStream::INOUT_ADD_SUCCESS)
	{
		mUsedId.insert(id);
	}
	else if (state == HbLoggerStream::INOUT_DEL_SUCCESS)
	{
		mUsedId.remove(id);
	}

	emit streamStateChanged(id, state);
}

quint32 HbLoggerStream::unusedId() const
{
	int id = 0;
	while (mUsedId.contains(id) && id != _UI32_MAX)
	{
		++id;
	}
	return id;
}