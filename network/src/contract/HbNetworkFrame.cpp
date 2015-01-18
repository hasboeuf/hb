#include <contract/HbNetworkFrame.h>

#include <QtCore/QDataStream>

using namespace hb::network;


HbNetworkFrame::HbNetworkFrame()
{

}

namespace hb
{
	namespace network
	{

		QDataStream & operator <<(QDataStream & stream, const HbNetworkFrame & header)
		{


			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkFrame & header)
		{

			return stream;
		}

	}
}
