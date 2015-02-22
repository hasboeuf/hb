# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

SUBDIRS += \
    tools/HbTools.pro \
    link/HbLink.pro \
    link-example/HbLinkExample.pro \
    log/HbLog.pro \
    log-viewer/HbLogViewer.pro \
    network/HbNetwork.pro \
    network-example/HbNetworkExample.pro \
    network-basic-example/HbNetworkBasicExample.pro \
    plugin/HbPlugin.pro \
    plugin-example/HbPluginExample.pro

log.depends = tools
network.depends = link log tools
network-example.depends = link tools log network
network-basic-example.depends = link tools log network
plugin.depends = log tools
plugin-example.depends = plugin log tools
link-example.depends = link

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
