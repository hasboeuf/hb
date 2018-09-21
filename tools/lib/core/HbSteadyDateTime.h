/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSTEADYDATETIME_H
#define HBSTEADYDATETIME_H

/*! \file HbSteadyDateTime.h */

// System
#include <chrono>
// Qt
#include <QtCore/QDateTime>
// Local
#include <HbTools.h>

using namespace std::chrono;

namespace hb {
namespace tools {
/*!
 * HbSteadyDateTime provides a non-exact* but steady datetime.
 * For micro and nano seconds precision.
 */
class HB_TOOLS_DECL HbSteadyDateTime {
public:
    static HbSteadyDateTime now();
    static HbSteadyDateTime fromDateTime(const QDateTime& datetime, quint64 steady = 0);
    static HbSteadyDateTime fromString(const QString& value, const QString& format);
    static HbSteadyDateTime fromNsSinceEpoch(qint64 nano);
    qint64 toNsSinceEpoch() const;
    QString toString(const QString& format);

    const QDateTime& datetime() const;
    quint64 steady() const;

protected:
    HbSteadyDateTime();

private:
    QDateTime mDateTime;
    quint64 mSteady;
};
} // namespace tools
} // namespace hb

#endif // HBSTEADYDATETIME_H
