// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbLogService.h>
#include <HbLogManager.h>
#include <HbLoggerOutputs.h>
#include <HbLoggerInputs.h>

using namespace hb::log;

QThreadStorage< HbLogManager * > HbLogService::msManager;

void HbLogService::subscribe()
{
    if( !msManager.hasLocalData() )
    {
        QCoreApplication * instance = QCoreApplication::instance();
        q_assert_x( instance, "HbLogService", "Qt application not defined" );

		HbLogManager * manager = q_check_ptr( new HbLogManager() );

        #if !defined( QT_NO_DEBUG )
            manager->qtMessageHandler( true );
        #endif
        msManager.setLocalData( manager );
    }
}


HbLogger * HbLogService::logger()
{
    HbLogService::subscribe();
    return msManager.localData();
}

HbLoggerInputs * HbLogService::inputs()
{
    HbLogService::subscribe();
    return q_assert_ptr( msManager.localData() )->inputs();
}

HbLoggerOutputs * HbLogService::outputs()
{
    HbLogService::subscribe();
    return q_assert_ptr( msManager.localData() )->outputs();
}

void HbLogService::processArgs(int argc, char *argv[])
{
    QStringList args;
    for (int n = 1; n < argc; ++n) // Skip the program name.
    {
        args.append(QString::fromLatin1(argv[n]));
    }

    processArgs( args );
}

void HbLogService::processArgs(QStringList args)
{
	// usage
	// -hblog-(output|input)-local:name
	// -hblog-(output|input)-tcp:port[:ip]
	// -hblog-output-file:dir:file_max_size



	QRegExp check("-hblog-(output|input)-(local|tcp|file):");

	// Required args number.
	static const quint32 ARG_NB_REQUIRED_FILE       = 2;
	static const quint32 ARG_NB_REQUIRED_LOCAL      = 1;
	static const quint32 ARG_NB_REQUIRED_INPUT_TCP  = 1;
	static const quint32 ARG_NB_REQUIRED_OUTPUT_TCP = 2;
	// Local arg positions.
	static const quint32 ARG_POS_LOCAL_NAME  = 0;
	// Tcp arg positions.
	static const quint32 ARG_POS_TCP_PORT  = 0;
	static const quint32 ARG_POS_TCP_IP    = 1;

	// File arg positions.
	static const quint32 ARG_POS_FILE_DIR = 0;
	static const quint32 ARG_POS_FILE_MAX_SIZE = 1;

	foreach(QString arg, args)
	{
		int pos = check.indexIn(arg);
		if (pos != -1)
		{
			QString inout = check.cap(1);
			QString type = check.cap(2);

			QStringList parameters = arg.split(":", QString::SkipEmptyParts);
			if (parameters.size() < 2)
			{
				break;
			}
			parameters.removeAt(0); // Remove -hblog-(output|input)-(local|tcp|file) entry.

			quint32 nb_parameters = parameters.size();


			if (type == "file" && nb_parameters == ARG_NB_REQUIRED_FILE)
			{
				bool is_valid_size = false;

				quint32 file_max_size = parameters.at(ARG_POS_FILE_MAX_SIZE).toInt(&is_valid_size);

				if (is_valid_size)
				{
					QString dir_name = parameters.at(ARG_POS_FILE_DIR);

					outputs()->addFileOutput(outputs()->unusedId(), dir_name, file_max_size);
				}
			}
			else if (type == "local" && nb_parameters == ARG_NB_REQUIRED_LOCAL)
			{
				QString local_address = parameters.at(ARG_POS_LOCAL_NAME);

				if (inout == "input")
				{
					inputs()->addLocalSocketInput(inputs()->unusedId(), local_address);
				}
				else // output
				{
					outputs()->addLocalSocketOutput(outputs()->unusedId(), local_address);
				}
			}
			else // Tcp
			{
				if (inout == "input" && nb_parameters == ARG_NB_REQUIRED_INPUT_TCP)
				{
					bool is_valid_port = false;
					quint32 port = parameters.at(ARG_POS_TCP_PORT).toInt(&is_valid_port);

					if (is_valid_port)
					{
						inputs()->addTcpSocketInput(outputs()->unusedId(), port);
					}
				}
				else if (inout == "output" && nb_parameters == ARG_NB_REQUIRED_OUTPUT_TCP)
				{
					bool is_valid_port = false;
					quint32 port = parameters.at(ARG_POS_TCP_PORT).toInt(&is_valid_port);

					if (is_valid_port)
					{
						QString ip = parameters.at(ARG_POS_TCP_IP);
						outputs()->addTcpSocketOutput(outputs()->unusedId(), ip, port);
					}
				}
			}
		}
	}
}
