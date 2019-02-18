#ifndef HBLOGCONSOLEOUTPUT_H
#define HBLOGCONSOLEOUTPUT_H

/*! \file HbLogConsoleOutput.h */

#include <outputs/HbLogAbstractOutput.h>

namespace hb {
namespace log {
/*!
 * \brief The %HbLogConsoleOutput class defines a console output.
 */
class HbLogConsoleOutput : public HbLogAbstractOutput {
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
