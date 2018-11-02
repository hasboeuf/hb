// System
#include <QDateTime>
#include <random>
// Qt
// Local
#include <core/HbStringHelper.h>

using namespace hb::tools;

QString HbStringHelper::randomString(quint32 length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static std::mt19937 randomEngine(QDateTime::currentDateTime().toMSecsSinceEpoch());
    std::uniform_int_distribution<int> distribution(0, sizeof(characters) - 2);
    QByteArray data;
    data.reserve(length);
    for (quint8 i = 0; i < length; ++i)
        data.append(characters[distribution(randomEngine)]);
    return QString::fromUtf8(data);
}
