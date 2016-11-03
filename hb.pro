# --------------------
# Environment Settings
# --------------------

NO_EXAMPLES = $$(HB_NO_EXAMPLES)
isEmpty( NO_EXAMPLES ) {
    android|winphone|winrt {
        NO_EXAMPLES = 1
    }
}

!isEmpty( NO_EXAMPLES ): message( Hb example apps are ignored. )

# -----------------
# Project Settings
# -----------------

PROJECT.NAME = hb

SUBDIRS += \
    tools/HbTools.pro \
    log/HbLog.pro \
    plugin/HbPlugin.pro \
    link/HbLink.pro \
    network/HbNetwork.pro \

isEmpty( NO_EXAMPLES ) {

    EXAMPLE_SUBDIRS += \
        tools-example/HbToolsExample.pro \
        log-viewer/HbLogViewer.pro \
        plugin-example/HbPluginExample.pro \
        link-example/HbLinkExample.pro \
        network-example/HbNetworkExample.pro \
        network-basic-example/HbNetworkBasicExample.pro

} else {
    # Let it void, Trick for qmake/qtcreator bug.
    EXAMPLE_SUBDIRS=
}

SUBDIRS += $$EXAMPLE_SUBDIRS

unset( NO_EXAMPLES )

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
