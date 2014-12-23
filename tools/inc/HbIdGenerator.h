#ifndef HBIDGENERATOR_H
#define HBIDGENERATOR_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QQueue>
// Hb
#include <HbTools.h>
#include <HbSingleton.h>
#include <HbGlobal.h>

namespace hb
{
    namespace tools
    {
        class HB_TOOLS_DECL HbIdGenerator : public QObject, public HbSingleton<HbIdGenerator>
        {
            Q_OBJECT

            friend HbIdGenerator* HbSingleton<HbIdGenerator>::get();
            friend void HbSingleton<HbIdGenerator>::kill();

        public:
            quint16 getUniqueId();
            quint16 getRandomId();
			void addUnusedId(quint16 unused_id);

        signals:

        public slots:


        private:
            quint16 mCurrent;
            QQueue<quint16> mUnused;

        private:
			HbIdGenerator(const HbIdGenerator&) = default;
            explicit HbIdGenerator(QObject *parent = 0);

            ~HbIdGenerator();

        };
    }
}

#endif // HBIDGENERATOR_H
