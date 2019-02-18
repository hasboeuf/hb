#ifndef HBUIDGENERATOR_H
#define HBUIDGENERATOR_H

/*! \file HbUidGenerator.h */

// System
#include <limits>
// Qt
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QQueue>
// Hb
#include <HbGlobal.h>
#include <HbTools.h>
#include <core/HbSingleton.h>

const quint32 LOWEST_UID = 1;

class TestHbUid;

namespace hb {
namespace tools {
/*!
 * HbUidGenerator maintains a list of unique integer identifiers for the application.
 * It is a singleton class.
 * \param C Uid belongings.
 * \sa HbUid
 */
template <size_t C = CLASS_DEFAULT> class HbUidGenerator : public HbSingleton<HbUidGenerator<C>> {
    Q_DISABLE_COPY(HbUidGenerator)

    friend class HbSingleton<HbUidGenerator<C>>;
    friend class ::TestHbUid;

public:
    quint32 uid() {
        quint32 value = 0;

        { // Mutex area
            QMutexLocker locker(&mMutex);

            if (!mUnused.isEmpty()) {
                value = mUnused.dequeue();
            } else {
                value = mCurrent++;
            }
        }

        Q_ASSERT(value != 0);
        return value;
    }

    quint32 randomId() {
        QMutexLocker locker(&mMutex);

        quint32 lowest = LOWEST_UID;
        quint32 highest = std::numeric_limits<quint32>::max();
        return qrand() % ((highest + 1) - lowest) + lowest;
    }

    void releaseUid(quint32 released_id) {
        QMutexLocker locker(&mMutex);
        mUnused.enqueue(released_id);
    }

private:
    HbUidGenerator() = default;
    ~HbUidGenerator() = default;

    void reset() {
        QMutexLocker locker(&mMutex);
        mUnused.clear();
        mCurrent = LOWEST_UID;
    }

    QMutex mMutex;
    quint32 mCurrent = LOWEST_UID;
    QQueue<quint32> mUnused;
};
} // namespace tools
} // namespace hb

#endif // HBUIDGENERATOR_H
