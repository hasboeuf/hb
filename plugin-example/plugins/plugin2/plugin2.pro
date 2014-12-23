include(../../../common.pri)

QT      += core widgets gui

TEMPLATE = lib
CONFIG += dll plugin warn_on

TARGET = $$qtLibraryTarget(plugin2)

UI_DIR  += $$ThirdDir/plugin-example/build/generated/inc
MOC_DIR += $$ThirdDir/plugin-example/build/generated/moc

DESTDIR += $$ThirdDir/plugin-example/bin/plugins

SOURCES += \
            src/Plugin2.cpp

HEADERS += \
            inc/Plugin2.hpp \
    inc/IPlugin2.hpp

FORMS += \

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += Plugin2.json

INCLUDEPATH += inc
INCLUDEPATH += $$ThirdDir/plugin-framework/inc
INCLUDEPATH += $$ThirdDir/plugin-example/plugin-interfaces/inc

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
