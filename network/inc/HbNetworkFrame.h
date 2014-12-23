#ifndef HBNETWORKFRAME_H
#define HBNETWORKFRAME_H

// Local
#include <HbNetworkHeader.h>
#include <HbNetworkContract.h>

namespace hb
{
	namespace network
	{
		class HbNetworkFrame final
		{
			Q_DISABLE_COPY(HbNetworkFrame)

		public:
			HbNetworkFrame();
			virtual ~HbNetworkFrame() = default;

			friend QDataStream & operator <<(QDataStream & stream, const HbNetworkFrame & header);
			friend QDataStream & operator >>(QDataStream & stream, HbNetworkFrame & header);

		private:

		};


	}
}

#endif // HBNETWORKFRAME_H
