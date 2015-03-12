# -----------------
# Project Settings
# -----------------

PROJECT.NAME =			HB
PROJECT.TYPE =			subdirs

SUBDIRS += \
    tools/HbTools.pro \
    tools-example/HbToolsExample.pro \
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
tools-example.depends = tools log
network.depends = tools log link
network-example.depends = network
network-basic-example.depends = network
plugin.depends = tools log
plugin-example.depends = plugin
link-example.depends = link

# ---------------
# QMake Includes
# ---------------

!include( $${PROJECT.NAME}.pri ): \
error( "QMake file $${PROJECT.NAME}.pri not found" )
