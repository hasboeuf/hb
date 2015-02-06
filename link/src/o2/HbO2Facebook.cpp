#include <o2/HbO2Facebook.h>

QString HbO2Facebook::msRequestUrl = QStringLiteral( "https://www.facebook.com/dialog/oauth" );

HbO2Facebook::HbO2Facebook()
{
    setRequestUrl( msRequestUrl );
}
