/*// Local
#include <HbUuidHelper.h>


QUuid HbUuidHelper::toUuid(const QString & name, bool use_hardware)
{
	if (!name.isEmpty())
	{
		QByteArray bytes(name.toUtf8());
		QByteArray hash = QCryptographicHash::hash(
			bytes.constData(), QCryptographicHash::Sha1);

		hash.resize(16);

		QUuid uuid = QUuid::fromRfc4122(hash);

		// QUuid Variant = DCE / Version = SHA1
		uuid.data4[0] = (uuid.data4[0] & 0x3F) | 0x80;
		uuid.data3 = (uuid.data3 & 0x0FFF) | (QUuid::Sha1 << 12);

		return uuid;
	}

	return QUuid();
}*/