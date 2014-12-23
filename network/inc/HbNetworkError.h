#ifndef HBNETWORKERROR_H
#define HBNETWORKERROR_H

// Qt
#include <QGlobal.h>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {

		class HB_NETWORK_DECL HbNetworkError
		{

		public:

			// TODO static
			enum Code
			{
				G_SUCCESS = 0,
				G_FAILLURE,
				G_ERROR_WTF,

				TCPSOCKETHANDLER_FULL,
				TCPSOCKETHANDLER_ALREADY_PRESENT,
				TCPSOCKETHANDLER_UNTHREADED_YET,
				TCPSOCKETHANDLER_BAD_DESCRIPTOR
			};
		};
    }
}


#endif // HBNETWORKERROR_H
