// Hb
#include <HbLogMessage.h>
#include <outputs/HbLogConsoleOutput.h>

using namespace hb::log;

HbLogConsoleOutput::HbLogConsoleOutput(QObject* parent) : HbLogAbstractOutput(parent) {
}

void HbLogConsoleOutput::init() {
}

void HbLogConsoleOutput::processMessage(const HbLogMessagePtr& message) {
    if (message->level() < HbLogger::LEVEL_CRITICAL) {
        std::cout << qUtf8Printable(message->toString()) << std::endl << std::flush;
        return;
    }
    std::cerr << qUtf8Printable(message->toString()) << std::endl << std::flush;
}
