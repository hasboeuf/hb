include(../../common.pri)

QT += widgets

TEMPLATE = app

CONFIG += warn_on

CONFIG(debug, debug|release){
    TARGET = plugin-demo_debug
} else {
    TARGET = plugin-demo_release
}

UI_DIR  += $$ThirdDir/plugin-example/build/generated/inc

DESTDIR    += $$ThirdDir/plugin-example/bin/

SOURCES += \
    src/main.cpp \
    src/AppMainWindow.cpp \

HEADERS  += \
    inc/AppMainWindow.hpp \

FORMS    += \
    forms/AppMainWindow.ui

INCLUDEPATH += inc
INCLUDEPATH += $$ThirdDir/plugin-example/plugin-interfaces/inc
INCLUDEPATH += $$ThirdDir/plugin-framework/inc
INCLUDEPATH += $$ThirdDir/tools/inc
INCLUDEPATH += $$ThirdDir/logger/inc
INCLUDEPATH += $$ThirdDir/build/generated/inc


CONFIG(debug, debug|release){
    LIBS += \
    -L$$ThirdDir/libs \
    -L$$ThirdDir/plugin-example/libs \
    -lplugin-interfacesd \
    -lplugin-frameworkd \
	
gcc: {
    PRE_TARGETDEPS += $$ThirdDir/plugin-example/libs/libplugin-interfacesd.a
    PRE_TARGETDEPS += $$ThirdDir/libs/libplugin-frameworkd.a
}

} else {
    LIBS += \
    -L$$ThirdDir/libs \
    -L$$ThirdDir/plugin-example/libs \
    -lplugin-interfaces \
    -lplugin-framework \

gcc: {
    PRE_TARGETDEPS += $$ThirdDir/plugin-example/libs/libplugin-interfaces.a
    PRE_TARGETDEPS += $$ThirdDir/libs/libplugin-framework.a
}
}

