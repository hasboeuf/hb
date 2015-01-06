# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

SUBDIRS += \
    tools/HbTools.pro \
    log/HbLog.pro \
    log-viewer/HbLogViewer.pro \
    network/HbNetwork.pro \
    network-example/HbNetworkExample.pro \
    plugin/HbPlugin.pro \
    plugin-example/HbPluginExample.pro

log.depends = tools
network.depends = log tools
network-example.depends = tools log network
plugin.depends = log tools
plugin-example.depends = plugin log tools

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
