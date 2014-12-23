include(../../common.pri)

QT      += core gui widgets

TEMPLATE = lib

CONFIG += staticlib warn_on

TARGET = $$qtLibraryTarget(plugin-interfaces)

UI_DIR  += $$ThirdDir/plugin-example/build/generated/inc

DESTDIR += $$ThirdDir/plugin-example/libs

SOURCES += \
    src/AppPluginInterface.cpp \
    src/AppPlatformService.cpp \
    src/AppService.cpp \
    src/MenuService.cpp

HEADERS += \
    inc/AppPluginInterface.hpp \
    inc/AppPlatformService.hpp \
    inc/AppService.hpp \
    inc/MenuService.hpp

FORMS += \

RESOURCES += \

INCLUDEPATH += inc
INCLUDEPATH += $$ThirdDir/plugin-framework/inc
INCLUDEPATH += $$ThirdDir/tools/inc

CONFIG(debug, debug|release){
    LIBS += \
    -L$$ThirdDir/libs \
    -L$$ThirdDir/plugin-example/libs \
    -lplugin-frameworkd \

gcc: {
    PRE_TARGETDEPS += $$ThirdDir/libs/libplugin-frameworkd.a
}

} else {
    LIBS += \
    -L$$ThirdDir/libs \
    -L$$ThirdDir/plugin-example/libs \
    -lplugin-framework \

gcc: {
    PRE_TARGETDEPS += $$ThirdDir/libs/libplugin-framework.a
}
}
