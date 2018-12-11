/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGUINOTIFIER_H
#define HBLOGGUINOTIFIER_H

/*! \file HbLogGuiNotifier.h */

// Qt
#include <QtCore/QObject>
// Hb
#include <HbLog.h>

namespace hb {
namespace log {

class HbLogMessage;

/*!
 * HbLogGuiNotifier is needed to add a gui output.
 * It is the middleman between HbLog and user class.
 * TODOC.
 */
class HB_LOG_DECL HbLogGuiNotifier : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HbLogGuiNotifier)
    friend class HbLogGuiOutput;

public:
    HbLogGuiNotifier();
    virtual ~HbLogGuiNotifier() = default;

signals:
    void newLogMessage(const HbLogMessagePtr& message);
};
} // namespace log
} // namespace hb

#endif // HBLOGGUINOTIFIER_H
