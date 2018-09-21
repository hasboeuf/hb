// Qt
#include <QtCore/QCoreApplication>
// Local
#include <core/HbSettings.h>

using namespace hb::tools;

HbSettings::HbSettings() : mSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName()) {
}

HbSettings::HbSettings(QSettings::Format format, QSettings::Scope scope) :
        mSettings(format, scope, QCoreApplication::organizationName(), QCoreApplication::applicationName()) {
}

bool HbSettings::write(const QString key, const QVariant& data) {
    if (!isValid()) {
        return false;
    }

    mSettings.setValue(key, data);
    mSettings.sync();

    return true;
}

QVariant HbSettings::read(const QString& key) {
    if (!isValid()) {
        return QVariant();
    }

    return mSettings.value(key);
}

void HbSettings::remove(const QString& key) {
    mSettings.remove(key);
}

bool HbSettings::isValid() const {
    return !mSettings.organizationName().isEmpty() && mSettings.isWritable();
}
