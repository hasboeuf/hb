# -----------------
# Platform Settings
# -----------------

HB_NO_EXAMPLES = $$(HBNOEXAMPLES)
isEmpty( HB_NO_EXAMPLES ) {
    android|winphone|winrt {
        HB_NO_EXAMPLES = 1
    }
}

!isEmpty( HB_NO_EXAMPLES ): message( Hb example apps are ignored. )

# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

SUBDIRS += \
    tools/HbTools.pro \
    log/HbLog.pro \
    plugin/HbPlugin.pro \
    link/HbLink.pro \
    network/HbNetwork.pro

log.depends = tools
plugin.depends = tools log
link.depends = tools log
network.depends = tools log link

message(  value=$$HB_NO_EXAMPLES )

isEmpty( HB_NO_EXAMPLES ) {

    EXAMPLE_SUBDIRS += \
        tools-example/HbToolsExample.pro \
        log-viewer/HbLogViewer.pro \
        plugin-example/HbPluginExample.pro \
        link-example/HbLinkExample.pro \
        network-example/HbNetworkExample.pro \
        network-basic-example/HbNetworkBasicExample.pro

    tools-example.depends = tools log
    log-viewer.depends = tools log
    plugin-example.depends = tools log plugin
    link-example.depends = tools log link
    network-example.depends = tools log link network
    network-basic-example.depends = tools log link network

} else {
    # Let it void, Trick for qmake/qtcreator bug.
    EXAMPLE_SUBDIRS=
}

SUBDIRS += $$EXAMPLE_SUBDIRS


# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
