// Hb
#include <HbLogMessage.h>
#include <outputs/HbLogConsoleOutput.h>

using namespace hb::log;

HbLogConsoleOutput::HbLogConsoleOutput(QObject* parent) : HbLogAbstractOutput(parent) {
}

void HbLogConsoleOutput::init() {
}

void HbLogConsoleOutput::processMessage(const HbLogMessagePtr& message) {
    fprintf(stderr, "%s\n", qUtf8Printable(message->toString()));
}
