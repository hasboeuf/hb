// Qt
// Local
#include <core/HbStringHelper.h>

using namespace hb::tools;

QString HbStringHelper::randomString( quint32 string_length, QString input )
{
    if( input.isEmpty() )
    {
        input = "abcdefghijklmnopqrstuvwxyz";
    }

    QString random_string;
    for( int i = 0; i< string_length; ++i )
    {
        int index = qrand() % input.length();
        random_string.append( input.at( index ) );
    }

    return random_string;
}
