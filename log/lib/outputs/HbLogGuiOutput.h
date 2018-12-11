/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGGUIOUTPUT_H
#define HBLOGGUIOUTPUT_H

/*! \file HbLogGuiOutput.h */

// Qt
#include <QtCore/QScopedPointer>
// Hb
#include <outputs/HbLogAbstractOutput.h>

namespace hb {
namespace log {

class HbLogGuiNotifier;

/*!
 * \brief The %HbLogGuiOutput class defines a GUI output.
 */
class HbLogGuiOutput : public HbLogAbstractOutput {
    Q_DISABLE_COPY(HbLogGuiOutput)

public:
    HbLogGuiOutput() = delete;
    HbLogGuiOutput(HbLogGuiNotifier* notifier, QObject* parent = nullptr);
    virtual ~HbLogGuiOutput();

protected:
    void init() override;
    void processMessage(const HbLogMessagePtr& message) override;

private:
    QScopedPointer<HbLogGuiNotifier> mNotifier;
};
} // namespace log
} // namespace hb

#endif
