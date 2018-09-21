/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBLOGCONSOLEOUTPUT_H
#define HBLOGCONSOLEOUTPUT_H

/*! \file HbLogConsoleOutput.h */

#include <outputs/HbLogAbstractOutput.h>

namespace hb {
namespace log {
/*!
 * \brief The %HbLogConsoleOutput class defines a console output.
 */
class HbLogConsoleOutput final : public HbLogAbstractOutput {
public:
    HbLogConsoleOutput(QObject* parent = nullptr);
    virtual ~HbLogConsoleOutput() = default;

protected:
    void init() override;
    void processMessage(const HbLogMessagePtr& message) override;
};
} // namespace log
} // namespace hb

#endif
