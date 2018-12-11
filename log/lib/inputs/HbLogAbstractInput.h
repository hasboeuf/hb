/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGABSTRACTINPUT_H
#define HBLOGABSTRACTINPUT_H

/*! \file HbLogAbstractInput.h */

// Hb
#include <HbLog.h>
#include <core/HbUid.h>
// Local

namespace hb {
namespace log {
class HbLogMessage;

/*!
 * TODOC.
 */
class HbLogAbstractInput : public QObject, public HbUid<CLASS_LOG> {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogAbstractInput)
    friend class HbLoggerPool;

public:
    HbLogAbstractInput(QObject* parent = nullptr);
    virtual ~HbLogAbstractInput() = default;

signals:
    void inputMessageReceived(HbLogMessage* message);

protected:
    virtual void init() = 0;
};
} // namespace log
} // namespace hb

#endif // HBLOGABSTRACTINPUT_H
