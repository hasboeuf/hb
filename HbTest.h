#ifndef HBTEST_H
#define HBTEST_H

#include <gmock/gmock.h>

#define WRAP_GMOCK_MAIN(mainMacro, tc) \
    namespace Wrap { \
    mainMacro(tc) \
    } \
    int main(int argc, char* argv[]) { \
        GTEST_FLAG(throw_on_failure) = true; \
        testing::InitGoogleMock(&argc, argv); \
        return Wrap::main(argc, argv); \
    }

#endif // HBTEST_H
