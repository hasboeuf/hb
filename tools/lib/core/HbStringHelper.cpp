// Qt
// Local
#include <core/HbStringHelper.h>

using namespace hb::tools;

QString HbStringHelper::randomString(quint32 string_length, QString input) {
    if (input.isEmpty()) {
        input = "abcdefghijklmnopqrstuvwxyz";
    }

    QString random_string;
    for (quint32 i = 0; i < string_length; ++i) {
        qint32 index = qrand() % input.length();
        random_string.append(input.at(index));
    }

    return random_string;
}
